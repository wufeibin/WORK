# 一、C++基础

> [C++ 参考手册](https://zh.cppreference.com)

## 类

**构造函数**、**析构函数**、**拷贝构造**、**赋值函数**是每个类的最基本函数。每个类只有一个析构函数和赋值函数，可以有多个构造函数（包含一个拷贝构造函数和其他的普通构造函数）。对于一个类，编译器会自动产生四个缺省的函数（无参构造、拷贝构造、析构、赋值）。

* 如果一个类没有显式地定义构造函数，编译器会隐式地合成一个默认构造函数，合成的默认构造函数只适合简单的类。如`Base b`调用了默认构造函数。

* 类对象的数据成员是在析构函数执行体之后的隐含阶段被销毁的。

* 非内部数据类型的成员对象（类对象），应采用初始化表方式初始化，提高效率。

* 拷贝构造函数是在对象被创建时调用，而赋值函数只能被存在的对象调用。

  ```c
  String a(“hello”);
  String b(“world”);
  String c = a; // 调用了拷贝构造函数，最好写成 c(a)
  c = b; // 调用了赋值函数 
  ```

* 内置类型之间定义了几种自动转换规则，同样的也能为类类型定义隐式转换规则。如果类的构造函数只有一个实参，则它实际上定义了转换为此类类型的**隐式转换**机制。  

  ```c
  // 比如一个类的构造函数只接受一个int参数，那么就定义了从int类型向这个类隐式转换的规则。在需要用到这个类类型的地方，可以用int类型替换，不需要显式转换。
  // 构造函数默认能够发生隐式自动转换。可以在构造函数声明时在前面加explicit抑制隐式转换。

  // 构造函数：CString(int size){...}
  CString A = 10;
  // 等同于：（构造函数的隐式转换）
  CString temp(10);
  CString A = temp;
  ```

* 通过访问说明符public/private/protect，来达到访问控制，加强封装性。

* 友元：友元函数、友元类。类可以通过友元特性访问其他类的非公有成员，友元特性会破坏封装。

  ```c
  class A {
      // B可以访问A
      friend void B::func();
      friend class B;
  }
  ```

* **函数重载**：同个作用域内，函数名相同，形参列表不同。（不允许两个函数只有返回类型不同）

* **函数覆盖**：派生类虚函数与基类虚函数的函数名和形参相同。

* **函数隐藏**：派生类函数与基类函数名和形参相同，又不是多态的覆盖，则会隐藏屏蔽基类函数。

## 虚函数

C++中虚函数的作用是实现了运行时多态的机制。关于多态，简而言之就是用基类指针指向其派生类对象，然后通过基类指针调用派生类的成员函数。 

![img](https://p-blog.csdn.net/images/p_blog_csdn_net/haoel/EntryImages/20081015/dd01.jpg) ![img](https://p-blog.csdn.net/images/p_blog_csdn_net/haoel/EntryImages/20081015/dd02.jpg)

* 如果一个类有虚函数，或者继承的类有虚函数，则这个类对应1(n)个虚函数表，类中有1(n)个虚函数表指针。虚函数表中存放着所有虚函数的地址，在编译时就确定。（虚表存放在只读数据段）
* 每个派生类对象的内存空间中都有该类的虚表指针和所有成员变量。虚表指针在调用构造函数的函数体执行前被赋值指向虚表，当我们用指针来调用虚函数时，先通过虚表指针找到虚函数表，然后根据虚函数在虚表中的偏移找到对应的函数地址。
* 继承过程中的虚表，基类的虚函数地址都会被覆盖成派生类的虚函数地址。
* 如果是单一继承，则只有一个虚表指针，虚表中存放基类和派生类的虚函数地址。如果是n重继承，则有n个虚表指针，第一个虚表存放基类和派生类的虚函数地址，其它虚表存放派生类的虚函数地址。

```c
//通过对象的地址来取得虚函数表的地址
Base b;
cout << "虚函数表地址：" << (int*)(&b) << endl;
cout << "虚函数表的第一个函数地址：" << (int*)*(int*)(&b) << endl;

typedef void(*Fun)(void);
Fun f = (Fun)*((int*)*(int*)(&b));
f();
```

* 成员函数不在类对象的内存空间中，成员函数本质上是一个包含指向具体对象this指针的普通函数。this指针是一个隐含于非静态成员函数中的特殊指针，它指向调用该成员函数的那个对象。

## const

1. 修饰变量，说明该变量不可以被改变。
2. 修饰指针，指向常量的指针、指针常量。
3. 修饰引用，常用于形参类型，即避免了拷贝和修改。
4. 修饰成员函数，说明该成员函数内不能修改成员变量。

```cpp
class A {
public:
    A() : a(0) {};
    A(int x) : a(x) {}; // 初始化列表

    // const可用于对重载函数的区分
    int getValue(); // 普通成员函数
    int getValue() const; // 常成员函数，不得修改类中的任何数据成员的值
private:
    const int a; // 常对象成员，只能在初始化列表赋值
};

void function() {
    // 对象（不允许将普通引用或指针绑定到const对象，防止通过引用修改对象）
    A b; // 普通对象，可以调用全部成员函数、更新常成员变量
    const A a; // 常对象，只能调用常成员函数
    const A *p = &a; // 常指针
    const A &q = a; // 常引用

    // 指针
    char greeting[] = "Hello";
    char* p1 = greeting; // 指针变量，指向字符数组变量
    const char* p2 = greeting; // 指针变量，指向字符数组常量（常用）
    char* const p3 = greeting; // 常指针，指向字符数组变量
    const char* const p4 = greeting; // 常指针，指向字符数组常量
}

// 函数入参
void function1(const int Var); // 传递过来的参数在函数内不可变
void function2(const char* Var); // 参数指针所指内容为常量
void function3(char* const Var); // 参数指针为常指针
void function4(const int& Var); // 引用参数在函数内为常量

// 函数返回值
const int function5(); // 返回一个常数
const int* function6(); // 返回一个指向常量的指针变量，使用：const int *p = function6();
int* const function7(); // 返回一个指向变量的常指针，使用：int* const p = function7();
```


## static

1. **静态变量**：main函数运行前，在数据段分配内存，未经初始化的静态变量会被程序自动初始化为0。
2. **静态函数**：表明函数的作用范围，仅在定义该函数的文件内才能使用。
3. **静态成员变量**：无论有多少个类对象，静态数据成员在内存中只有一份拷贝，由所有该类的对象共享，可以直接使用类名加作用域运算符(::)直接访问。只能在类中声明，在类外进行定义和初始化，默认初始化为0。
4. **静态成员函数**：静态成员函数只能访问静态数据成员和静态成员函数。静态成员函数属于类，不属于任意一个类对象。静态成员函数没有 this 指针，可以使用 <类名>::<函数名> 访问，也可由类对象使用(./->)访问。

## extern

1. 修饰全局变量

```c
// 定义只能一次，声明可以多次。在一个源文件中声明定义全局变量（下面3种形式都可行），在使用的源文件（或包含的头文件）中声明全局变量后，即可使用。
extern int i; // 声明
extern int i = 0; // 声明并定义
int i; // 声明并定义
int i = 0; // 声明并定义
```

2. 修饰全局函数

```c
// 函数定义和声明的区别是有无函数体，所以定义和声明时可省略extern。在一个源文件中声明定义了全局函数，在源文件（或包含的头文件）中声明全局函数（通常加上extern）后，即可使用。
(extern) void func() { // 声明并定义
    printf("hello\n");
}
(extern) void func();	// 声明
```


3. extern "C"  链接指示符：如果要在一个cpp源文件中要使用一个C的函数，需要告诉编译器使用C语言的方式进行编译和链接。 

```c
//1.h
#ifdef  __cplusplus // __cplusplus是C++中定义的宏，使用后的头文件可兼容c/cpp文件
extern "C" {
#endif
    void func1();
    void func2();
#ifdef  __cplusplus
}
#endif

//1.c
#include "1.h"
void func1(){};
void func2(){};
```

```c
//main.cpp
#include "1.h"
int main() {
    func1();
    func2();
}
```

## 类型转换

**C风格强制类型转换**：

```
TypeName b = (TypeName)a;
```

**C++强制类型转换**：

* static_cast：和C语言风格强制转换的效果一样，没有运行时类型检查来保证转换的安全性。
  * 用于类层次间的上下行转换，下行转换没有运行时类型检测，不安全。（下行类型转换：基类指针转换成派生类指针 ）
  * 用于基本数据类型之间的转换，转换的安全性需要开发者来维护。
  * C++任何的隐式转换都是使用static_cast来实现。

* dynamic_cast：用于类层次间的上下行转换，下行转换有运行时类型检测，转换失败则返回NULL，比static_cast更安全，最为常用。

  ```c++
  Base *pBase = new Base();
  pBase->print();
  Sub *pSub = dynamic_cast<Sub*>(pBase);
  if (pSub != nullptr) {
      pSub->print();
  }
  ```
  
* const_cast：用于修改类型的const属性

  - 常量指针/引用被转化成非常量的指针/引用，并且仍然指向原来的对象。
  - const_cast一般用于修改指针。如const char *p形式。

* reinterpret_cast：常用于指针类型和整形之间的转换

  ```c++
  int *ptr = new int(222);
  uint32_t ptr_addr = reinterpret_cast<uint32_t>(ptr);
  ```

## 补充

-  malloc/free、new/delete

  * malloc是C语言的标准库函数，申请一块内存，返回void*指针。
  * new是C++运算符，申请一块内存，构造对象，并返回该对象的指针。
- 指针和引用

  * 引用是对象的别名，不占用内存空间，必须初始化且不能修改。（有时理解为const指针）
  * 指针是一个对象，存放的是一个地址，来操作地址上的对象。
- 结构体内存对齐规则

  * 第一个数据成员存储offset=0位置，之后每个成员的起始地址需从自己大小的整数倍开始存储。
  * 结构体作成员，以内部的最大基本类型的整数倍地址开始存储。
  * 联合体作成员，以内部的最大基本类型作为size。
  * 结构体的总大小，是内部最宽基本类型的整数倍，不足要补齐。
-  do { } while (0) 作用：帮助定义复杂的宏函数；通过break替换goto，控制程序流。
- volatile 关键字声明的变量，每次访问时都必须从内存中取出值。没有被 volatile 修饰的变量，可能由于编译器的优化，从CPU寄存器中取值，使用 volatile 告诉编译器不应对这样的对象进行优化。
- 内联inline函数相当于宏，在编译期将函数体复制到调用处，但比宏多了类型检测，具有函数的特性。一方面避免了函数调用的开销，提高了运行效率；另一方面会造成代码膨胀，适用于短小且频繁调用的函数。
- 如果表达式既有带符号类型又有无符号类型，带符号类型会自动地转换成无符号类型。
- 含有可变形参的函数：如果实参数量不确定，类型都相同，可以传递一个initializer_list的标准库类型作为参数。



# 二、[STL](https://github.com/steveLauwh/SGI-STL)

C++ 标准模板库（STL）是一套功能强大的 C++ 模板类，提供了通用的模板类和函数，这些模板类和函数可以实现多种流行和常用的算法和数据结构。

## 六大组件

STL六大组件的交互关系：

- Container 通过 Allocator 取得数据储存空间
- Algorithm 通过 Iterator 存取 Container 内容
- Functor 可以协助 Algorithm 完成不同的策略变化
- Adapter 可以修饰或套接 Functor、Iterator

![STL 六大组件](https://img-blog.csdn.net/20160320180158788)

1. **容器**（containers）

   各种数据结构，如vector、list、deque、set、map，用来存放数据。从实现的角度看，STL 容器是一种class template。

2. **算法**（algorithms）

   各种常用算法如sort、search、copy。从实现的角度看，STL 算法是一种function template。

3. **迭代器**（iterators）

   迭代器是容器和算法之间的桥梁，算法通过容器的迭代器来进行操作。迭代器可以看作是一种智能指针，支持原生指针的一般操作，如`*、->、++`等。从实现的角度看，STL 迭代器是一种class template，通过重载`operator*、operator->、operator++`等运算符来实现和原生指针类似的功能。

4. **仿函数**（functors）

   行为类似函数，可做为算法的某种策略。从实作的角度看，仿函数是一种重载了`operator()`的class或class template。

5. **配接器**（adapters）

   一种用来修饰容器或仿函数或迭代器接口的东西。例如 STL 提供的queue和stack，虽然看似容器，其实只能算是一种容器配接器，因为它们的底部完全借重deque，所有动作都由底层的deque供应。改变functor接口者，称为function adapter；改变container接口者，称为container adapter；改变iterator接口者，称为iterator adapter。

6. **配置器**（allocators）

   负责空间配置与管理。从实现的角度看，配置器是一个实现了动态空间配置、空间管理、空间释放的class template。

## vector原理

vector通过一个连续数组存放元素，使用的是堆内存。如果集合已满，再新增数据时，就要分配一块更大的内存，将原来的数据复制过来，释放之前的内存，再插入新增的元素。不同的编译器实现的扩容方式不一样，VS2015中以1.5倍扩容，GCC以2倍扩容。

vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器就都失效了。初始vector的capacity为0，插入第一个元素后capacity增加为1。

## map原理

map 的底层机制是红黑树，红黑树本质是一个二叉搜索树，每个节点要么是红色，要么是黑色，加上一些特性，变成平衡二叉搜索树。

红黑树的插入、删除、查找操作的时间复杂度是 O(logN)。红黑树的高度在 [logN, logN+1]。

- 规则 1：每个节点不是红色，就是黑色；
- 规则 2：根节点必须是黑色；
- 规则 3：如果一个节点是红色，那么它的孩子必须是黑色；
- 规则 4：任何一个节点向下遍历到其叶子节点，所经过的黑色节点必须相等；
- 规则 5：空节点必须是黑色；

```c++
typedef bool _Rb_tree_Color_type;
const _Rb_tree_Color_type _S_rb_tree_red = false;
const _Rb_tree_Color_type _S_rb_tree_black = true;

struct _Rb_tree_node_base
{
    typedef _Rb_tree_Color_type _Color_type;
    typedef _Rb_tree_node_base* _Base_ptr;
    
    _Color_type _M_color;  // 颜色
    _Base_ptr _M_parent;   // 父亲节点
    _Base_ptr _M_left;     // 左孩子节点
    _Base_ptr _M_right;    // 右孩子节点
    
    // 找值最小节点
    static _Base_ptr _S_minimum(_Base_ptr __x)
    {
        while (__x->_M_left != 0) __x = __x->_M_left;
        return __x;
    }
    
    // 找值最大节点
    static _Base_ptr _S_maximum(_Base_ptr __x)
    {
        while (__x->_M_right != 0) __x = __x->_M_right;
        return __x;
    }
}

template <class _Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
    typedef _Rb_tree_node<_Value>* _Link_type;
    _Value _M_value_field;  // 键值
};
```

```C++
template <class _Key, class _Tp, class _Compare, class _Alloc>
class map {
public:
    typedef _Key                  key_type; // 键值类型
    typedef _Tp                   data_type; // 实值类型
    typedef _Tp                   mapped_type;
    typedef pair<const _Key, _Tp> value_type;  // 元素类型(键值/实值)
    typedef _Compare              key_compare; // 键值比较函数

private:
    typedef _Rb_tree<key_type, value_type, 
                   _Select1st<value_type>, key_compare, _Alloc> _Rep_type; // map 的底层机制 RB-tree 
    _Rep_type _M_t;  // red-black tree representing map 以红黑树(RB-tree) 表现 map
    
public:
    typedef typename _Rep_type::iterator iterator;  // map 迭代器
};
```



# 三、C++11特性

## 智能指针

我们不能保证申请的内存被正确释放，所以需要使用智能指针来管理。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域时，类会自动调用析构函数，析构函数会自动释放资源。智能指针通过类模板将基本类型指针封装为类对象指针，并在析构函数里编写delete语句删除指针指向的内存空间，这样内存也被自动释放了。

智能指针实质是一个类模版，定义的对象行为表现像指针，使用时和普通指针类似。对于智能指针都要避免一点：不能将delete作用于非堆的内存。

智能指针类都有一个explicit构造函数，以指针作为参数。因此不能自动将指针转换为智能指针对象，必须显式调用：

```cpp
double *p_reg = new double;
shared_ptr<double> pshared = p_reg; // not allowed (implicit conversion)
shared_ptr<double> pshared(p_reg); // allowed (explicit conversion)
```

STL提供的智能指针：shared_ptr、unique_ptr、weak_ptr、auto_ptr（被摒弃）

1. **shared_ptr**

   允许多个share_ptr指针指向同个对象。每个share_ptr有一个关联的计数器，称为**引用计数**。当拷贝一个share_ptr，计数器会递增；当一个share_ptr被赋新值或share_ptr被销毁，计数器会递减；当一个share_ptr的计数器为0时，它就会自动释放所管理的对象。  

2. **unique_ptr**

   unique_ptr独占所指对象。当程序试图将一个unique_ptr赋值给另一个时，如果源unique_ptr是个临时右值，编译器允许这么做；如果源unique_ptr将存在一段时间，编译器将禁止这么做。


## 移动语义

C++ 程序的一个特点就是需要程序员管理内存，需要的时候申请内存，在合适的时候释放申请的内存。如果没有释放掉申请的内存会造成内存泄漏，多次释放同一块内存会造成程序异常，所以对于指针的操作需要特别小心。如果类中包含指针成员，就需要特别小心拷贝构造函数的编写。

**1、浅拷贝**：增加一个指针，指向一个已经存在的内存，实现了逻辑上的拷贝。

```c++
class HasPtrMem {
    public:
    HasPtrMem() : d(new int(0)) {}
    // HasPtrMem(HasPtrMem &rhs) :d(new int(*rhs.d)) {} 浅拷贝：不定义拷贝构造函数时，编译器生成默认拷贝构造函数
    ~HasPtrMem() { delete d; }
    int *d; // 指针成员
};

void main()
{
    // 两个HasPtrMem对象中的指针都指向了同一块推内存，在析构函数中两次释放内存时就会造成异常。
    HasPtrMem a;
    HasPtrMem b(a); // 拷贝构造
    cout << *a.d << std::endl;
    cout << *b.d << std::endl;
}
```

**2、深拷贝**：申请一块内存，并把数据拷贝到新的内存，实现逻辑和物理上的拷贝。

```c++
class HasPtrMem {
public:
    HasPtrMem() : d (new int(0)) {}
    HasPtrMem(HasPtrMem &rhs) : d (new int(*rhs.d)) {} // 深拷贝：复制构造函数
    ~HasPtrMem() { delete d; }
    int *d;
};

void main()
{
    HasPtrMem a;
    HasPtrMem b(a); // 拷贝构造
    cout << *a.d << std::endl;
    cout << *b.d << std::endl;
}
```

**3、左值与右值**：可以取地址，有名字的是左值；不可以取地址，没有名字的是右值。

`T &&a = returnValue();`，returnValue函数返回一个临时变量，申明一个右值引用，其值等于临时变量的值。returnValue返回的右值在表达式结束后就终结了，但是右值引用让其重获新生，它的生命周期将和右值引用变量一样，直到右值引用变量消亡。如果不使用右值引用：`T b = returnValue(); `，那么就会多一次对象构造和析构开销。

- 右值引用不能绑定到任何左值。`int n = 0; int &&m = n; // 编译错误`

- 左值引用通常不能绑定到右值。`T &e = returnValue(); // 编译错误`


**4、移动构造**：如果使用一个右值去初始化对象，并且对象类实现了以右值为参数的移动构造函数，那么就会触发移动构造。移动构造可以有效的减少无用的拷贝，但是滥用移动构造也会造成问题，在使用移动构造后，就代表不再使用原对象，否则就不应该使用。

```c++
class HugeMem {
public:
    HugeMem(int size) : sz( size > 0 ? size : 1 ) {
        c = new int[sz];
    }
    HugeMem(HugeMem &hm) : sz(hm.sz) {
        c = new int[sz];
        memcpy(c, hm.c, sz * sizeof(int));
    }
    HugeMem(HugeMem &&hm) : sz(hm.sz), c(hm.c) {
        hm.c = nullptr;
    }
    ~HugeMem() { delete[]c; }
    int sz;
    int *c;
};

class HasPtrMem {
public:
    HasPtrMem() : d(new int(0)), hm(1024) { }
    HasPtrMem(HasPtrMem &rhs) : d(new int(*rhs.d)), hm(rhs.hm) {}
    // std::move()可以强制将一个左值或右值转换为右值，等同于类型转换static_cast<T&& >(lvalue)。
    HasPtrMem(HasPtrMem &&rhs) : d(rhs.d), hm(std::move(rhs.hm)) { // 强制转为右值，调用移动构造
        rhs.d = nullptr;
    }
    ~HasPtrMem() { delete d; }
    int *d;
    HugeMem hm;
};

HasPtrMem getTemp()
{
    HasPtrMem temp;
    return temp;
}

void main()
{
    HasPtrMem b(getTemp()); // 移动构造
    std::cout << b.hm.c << std::endl;
}
```

## Lambda表达式

C++11的一大亮点就是引入了Lambda表达式，利用Lambda表达式可以方便地定义和创建匿名函数。

Lambda表达式完整的声明格式：`[capture list] (params list) mutable exception-> return type { function body }`

1. capture list：捕获外部变量列表
2. params list：形参列表
3. mutable指示符：用来说用是否可以修改捕获的变量
4. exception：异常设定
5. return type：返回类型
6. function body：函数体

此外，我们还可以省略其中的某些成分来声明“不完整”的Lambda表达式，常见的有以下几种：

1. `[capture list] (params list) -> return type {function body}`  声明了const类型的表达式，这种类型的表达式不能修改捕获列表中的值。

2. `[capture list] (params list) {function body}` 省略了返回值类型，编译器可以根据规则推断出Lambda表达式的返回类型。

   - 如果function body中存在return语句，则该Lambda表达式的返回类型由return语句的返回类型确定。

   - 如果function body中没有return语句，则返回值为void类型。

3. `[capture list] {function body}`省略了参数列表，类似普通函数中的无参函数。

## 其他特性

- **unordered_map、unordered_set**

    map与unordered_map的用法是一样的。map底层通过红黑树实现；unordered_map底层通过哈希表实现，适用于快速查找，不需要排序的场景。

- **emplace_front、emplace、emplace_back**

    对于顺序容器，C++11引入emplace_front、emplace、emplace_back，分别对应push_front、insert、push_back。

    对于关联容器，也有对应emplace相关函数，map：emplace、emplace_hint；set：emplace、emplace_hint。

    当调用insert成员函数时，我们将元素对象传递给它们，这些对象被拷贝到容器中。而当调用一个emplace成员函数时，则是将参数传递给元素类型的构造函数，emplace在容器管理的内存空间中直接构造元素。emplace相关函数可以**减少内存拷贝和移动**。

    ```c++
    std::vector<President> v1;
    v1.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
    
    std::vector<President> v2;
    v2.emplace_back("Nelson Mandela", "South Africa", 1994);
    ```

- **std::function、std::bind**

    通过std::function对C++中各种可调用实体（普通函数、Lambda表达式、仿函数、类成员函数以及类静态函数等）的封装，形成一个新的可调用的std::function对象。绑定成员函数时须借助std::bind，或者传入*this指针。

    std::bind可以预先把指定可调用实体的某些参数绑定到已有的变量，产生一个新的可调用实体，在回调函数的使用中颇为有用。

    ```C++
    #include <functional>
    
    class Test {
    public:
        int Sum(int x, int y) {
            return x + y;
        }
    };
    
    std::function<int(int, int)> Functional1;
    std::function<int(Test, int, int)> Functional2;
    
    int main()
    {
        Test testObj;
        Functional1 = std::bind(&Test::Sum, testObj, 
                                std::placeholders::_1, std::placeholders::_2); // std::placeholders::_1是一个占位符
        int result = Functional1(1, 2);
    
        Functional2 = &Test::Sum;
        result = Functional2(testObj, 1, 2);
        return 0;
    }
    ```

- **constexpr**

    常量表达式constexpr必须在编译期间计算出它的值并且不可被改变。常量表达式主要是允许一些计算发生在编译时，而不是运行时，得到一定优化。

    定义为constexpr类型的函数都隐式为内联函数。

    ```c++
    constexpr int mf = 20; // 常量表达式
    constexpr int limit = mf + 1; // 常量表达式
    constexpr int sz = size(); // 如果size()是常量表达式则编译通过，否则报错
    ```

    

# 四、Effective C++

1. 视 C++ 为一个语言联邦（C、Object-Oriented C++、Template C++、STL）
2. 宁可以编译器替换预处理器（尽量以 `const`、`enum`、`inline` 替换 `#define`）
3. 尽可能使用 const
4. 确定对象被使用前已先被初始化（构造时赋值（copy 构造函数）比 default 构造后赋值（copy assignment）效率高）
5. 了解 C++ 默默编写并调用哪些函数（编译器暗自为 class 创建 default 构造函数、copy 构造函数、copy assignment 操作符、析构函数）
6. 若不想使用编译器自动生成的函数，就应该明确拒绝（将不想使用的成员函数声明为 private，并且不予实现）
7. 为多态基类声明 virtual 析构函数（如果 class 带有任何 virtual 函数，它就应该拥有一个 virtual 析构函数）
8. 别让异常逃离析构函数（析构函数应该吞下不传播异常，或者结束程序，而不是吐出异常；如果要处理异常应该在非析构的普通函数处理）
9. 绝不在构造和析构过程中调用 virtual 函数（因为这类调用从不下降至 derived class）
10. 令 `operator=` 返回一个 `reference to *this` （用于连锁赋值）
11. 在 `operator=` 中处理 “自我赋值”
12. 赋值对象时应确保复制 “对象内的所有成员变量” 及 “所有 base class 成分”（调用基类复制构造函数）
13. 以对象管理资源（资源在构造函数获得，在析构函数释放，建议使用智能指针，资源取得时机便是初始化时机（Resource Acquisition Is Initialization，RAII））
14. 在资源管理类中小心 copying 行为（普遍的 RAII class copying 行为是：抑制 copying、引用计数、深度拷贝、转移底部资源拥有权（类似 auto_ptr））
15. 在资源管理类中提供对原始资源（raw resources）的访问（对原始资源的访问可能经过显式转换或隐式转换，一般而言显示转换比较安全，隐式转换对客户比较方便）
16. 成对使用 new 和 delete 时要采取相同形式（`new` 中使用 `[]` 则 `delete []`，`new` 中不使用 `[]` 则 `delete`）
17. 以独立语句将 newed 对象存储于（置入）智能指针（如果不这样做，可能会因为编译器优化，导致难以察觉的资源泄漏）
18. 让接口容易被正确使用，不易被误用（促进正常使用的办法：接口的一致性、内置类型的行为兼容；阻止误用的办法：建立新类型，限制类型上的操作，约束对象值、消除客户的资源管理责任）
19. 设计 class 犹如设计 type，需要考虑对象创建、销毁、初始化、赋值、值传递、合法值、继承关系、转换、一般化等等。
20. 宁以 pass-by-reference-to-const 替换 pass-by-value （前者通常更高效、避免切割问题（slicing problem），但不适用于内置类型、STL迭代器、函数对象）
21. 必须返回对象时，别妄想返回其 reference（绝不返回 pointer 或 reference 指向一个 local stack 对象，或返回 reference 指向一个 heap-allocated 对象，或返回 pointer 或 reference 指向一个 local static 对象而有可能同时需要多个这样的对象。）
22. 将成员变量声明为 private（为了封装、一致性、对其读写精确控制等）
23. 宁以 non-member、non-friend 替换 member 函数（可增加封装性、包裹弹性（packaging flexibility）、机能扩充性）
24. 若所有参数（包括被this指针所指的那个隐喻参数）皆须要类型转换，请为此采用 non-member 函数
25. 考虑写一个不抛异常的 swap 函数
26. 尽可能延后变量定义式的出现时间（可增加程序清晰度并改善程序效率）
27. 尽量少做转型动作（旧式：`(T)expression`、`T(expression)`；新式：`const_cast<T>(expression)`、`dynamic_cast<T>(expression)`、`reinterpret_cast<T>(expression)`、`static_cast<T>(expression)`、；尽量避免转型、注重效率避免 dynamic_casts、尽量设计成无需转型、可把转型封装成函数、宁可用新式转型）
28. 避免使用 handles（包括 引用、指针、迭代器）指向对象内部（以增加封装性、使 const 成员函数的行为更像 const、降低 “虚吊号码牌”（dangling handles，如悬空指针等）的可能性）
29. 为 “异常安全” 而努力是值得的（异常安全函数（Exception-safe functions）即使发生异常也不会泄露资源或允许任何数据结构败坏，分为三种可能的保证：基本型、强列型、不抛异常型）
30. 透彻了解 inlining 的里里外外（inlining 在大多数 C++ 程序中是编译期的行为；inline 函数是否真正 inline，取决于编译器；大部分编译器拒绝太过复杂（如带有循环或递归）的函数 inlining，而所有对 virtual 函数的调用（除非是最平淡无奇的）也都会使 inlining 落空；inline 造成的代码膨胀可能带来效率损失；inline 函数无法随着程序库的升级而升级）
31. 将文件间的编译依存关系降至最低（如果使用 object references 或 object pointers 可以完成任务，就不要使用 objects；如果能过够，尽量以 class 声明式替换 class 定义式；为声明式和定义式提供不同的头文件）
32. 确定你的 public 继承塑模出 is-a（是一种）关系（适用于 base classes 身上的每一件事情一定适用于 derived classes 身上，因为每一个 derived class 对象也都是一个 base class 对象）
33. 避免遮掩继承而来的名字（可使用 using 声明式或转交函数（forwarding functions）来让被遮掩的名字再见天日）
34. 区分接口继承和实现继承（在 public 继承之下，derived classes 总是继承 base class 的接口；pure virtual 函数只具体指定接口继承；非纯 impure virtual 函数具体指定接口继承及缺省实现继承；non-virtual 函数具体指定接口继承以及强制性实现继承）
35. 考虑 virtual 函数以外的其他选择（如 Template Method 设计模式的 non-virtual interface（NVI）手法，将 virtual 函数替换为 “函数指针成员变量”，以 `tr1::function` 成员变量替换 virtual 函数，将继承体系内的 virtual 函数替换为另一个继承体系内的 virtual 函数）
36. 绝不重新定义继承而来的 non-virtual 函数
37. 绝不重新定义继承而来的缺省参数值，因为缺省参数值是静态绑定（statically bound），而 virtual 函数却是动态绑定（dynamically bound）
38. 通过复合塑模 has-a（有一个）或 “根据某物实现出”（在应用域（application domain），复合意味 has-a（有一个）；在实现域（implementation domain），复合意味着 is-implemented-in-terms-of（根据某物实现出））
39. 明智而审慎地使用 private 继承（private 继承意味着 is-implemented-in-terms-of（根据某物实现出），尽可能使用复合，当 derived class 需要访问 protected base class 的成员，或需要重新定义继承而来的时候 virtual 函数，或需要 empty base 最优化时，才使用 private 继承）
40. 明智而审慎地使用多重继承（多继承比单一继承复杂，可能导致新的歧义性，以及对 virtual 继承的需要，但确有正当用途，如 “public 继承某个 interface class” 和 “private 继承某个协助实现的 class”；virtual 继承可解决多继承下菱形继承的二义性问题，但会增加大小、速度、初始化及赋值的复杂度等等成本）
41. 了解隐式接口和编译期多态（class 和 templates 都支持接口（interfaces）和多态（polymorphism）；class 的接口是以签名为中心的显式的（explicit），多态则是通过 virtual 函数发生于运行期；template 的接口是奠基于有效表达式的隐式的（implicit），多态则是通过 template 具现化和函数重载解析（function overloading resolution）发生于编译期）
42. 了解 typename 的双重意义（声明 template 类型参数是，前缀关键字 class 和 typename 的意义完全相同；请使用关键字 typename 标识嵌套从属类型名称，但不得在基类列（base class lists）或成员初值列（member initialization list）内以它作为 base class 修饰符）
43. 学习处理模板化基类内的名称（可在 derived class templates 内通过 `this->` 指涉 base class templates 内的成员名称，或藉由一个明白写出的 “base class 资格修饰符” 完成）
44. 将与参数无关的代码抽离 templates（因类型模板参数（non-type template parameters）而造成代码膨胀往往可以通过函数参数或 class 成员变量替换 template 参数来消除；因类型参数（type parameters）而造成的代码膨胀往往可以通过让带有完全相同二进制表述（binary representations）的实现类型（instantiation types）共享实现码）
45. 运用成员函数模板接受所有兼容类型（请使用成员函数模板（member function templates）生成 “可接受所有兼容类型” 的函数；声明 member templates 用于 “泛化 copy 构造” 或 “泛化 assignment 操作” 时还需要声明正常的 copy 构造函数和 copy assignment 操作符）
46. 需要类型转换时请为模板定义非成员函数（当我们编写一个 class template，而它所提供之 “与此 template 相关的” 函数支持 “所有参数之隐式类型转换” 时，请将那些函数定义为 “class template 内部的 friend 函数”）
47. 请使用 traits classes 表现类型信息（traits classes 通过 templates 和 “templates 特化” 使得 “类型相关信息” 在编译期可用，通过重载技术（overloading）实现在编译期对类型执行 if...else 测试）
48. 认识 template 元编程（模板元编程（TMP，template metaprogramming）可将工作由运行期移往编译期，因此得以实现早期错误侦测和更高的执行效率；TMP 可被用来生成 “给予政策选择组合”（based on combinations of policy choices）的客户定制代码，也可用来避免生成对某些特殊类型并不适合的代码）
49. 了解 new-handler 的行为（set\_new\_handler 允许客户指定一个在内存分配无法获得满足时被调用的函数；nothrow new 是一个颇具局限的工具，因为它只适用于内存分配（operator new），后继的构造函数调用还是可能抛出异常）
50. 了解 new 和 delete 的合理替换时机（为了检测运用错误、收集动态分配内存之使用统计信息、增加分配和归还速度、降低缺省内存管理器带来的空间额外开销、弥补缺省分配器中的非最佳齐位、将相关对象成簇集中、获得非传统的行为）
51. 编写 new 和 delete 时需固守常规（operator new 应该内涵一个无穷循环，并在其中尝试分配内存，如果它无法满足内存需求，就应该调用 new-handler，它也应该有能力处理 0 bytes 申请，class 专属版本则还应该处理 “比正确大小更大的（错误）申请”；operator delete 应该在收到 null 指针时不做任何事，class 专属版本则还应该处理 “比正确大小更大的（错误）申请”）
52. 写了 placement new 也要写 placement delete（当你写一个 placement operator new，请确定也写出了对应的 placement operator delete，否则可能会发生隐微而时断时续的内存泄漏；当你声明 placement new 和 placement delete，请确定不要无意识（非故意）地遮掩了它们地正常版本）
53. 不要轻忽编译器的警告
54. 让自己熟悉包括 TR1 在内的标准程序库（TR1，C++ Technical Report 1，C++11 标准的草稿文件）
55. 让自己熟悉 Boost（准标准库）