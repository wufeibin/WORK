#include <poll.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* 
int poll(struct pollfd *fds, nfds_t nfds, int timeout); // 监视并等待多个文件描述符的属性变化。
1、fd：每一个pollfd结构体指定了一个被监视的文件描述符，可以传递多个结构体，指示poll()监视多个文件描述符。
    struct pollfd {
        int fd; // 文件描述符
        short events; // 等待的事件
        short revents; // 实际发生了的事件
    }; 
    events：监视该文件描述符的事件掩码
        处理输入：
        POLLIN 普通或优先级带数据可读
        POLLRDNORM 普通数据可读
        POLLRDBAND 优先级带数据可读
        POLLPRI 高优先级数据可读
        处理输出：
        POLLOUT 普通或优先级带数据可写
        POLLWRNORM 普通数据可写
        POLLWRBAND 优先级带数据可写
        处理错误：
        POLLERR 发生错误
        POLLHUP 发生挂起
        POLLVAL 描述字不是一个打开的文件
    revents：文件描述符的操作结果事件掩码。内核在调用返回时设置这个域，events域中请求的任何事件都可能在revents域中返回。

2、nfds: 用来指定第一个参数数组元素个数。

3、timeout: 指定等待的毫秒数，无论I/O是否准备好，poll()都会返回。当等待时间为0时，poll()函数立即返回，为-1则使poll()一直阻塞等待事件发生。

poll()的实现和select()非常相似，只是描述fd集合的方式不同，poll()使用pollfd结构，而select()使用fd_set结构，其他的都差不多。
 */

int main(int argc, char *argv[])
{
    int ret = mkfifo("test_fifo", 0666); // 创建有名管道
    if (ret != 0) {
        perror("mkfifo");
    }
    
    int fd = open("test_fifo", O_RDWR); // 读写方式打开管道
    if(fd < 0){
        perror("open fifo");
        return -1;
    }

    struct pollfd fds[2]; // 监视文件描述符结构体，2个元素
    fds[0].fd = 0;	 // 标准输入
    fds[0].events = POLLIN;	// 普通或优先级带数据可读
    fds[1].fd = fd;	 // 有名管道
    fds[1].events = POLLIN; // 普通或优先级带数据可读

    while (1) {
        // 监视并等待多个文件描述符的属性变化（是否可读）。没有属性变化，这个函数会阻塞，直到有变化才往下执行，这里没有设置超时。
        ret = poll(fds, 2, -1);
        //ret = poll(fds, 2, 1000);
 
        if (ret == -1) {
            perror("poll");
        } else if (ret > 0) { // 准备就绪的文件描述符
            char buf[100] = {0};
            if ((fds[0].revents & POLLIN) ==  POLLIN) { // 标准输入
                read(0, buf, sizeof(buf));
                printf("read from stdin buf : %s\n", buf);
                
            } else if((fds[1].revents & POLLIN) ==  POLLIN) { // 有名管道
                read(fd, buf, sizeof(buf));
                printf("read from fifo buf : %s\n", buf);
            }
        } else if (ret == 0) { // 超时
            printf("time out\n");
        }
    
    }
    
    return 0;
}
