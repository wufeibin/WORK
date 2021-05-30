#include "common.h"
#include "cpp_class.h"
#include "cpp_basic.h"
#include "thread.h"
#include "file.h"

/*
 * 类型命名风格：
 * 【大驼峰】类类型、结构体类型、枚举类型、联合体类型、作用域名称
 * 【大驼峰】函数（包括全局函数，作用域函数，成员函数）
 * 【小驼峰】全局变量（包括全局和命名空间域下的变量，类静态变量）、局部变量、函数参数、类/结构体/联合体中的成员变量 
 * 【全大写，下划线分割】宏、常量、枚举值、goto标签
 */


int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
    ThreadDemo::Instance().Run();
    CreateThread();
    ThreadDemo::Instance().Stop();

    CallbackTest();
    LOGINFO("main end ...");
    return 0;
}
