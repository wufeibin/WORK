#include "thread.h" 

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
        LOGERR("pthread_create error");
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