[TOC]

> GitHub搜索：
>
> in:name/readme/description 关键词 language:python star:>1000 fork:>500 pushed:>2020-1-1 

# Linux进程&线程

>  进程是资源分配的独立单位
>
> 线程是资源调度的独立单位



## 进程控制

> 进程之间的通信方式：
>
> - 管道（PIPE）
> - 信号量（Semaphore）
> - 信号（Signal）
> - 消息队列（Message Queue）
> - 共享内存（Shared Memory）
> - 套接字（Socket）


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



## 线程同步

一个线程在访问资源未结束时，其他线程不能访问资源。在多线程编程时，要解决数据访问的同步与互斥，最常见的方法是锁，这时可能会引入死锁的问题。死锁指的是，两个（以上）线程在执行过程中，因争夺资源而造成一种互相等待的现象，若无外部处理，将会无限等待下去。死锁本质上就是一个线程在请求锁的时候，永远也请求不到。

* **信号量**：一个特殊类型的变量
```c
//二元信号量：一个线程独占访问的资源。
//多元信号量：一个初始值为N的信号量允许被N个线程并发访问。
int sem_init (sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);	//阻塞等待信号量，当信号量值大于0时，信号量减1，向下执行。
int sem_trywait(sem_t *sem);
int sem_post(sem_t *sem);	//释放信号量，信号量值加1。
int sem_getvalue(sem_t *sem, int *sval)
int sem_destroy(sem_t *sem);
```

* **互斥量/锁**：与二元信号量很相似。区别是互斥量由哪个线程获取，那个线程就负责释放。
```c
#include<pthread.h>
pthread_mutex_t mutex;
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutex_attr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t * mutex,const struct timespec * tsptr);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

* **读写锁**：读写锁有三种状态：自由、共享、独占。
```c
//自由状态下（无读者写者），能以共享/独占方式获取（被读/被写）。
//共享状态下（被读），能以共享方式再被获取（被读）。 
//独占状态下（被写），不能被获取。
#include<pthread.h>
pthread_rwlock_t rwlock;
int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_timedrdlock(pthread_rwlock_t * rwlock, const struct timespec * abstime);
int pthread_rwlock_timedwrlock(pthread_rwlock_t * rwlock, const struct timespec * abstime);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
```

* **递归锁**：也叫可重入锁，同一个线程可以多次获取同一个递归锁，不会产生死锁。
* **条件变量**：阻塞线程，避免线程不断轮训，类似于一个栅栏。一个条件变量可以被多个线程等待，当条件变量被唤醒，所有的线程可以一起恢复执行。

```c
#include <pthread.h>
pthread_cond_t cond;
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timewait(pthread_cond_t *cond, pthread_mutex *mutex, const timespec *abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_destroy(pthread_cond_t *cond);
```

```c
void *product(void *arg)
{
  while(1)
  {
    if(需要生产)
    {
      pthread_mutex_lock(&lock);
      push_node(data);
      pthread_mutex_unlock(&lock);
      pthread_cond_signal(&cond);
    }
    sleep(1);
  }
}
void *consumer(void *arg)
{
  data_type data;
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(-1 == pop_node(&data));   //为空
    {
      pthread_cond_wait(&cond,&lock); //阻塞等待，解锁；唤醒执行，加锁。
    }
    func(data);  //执行业务
    pthread_mutex_unlock(&lock);
    sleep(1);
  }
}

int main()
{
  pthread_cond_t cond;
  pthread_cond_init(&cond,NULL);
  pthread_t tid1,tid2;
  pthread_create(&tid1,NULL,product,NULL);
  pthread_create(&tid2,NULL,consumer,NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_cond_destroy(&cond);
  return 0;
}
```




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



# Git

[Git教程](https://github.com/luotf/Git/blob/master/Git%E6%95%99%E7%A8%8B.md)

- Git属于分布式版本控制系统，而SVN属于集中式。集中式版本控制只有中心服务器拥有一份代码，而分布式版本控制每个电脑上都有一份完整代码。GitHub就是中心服务器，用来交换每个用户的修改。
- Git仓库和GitHub中心服务器仓库的传输通过SSH加密。主目录中的.ssh目录下有id_rsa(私钥)和id_rsa.pus(公钥)两个文件，将公钥内容复制到GitHub的SSH Keys中用于传输。
- 工作流：新建一个仓库后，当前目录就成了**工作目录**，工作目录下有一个隐藏目录.git，它属于Git的版本库。Git版本库有一个称为Stage**暂存区**和History**版本库**。History版本库中存有所有的分支，使用一个HEAD指针指向当前分支。

- Git命令

```
工作目录 ----add/rm----> 缓存区 ----commit----> 本地仓库 ----push----> 远程仓库
工作目录 <----checkout---- 缓存区 <-------- 本地仓库 <----pull---- 远程仓库

git init 创建当前目录新仓库
git clone git@github.com:wufeibin/WORK.git 克隆创建仓库
git branch 查看分支
git branch <name> 创建分支
git branch -d <name> 删除分支
git checkout <name> 切换分支
git checkout -b <name> 创建并切换分支
git checkout -- <filename> 回退替换工作目录的文件
git status 查看仓库状态
git diff <filename>
git diff <source_branch> <target_branch>
git add <filename>
git commit -m "xxxx"
git log
git reset HEAD <filename> 回退缓存区的修改至工作目录
git reset --hard HEAD^ 回退至上个版本
git reset --hard <id> 回退至某个版本
git reset --hard origin/master
git pull 更新本地仓库
git pull origin <branch>
git push 推送改动至远端仓库
git push origin <branch>

git fetch origin
git merge <branch> 合并某分支到当前分支
```



# RESTful
[RESTful API 设计规范](https://github.com/godruoyi/restful-api-specification)


RESTful架构，就是目前最流行的一种互联网软件架构。它结构清晰、符合标准、易于理解、扩展方便，所以正得到越来越多网站的采用。REST，即Representational State Transfer，表现层状态转化。如果一个架构符合REST原则，就称它为RESTful架构。



**1.资源（Resources）**: 每种资源对应一个特定的URI(统一资源定位符),URI为每一个资源的地址或独一无二的识别符;

**2.表现层（Representation）**:把"资源"具体呈现出来的形式，叫做它的"表现层"，URI只代表"资源"的位置。它的具体表现形式，应该在HTTP请求的头信息中用Accept和Content-Type字段指定，这两个字段才是对"表现层"的描述。

**3.状态转化（State Transfer）**:客户端想要操作服务器，必须通过某种手段，让服务器端发生"状态转化"。而这种转化是建立在表现层之上的，所以就是"表现层状态转化"。客户端用到的手段就是HTTP协议里面，四个表示操作方式的动词：GET、POST、PUT、DELETE。它们分别对应四种基本操作：GET用来获取资源，POST用来新建资源（也可以用于更新资源），PUT用来更新资源，DELETE用来删除资源。

总结:

- 每一个URI代表一种资源；
- 客户端和服务器之间，传递这种资源的某种表现层；
- 客户端通过四个HTTP动词，对服务器端资源进行操作，实现"表现层状态转化"。



对于资源的具体操作类型，由HTTP动词表示。 常用的HTTP动词有下面五个

- GET（SELECT）：从服务器取出资源（一项或多项）。 
- POST（CREATE）：在服务器新建一个资源。
- PUT（UPDATE）：在服务器更新资源（客户端提供改变后的完整资源）。
- PATCH（UPDATE）：在服务器更新资源（客户端提供改变的属性）。
- DELETE（DELETE）：从服务器删除资源。

还有两个不常用的HTTP动词。

- HEAD：获取资源的元数据。
- OPTIONS：获取信息，关于资源的哪些属性是客户端可以改变的。

下面是一些例子。

> GET /zoos：列出所有动物园  
>  POST /zoos：新建一个动物园  
>  GET /zoos/ID：获取某个指定动物园的信息  
>  PUT /zoos/ID：更新某个指定动物园的信息（提供该动物园的全部信息）  
>  PATCH /zoos/ID：更新某个指定动物园的信息（提供该动物园的部分信息）  
>  DELETE /zoos/ID：删除某个动物园  
>  GET /zoos/ID/animals：列出某个指定动物园的所有动物  
>  DELETE /zoos/ID/animals/ID：删除某个指定动物园的指定动物  

针对不同操作，服务器向用户返回的结果应该符合以下规范。

> GET /collection：返回资源对象的列表（数组）  
> GET /collection/resource：返回单个资源对象  
> POST /collection：返回新生成的资源对象  
> PUT /collection/resource：返回完整的资源对象  
> PATCH /collection/resource：返回完整的资源对象  
> DELETE /collection/resource：返回一个空文档  



# POCO

https://github.com/pocoproject/poco

https://pocoproject.org/docs/index.html