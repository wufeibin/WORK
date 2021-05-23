#ifndef __THREAD_H
#define __THREAD_H
#include "common.h"

void CreateThread();

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

#endif