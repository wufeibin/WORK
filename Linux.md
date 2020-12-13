# Linux进程&线程

>  进程是资源分配的独立单位
>
>  线程是资源调度的独立单位



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

