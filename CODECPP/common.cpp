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

static void *ThreadProc(void *arg)
{
	int c = *((int*)arg);
	while (c < 10) {
		LOGINFO("%d", c++);
		sleep(1);
	}
	return NULL;
}

void CreateThread()
{
	pthread_t tpid;
	int arg = 1;
	int ret = pthread_create(&tpid, NULL, ThreadProc, (void *)&arg);
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




