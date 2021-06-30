#include <sys/select.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 

/* 
void FD_ZERO(fd_set *fdset); // 清空集合
void FD_SET(int fd, fd_set *fdset); // 将一个给定的文件描述符加入集合之中
void FD_CLR(int fd, fd_set *fdset); // 将一个给定的文件描述符从集合中删除
int FD_ISSET(int fd, fd_set *fdset); // 检查集合中指定的文件描述符是否可以读写

// 监视并等待多个文件描述符的属性变化（可读、可写或错误异常）。
// 调用后select()函数会阻塞，直到有描述符就绪（有数据可读、有数据可写、有错误异常），或者超时，函数才返回。当select()函数返回后，可以通过遍历fdset，来找到就绪的描述符。
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
1、nfds: 要监视的文件描述符的范围，一般取监视的最大描述符数+1。
2、readfds: 监视的可读描述符集合
3、writefds: 监视的可写描述符集合
4、exceptfds: 监视的错误异常描述符集合
5、timeout: 超时时间，它告知内核等待所指定描述字中的任何一个就绪可花多少时间，timeval结构用于指定这段时间的秒数和微秒数。
    struct timeval {
        time_t tv_sec; // 秒
        suseconds_t tv_usec; // 微秒
    };
 */
int main(int argc, char *argv[])
{
    int ret = mkfifo("test_fifo", 0666); // 创建有名管道
    if (ret != 0) {
        perror("mkfifo");
    }
    
    int fd = open("test_fifo", O_RDWR); // 读写方式打开管道
    if (fd < 0) {
        perror("open fifo");
        return -1;
    }

    fd_set rfds;
    struct timeval tv;
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);   // 标准输入描述符 0 加入集合
        FD_SET(fd, &rfds);  // 有名管道描述符 fd 加入集合
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        // 监视并等待多个文件描述符的属性变化（是否可读），没有属性变化，这个函数会阻塞，直到有变化才往下执行，这里没有设置超时。
        // FD_SETSIZE 为 <sys/select.h> 的宏定义，值为 1024
        ret = select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
        //ret = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
 
        if (ret == -1) {
            perror("select");
        } else if (ret > 0) { // 准备就绪的文件描述符
            char buf[100] = {0};
            if (FD_ISSET(0, &rfds)) { // 标准输入
                read(0, buf, sizeof(buf));
                printf("read from stdin : %s\n", buf);
                
            } else if(FD_ISSET(fd, &rfds)) { // 有名管道
                read(fd, buf, sizeof(buf));
                printf("read from fifo : %s\n", buf);
            }
        } else if (ret == 0) { // 超时
            printf("time out\n");
        }
    }
    return 0;
}