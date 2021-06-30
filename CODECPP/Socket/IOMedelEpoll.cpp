#include <sys/epoll.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* 
// 生成一个epoll专用的文件描述符
1、int epoll_create(int size);

// epoll的事件注册函数，它不同于select()是在监听事件时告诉内核要监听什么类型的事件，而是先注册要监听的事件类型。
2、int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
epfd: epoll专用的文件描述符，epoll_create()的返回值
op: 表示动作
    EPOLL_CTL_ADD：注册新的fd到epfd中；
    EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
    EPOLL_CTL_DEL：从epfd中删除一个fd；
fd: 需要监听的文件描述符
event: 内核要监听的事件，struct epoll_event 结构如下：
    typedef union epoll_data { // 保存触发事件的某个文件描述符相关的数据
        void *ptr;
        int fd;
        __uint32_t u32;
        __uint64_t u64;
    } epoll_data_t;

    struct epoll_event {
        __uint32_t events; // Epoll events
        epoll_data_t data; // User data variable
    };
    events 可以是以下几个宏的集合：
        EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）
        EPOLLOUT：表示对应的文件描述符可以写
        EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
        EPOLLERR：表示对应的文件描述符发生错误
        EPOLLHUP：表示对应的文件描述符被挂断
        EPOLLET ：将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)
        EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

// 等待事件的产生，收集在epoll监控的事件中已经发送的事件，类似于select()调用。
3、int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
    epfd: 文件描述符，epoll_create()的返回值
    events: 分配好的 epoll_event结构体数组，epoll将会把发生的事件赋值到events数组中（events不可以是空指针，内核只负责把数据复制到这个events数组中，不会去帮助我们在用户态中分配内存）。
    maxevents: maxevents告之内核这个events有多大。
    timeout: 超时时间，单位为毫秒，-1时函数为阻塞。
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

    int epfd = epoll_create(10); // 创建一个epoll句柄，参数要大于0
    if (epfd == -1) {
        perror ("epoll_create");
        return -1;
    }

    struct epoll_event event;
    event.data.fd = 0; // 标准输入
    event.events = EPOLLIN; // 表示对应的文件描述符可以读
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event); // 事件注册函数，将标准输入描述符 0 加入监听事件
    if (ret == -1) {
        perror("epoll_ctl");
        return -1;
    }
    
    event.data.fd = fd; // 有名管道
    event.events = EPOLLIN; // 表示对应的文件描述符可以读
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event); // 事件注册函数，将有名管道描述符 fd 加入监听事件
    if (ret == -1) {
        perror("epoll_ctl");
        return -1;
    }

    struct epoll_event wait_event;
    while (1) {
        // 监视并等待多个文件描述符的属性变化（是否可读），没有属性变化，这个函数会阻塞，直到有变化才往下执行，这里没有设置超时。
        ret = epoll_wait(epfd, &wait_event, 2, -1);
        //ret = epoll_wait(epfd, &wait_event, 2, 1000);
        
        if (ret == -1) {
            perror("epoll");
        } else if (ret > 0) { // 准备就绪的文件描述符
            char buf[100] = {0};
            if ((0 == wait_event.data.fd) && (EPOLLIN == wait_event.events & EPOLLIN)) { // 标准输入
                read(0, buf, sizeof(buf));
                printf("read from stdin buf : %s\n", buf);
            } else if ((fd == wait_event.data.fd) && (EPOLLIN == wait_event.events & EPOLLIN)) { // 有名管道
                read(fd, buf, sizeof(buf));
                printf("read from fifo buf : %s\n", buf);
            }
        } else if (ret == 0) { // 超时
            printf("time out\n");
        }
    }
    close(epfd);
    return 0;
}