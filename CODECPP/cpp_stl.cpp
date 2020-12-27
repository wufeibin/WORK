#include "cpp_stl.h"

// stringstream通常是用来做数据转换
void UseStringStream()
{
    std::stringstream stream;
    std::string result;
    int i = 1000;
    stream << i;  // 将int输入流
    stream >> result;
    LOGINFO("result:%s", result.c_str());
}