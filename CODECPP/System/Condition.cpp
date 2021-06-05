#include "../common.h" 

/* 
线程同步典型的案例即为生产者消费者模型，而借助条件变量来实现这一模型，是比较常见的一种方法。假定有两个线程，一个模拟生产者行为，一个模拟消费者行为。
两个线程同时操作一个共享资源（一般称之为汇聚），生产者向其中添加产品，消费者从中消费掉产品。
 */

struct msg {
    struct msg *next;
    int num;
};
struct msg *head;

// 静态初始化 一个条件变量 和 一个互斥变量，可以代替init函数
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock_product = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *p)
{
    struct msg *mp;
    while (1) {
        mp = (struct msg *)malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1; // 生产一个产品
        LOGINFO("Produce = %d", mp->num);

        pthread_mutex_lock(&lock_product);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock_product);

        pthread_cond_signal(&has_product); // 将等待在该条件变量上的一个线程唤醒
        sleep(rand() % 2);
    }
}

void *consumer(void *p)
{
    struct msg *mp;
    while (1) {
        pthread_mutex_lock(&lock_product);
        while (head == NULL) { // 数据资源为空
            pthread_cond_wait(&has_product, &lock_product); // 阻塞等待，解锁；唤醒执行，加锁。
        }
        mp = head;      
        head = mp->next; // 消费一个产品
        pthread_mutex_unlock(&lock_product);

        LOGINFO("Consume = %d", mp->num);
        free(mp);
        sleep(rand() % 2);
    }
}

int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
    pthread_t pid, cid;
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    LOGINFO("main end ...");
    return 0;
}

/* 
wufeibindeMacBook-Pro:System wufeibin$ g++ -std=c++11 Condition.cpp
wufeibindeMacBook-Pro:System wufeibin$ ./a.out 
[LOG_INFO][2021-06-05 22:05:28][4396350976][Condition.cpp:56][main] main start ...
[LOG_INFO][2021-06-05 22:05:28][123145437642752][Condition.cpp:24][producer] Produce = 808
[LOG_INFO][2021-06-05 22:05:28][123145438179328][Condition.cpp:48][consumer] Consume = 808
[LOG_INFO][2021-06-05 22:05:29][123145437642752][Condition.cpp:24][producer] Produce = 659
[LOG_INFO][2021-06-05 22:05:29][123145437642752][Condition.cpp:24][producer] Produce = 273
[LOG_INFO][2021-06-05 22:05:29][123145438179328][Condition.cpp:48][consumer] Consume = 659
[LOG_INFO][2021-06-05 22:05:29][123145437642752][Condition.cpp:24][producer] Produce = 879
[LOG_INFO][2021-06-05 22:05:30][123145438179328][Condition.cpp:48][consumer] Consume = 879
 */