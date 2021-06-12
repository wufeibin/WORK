#ifndef __CPP_CLASS_H
#define __CPP_CLASS_H
#include "common.h" 

class SalesData;

// 辅助类
class Help {
public:
    Help() : data(0) {};
    ~Help() {};
    void SalesDataFriFunc(const SalesData &obj);
private:
    int data;
};

// C++类特性示例
class SalesData {
public:
    SalesData() = default; // 编译器发现类没有定义构造函数时，会自动合成一个默认构造函数；如果有了自定义构造函数，还需要默认构造函数，则通过则参数列表后加 = default来要求编译器生产。
    SalesData(const string &name, double p) : m_book_name(name), m_book_price(p) {}
    explicit SalesData(const string &name) : m_book_name(name) {} // explicit阻止隐式转换
    ~SalesData() {}

    static void AddBookNum();

    string GetBookName() const;

    void UselessFunc() = delete; // "=delete"表示这个函数被定义为deleted，该成员函数不能再被调用。

    inline void PrintBookName() { // 显式内联，类内部定义的成员函数自动inline，可省略
        LOGINFO("%s", m_book_name.c_str());
    }

    // 通过友元声明，类可以允许其他类或者函数访问它的非公有成员。但破坏封装性，不推荐使用。
    friend void SalesDataFriFunc(const SalesData &obj);
    friend void Help::SalesDataFriFunc(const SalesData &obj);
    friend class Help;

private:
    string m_book_name;
    double m_book_price = 0.0;
    static unsigned m_book_num;
};
void SalesDataFriFunc(const SalesData &obj);


#endif