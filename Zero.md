[TOC]

# Makefile

[跟我一起写Makefile](https://github.com/seisman/how-to-write-makefile) 
> make先找到makefile中的第一个目标文件，一层层去找target的依赖关系，执行command，最终编译出第一个目标文件。


编译过程：

1. 预处理：替换inclue内容，宏定义， gcc –E hello.c –o hello.i
2. 编译：生成汇编代码，gcc –S hello.i –o hello.s
3. 汇编：生成机器代码，gcc –c hello.s –o hello.o
4. 链接：链接目标文件，gcc hello.o –o hello

编译选项：

`g++ -c hello.cpp -g -O -Wall -L./libpath -llibname -o hello.o`

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
- -fPIC 生成相对路径的代码，编译共享库时需要
- -pipe 使用管道代替编译中的临时文件

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




# Linux操作系统

* 进程是资源分配的独立单位
* 线程是资源调度的独立单位
* 进程之间的通信方式
    * 管道（PIPE）
    * 信号量（Semaphore）
    * 信号（Signal）
    * 消息队列（Message Queue）
    * 共享内存（Shared Memory）
    * 套接字（Socket）



# Linux内存

* Linux虚拟内存分布（高地址-低地址，内核空间：1G、用户空间：3G）
    * 栈：函数局部变量空间，一般为8M。
    * 文件映射区：动态库、共享内存，可通过mmap函数分配。
    * 堆：动态内存，通过malloc/free管理，堆顶位置可通过brk函数调整。
    * 数据段：bss段（未初始化或初始化为0的静态/全局变量）、data段（初始化的静态/全局变量）
    * 只读段：代码段、rodata段（字符常量和宏定义常量）

> * 进程栈：也可叫主线程栈，就是虚拟地址空间中的栈区。进程栈大小是执行时增长的，系统默认的最大值8M，可通过ulimit查看和设置。
> * 线程栈：其他线程栈是在主线程的堆中通过mmap分配的，大小固定，默认为8M，可通过pthread_attr_setstacksize接口来设置线程栈的大小。所以每个线程栈空间都是独立的。


Linux较Windows的内存管理区别：在linux中程序被关闭，占用的内存不会归还物理内存，而是用来做缓存。当物理内存有空闲时，优先使用物理内存（所以当使用 一段时间后，即使有很大内存也会被占用）。这样做的好处是，启动那些刚启动的程序，或是存取刚存取的数据，效率速度会比较快，适用于服务器的场景。



# 同步与锁
一个线程在访问资源未结束时，其他线程不能访问资源。最常见的同步方法是锁。
* **二元信号量**：最简单的一种锁，只有两种状态：占用、非占用。适用：一个线程独占访问的资源。
* **多元信号量**：一个初始值为N的信号量允许被N个线程并发访问。
* **互斥量**：与二元信号量很相似。区别是互斥量由哪个线程获取，那个线程就负责释放。
* **临界区**：临界区的作用范围仅限于当前进程，其他进程无法获取。
* **读写锁**：读写锁有三种状态：自由、共享、独占。
> 自由状态下（无读者写者），能以共享/独占方式获取（被读/被写）。  
> 共享状态下（被读），能以共享方式再被获取（被读）。  
> 独占状态下（被写），不能被获取。  
* **条件变量**：类似于一个栅栏。一个条件变量可以被多个线程等待，当事件发生（条件变量被唤醒），所有的线程可以一起恢复执行。
* **递归锁**：也叫可重入锁，同一个线程可以多次获取同一个递归锁，不会产生死锁。

在多线程编程时，要解决数据访问的同步与互斥，这时可能会引入死锁的问题。死锁指的是，两个（以上）线程在执行过程中，因争夺资源而造成一种互相等待的现象，若无外部处理，将会无限等待下去。死锁本质上就是一个线程在请求锁的时候，永远也请求不到。

死锁的危险始终存在，应该在程序编写的时候尽量减少死锁存在的范围。死锁发生的情况：  
1. 忘记释放锁
```c++
void process()
{
	mutex1.enter();
	if(...)	return;
	mutex1.leave();
} 
```
2. 单线程重复申请锁
```c++
void process()
{
	mutex1.enter();
	func();
	mutex1.leave();
} 
void func()
{
	mutex1.enter();
	do_Something;
	mutex1.leave();
}
```
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


# pthread
```c++
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
	thread：线程标识符的指针
	attr：线程属性
	start_routine：线程运行函数地址
	arg：运行函数入参
	*/
	pthread_t tpid;
	int arg = 1;
	int ret = pthread_create(&tpid, NULL, ThreadProc, (void *)&arg);
	if(ret != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}
	
	if(pthread_join(tpid, NULL))	//等待线程释放
		return -1;

	return 0;
}
```





