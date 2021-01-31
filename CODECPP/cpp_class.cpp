#include "cpp_class.h"

void Help::SalesDataFriFunc(const SalesData &obj)
{
    LOGINFO("%s", obj.m_book_name.c_str());
}


unsigned SalesData::m_book_num = 0;
void SalesData::AddBookNum()
{
    m_book_num++;
}

string SalesData::GetBookName() const
{
    return m_book_name;
}

void SalesDataFriFunc(const SalesData &obj)
{
    LOGINFO("%s", obj.m_book_name.c_str());
}

// 智能指针。当您想要一个指向对象的单个指针时，请使用unique_ptr，该指针在销毁该单个指针时将被回收。如果需要多个指向同一资源的指针，请使用shared_ptr。
void UsePtr()
{
    // c++11 条款21：尽量使用std::make_unique和std::make_shared而不直接使用new
    unique_ptr<SalesData> p1(new(nothrow) SalesData());
    unique_ptr<SalesData> p2 = make_unique<SalesData>();

    shared_ptr<SalesData> p3(new(nothrow) SalesData());
    shared_ptr<SalesData> p4 = make_shared<SalesData>();

    if (p4) {
        p4->PrintBookName();
    }
}