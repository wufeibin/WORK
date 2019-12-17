[TOC]


# Linux进程/线程

>  进程是资源分配的独立单位
>
> 线程是资源调度的独立单位

- 进程之间的通信方式
  - 管道（PIPE）
  - 信号量（Semaphore）
  - 信号（Signal）
  - 消息队列（Message Queue）
  - 共享内存（Shared Memory）
  - 套接字（Socket）

## 进程控制


- fork/vfork 创建子进程
- exec族函数 将当前进程替换为新进程
- wait/waitpid 等待获取子进程状态的改变
- exit 终止进程

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(pid < 0) {
		perror("fork failed");
		exit(1);
	}else if(pid == 0) {
		printf("This is in child progress\n");
		char *const argv[] ={"exec_call", NULL};
		execv("./exec_call", argv);	//执行exec_call新程序
	}
	else {
		printf("This is in parent progress\n");
		int stat_val;
		waitpid(pid, &stat_val, 0);
		if ( WIFEXITED(stat_val) ){
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val) );		
		}
	}
	return 0;
}
```

## 线程创建

```c
#include <cstdio>
#include <iostream>
#include <pthread.h>
using namespace std;

void * ThreadProc(void *arg)	//线程执行体
{
	int c = *((int*)arg);
	while(c < 10)
	{
		cout << c++ << endl;
		sleep(1);
	}
}

int main()
{
	/*
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	thread：线程标识符的指针，attr：线程属性，start_routine：线程运行函数地址，arg：运行函数入参
	*/
	pthread_t tpid;
	int arg = 1;
	int ret = pthread_create(&tpid, NULL, ThreadProc, (void *)&arg);
	if(ret != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}
	if(pthread_join(tpid, NULL))	//阻塞等待线程释放
		return -1;

	return 0;
}
```

## 线程同步与锁
一个线程在访问资源未结束时，其他线程不能访问资源。在多线程编程时，要解决数据访问的同步与互斥，最常见的方法是锁，这时可能会引入死锁的问题。死锁指的是，两个（以上）线程在执行过程中，因争夺资源而造成一种互相等待的现象，若无外部处理，将会无限等待下去。死锁本质上就是一个线程在请求锁的时候，永远也请求不到。

* **二元信号量**：最简单的一种锁，只有两种状态：占用、非占用。适用：一个线程独占访问的资源。
* **多元信号量**：一个初始值为N的信号量允许被N个线程并发访问。
* **互斥量**：与二元信号量很相似。区别是互斥量由哪个线程获取，那个线程就负责释放。
* **读写锁**：读写锁有三种状态：自由、共享、独占。
> 自由状态下（无读者写者），能以共享/独占方式获取（被读/被写）。  
> 共享状态下（被读），能以共享方式再被获取（被读）。  
> 独占状态下（被写），不能被获取。  

* **递归锁**：也叫可重入锁，同一个线程可以多次获取同一个递归锁，不会产生死锁。
* **临界区**：临界区的作用范围仅限于当前进程，其他进程无法获取。
* **条件变量**：类似于一个栅栏。一个条件变量可以被多个线程等待，当事件发生（条件变量被唤醒），所有的线程可以一起恢复执行。


死锁的危险始终存在，应该在程序编写的时候尽量减少死锁存在的范围。死锁发生的情况：  
1. 忘记释放锁
2. 单线程重复申请锁
3. 多线程申请多把锁
```c++
void process1()
{
	mutex1.enter();
	mutex2.enter();
	do_Something;
	mutex2.leave();
	mutex1.leave();
}
void process2()
{
	mutex2.enter();
	mutex1.enter();
	do_Something;
	mutex1.leave();
	mutex2.leave();
}
```



# Linux内存

- Linux虚拟内存分布（高地址-低地址，内核空间：1G、用户空间：3G）
  - 栈：函数局部变量空间，一般为8M。
  - 文件映射区：动态库、共享内存，可通过mmap函数分配。
  - 堆：动态内存，通过malloc/free管理，堆顶位置可通过brk函数调整。
  - 数据段：bss段（未初始化或初始化为0的静态/全局变量）、data段（初始化的静态/全局变量）
  - 只读段：代码段、rodata段（字符常量和宏定义常量）

- 进程栈：也可叫主线程栈，就是虚拟地址空间中的栈区。进程栈大小是执行时增长的，系统默认的最大值8M，可通过ulimit查看和设置。
- 线程栈：其他线程栈是在主线程的堆中通过mmap分配的，大小固定，默认为8M，可通过pthread_attr_setstacksize接口来设置线程栈的大小。所以每个线程栈空间都是独立的。

Linux较Windows的内存管理区别：在linux中程序被关闭，占用的内存不会归还物理内存，而是用来做缓存。当物理内存有空闲时，优先使用物理内存（所以当使用 一段时间后，即使有很大内存也会被占用）。这样做的好处是，启动那些刚启动的程序，或是存取刚存取的数据，效率速度会比较快，适用于服务器的场景。



# 数据库

>数据库是按照数据结构来组织、存储和管理数据的仓库。
>
>虽然也可以将数据存储在文件中，但是在文件中读写数据速度相对较慢，所以使用关系型数据库管理系统（RDBMS）来存储和管理大数据量。
>
>关系数据库管理系统特点：数据以表格的形式出现；每行为各种记录名称；每列为记录名称所对应的数据域；许多行和列组成一张表单；若干的表单组成database。

## SQL语句

> SQL(Structured Query Language) 是用于访问和处理数据库的标准的计算机语言。大小写不敏感。

- 创建数据库 create database <dbname>
- 删除数据库 drop database <dbname>
- 创建表 create table <tablename>(...)
- 删除表 drop table <tablenme>
- **插入** insert into table1(field1,field2) values(value1,value2)
- **删除** delete from table1 where 范围
- **更新** update table1 set field1=value1 where 范围
- **查找** select * from table1 where field1 like ’%value1%’

## MongoDB

[MongoDB API](https://api.mongodb.com/cplusplus/current/annotated.html)

- 连接数据库

```
conn.connect(DATABSE_IP +":"+ DATABSE_PORT),errmsg)
```

- 插入

```
BSONObj p = BSONObjBuilder().append("ID", "1").append("Words", "Hello World").obj();
conn.insert(DATABASE_NAME+"."+COLLECTION_NAME, p);
```

- 更新

```
bool upsert = false; // update, if not exist, insert.
bool updateMulti = false; // update multi
BSONObj updateQuery = BSONObjBuilder().append("ID", "1").obj();
BSONObj updateData = BSONObjBuilder().append("Words", "This is MongoDB C++ Driver").obj();
con.update(DATABASE_NAME+"."+COLLECTION_NAME, updateQuery, updateData, upsert, updateMulti);
```

- 删除

```
bool deleteOne = true; // delete only one record after selected. otherwise, delete all selected records.
BSONObj deleteQuery = BSONObjBuilder().append("ID", "1").obj();
con.remove(DATABASE_NAME+"."+COLLECTION_NAME, deleteQuery, deleteOne);
```

- 查询

```
auto_ptr<DBClientCursor> dc = con.query(DATABASE_NAME+"."+COLLECTION_NAME);
return dc;
```





# Makefile

[跟我一起写Makefile](https://github.com/seisman/how-to-write-makefile) 

> make先找到makefile中的第一个目标文件，一层层去找target的依赖关系，执行command，最终编译出第一个目标文件。

编译过程：

1. 预处理：替换inclue内容，宏定义， gcc –E hello.c –o hello.i
2. 编译：生成汇编代码，gcc –S hello.i –o hello.s
3. 汇编：生成机器代码，gcc –c hello.s –o hello.o
4. 链接：链接目标文件，gcc hello.o –o hello

编译选项：

- -o 指定目标文件名称
- -c 生成目标文件
- -g 生成编译信息
- -O 优化生成代码
- -Wall 生成所有告警信息
- -I 指定额外的头文件搜素路径
- -L 指定额外的库搜索路径
- -l 指定链接的库名
- -M 生成文件关联的信息
- -share 生成共享目标文件
- -fPIC 生成位置独立的代码，编译共享库时需要
- -pipe 使用管道代替编译中的临时文件

```
//静态库编译
g++ -c hello.cpp
ar -crv libhello.a hello.o
//动态库编译
g++ -fPIC -share -o libhello.so helo.cpp
//静态库、动态库使用
g++ -c main.cpp -L./libpath -lhello
```

常见字符：

- @ 不打印命令，只打印结果
- % 匹配到若干个字符，给%赋值。%.o:%.c，找出匹配的所有的.o和.c文件
- $@ 目标文件
- $^ 所有的依赖文件
- $< 第一个依赖文件
- := 只能使用前面已定义的变量来赋值
- ?= 赋值一个新的变量，若变量已定义则不处理
- += 追加变量值
- CFLAGS C编译器参数
- CXXFLAGS C++编译器参数
- LDFLAGS 链接器参数
- .PHONY 伪目标，可开头声明一个all的伪目标，依赖多个目标，实现一次生成多个目标
- include 引用其他Makefile
- $(MAKE) -C subdir，进入subdir嵌套执行make命令
- strip函数，去掉字符串头尾的空字符，合并中间的连续空字符为一个空字符
- addprefix函数，给字符加前缀



# GDB

- break file:line
- break function
- break ... if ...	//设置条件断点
- info breakpoints	//查看当前设置了哪些断点
- delete breakpoints	//删除断点
- enable/disable breakpoints	//启用/禁用断点
- display		//跟踪查看某个变量，每次遇到断点都显示它的值
- command	breakpoints ··· end	//为断点设置运行命令
- run			//从头开始连续运行程序
- continue	//从当前位置开始连续运行程序
- next		//执行下一行语句
- step		//执行下一行语句，若有函数调用则进入到函数中
- finish		//运行到当前函数返回为止
- backtrace	//查看各级函数调用及参数
- t ..		//跳转到指定线程
- f ..		//跳转到指定栈帧
- info locals	//查看当前栈帧局部变量的值
- info args	//查看当前函数入参的值
- info r		//查看寄存器的值
- print		//打印表达式的值
- disassemble //打开该帧函数的反汇编代码
- examine(x)	//按字节打印某个地址中开始的值



# Git

[Git教程](https://www.liaoxuefeng.com/wiki/896043488029600)

- Git属于分布式版本控制系统，而SVN属于集中式。集中式版本控制只有中心服务器拥有一份代码，而分布式版本控制每个电脑上都有一份完整代码。GitHub就是中心服务器，用来交换每个用户的修改。
- Git仓库和GitHub中心服务器仓库的传输通过SSH加密。工作区的.ssh目录下有id_rsa(私钥)和id_rsa.pus(公钥)两个文件，将公钥内容复制到GitHub的SSH Keys中用于传输。
- 新建一个仓库后，当前目录就成了工作区，工作区下有一个隐藏目录.git，它属于Git的版本库。Git版本库有一个称为Stage暂存区和History版本库。History版本库中存有所有的分支，使用一个HEAD指针指向当前分支。
- git命令

```
工作目录 ----add/rm----> 缓存区 ----commit----> 本地仓库 ----push----> 远程仓库
工作目录 <----checkout---- 缓存区 <-------- 本地仓库 <----pull/fetch---- 远程仓库

git clone
git branch 查看分支
git branch <name> 创建分支
git branch -d <name> 删除分支
git checkout <name> 切换分支
git add
git commit
git reset
git pull
git push
git merge 合并某分支到当前分支
```

# 
