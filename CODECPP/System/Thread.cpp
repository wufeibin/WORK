#include "../common.h" 

class ThreadMsg {
public:
    ThreadMsg(int i, string desc) : index(i), description(desc) {}
    ~ThreadMsg() {}
    void print() { LOGINFO("index:%d, description:%s", index, description.c_str()); }
private:
    int index;
    string description;
};

class ThreadDemo {
public:
    ThreadDemo();
    ~ThreadDemo();
    static ThreadDemo &Instance();
    void Run();
    void Stop();
    void ThreadBody();
    void MsgPush(std::shared_ptr<ThreadMsg> &msg);

private:
    std::thread threadObj;
    volatile bool isRunning {false};
    std::mutex msgMutex;
    std::queue<std::shared_ptr<ThreadMsg>> threadMsg_;
};

static void *ThreadProc1(void *arg)
{
    int cnt = *((int*)arg);
    while (cnt < 5) {
        LOGINFO("running %d", cnt++);
        sleep(1);
    }

    if (true) { // 测试demo
        LOGINFO("ThreadDemo test!");
        std::shared_ptr<ThreadMsg> msg = std::make_shared<ThreadMsg>(1, "threadMsg1");
        ThreadDemo::Instance().MsgPush(msg);
    }

    return NULL;
}

void CreateThread()
{
    pthread_t tpid;
    int arg = 1;
    int ret = pthread_create(&tpid, NULL, ThreadProc1, (void *)&arg);
    if (ret != 0) {
        LOGINFO("pthread_create error");
        return;
    }
    if (pthread_join(tpid, NULL)) { // 阻塞等待线程释放
        return;
    }
}

ThreadDemo::ThreadDemo()
{
    
}

ThreadDemo::~ThreadDemo()
{
    
}

ThreadDemo &ThreadDemo::Instance()
{
    static ThreadDemo ins;
    return ins;
}

void ThreadDemo::Run()
{
    isRunning = true;
    threadObj = std::thread([]() {
        ThreadDemo::Instance().ThreadBody();
    });
}

void ThreadDemo::Stop()
{
    isRunning = false;
    if (threadObj.joinable()) {
        threadObj.join();
    }
}

void ThreadDemo::ThreadBody()
{
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 当前线程休眠1000毫秒
        LOGINFO("running");
        std::lock_guard<std::mutex> lk(msgMutex);
        while (!threadMsg_.empty()) {
            const auto msg = threadMsg_.front();
            msg->print();
            threadMsg_.pop();
        }
    }
}

void ThreadDemo::MsgPush(std::shared_ptr<ThreadMsg> &msg)
{
    std::lock_guard<mutex> lk(msgMutex);
    threadMsg_.push(msg);
}

int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
    ThreadDemo::Instance().Run();
    CreateThread();
    ThreadDemo::Instance().Stop();
    LOGINFO("main end ...");
    return 0;
}

/* 
wufeibindeMacBook-Pro:System wufeibin$ g++ -std=c++11 Thread.cpp
wufeibindeMacBook-Pro:System wufeibin$ ./a.out 
[LOG_INFO][2021-06-05 22:03:36][4457020928][Thread.cpp:115][main] main start ...
[LOG_INFO][2021-06-05 22:03:36][123145434861568][Thread.cpp:34][ThreadProc1] running 1
[LOG_INFO][2021-06-05 22:03:37][123145434861568][Thread.cpp:34][ThreadProc1] running 2
[LOG_INFO][2021-06-05 22:03:37][123145434324992][Thread.cpp:97][ThreadBody] running
[LOG_INFO][2021-06-05 22:03:38][123145434861568][Thread.cpp:34][ThreadProc1] running 3
[LOG_INFO][2021-06-05 22:03:38][123145434324992][Thread.cpp:97][ThreadBody] running
[LOG_INFO][2021-06-05 22:03:39][123145434861568][Thread.cpp:34][ThreadProc1] running 4
[LOG_INFO][2021-06-05 22:03:39][123145434324992][Thread.cpp:97][ThreadBody] running
[LOG_INFO][2021-06-05 22:03:40][123145434324992][Thread.cpp:97][ThreadBody] running
[LOG_INFO][2021-06-05 22:03:40][123145434861568][Thread.cpp:39][ThreadProc1] ThreadDemo test!
[LOG_INFO][2021-06-05 22:03:41][123145434324992][Thread.cpp:97][ThreadBody] running
[LOG_INFO][2021-06-05 22:03:41][123145434324992][Thread.cpp:7][print] index:1, description:threadMsg1
[LOG_INFO][2021-06-05 22:03:41][4457020928][Thread.cpp:119][main] main end ...
 */