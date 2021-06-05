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
#include <sys/syscall.h>
#include <pthread.h>

// C++常用头文件
#include <iostream>
#include <sstream>
#include <fstream>
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
#include <thread>
#include <initializer_list>

using namespace std;

#define LOG(level, format, ...) Log(level, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGERR(format, ...) Log("LOG_ERROR", __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGINFO(format, ...) Log("LOG_INFO", __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOGDBG(format, ...) Log("LOG_DEBUG", __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

inline void Log(const char *level, const char *file, const int line, const char *func, const char *format, ...)
{
    time_t loacl_time;
    char log_time[128];
    time(&loacl_time);
    strftime(log_time, sizeof(log_time), "%Y-%m-%d %X", localtime(&loacl_time));
    
    // 日志内容格式转换
    va_list ap;
    va_start(ap, format);
    char fmt_str[2048];
    vsnprintf(fmt_str, sizeof(fmt_str), format, ap);
    va_end(ap);

#ifdef FILE_LOG_ON
    const char *log_file = "./main.log";
    FILE *file_fp = fopen(log_file, "a");
    if (file_fp != NULL) {
        fprintf(file_fp, "[%s][%s][%s:%d][%s] %s\n", level, log_time, file, line, func, fmt_str);
        fclose(file_fp);
    } else {
        fprintf(stderr, "[%s][%s][%s:%d][%s] %s\n", level, log_time, file, line, func, fmt_str);
    }
#else
    printf("[%s][%s][%lu][%s:%d][%s] %s\n", level, log_time, (unsigned long)pthread_self(), file, line, func, fmt_str);
#endif
}


/*  
time函数总结：https://www.runoob.com/w3cnote/c-time-func-summary.html
1. clock_t clock(void);
   返回clock函数执行起，处理器时钟所使用的时间。用来程序的某一段的执行时间
2. time_t time(time_t *timer);
   得到当前日历时间或者设置日历时间。timer=NULL时得到当前日历时间（从1970-01-01 00:00:00到现在的秒数）
3. char *ctime(const time_t *timer);
   将日历时间参数timer转换为一个表示本地当前时间的字符串，返回字符串格式：星期,月,日,小时:分:秒,年
4. struct tm *localtime(const time_t *timer);
   使用 timer 的值来填充 tm 结构
5. char *asctime(struct tm *ptr);
   将结构struct tm *ptr所表示的时间以字符串表示，返回字符串格式：星期,月,日,小时:分:秒,年
6. double difftime(time_t time2, time_t time1);
   time2 - time1 两次机器时间差，单位为秒
7. struct tm *gmtime(time_t *timer);
8. time_t mktime(struct tm *timeptr);

struct tm {
    int tm_sec; // 秒，范围从 0 到 59
    int tm_min; // 分，范围从 0 到 59
    int tm_hour; // 小时，范围从 0 到 23
    int tm_mday; // 一月中的第几天，范围从 1 到 31
    int tm_mon; // 月，范围从 0 到 11(注意)
    int tm_year; // 自 1900 年起的年数
    int tm_wday; // 一周中的第几天，范围从 0 到 6
    int tm_yday; // 一年中的第几天，范围从 0 到 365
    int tm_isdst; // 夏令时
};

std::chrono 已定义的时间单位
typedef duration <Rep, ratio<3600,1>> hours;
typedef duration <Rep, ratio<60,1>> minutes;
typedef duration <Rep, ratio<1,1>> seconds;
typedef duration <Rep, ratio<1,1000>> milliseconds;
typedef duration <Rep, ratio<1,1000000>> microseconds;
typedef duration <Rep, ratio<1,1000000000>> nanoseconds;
 */

inline uint64_t GetCurrentTime()
{
    auto time_now = std::chrono::system_clock::now();
    // time_since_epoch()用来获得1970年1月1日到time_point时间经过的duration
    auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch());
    return duration_in_ms.count();
}

inline void ChronoTimeDemo()
{
    chrono::minutes mins{2}; // 2分钟
    chrono::seconds secs{3}; // 3秒钟
    chrono::milliseconds mills{500}; // 500毫秒
    auto dul = secs - mills; // 两者差值，单位默认转到更小的
    chrono::duration_cast<chrono::seconds>(mins).count(); // 2分钟换算为120秒 

    chrono::system_clock::time_point time_point1 = chrono::system_clock::now(); // 获取当前时间
    time_t time1 = chrono::system_clock::to_time_t(time_point1); // 转换为旧式接口，单位:秒
    chrono::system_clock::time_point time_point2 = chrono::system_clock::now(); // 获取当前时间
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_point2 - time_point1);
    LOGINFO("%d", duration_ms.count());
}

#endif