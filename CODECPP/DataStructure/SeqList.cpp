// 顺序表
#include<iostream>
#include<vector>
using namespace std;

const size_t ListInitCapacity = 50;

template<typename Type>
class SeqList {
public:
    SeqList(size_t cap = ListInitCapacity);
    ~SeqList();
    void push_back(const Type &key);
    void push_front(const Type &key);
    void insert(size_t pos, const Type &key);
    void pop_back();
    void pop_front();
    void delete_pos(size_t pos);
    void delete_val(const Type &key);
    void clear();

    std::vector<int> find(const Type &key);
    const int length();
    void swap(size_t pos1, size_t pos2);
    void sort();
    void reverse();
    void print();

private:
    Type *element;
    size_t capacity;
    size_t size;
};

template<typename Type>
SeqList<Type>::SeqList(size_t cap)
{
    element = new Type[cap];
    capacity = cap;
    size = 0;
}

template<typename Type>
SeqList<Type>::~SeqList()
{
    delete[] element;
    std::cout << "析构函数" << std::endl;
}

// 在尾部添加元素
template<typename Type>
void SeqList<Type>::push_back(const Type &key)
{
    if (size < capacity) {
        element[size++] = key;
    } else {
        std::cerr << "空间已满，不能添加" << std::endl;
    }
}

// 在头部添加元素
template<typename Type>
void SeqList<Type>::push_front(const Type &key)
{
    if (size < capacity) {
        for (int i = size; i != 0; --i) {
            element[i] = element[i - 1];
        }
        element[0] = key;
        ++size;
    } else {
        std::cerr << "空间已满，不能添加" << std::endl;
    }
}

// 在指定位置添加元素
template<typename Type>
void SeqList<Type>::insert(size_t pos, const Type &key)
{
    if (size < capacity) {
        for (int i = size; i != pos-1; --i) {
            element[i] = element[i - 1];
        }
        element[pos - 1] = key;
        ++size;
    } else {
        std::cout << "容量已满或添加位置不在范围内" << std::endl;
    }
}

// 删除尾部元素
template<typename Type>
void SeqList<Type>::pop_back()
{
    if (size != 0) {
        --size;
    }
}

// 删除头部元素
template<typename Type>
void SeqList<Type>::pop_front()
{
    if (size != 0) {
        for (int i = 0; i != size; ++i) {
            element[i] = element[i + 1];
        }
        --size;
    }
}

// 删除指定位置的元素，从1开始计数
template<typename Type>
void SeqList<Type>::delete_pos(size_t pos)
{
    if (pos > size || pos < 1) {
        std::cout << pos << std::endl;
        std::cerr << "位置不在范围内" << std::endl;
    } else {
        if (pos == size) {
            pop_back();
        } else {
            for (int i = pos - 1; i != size - 1; ++i) {
                element[i] = element[i + 1];
            }
            --size;
        }
    }
}

// 删除指定大小的所有元素
template<typename Type>
void SeqList<Type>::delete_val(const Type &key)
{
    int i = 0, temp = 0;
    vector<int> obj = find(key);
    while (i != obj.size()) {
        delete_pos(obj[i] - temp);
        ++i;
        ++temp;
    }
}

template<typename Type>
void SeqList<Type>::clear()
{
    while (size) {
        element[--size] = NULL;
    }
}

// 找到指定大小的所有元素，并返回所在位置，从1计数
template<typename Type>
std::vector<int> SeqList<Type>::find(const Type &key)
{
    int pos = 1;
    vector<int> obj;
    for (int i = 0; i != size;++i) {
        if (element[i] != key) {
            ++pos;
        } else {
            obj.push_back(pos);
            ++pos;
        }
    }
    
    std::cout << "SeqList find : ";
    for (auto i : obj) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return obj;
}

template<typename Type>
const int SeqList<Type>::length()
{
    return size;
}

template<typename Type>
void SeqList<Type>::swap(size_t pos1, size_t pos2)
{
    int temp = 0;
    temp = element[pos1];
    element[pos1] = element[pos2];
    element[pos2] = temp;
}

template<typename Type>
void SeqList<Type>::sort()
{
    if (size > 1) {
        for (int i = 1; i != size; ++i) {
            for (int j = i; j != 0; --j) {
                if (element[j] < element[j - 1]) {
                    swap(j, j - 1);
                }
            }
        }
    }
    return;
}

template<typename Type>
void SeqList<Type>::reverse()
{
    int temp = 0;
    if (size>1) {
        for (int i = 0, j = size - 1; i < j; ++i, --j) {
            swap(i, j);
        }
    }
}

template<typename Type>
void SeqList<Type>::print()
{
    std::cout << "SeqList print : ";
    for (int i = 0; i != size;++i) {
        std::cout << element[i] << " ";
    }
    std::cout << std::endl;
}



int main()
{
    SeqList<int> testList;
    int array[10] = {7, 3, 1, 4, 8, 2, 9, 10, 5, 6};
    for (int i = 1; i <= 10; ++i) {
        testList.insert(i, array[i - 1]);
    }
    testList.print();

    testList.push_back(11);
    testList.push_front(11);
    testList.print();

    testList.find(11);
    testList.delete_pos(5);
    testList.delete_val(11);
    testList.pop_back();
    testList.pop_front();
    testList.print();

    testList.sort();
    testList.reverse();
    testList.print();
    return 0;
}

/* 
SeqList print : 7 3 1 4 8 2 9 10 5 6 
SeqList print : 11 7 3 1 4 8 2 9 10 5 6 11 
SeqList find : 1 12 
SeqList find : 1 11 
SeqList print : 3 1 8 2 9 10 5 
SeqList print : 10 9 8 5 3 2 1 
析构函数
 */