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

int main(int argc, char *argv[])
{
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

/* 
wufeibindeMacBook-Pro:System wufeibin$ g++ Daemon.cpp
wufeibindeMacBook-Pro:System wufeibin$ ./a.out
wufeibindeMacBook-Pro:System wufeibin$ ps -ef  |grep a.out
  501 54270     1   0  9:24下午 ??         0:00.00 ./a.out
wufeibindeMacBook-Pro:System wufeibin$ cat /tmp/daemon.log
This is a daemon:  Sat Jun  5 21:24:36 2021
This is a daemon:  Sat Jun  5 21:25:36 2021
 */