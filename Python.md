

# malloc与new区别



# TCP的三次握手与四次挥手



# CPU两大架构 X86 ARM

| cpu架构 | 指令集           | 特点                                                         |
| ------- | ---------------- | ------------------------------------------------------------ |
| X86     | 复杂指令集(CISC) | 主要面向家用、商用领域，在**性能**和**兼容性**方面做得更好。Intel和AMD |
| ARM     | 精简指令集(RISC) | 主要面向移动、低功耗领域，因此在设计上更偏重**节能**方面。   |



# Iass Pass SaaS 三种云计算服务模式

![img](https://www.pianshen.com/images/165/ce07a6dfc25a8c817677ab087e564175.png)

- IaaS：Infrastructure-as-a-Service 基础设施即服务。IaaS公司提供的场外服务器，存储和网络硬件，比如阿里云服务器。节省了维护成本和办公场地。
- PaaS：Platform-as-a-Service 平台即服务。PaaS公司提供各种开发和分发应用的解决方案，比如虚拟服务器和操作系统。节省了你在硬件上的费用，也让分散的工作室之间的合作变得更加容易。
- SaaS：Software-as-a-Service 软件即服务。将软件应用后台放在云端，比如平时使用的苹果手机云服务。



# 分布式系统

分布式系统是由一组通过网络通信，协调完成共同任务的计算机节点组成的系统。分布式系统的出现是为了用普通的机器完成单个计算机无法完成的计算、存储任务，其目的是**利用更多的机器，处理更多的数据**。分布式系统分为**分布式计算**与**分布式存储**。

只有当单个节点的处理能力无法满足日益增长的计算、存储任务的时候，且硬件的提升（加内存、加磁盘、更好的CPU）高昂到得不偿失的时候，应用程序也不能进一步优化时，才需要考虑分布式系统。因为分布式系统多节点通过网络通信的拓扑结构，会引入很多单机系统没有的问题，为了解决这些问题又会引入更多的机制、协议，带来更多的问题。

分布式系统面临的挑战：

- **异构的机器与网络**：分布式系统中的机器，配置不一样，其上运行的服务也可能由不同的语言、架构实现，因此处理能力也不一样；节点间通过网络连接，而不同网络运营商提供的网络的带宽、延时、丢包率又不一样。
- **普遍的节点故障**：节点数目达到一定规模，出故障的概率就变高了。分布式系统需要保证故障发生的时候，系统仍然是可用的，这就需要监控节点的状态，在节点故障的情况下将该节点负责的计算、存储任务转移到其他节点。
- **不可靠的网络**：节点间通过网络通信，而网络是不可靠的。可能的网络问题包括：网络分割、延时、丢包、乱序。相比单机过程调用，网络通信最让人头疼的是超时：节点A向节点B发出请求，在约定的时间内没有收到节点B的响应，那么B是否处理了请求，这个是不确定的，这个不确定会带来诸多问题，最简单的，是否要重试请求，节点B会不会多次处理同一个请求。

分布式系统问题解决思路：

- **分片**：把任务分发到各个节点，完成后统一汇总，就是MapReduce的思想。
- **冗余**：提升系统可用性。由于单节点故障、网络通信异常的可能性，需要较强的容错性保障系统服务，多节点负责同一任务，多节点存储同一数据。

分布式系统衡量标准：

- 可扩展性
- 可用性与可靠性
- 高性能
- 一致性



# MQ 消息中间件

## 概述

消息队列已经逐渐成为企业IT系统内部通信的核心手段。它具有低耦合、可靠投递、广播、流量控制、最终一致性等一系列功能，成为异步RPC的主要手段之一。当今市面上有很多主流的消息中间件，如老牌的ActiveMQ、RabbitMQ，炙手可热的Kafka，阿里自主开发RocketMQ等。

## 组成

- **Broker**：消息服务器，作为server提供消息核心服务。
- **Producer**：消息生产者，业务的发起方，负责生产消息传输给broker。
- **Consumer**：消息消费者，业务的处理方，负责从broker获取消息并进行业务逻辑处理。
- **Topic**：主题，发布订阅模式下的消息统一汇集地，不同生产者向topic发送消息，由MQ服务器分发到不同的订阅者，实现消息的广播。
- **Queue**：队列，PTP模式下，特定生产者向特定queue发送消息，消费者订阅特定的queue完成指定消息的接收。
- **Message**：消息体，根据不同通信协议定义的固定格式进行编码的数据包，来封装业务数据，实现消息的传输。

## [模式](https://blog.csdn.net/maihilton/article/details/81628152)

- **点对点模式**：Queue作为通信载体 

  ![img](https://img-blog.csdn.net/20150817113531436)
  消息生产者生产消息发送到queue中，然后消息消费者从queue中取出并且消费消息。 消息被消费以后，queue中不再存储，所以消息消费者不可能消费到已经被消费的消息。 Queue支持存在多个消费者，但是对一个消息而言，只会有一个消费者可以消费，实现了负载均衡。

- **发布/订阅模式**：Topic作为通信载体 
  ![img](https://img-blog.csdn.net/20150817113626248)
  消息生产者（发布）将消息发布到topic中，同时有多个消息消费者（订阅）消费该消息。和点对点方式不同，发布到topic的消息会被所有订阅者消费。

## 应用场景

- **异步通信**：有些业务不想也不需要立即处理消息。消息队列提供了异步处理机制，允许用户把一个消息放入队列，但并不立即处理它。想向队列中放入多少消息就放多少，然后在需要的时候再去处理它们。
- **解耦**：降低工程间的强依赖程度，针对异构系统进行适配。在项目启动之初来预测将来项目会碰到什么需求，是极其困难的。通过消息系统在处理过程中间插入了一个隐含的、基于数据的接口层，两边的处理过程都要实现这一接口，当应用发生变化时，可以独立的扩展或修改两边的处理过程，只要确保它们遵守同样的接口约束。
- **冗余**：有些情况下，处理数据的过程会失败。除非数据被持久化，否则将造成丢失。消息队列把数据进行持久化直到它们已经被完全处理，通过这一方式规避了数据丢失风险。许多消息队列所采用的”插入-获取-删除”范式中，在把一个消息从队列中删除之前，需要你的处理系统明确的指出该消息已经被处理完毕，从而确保你的数据被安全的保存直到你使用完毕。
- **扩展性**：因为消息队列解耦了你的处理过程，所以增大消息入队和处理的频率是很容易的，只要另外增加处理过程即可。不需要改变代码、不需要调节参数。便于分布式扩容。
- **过载保护**：在访问量剧增的情况下，应用仍然需要继续发挥作用，但是这样的突发流量无法提取预知；如果以为了能处理这类瞬间峰值访问为标准来投入资源随时待命无疑是巨大的浪费。使用消息队列能够使关键组件顶住突发的访问压力，而不会因为突发的超负荷的请求而完全崩溃。
- **可恢复性**：系统的一部分组件失效时，不会影响到整个系统。消息队列降低了进程间的耦合度，所以即使一个处理消息的进程挂掉，加入队列中的消息仍然可以在系统恢复后被处理。
- **顺序保证**：在大多使用场景下，数据处理的顺序都很重要。大部分消息队列本来就是排序的，并且能保证数据会按照特定的顺序来处理。



# RPC





# 简历

## 1. 个人信息

## 2. 技术能力 

## 3. 项目经历

- 性能优化
- 疑难问题















# 简介&安装

> Python的定位是简单优雅。Python提供了完善的基础库以及大量的第三方库，有丰富的社区资源。
>
> Python是解释型语言，代码在执行时一行一行地翻译成CPU能理解的机器码，这个过程耗时，执行较慢。而C程序是运行前直接编译成CPU能执行的机器码，执行较快。

- 启动Python提示符终端：python
- 退出Python提示符终端：[ctrl + d]、exit()

# 基础

```python
name = 'wu'
age = 10
print('%s -- %d' % ('wu', 10))
print('{0} -- {1}'.format(name, age))
print('{0} --'.format(name))
print('{} --'.format(name))
print('{name} -- {age}'.format(name='wu', age=20))
print('{0:.3f}'.format(10.0/3))  # 保留小数点(.)后三位
print('{0:_^11}'.format('hello'))   # 使用下划线填充文本，并保持居中，^ 定义字符串长度为11

print(ord('A'))
print(chr(66))
print(ord('中'))
print(chr(25991))
```

```
# str通过encode()方法编码为指定的bytes，对bytes类型的数据用带b前缀的单引号或双引号表示
>>> 'ABC'.encode('ascii')	# 纯英文的str可以用ASCII编码为bytes
b'ABC'
>>> '中文'.encode('utf-8')	# 含有中文的str可以用UTF-8编码为bytes
b'\xe4\xb8\xad\xe6\x96\x87'

# len()计算的是str的字符数，或bytes的字节数：
>>> len('ABC')
3
>>> len('中文')
2
>>> len(b'ABC')
3
>>> len(b'\xe4\xb8\xad\xe6\x96\x87')
6
```



# 条件&循环

```python
run = False or True #布尔值用and、or和not运算
while run:
    guess = int(input('Enter an integer : '))
    if guess < 9:
        print('guess < 9')
        continue
    elif guess > 9:
        pass
    else:
        print('guess = 9')
        break
else:
    print('The while loop over')

# for控制流
for i in range(1, 9, 2):	#range()函数生成整数序列
    print(i)
else:
    print('The for loop over')
```



# 数据结构

- 列表List

```python
classmates = ['Michael', 'Bob', 'Tracy']
print(classmates)
print(len(classmates))
print(classmates[0])
print(classmates[2])
print(classmates[-1])
classmates.append('Adam')
classmates.insert(1, 'Jack')
print(classmates.pop())
print(classmates.pop(1))

for item in classmates:
    print(item, end=' ')
```

- 元组Tuple

```python
classmates = ('Michael', 'Bob', 'Tracy')	# 初始化后不能修改
print(len(classmates))
```

- 字典Dictionary

```python
d = {'Michael': 95, 'Bob': 75, 'Tracy': 85}
d['Michael']
d['Adam'] = 67
d.get('Thomas')
d.pop('Bob')
```

- 集合Set

```python
s = set([1, 2, 3])
s.add(4)
s.remove(4)
```



# 函数&模块

```python
g_num = 0
def add_func(a, b=1):
    print('sum is', a+b)
    global g_num
    g_num += 2
    print('g_num is', g_num)
    return a+1, b+1
x, y = add_func(1, 2)
print(x, y)
add_func(1)
add_func(b=5, a=10)


def calc(numbers):
    sum = 0
    for n in numbers:
        sum = sum + n * n
    return sum
calc([1, 2, 3])
calc((1, 3, 5))


def person(name, age, **kw):
    print('name:', name, 'age:', age, 'other:', kw)
person('Michael', 30)
person('Adam', 45, gender='M', job='Engineer')
```



```python
import sys	# 导入sys模块后，变量sys指向该模块，就可以访问sys模块
for i in sys.argv:
    print(i)
print('\nThe PYTHONPATH is', sys.path, '\n')

import module
module.function()
print('Version', module.__version__)
```

```python
'module.py'
def function():
    if __name__ == '__main__':
        print('name is main')
    else:
        print('name isnot main')

__version__ = '0.1'
```

- 普通函数和变量名是公开的（public），可以被直接引用。
- 前缀为 _ 和 __ 的函数或变量就是非公开的（private），不应该被直接引用。
- 安装第三方模块：`pip install 模块名`
- 查看模块搜索路径：`sys.path`，添加搜索路径：`sys.path.append('/Users/my_path')`



# 类

```python
class SchoolMember:
    totalNum = 0;  # 类变量，不属于某个对象
    def __init__(self, name, age):
        self.name = name    # 对象变量
        self.age = age
        print('Initialized SchoolMember: {}'.format(self.name))
        SchoolMember.totalNum +=1
    def tell(self):
        '''告诉我有关我的细节。'''
        print('Name:"{}" Age:"{}"'.format(self.name, self.age), end=" ")
    @classmethod    # 属于类而非属于对象的方法，可以将它定义为一个 classmethod(类方法) 或 staticmethod(静态方法)
    def get_toalNum(cls):
        print("totalNum is {:d}".format(cls.totalNum))

class Teacher(SchoolMember):
    '''代表一位老师。'''
    def __init__(self, name, age, salary):
        SchoolMember.__init__(self, name, age)
        self.salary = salary
        print('Initialized Teacher: {}'.format(self.name))
    def tell(self):
        SchoolMember.tell(self)
        print('Salary: "{:d}"'.format(self.salary))

class Student(SchoolMember):
    '''代表一位学生。'''
    def __init__(self, name, age, marks):
        SchoolMember.__init__(self, name, age)
        self.marks = marks
        print('Initialized Student: {}'.format(self.name))
    def tell(self):
        SchoolMember.tell(self)
        print('Marks: "{:d}"'.format(self.marks))

t = Teacher('Mars', 40, 30000)
s = Student('Tom', 25, 75)
members = [t, s]
for member in members:
    member.tell()

SchoolMember.get_toalNum()
```

- 类的属性(**Attribute**)：字段 (**Field**)、方法 (**Method**)

- 类的访问控制：属性的名称前加前缀`__`，变成私有属性。

- type()：获取对象类型

- isinstance()：判断对象类型

- dir()：获取一个对象的所有属性和方法



# 文件

```python
f = open('1.txt', 'a+')  # 如果没有特别指定，启用默认的阅读(r)模式
f.write('this is test1 \nthis is test2')
while True:
    line = f.readline()
    if len(line) == 0:
        break
    print(line, end='')

f.close()


import os
os.uname()  # 详细系统信息
os.environ  # 环境变量
os.environ.get('PATH')   # 某个环境变量
# 操作文件和目录的函数一部分放在os模块中，一部分放在os.path模块中
os.path.abspath('.')
os.mkdir('/Users/wufeibin/Documents/WORK/testdir')
os.rmdir('/Users/wufeibin/Documents/WORK/testdir')
os.rename('1.txt', 'test.txt')
os.remove('test.txt')

for x in os.listdir('/Users/wufeibin/Documents/WORK'):
    if os.path.splitext(x)[1]=='.md':
        print(x)


import pickle
d = dict(name='Bob', age=20, score=88)
print(pickle.dumps(d))  # 对象序列化
f = open('1.txt', 'wb')
pickle.dump(d, f)
f.close()
```



# 进程&线程

```python
import os

print('Process (%s) start...' % os.getpid())
pid = os.fork()
if pid == 0:
    print('I am child process (%s) and my parent is %s.' % (os.getpid(), os.getppid()))
else:
    print('I (%s) just created a child process (%s).' % (os.getpid(), pid))
```

```python
import time, threading

def loop():
    print('thread %s is running...' % threading.current_thread().name)
    n = 0
    while n < 5:
        n = n + 1
        print('thread %s >>> %s' % (threading.current_thread().name, n))
        time.sleep(1)
    print('thread %s ended.' % threading.current_thread().name)

print('thread %s is running...' % threading.current_thread().name)
t = threading.Thread(target=loop, name='LoopThread')
t.start()
t.join()
print('thread %s ended.' % threading.current_thread().name)
```



# 网络编程





---

- python最具特色的就是使用缩进来表示代码块，不需要使用大括号 {} 。放置在一起的语句必须拥有相同的缩进，每一组这样的语句被称为块(block)。
- 包是指一个包含模块与一个特殊的 `__init__.py` 文件的文件夹
- 模块是一种可重用的程序；包是用以组织模块的另一种层次结构；
- 切分：取指定索引范围的数据，L[0:3]
- 迭代：遍历数据对象
- 异常处理

```
try...
except: 处理异常
finally...
当我们认为某些代码可能会出错时，就可以用try来运行这段代码，如果执行出错，则后续代码不会继续执行，而是直接跳转至错误处理代码，即except语句块，执行完except后，如果有finally语句块，则执行finally语句块，至此执行完毕。
```



