#include <sys/select.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// IO模型测试demo
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
    
    while (1) {
        char str[] = "this is test\n";
        write(fd, str, strlen(str)); // 往管道里写内容
        printf("write to fifo : %s\n", str);
        sleep(5);
    }
    return 0;
}