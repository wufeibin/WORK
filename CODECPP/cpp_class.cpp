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
