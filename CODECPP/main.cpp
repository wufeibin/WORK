#include "common.h"
#include "cpp_class.h"
#include "cpp_basic.h"
#include "file.h"

/*
 * 类型命名风格：
 * 【大驼峰】类类型、结构体类型、枚举类型、联合体类型、作用域名称
 * 【大驼峰】函数（包括全局函数，作用域函数，成员函数）
 * 【小驼峰】全局变量（包括全局和命名空间域下的变量，类静态变量）、局部变量、函数参数、类/结构体/联合体中的成员变量 
 * 【全大写，下划线分割】宏、常量、枚举值、goto标签
 */


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

int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
    CallbackTest();
    LOGINFO("main end ...");
    return 0;
}


/* 线程池
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

*/