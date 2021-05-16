#include "common.h" 

void Log(const char *level, const char *file, const int line, const char *func, const char *format, ...)
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
    printf("[%s][%s][%s:%d][%s] %s\n", level, log_time, file, line, func, fmt_str);
#endif
}


static void *ThreadProc1(void *arg)
{
    int c = *((int*)arg);
    while (c < 5) {
        LOGINFO("%d", c++);
        sleep(1);
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


static int CallbackFunc(int i, string str)
{
    LOGINFO("%d, %s", i, str.c_str());
    return 0;
}

void CallbackTest()
{
    CallBack cb;
    cb.Register(&CallbackFunc);
    cb.Test();
}

void CallBack::Register(FUNC_PTR call_back_ptr)
{
    m_call_back_ptr = call_back_ptr;
}

void CallBack::Test()
{
    if (m_call_back_ptr) {
        (*m_call_back_ptr)(1, "test1");
        m_call_back_ptr(1, "test2");
    }
}



/*

#include <iostream>
#include <vector>
#include <chrono>
#include "ThreadPool.h"

int main()
{
    // create thread pool with 4 worker threads
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}


调用：
DemoThread::Instance().Run();

std::shared_ptr<KpiKafkaMsg> msg = std::make_shared<KpiKafkaMsg>();
KpiManager::Instance().MsgPush(msg);

std::thread rptThread_;
volatile bool isRunning_{false};
std::vector<std::shared_ptr<KpiMsg>> kpiMsg_; // queuing kpi msg

DemoThread();
~DemoThread();
static DemoThread &Instance();


void DemoThread::Run()
{
    isRunning_ = true;
    rptThread_ = std::thread([]() {
        DemoThread::Instance().threadBody();
    });
}

void DemoThread::Stop()
{
    isRunning_ = false;
    if (rptThread_.joinable()) {
        rptThread_.join();
    }
}

void DemoThread::ThreadBody()
{
    while (isRunning_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 当前线程休眠1000毫秒
        std::lock_guard<std::mutex> lk(kpiMux_);
        for (const auto &msg : kpiMux_) {
            msg->report();
        }
    }
}

void KpiManager::MsgPush(std::shared_ptr<KpiMsg> &msg)
{
    std::lock_guard<std::mutex> lk(kpiMux_);
    kpiMsg_.push_back(msg);
}


*/







