# 一、Linux命令

[Linux命令大全](https://man.linuxde.net/)

| 命令                                 | 示例                                                         |
| ------------------------------------ | ------------------------------------------------------------ |
| **grep**<br />搜索数据               | grep -n xxx file 【显示行号】<br />grep -r xxx path 【递归查找目录文件】<br />grep -v xxx file 【反向搜索，输出不匹配的行】<br />grep -w xxx file 【显示全词匹配的行】<br />grep -c xxx file 【显示匹配的行数】<br />grep -l xxx * 【显示匹配的文件名】 <br />grep -A 2 xxx file 【显示匹配内容和后2行】<br />grep -B 2 xxx file 【显示匹配内容和前2行】<br />grep -C 2 xxx file 【显示匹配内容和前后2行】<br />grep -e xxx -e yyy file, grep -E 'xxx\|yyy' file, egrep 'xxx\|yyy' file 【或匹配】 <br />grep '2020-08-3[0-9]' file |
| **find**<br />递归查找文件           | find [path] -name file<br />find [path] -type f -name file 【f 普通文件，d 目录】<br />find . -type f -name file -exec printf "File: %s\n" {} \; |
| **xargs**<br />配合管道｜使用        | find . -name "1.txt" \| xargs ls 【与管道配合使用，将标准输出转化为参数】 |
| **chmod/chown**<br />修改文件权限    | drwxr-x--- 1 va ivs 4096 Dec 16 04:10 VA2<br/>d : 目录<br/>rwx : 文件属主权限(va)<br/>r-x : 属组成员权限(ivs)<br/>--- : 其他用户权限 |
| **tar**<br />归档                    | tar -xzvf xxx.tar.gz -C [path] 【解压缩文件】<br />tar -czvf xxx.tar.gz [file] 【打包压缩文件】 |
| **zip/unzip**<br />压缩/解压zip文件  | zip -r xxx.zip ./*<br />unzip -d /home xxx.zip               |
| **gzip/gunzip**<br />压缩/解压gz文件 | gzip -c -r xxx >xxx.gz<br />gunzip -c xxx.gz >xxx            |
| **ln**<br />创建链接文件             | ln -snf file ln_file                                         |
| **netstat**<br />查看网络端口        | netstat -anp                                                 |
| **ldd**<br />查看程序/库依赖的共享库 | ldd -r xxx.so 【-r选项，数据对象和函数的重定位】             |
| **readelf**<br />查看elf目标文件信息 | readelf -sD xxx.so 【查看elf文件的动态符号表】               |
| **nm**<br />查看目标文件的符号表     |                                                              |
| **objdump**<br />查看目标文件的构成  |                                                              |
| **top**<br />查看系统实时进程情况    | top -H -p [pid]                                              |
| **mount/umount**<br />挂载存储媒体   | mount -t type device directory<br />umount device            |
| **df**<br />查看挂载设备磁盘使用     | df -h                                                        |
| **du**<br />查看目录的硬盘使用       | du -ch path<br />du -sh *                                    |
|                                      |                                                              |
|                                      |                                                              |
|                                      |                                                              |
|                                      |                                                              |
|                                      |                                                              |
|                                      |                                                              |
|                                      |                                                              |
| **其他实用命令**                     | cat -n file 【按行号查看文件】<br />tail -f file 【循环显示文件末尾内容】<br />tail -n 10 file 【显示文件末尾10行内容】<br />head -n 10 file 【显示文件起始10行内容】<br />more file<br />less file |
|                                      |                                                              |
|                                      |                                                              |

### sed 流编辑器

- echo this is xxx | sed 's/xxx/yyy/'
- sed 's/xxx/yyy/' file 【替换文本中的字符串】
- sed 's/xxx/yyy/g' file 【/g 替换每一行中的所有匹配】
- sed -n 's/xxx/yyy/p' file 【-n选项和p命令一起使用，只打印那些发生替换的行】
- sed -e 's/brown/green/; s/dog/cat/' file 【-e选项，同一行里执行多条命令】
- sed -f script.sed file
- sed -n '/2020-08-30-15-38-[0-9]/,/2020-08-30-15-50-[0-9]/p' file 【,选项，选定行范围】

### awk

- awk 'BEGIN{ commands } pattern{ commands } END{ commands }'
  - 第一步：执行`BEGIN{ commands }`语句
  - 第二步：从文件或标准输入逐行读取，执行`pattern{ commands }`语句
  - 第三步：执行`END{ commands }`语句

- echo -e "A line 1\nA line 2" | awk 'BEGIN{ print "Start" } { print; print $1 } END{ print "End" }'
  - $0 整行内容
  - $n 第n个字段
  - NF 字段数

- awk -F: '{print $1}' data.txt 【-F指定分隔符 : 】


# 二、Shell脚本

| 数值比较  |              |
| --------- | ------------ |
| n1 -eq n2 | n1等于n2     |
| n1 -ne n2 | n1不等于n2   |
| n1 -ge n2 | n1大于等于n2 |
| n1 -gt n2 | n1大于n2     |
| n1 -le n2 | n1小于等于n2 |
| n1 -lt n2 | n1小于n2     |


| 字符串比较   |                 |
| ------------ | --------------- |
| str1 = str2  | str1和str2相同  |
| str1 != str2 | str1和str2不同  |
| str1 < str2  | str1比str2小    |
| str1 > str2  | str1比str2大    |
| -n str1      | str1的长度不为0 |
| -z str1      | str1的长度为0   |


| 文件比较 |                              |
| -------- | ---------------------------- |
| -e file  | 检查file是否存在             |
| -f file  | 检查file是否存在并是一个文件 |
| -d file  | 检查file是否存在并是一个目录 |
| -r file  | 检查file是否存在并可读       |
| -s file  | 检查file是否存在并非空       |
| -w file  | 检查file是否存在并可写       |
| -x file  | 检查file是否存在并可执行     |

 


- if | case

```
#!bin/bash
str="yyy"
if [ $str = "xxx" ]; then
    echo "xxx"
elif [ $str = "yyy" ]; then
    echo "yyy"
else
    echo "zzz"
fi
```

```
#!bin/bash
case $1 in
jack | lisa)
    echo "Welcome, $1"
    echo "Please";;
mike)
    echo "xxx";;
james)
    echo "yyy";;
*)
    echo "zzz";;
esac
```

- for | while | until | break | continue

```
#!/bin/bash
for file in `pwd`/*
do
    echo "file : $file"
done

for (( a=1, b=10; a <= 10; a++, b-- ))
do
    echo "$a - $b"
done
```

```
var=10
while [ $var -gt 0 ]
do
    echo $var
    var=$[ $var - 1 ]
done
```

```
var=10
until [ $var -eq 0 ]
do
    echo $var
    var=$[ $var - 1 ]
done
```

- function

```
function name {
	commands
}

name() {
	commands
}
```



**内置变量**

- $0：脚本文件名称

- $1：第1个位置参数

- $#：位置参数个数

- $@/*：所有的位置参数

- $?：退出状态码

- $PATH：可执行文件的搜索路径

- $PWD：当前工作目录




### Shell实例

- 菜单脚本

```shell
#!/bin/bash

echo "Tool Menu"
PS3="Please choose your option: "
select option in "Option1" "Option2" "Option3" "Test" "Exit"
do
    case $option in
        "Option1")
            echo "option 1";;
        "Option2")
            echo "option 2";;
        "Option3")
            ls;;
        "Test")
            pwd;;
        "Exit")
            break ;;
        *)
            echo "invalid option"
            break ;;
    esac
done
```

- 输入一个数字，运行对应的一个命令。

```shell
#!/bin/bash
echo "1:date; 2:ls 3:who 4:pwd"
read -p "Please input a number: " n
echo ${n:=1}	# 默认值为1
if [ -z "$n" ]
then
    echo "请输入一个纯数字,范围1-4."
    exit
fi

${n=1}
case $n in 
    1)
      date
      ;;
    2)
      ls
      ;;
    3)
      who
      ;;
    4)
      pwd
      ;;
    *)
      echo "请输入1-4的数字"
      ;;
esac
```

- 以 2017-12-20.log 格式每日生成一个文件，并删除一年以前的文件。

```shell
#!/bin/bash
#时间格式：date +%F、date +%y%m%d、date +%Y-%m-%d-%H-%M-%S
d=`date +%F` #将命令输出赋给变量：`` 或 $()
dir=/data/logs/disklog
if [ ! -d $dir ]
then
    mkdir -p $dir
fi
df -h > $dir/$d.log #输出重定向，写入覆盖文件：>；追加到文件末尾：>> 
find $dir/ -mtime +365 |xargs rm
```

- 找到/123目录下所有后缀名为.txt的文件，打包压缩为123.tar.gz

```shell
#!/bin/bash
find /123/ -type f -name "*.txt" > /tmp/txt.list
tar -czvf 123.tar.gz `cat /tmp/txt.bak.list |xargs`
```

- 把一个文本文档的前5行中包含字母的行删除掉，同时把6到10行中的全部字母删除掉。

```shell
#!/bin/bash
sed -n '1,5'p 1.txt |sed '/[a-zA-Z]/d' #把一个文本文档的前5行中包含字母的行删除掉
sed '1,5d' 1.txt |sed '1,5s/[a-zA-Z]//g' ##把6到10行中的全部字母删除掉。
```

- 当时间是0点和12点时，需要将目录/data/log/下的文件全部清空，而其他时间统计每个文件的大小，一个文件一行，输出到一个按日期和时间为名字的日志里。

```shell
#!/bin/bash
dir=/tmp/log_stat
t=`date +%d%H`
t1=`date +%H`
logdir=/data/log

[ -d $dir ] || mkdir $dir #或运算符，同-o
[ -f $dir/$t.log ] && rm -f $dir/$t.log #与运算符，同-a

if [ $t == "00" -o $t1 == "12" ]
then
    for f in `find $logdir/ -type f`
    do
      > $f
    done
else
    for f in `find $logdir/ -type f`
    do
      du -sh $f >> $dir/$t.log
    done
fi
```

- 把文本里面每三行内容合并到一行

```shell
#!/bin/bash
n=1
cat $1 |while read line #逐行遍历
do
    n1=$[$n%3]
    if [ $n1 -eq 0 ]
    then
      echo "$line"
    else
      echo -n "$line " #不换行
    fi
      n=$[$n+1]
done
```



# 三、进程&线程

进程是程序执行时的一个实例，即它是程序已经执行到何种程度的数据结构的汇集。从内核的观点看，进程的目的就是担当分配系统资源（CPU时间、内存等）的基本单位。

线程是进程的一个执行流，是CPU调度和分派的基本单位，它是比进程更小的能独立运行的基本单位。一个进程由几个线程组成（拥有很多相对独立的执行流的用户程序共享应用程序的大部分数据结构），线程与同属一个进程的其他的线程共享进程所拥有的全部资源。

进程有独立的地址空间，一个进程崩溃后，在保护模式下不会对其它进程产生影响，而线程只是一个进程中的不同执行路径。线程有自己的堆栈和局部变量，但线程没有单独的地址空间，一个线程死掉就等于整个进程死掉，所以多进程的程序要比多线程的程序健壮，但在进程切换时，耗费资源较大，效率要差一些。但对于一些要求同时进行并且又要共享某些变量的并发操作，只能用线程，不能用进程。

> "进程是资源分配的最小单位，线程是程序执行的最小单位"



## 3.1 进程

正常情况下，子进程是通过父进程创建的，子进程的结束和父进程的运行是一个异步过程，即父进程永远无法预测子进程到底什么时候结束。 当一个进程完成它的工作终止之后，它的父进程需要调用wait()或者waitpid()系统调用取得子进程的终止状态。

```c
1、fork/vfork // 创建子进程
2、exec族函数 // 将当前进程替换为新进程
3、wait/waitpid // 等待获取子进程状态的改变
4、exit // 终止进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("This is in child progress\n");
        char *const argv[] = {"exec_call", NULL};
        execv("./exec_call", argv);	// 执行exec_call新程序
    } else {
        printf("This is in parent progress\n");
        int stat_val;
        waitpid(pid, &stat_val, 0);
        if (WIFEXITED(stat_val)) {
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));		
        }
    }
    return 0;
}
```

### 孤儿进程

一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集工作。由于孤儿进程会被init进程给收养，所以孤儿进程不会对系统造成危害。

### 僵尸进程

一个进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，那么子进程的进程描述符仍然保存在系统中，这种进程称之为僵死进程。如果要消灭系统中大量的僵死进程，只需要将其父进程杀死，此时所有的僵死进程就会编程孤儿进程，从而被init所收养，这样init就会释放所有的僵死进程所占有的资源，从而结束僵死进程。

在每个进程退出的时候，内核释放该进程所有的资源，包括打开的文件，占用的内存等。 但是仍然为其保留一定的信息（进程号、退出状态、运行时间t等），直到父进程通过wait / waitpid来取时才释放。 如果进程不调用wait / waitpid的话， 那么保留的那段信息就不会释放，其进程号就会一直被占用，但是系统所能使用的进程号是有限的，如果大量的产生僵死进程，将因为没有可用的进程号而导致系统不能产生新的进程，此即为僵尸进程的危害，应当避免。

### 守护进程

一个守护进程的父进程是init进程，因为它真正的父进程在fork出子进程后就先于子进程exit退出了，所以它是一个由init继承的孤儿进程。

Linux Daemon（守护进程）是运行在后台的一种特殊进程。它独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件。Linux系统的大多数服务器就是通过守护进程实现的。常见的守护进程包括系统日志进程syslogd、 web服务器httpd、邮件服务器sendmail和数据库服务器mysqld等。守护进程一般在系统启动时开始运行，除非强行终止，否则直到系统关机都保持运行。守护进程经常以超级用户（root）权限运行，因为它们要使用特殊的端口（1-1024）或访问某些特殊的资源。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 守护进程初始化函数
void init_daemon()
{
    pid_t pid;
    if ((pid = fork()) == -1) {
        printf("Fork error !\n");
        exit(1);
    }
    if (pid != 0) {
        exit(0);        // 父进程退出
    }

    setsid();           // 子进程开启新会话，并成为会话首进程和组长进程
    if ((pid = fork()) == -1) {
        printf("Fork error !\n");
        exit(-1);
    }
    if (pid != 0) {
        exit(0);        // 结束第一子进程，第二子进程不再是会话首进程
    }
    chdir("/tmp");      // 改变工作目录
    umask(0);           // 重设文件掩码
    for (int i = 0; i < getdtablesize(); ++i) {
       close(i);        // 关闭打开的文件描述符
    }
    return;
}

int main(int argc, char *argv[]) {
    int fp;
    time_t t;
    char buf[] = {"This is a daemon:  "};
    char *datetime;
    int len = 0;

    init_daemon(); // 初始化 Daemon 进程
    while (1) {
        if (-1 == (fp = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600))) {
          printf("Open file error !\n");
          exit(1);
        }
        len = strlen(buf);
        write(fp, buf, len);
        t = time(0);
        datetime = asctime(localtime(&t));
        len = strlen(datetime);
        write(fp, datetime, len);
        close(fp);
        sleep(60); // 每隔一分钟记录运行状态
    }
    return 0;
}
// 注：也利用库函数daemon()创建守护进程
```

### 进程间通信

进程之间的通信方式：管道（PIPE）、信号量（Semaphore）、信号（Signal）、消息队列（Message Queue）、共享内存（Shared Memory）、套接字（Socket）



## 3.2 线程

**资源消耗**：多个线程之间使用相同的地址空间，共享大部分数据，启动一个线程所花费的空间远远小于启动一个进程所花费的空间，线程间彼此切换所需的时间也远远小于进程间切换所需要的时间。**通信机制**：线程之间共享数据空间，所以一个线程的数据可以直接为其它线程所用，快捷且方便。

```c
1、int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); // 创建一个线程。thread：线程标识符的指针，attr：线程属性，start_routine：线程运行函数地址，arg：运行函数入参
2、int pthread_join(pthread_t tid, void ** status); // 等待某个线程退出
3、pthread_t pthread_self(void); // 返回当前线程的ID
4、int pthread_detach(pthread_t tid); // 指定线程变为分离状态。变为分离状态的线程，如果线程退出，它的所有资源将全部释放；而不是分离状态，线程必须保留它的线程ID、退出状态，直到其它线程对它调用了pthread_join。
5、void pthread_exit(void *status); // 终止线程

#include <cstdio>
#include <iostream>
#include <pthread.h>
using namespace std;

void * ThreadProc(void *arg) { // 线程执行体
    int c = *((int*)arg);
    while (c < 10) {
        cout << c++ << endl;
        sleep(1);
    }
}

int main() {
    pthread_t tpid;
    int arg = 1;
    int ret = pthread_create(&tpid, NULL, ThreadProc, (void *)&arg);
    if (ret != 0) {
        cout << "pthread_create error" << endl;
        return 0;
    }
    if (pthread_join(tpid, NULL))
        return -1;

    return 0;
}
```



## 3.3 线程互斥&同步

一个线程在访问资源未结束时，其他线程不能访问资源。在多线程编程时，要解决数据访问的互斥与同步，最常见的方法是加锁。

### 信号量
一个特殊类型的变量

```c
// 二元信号量：一个线程独占访问的资源。
// 多元信号量：一个初始值为N的信号量允许被N个线程并发访问。
int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);	// 阻塞等待信号量，当信号量值大于0时，信号量减1，向下执行。
int sem_trywait(sem_t *sem);
int sem_post(sem_t *sem);	// 释放信号量，信号量值加1。
int sem_getvalue(sem_t *sem, int *sval)
int sem_destroy(sem_t *sem);
```

### 互斥量/锁

与二元信号量很相似。区别是互斥量由哪个线程获取，那个线程就负责释放。

```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutex_attr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t * mutex,const struct timespec *tsptr);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

### 读写锁

读写锁有三种状态：自由、共享、独占。

```c
// 自由状态下（无读者写者），能以共享/独占方式获取（被读/被写）。
// 共享状态下（被读），能以共享方式再被获取（被读）。 
// 独占状态下（被写），不能被获取。
int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_timedrdlock(pthread_rwlock_t * rwlock, const struct timespec *abstime);
int pthread_rwlock_timedwrlock(pthread_rwlock_t * rwlock, const struct timespec *abstime);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
```

### 递归锁

也叫可重入锁，同一个线程可以多次获取同一个递归锁，不会产生死锁。

### 条件变量

阻塞线程，避免线程不断轮训，类似于一个栅栏。一个条件变量可以被多个线程等待，当条件变量被唤醒，所有的线程可以一起恢复执行。

```c
int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timewait(pthread_cond_t *cond, pthread_mutex *mutex, const timespec *abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_destroy(pthread_cond_t *cond);
```

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
data_type data;

void *product(void *arg) {
    while(1) {
        if (需要生产) {
            pthread_mutex_lock(&lock);
            push_node(data);
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&cond);
        }
        sleep(1);
    }
}

void *consumer(void *arg) {
    while(1) {
        pthread_mutex_lock(&lock);
        while(-1 == pop_node(&data)) { // 为空
            pthread_cond_wait(&cond, &lock); // 阻塞等待，解锁；唤醒执行，加锁。
        }
        func(data); // 执行业务
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, product, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
```

### 死锁

死锁指的是，两个以上线程在执行过程中，因争夺资源而造成一种互相等待的现象，若无外部处理，将会无限等待下去。死锁本质上就是一个线程在请求锁的时候，永远也请求不到。死锁的危险始终存在，应该在程序编写的时候尽量减少死锁存在的范围。

- 死锁发生的情况：  1、忘记释放锁；2、单线程重复申请锁；3、多线程申请多把锁，造成相互等待；

```c++
void process1() {
    mutex1.enter(); // 步骤1
    mutex2.enter(); // 步骤3
    do_Something;
    mutex2.leave();
    mutex1.leave();
}
void process2() {
    mutex2.enter(); // 步骤2
    mutex1.enter(); // 步骤4
    do_Something;
    mutex1.leave();
    mutex2.leave();
}
```

- 死锁问题排查：通过gdb pstack命令可查看进程的栈跟踪，多次对比线程堆栈，查看哪些线程一直处于等锁状态，进一步查看栈帧相关变量，结合代码推断确认哪些线程死锁。coredump文件，依据堆栈可同样分析。



# 四、套接字

网络层的“ip地址”可以唯一标识网络中的主机，而传输层的“协议+端口”可以唯一标识主机中的应用程序。

> 1. 服务端先通过socket()创建一个套接字，返回一个唯一描述符，再通过bind()把一个IP+端口绑定到套接字上，再调用listen()来监听这个套接字。
> 2. 客户端也通过socket()创建一个套接字，通过connect()指定地址向服务端发起连接请求。服务端监听接收到请求后，通过accept()完成连接。
> 3. 之后两端通过read()/write()或recv()/send()进行I/O操作，结束后close()关闭套接字。

* int **socket**(int domain, int type, int protocol);	
* int **bind**(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
* int **listen**(int sockfd, int backlog);
* int **connect**(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
* int **accept**(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
* ssize_t **recv**(int sockfd, void *buf, size_t len, int flags);
* ssize_t **send**(int sockfd, const void *buf, size_t len, int flags);
* ssize_t **read**(int fd, void *buf, size_t count);
* ssize_t **write**(int fd, const void *buf, size_t count);
* int **close**(int fd);



# 五、Linux内存

- Linux虚拟内存分布（高地址-低地址，内核空间：1G、用户空间：3G）
  - 栈：函数局部变量空间，一般为8M。
  - 文件映射区：动态库、共享内存，可通过mmap函数分配。
  - 堆：动态内存，通过malloc/free管理，堆顶位置可通过brk函数调整。
  - 数据段：bss段（未初始化或初始化为0的静态/全局变量）、data段（初始化的静态/全局变量）
  - 只读段：代码段、rodata段（字符常量和宏定义常量）

- 进程栈：也可叫主线程栈，就是虚拟地址空间中的栈区。进程栈大小是执行时增长的，系统默认的最大值8M，可通过ulimit查看和设置。
- 线程栈：其他线程栈是在主线程的堆中通过mmap分配的，大小固定，默认为8M，可通过pthread_attr_setstacksize接口来设置线程栈的大小。所以每个线程栈空间都是独立的。

Linux较Windows的内存管理区别：在linux中程序被关闭，占用的内存不会归还物理内存，而是用来做缓存。当物理内存有空闲时，优先使用物理内存（所以当使用 一段时间后，即使有很大内存也会被占用）。这样做的好处是，启动那些刚启动的程序，或是存取刚存取的数据，效率速度会比较快，适用于服务器的场景。

- free 查看系统内存使用情况

```
             total       used       free     shared    buffers     cached
Mem:     131916676  130603592    1313084    1539580    3569100   42805216
-/+ buffers/cache:   84229276   47687400

total：总物理内存 used：已使用物理内存 free：未使用物理内存 buffer/cache：缓存
total = used + free
```

- cat proc/500/maps 查看进程的虚拟地址空间使用情况
- cat proc/500/status 查看进程的状态信息
- cat proc/meminfo 查看操作系统的内存使用情况
