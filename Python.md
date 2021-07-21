# 一、简介

Python的定位是简单优雅。Python提供了完善的基础库以及大量的第三方库，有丰富的社区资源。

Python是解释型语言，代码在执行时一行一行地翻译成CPU能理解的机器码，这个过程耗时，执行较慢。而C程序是运行前直接编译成CPU能执行的机器码，执行较快。

- 启动Python提示符终端：python
- 退出Python提示符终端：[ctrl + d]、exit()

## 交互式编程

不需要创建脚本文件，是通过 Python 解释器的交互模式进来编写代码。

```
wufeibindeMacBook-Pro:practice wufeibin$ python3
Python 3.9.5 (default, May  4 2021, 03:36:27) 
[Clang 12.0.0 (clang-1200.0.32.29)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> print("Hello, Python!")
Hello, Python!
```

## 脚本式编程

通过脚本参数调用解释器开始执行脚本，直到脚本执行完毕。当脚本执行完成后，解释器不再有效。

```
wufeibindeMacBook-Pro:practice wufeibin$ cat 1.py 
print("Hello, Python!")       
wufeibindeMacBook-Pro:practice wufeibin$ python3 1.py 
Hello, Python!
```

```
wufeibindeMacBook-Pro:practice wufeibin$ cat 1.py 
#!/usr/bin/python3
print("Hello, Python!")
wufeibindeMacBook-Pro:practice wufeibin$ chmod +x 1.py 
wufeibindeMacBook-Pro:practice wufeibin$ ./1.py 
Hello, Python!
```



# 二、基础

## 缩进

学习 Python 与其他语言最大的区别就是，Python 的代码块不使用大括号 **{}** 来控制类，函数以及其他逻辑判断。python 最具特色的就是用缩进来写模块，缩进的空白数量是可变的，但是所有代码块语句必须包含相同的缩进空白数量。

缩进相同的一组语句构成一个代码块，我们称之代码组。像if、while、def和class这样的复合语句，首行以关键字开始，以冒号结束，该行之后的一行或多行代码构成代码组。

```python
if expression : 
   suite
elif expression : 
   suite
else : 
   suite
```

## 多行

Python语句中一般以新行作为语句的结束符，但是我们可以使用斜杠将一行的语句分为多行显示。如下：

```python
total = item_one + \
        item_two + \
        item_three
```

语句中包含 [], {}, () 括号就不需要使用多行连接符。如下：

```python
days = ['Monday', 'Tuesday', 'Wednesday',
        'Thursday', 'Friday']
```

## 引号

Python可以使用引号( **'** )、双引号( **"** )、三引号( **'''** 或 **"""** ) 来表示字符串，引号的开始与结束必须是相同类型的。其中三引号可以由多行组成，编写多行文本的快捷语法，常用于文档字符串，在文件的特定地点，被当做注释。

```python
word = 'word'
sentence = "这是一个句子。"
paragraph = """这是一个段落。
包含了多个语句"""
```

## 注释

Python中单行注释采用 # 开头，多行注释使用三个单引号(''')或三个双引号(""")。

```python
#!/usr/bin/python3

'''
这是多行注释，使用单引号。
这是多行注释，使用单引号。
'''

"""
这是多行注释，使用双引号。
这是多行注释，使用双引号。
"""
```



# 三、变量

Python中的变量赋值不需要类型声明。变量在使用前都必须赋值，赋值后才会被创建。

## 数字

int（整型）、long（长整型）、float（浮点型）、complex（复数）

## 字符串

字符串是 Python 中最常用的数据类型。我们可以使用引号( **'** 或 **"** )来创建字符串。

```python
#!/usr/bin/python3
 
str1 = 'Hello World!'
str2 = "Runoob"
print("var1[0]: ", str1[0])
print("var2[1:5]: ", str2[1:5])
print("已更新字符串 : ", str1[:6] + 'Runoob!')
print("我叫 %s 今年 %d 岁!" % ('小明', 10)) # 字符串格式化
```

## 列表

由一系列按特定顺序排列的元素组成，用 **[ ]** 标识，并用逗号来分隔其中的元素。可以完成大多数集合类的数据结构实现，支持数字、字符串、嵌套列表。

```python
#!/usr/bin/python3

list = ['red', 'green', 'blue', 'yellow', 'white']
print(list[0])
print(list[1])
print(list[-1])
list[2] = 'black'
list.append('black')
print("更新后的列表 : ", list)
```

## 元组

元组与列表类似，区别在于元组的元素不能修改，用 **()** 标识，内部元素用逗号隔开。

```python
#!/usr/bin/python3

tup1 = ('Google', 'Runoob', 1997, 2000)
tup2 = (1, 2, 3, 4, 5, 6, 7)
print("tup1[0]: ", tup1[0])
print("tup2[1:5]: ", tup2[1:5])
tup3 = tup1 + tup2
print(tup3)
```

## 字典

字典是一系列键值对，每个键与值用冒号**:**分割，每个键值对之间用逗号**,**分割，整个字典在花括号 **{ }** 中。可以使用键来访问与之关联的值，如果用字典里没有的键访问数据，会输出错误。

```python
#!/usr/bin/python3

dict = {'Name': 'Runoob', 'Age': 7, 'Class': 'First'}
print("dict['Name']: ", dict['Name'])
print("dict['Age']: ", dict['Age'])
dict['Age'] = 8 # 更新
dict['School'] = "菜鸟教程" # 添加
del dict['Name'] # 删除
dict.clear() # 清空字典
del dict # 删除字典
```

## 集合

集合是一个无序的不重复元素序列，用花括号 **{ }** 或者 **set()** 函数创建集合。注意：创建一个空集合必须用 **set()** 而不是 **{ }**，因为 **{ }** 是用来创建一个空字典。

```python
#!/usr/bin/python3

s = set(("Google", "Runoob", "Taobao"))
s.add("Facebook")
s.remove("Taobao") # 不存在会发生错误
s.discard("Facebook") # 不存在不会发生错误
s.clear()
```



# 四、条件&循环

```python
#!/usr/bin/python3

# while 循环
while True:
    guess = int(input('Enter an integer : '))
    if guess < 9 :
        print('guess < 9')
        continue
    elif guess > 9 :
        pass # pass语句不做任何事情
    else:
        print('guess = 9')
        break
else:
    print('The while loop over')

# for 循环
for i in range(1, 9, 2): # range()函数生成整数序列
    print(i)
else:
    print('The for loop over')
```



# 五、函数&模块

```python
#!/usr/bin/python3

g_num = 0
def add_func(a, b = 1):
    print('sum is', a+b)
    global g_num
    g_num += 2
    print('g_num is', g_num)
    return a + 1, b + 1
x, y = add_func(1, 2)
print(x, y)
add_func(1)
add_func(b = 5, a = 10)


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
person('Adam', 45, gender = 'M', job = 'Engineer')
```

模块是一个包含所有你定义的函数和变量的文件，其后缀名是.py。模块可以被别的程序引入，以使用该模块中的函数等功能。这也是使用 python 标准库的方法。

模块是一种可重用的程序

包是指一个包含模块与一个特殊的 `__init__.py` 文件的文件夹，用以组织模块的另一种层次结构。

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



# 六、文件

```python
f = open('1.txt', 'a+') # 如果没有特别指定，启用默认的阅读(r)模式
f.write('this is test1 \nthis is test2')
while True:
    line = f.readline()
    if len(line) == 0:
        break
    print(line, end='')

f.close()


import os
os.uname() # 详细系统信息
os.environ # 环境变量
os.environ.get('PATH') # 某个环境变量
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
d = dict(name = 'Bob', age = 20, score = 88)
print(pickle.dumps(d)) # 对象序列化
f = open('1.txt', 'wb')
pickle.dump(d, f)
f.close()
```



# 七、面向对象

```python
class SchoolMember:
    totalNum = 0;  # 类变量，不属于某个对象
    def __init__(self, name, age):
        self.name = name # 对象变量
        self.age = age
        print('Initialized SchoolMember: {}'.format(self.name))
        SchoolMember.totalNum +=1
    def tell(self):
        '''告诉我有关我的细节。'''
        print('Name:"{}" Age:"{}"'.format(self.name, self.age), end=" ")
    @classmethod # 属于类而非属于对象的方法，可以将它定义为一个 classmethod(类方法) 或 staticmethod(静态方法)
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



# 八、进程&线程

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



# 九、网络编程

Python 提供了两个级别访问的网络服务：

- 低级别的网络服务支持基本的 Socket，它提供了标准的 BSD Sockets API，可以访问底层操作系统Socket接口的全部方法。
- 高级别的网络服务模块 SocketServer，它提供了服务器中心类，可以简化网络服务器的开发。

```python
#!/usr/bin/python3
# 文件名：server.py

# 导入 socket、sys 模块
import socket
import sys

# 创建 socket 对象
serversocket = socket.socket(
            socket.AF_INET, socket.SOCK_STREAM) 

# 获取本地主机名
host = socket.gethostname()

port = 9999

# 绑定端口号
serversocket.bind((host, port))

# 设置最大连接数，超过后排队
serversocket.listen(5)

while True:
    # 建立客户端连接
    clientsocket,addr = serversocket.accept()      

    print("连接地址: %s" % str(addr))
    
    msg='欢迎访问菜鸟教程！'+ "\r\n"
    clientsocket.send(msg.encode('utf-8'))
    clientsocket.close()
```

```python
#!/usr/bin/python3
# 文件名：client.py

# 导入 socket、sys 模块
import socket
import sys

# 创建 socket 对象
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# 获取本地主机名
host = socket.gethostname() 

# 设置端口号
port = 9999

# 连接服务，指定主机和端口
s.connect((host, port))

# 接收小于 1024 字节的数据
msg = s.recv(1024)

s.close()

print (msg.decode('utf-8'))
```



> [Python编程：从入门到实践 项目《外星人入侵》完整代码](https://www.cnblogs.com/qbdj/p/11004744.html)



> 🌈 ToDoList
>
> - C++11特性学习（使用、原理）
> - 泛型编程-模版
> - 设计模式理解应用
> - Hook钩子函数
