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

