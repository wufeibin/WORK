#ifndef __COMMON_H
#define __COMMON_H

// C常用头文件
#include <stdio.h> 
#include <stdlib.h>
#include <stddef.h> 
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

// C++常用头文件
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <algorithm>
#include <memory>
#include <initializer_list>

using namespace std;

#define LOG(level, format, ...) Log(level, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGERR(format, ...) Log("LOG_ERROR", __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGINFO(format, ...) Log("LOG_INFO", __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGDBG(format, ...) Log("LOG_DEBUG", __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

void Log(const char *level, const char *file, const int line, const char *func, const char *format, ...);

void CreateThread();


// 函数指针回调
void CallbackTest();
typedef int (*FUNC_PTR)(int, string);
class CallBack {
public:
    CallBack() : m_call_back_ptr(nullptr) {};
    ~CallBack() {};
    void Register(FUNC_PTR call_back_ptr);
    void Test();
private:
    FUNC_PTR m_call_back_ptr;
};

#endif