[TOC]

# const

1. 修饰变量，说明该变量不可以被改变。
2. 修饰指针，分为指向常量的指针和指针常量。
3. 修饰引用，经常用于形参类型，即避免了拷贝，又避免了函数对值的修改。
4. 修饰成员函数，说明该成员函数内不能修改成员变量。

```cpp
class A
{
public:
    A() : a(0) { };
    A(int x) : a(x) { };        // 初始化列表

    // const可用于对重载函数的区分
    int getValue();             // 普通成员函数
    int getValue() const;       // 常成员函数，不得修改类中的任何数据成员的值
    
private:
    const int a;                // 常对象成员，只能在初始化列表赋值
};

void function()
{
    // 对象（不允许将普通引用或指针绑定到const对象，防止通过引用修改对象）
    A b;                        // 普通对象，可以调用全部成员函数、更新常成员变量
    const A a;                  // 常对象，只能调用常成员函数
    const A *p = &a;            // 常指针
    const A &q = a;             // 常引用

    // 指针
    char greeting[] = "Hello";
    char* p1 = greeting;                // 指针变量，指向字符数组变量
    const char* p2 = greeting;          // 指针变量，指向字符数组常量（常用）
    char* const p3 = greeting;          // 常指针，指向字符数组变量
    const char* const p4 = greeting;    // 常指针，指向字符数组常量
}

// 函数入参
void function1(const int Var);           // 传递过来的参数在函数内不可变
void function2(const char* Var);         // 参数指针所指内容为常量
void function3(char* const Var);         // 参数指针为常指针
void function4(const int& Var);          // 引用参数在函数内为常量

// 函数返回值
const int function5();      // 返回一个常数
const int* function6();     // 返回一个指向常量的指针变量，使用：const int *p = function6();
int* const function7();     // 返回一个指向变量的常指针，使用：int* const p = function7();
```


# static

1. **静态变量**：main函数运行前，在数据段分配内存，未经初始化的静态变量会被程序自动初始化为0。
2. **静态函数**：表明函数的作用范围，仅在定义该函数的文件内才能使用。
3. **静态成员变量**：无论有多少个类对象，静态数据成员在内存中只有一份拷贝，由所有该类的对象共享，可以直接使用类名加作用域运算符(::)直接访问。只能在类中声明，在类外进行定义和初始化，默认初始化为0。
4. **静态成员函数**：静态成员函数只能访问静态数据成员和静态成员函数。静态成员函数属于类，不属于任意一个类对象。静态成员函数没有 this 指针，可以使用 <类名>::<函数名> 访问，也可由类对象使用(./->)访问。


# malloc、new

* malloc是C语言的标准库函数，申请一块内存，返回void*指针。
* new是C++运算符，申请一块内存，构造对象，并返回该对象的指针。
```
int *p1 = (int *)malloc(sizeof(int) * 5);
free(p1);
p1 = NULL;
int *p2 = new int[5];
delete []p2;
p2 = NULL;

Base *pb1 = new Base;
Base *pb2 = new Base();
Base *pb3 = new Base(1);
delete pb1;
delete pb2;
delete pb3;
```

# sizeof、strlen
```
char str[10] = "123456";
char *pc = str;
char *ps = "1234";
//sizeof运算符：查询对象或数据类型的大小，返回size_t常量。
cout << "sizeof(str)=" << sizeof(str) << endl;  //sizeof(数组名) 数组的大小，10
cout << "sizeof(pc)=" << sizeof(pc) << endl;    //sizeof(数组指针) 指针大小，4
//strlen函数：统计字符串的长度。字符串的长度由终止空字符确定，不包括终止空字符本身。
cout << "strlen(str)=" << strlen(str) << endl;  //6
cout << "strlen(pc)=" << strlen(pc) << endl;    //6
cout << "strlen(ps)=" << strlen(ps) << endl;    //4
cout << "strlen(abc)=" << strlen("abc") << endl;    //3
```

# 字符串拷贝
```
typedef struct student
{
    char  name[16];
    int   age;
}STUDENT;
STUDENT stu1;
STUDENT stu2[5];
char pc1[10];
char pc2[5] = "abcd";

1、memset
原型：void *memset(void *s, int c, size_t n);
用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为0
memset(&stu1, 0, sizeof(STUDENT));
memset(stu2, 0, sizeof(STUDENT)*5);
memset(pc1, 0, sizeof(pc1));

2、memcpy
原型：void * memcpy (void *dest, const void *src, size_t num); 复制src所指的内存内容的前num个字节到dest所指的内存地址上，不会因为遇到“\0”而结束。
返回值：返回dest指针。注意返回的指针类型是void*，使用时一般要进行强制类型转换。
注意点：dest指针要分配足够的空间，>=num个字节。可用于很多数据类型的复制。
memcpy(pc1, pc2, 5);

3、strcpy
原型：char *strcpy(char *dest, const char *src);将参数src字符串拷贝至参数dest所指的地址，遇到'\0'拷贝完就就结束。
返回值：返回dest指针
注意点：如果dest所指的内存空间不够大，会造成缓存溢出。使用时用strncpy()来取代。
strcpy(pc1, pc2);

4、strncpy
原型：char * strncpy(char *dest, const char *src, size_t n);将参数src字符串前n个字节拷贝至参数dest所指的地址，遇到'\0'拷贝完就就结束。长度n超出源字符串长度部分会填0。
返回值：返回dest指针
strncpy(pc1, pc2, 4);
pc1[sizeof(pc1)-1] = '\0';

5、sprintf
原型：int sprintf(char *str, const char *format, ...);
sprintf(pc1, "%s", "aaaa");

6、snprintf
原型：int snprintf(char *str, size_t size, const char *format, ...);最多从源串中拷贝n－1个字符到目标串中，然后再在后面加一个0。所以如果目标串的大小为n的话，不会溢出。（建议使用：安全高效）
snprintf(pc1, sizeof(pc1), "%s", "bbb");
```


# C++类特性

* **构造函数**、**析构函数**、**拷贝构造**、**赋值**函数是每个类的最基本函数。每个类只有一个析构函数和赋值函数，可以有多个构造函数（包含一个拷贝构造函数和其他的普通构造函数）。对于一个类，编译器会自动产生四个缺省的函数（无参构造、拷贝构造、析构、赋值）。
    * 如果一个类没有显式地定义构造函数，编译器会隐式地合成一个默认构造函数。合成的默认构造函数只适合简单的类。如`Base b;`调用了默认构造函数。
    * 类对象的数据成员是在析构函数执行体之后的隐含阶段被销毁的
    * 非内部数据类型的成员对象（类对象），应采用初始化表方式初始化，提高效率。
    * 拷贝构造函数是在对象被创建时调用，而赋值函数只能被存在的对象调用。
    ```c
    String a(“hello”);
    String b(“world”);
    String c = a; // 调用了拷贝构造函数，最好写成 c(a);
    c = b; // 调用了赋值函数 
    ```
    * 内置类型之间定义了几种自动转换规则，同样的也能为类类型定义隐式转换规则。如果类的构造函数只有一个实参，则它实际上定义了转换为此类类型的**隐式转换**机制。  
    ```c
    //比如一个类的构造函数只接受一个int参数，那么就定义了从int类型向这个类隐式转换的规则。在需要用到这个类类型的地方，可以用int类型替换，不需要显式转换。
    //构造函数默认能够发生隐式自动转换。可以在构造函数声明时在前面加explicit抑制隐式转换。
    构造函数：CString(int size){...}
    CString A = 10;
    等同于：(构造函数的隐式转换)
    CString temp(10);
    CString A = temp;
    ```
* 通过访问说明符public/private/protect，来达到访问控制，加强封装性。
* 友元：友元函数、友元类。类可以通过访问其他类的非公有成员，友元特性会破坏封装。
    ```c
    class A
    {
        //B可以访问A
        friend void B::func();
        friend class B;
    }
    ```
* **函数重载**：同个作用域内，函数名相同，形参列表不同。
* **函数覆盖**：派生类虚函数与基类虚函数的函数名和形参相同。
* **函数隐藏**：派生类函数与基类函数同名，又不是多态的覆盖，则会隐藏屏蔽基类函数。

**虚函数**：C++中虚函数的作用是实现了运行时多态的机制。关于多态，简而言之就是用基类指针指向其派生类对象，然后通过基类指针调用派生类的成员函数。 

* 如果一个类有虚函数，或者继承的类有虚函数，则这个类对应一(n)个虚函数表，类中有一(n)个虚函数表指针。虚函数表中存放着所有虚函数的地址，在编译时就确定。（虚表存放在只读数据段）
* 每个派生类对象的内存空间中都有该类的虚表指针和所有成员变量。虚表指针在调用构造函数的函数体执行前被赋值指向虚表。当我们用指针来调用虚函数时，先通过虚表指针找到虚函数表，然后根据虚函数在虚表中的偏移找到对应的函数地址。
* 继承过程中的虚表，基类的虚函数地址都会被覆盖成派生类的虚函数地址。
* 如果是单一继承，则只有一个虚表指针，虚表中存放基类和派生类的虚函数地址。如果是n重继承，则有n个虚表指针，第一个虚表存放基类和派生类的虚函数地址，其它虚表存放派生类的虚函数地址。
```c
//通过对象的地址来取得虚函数表的地址
Base b;
cout << "虚函数表地址：" << (int*)(&b) << endl;
cout << "虚函数表的第一个函数地址：" << (int*)*(int*)(&b) << endl;

typedef void(*Fun)(void);
Fun pFun = (Fun)*((int*)*(int*)(&b));
pFun();
```

* 成员函数不在类对象的内存空间中，成员函数本质上是一个包含指向具体对象this指针的普通函数。this指针是一个隐含于非静态成员函数中的特殊指针，它指向调用该成员函数的那个对象。
* inline内联函数相当于宏，在编译期将函数体复制到调用处，但比宏多了类型检测，具有函数的特性。一方面提高了运行效率，另一方面会造成代码膨胀，适用于短小且频繁调用的函数。

# STL容器
[STL文档](https://github.com/huihut/interview/tree/master/STL)
> * 容器的定义：容器就是一些特定类型对象的集合。在数据存储上，有一种对象类型，它可以持有其它对象或指向其它对像的指针，这种对象类型就叫做容器。很简单，容器就是保存其它对象的对象，当然这是一个朴素的理解，这种“对象”还包含了一系列处理“其它对象”的方法。
> * 顺序容器：是一种各元素之间有顺序关系的线性表，是一种线性结构的可序群集。顺序性容器中的每个元素均有固定的位置，除非用删除或插入的操作改变这个位置。顺序容器的元素排列次序与元素值无关，而是由元素添加到容器里的次序决定。
>    * 包含：string、vector(动态数组)、list（双向链表）、forward_list（单向链表）、array（固定数组）、deque（双端队列）
> * 关联容器：关联式容器是非线性的树结构，更准确的说是二叉树结构。各元素之间没有严格的物理上的顺序关系，也就是说元素在容器中并没有保存元素置入容器时的逻辑顺序。但是关联式容器提供了另一种根据元素特点排序的功能，这样迭代器就能根据元素的特点“顺序地”获取元素。元素是有序的集合，默认在插入的时候按升序排列。
>    * 包含：map（集合）、set（映射）、multimap（多重集合）、multiset（多重映射）。

* string
```c++
//1、定义与初始化
string s1;//默认初始化，一个空字符串
string s2("s2");
string s3 = "s3";
string s4(4, 's');
string s5 = string(5, 's');
string s6(s5);
string s7 = s5;
const char cs[] = "123456789";
string s8(cs, 8);//复制cs前3个字符到string中
string s9(s8, 6);//复制s8前4个字符到string中
string s10(s8, 2, 5);//复制s8下标2开始的5个字符到string中。若超出s8长度，则抛出out_of_range异常
//2、操作
string str("abcdefg");
string str2("ABCDEFG");
str.empty();
str.size();//str中的字符的个数：7
str[2];//str中第2个字符的引用：c（从0计起）
if(str == str2) cout << "str and str2 is equal" << endl;
str + str2;
str = str2;
str.substr(0,3);//abcd（返回一个子string）
str.substr(4);//efg
str.insert(5, 6, '!');//在str的第5个字符后插入6个'!'
str.erase(4, 2);//在str的第4个字符后删除2个字符
const char *cp = "123456789";
str.assign(cp, 3);//赋值
str.append("abcd");//添加
str.replace(2, 3, "sssss");//替换：删除第2个字符后的3个字符，替换成"sssss"
//3、搜索
string str3("hello world");
string str4("HELLO world");
string::size_type pos;
pos = str3.find("l");//查找str3中第一次出现'l'的位置的下标值，没有则返回string:npos
pos = str3.find("lo");
pos = str3.rfind("l");//查找str3中最后一次出现'l'的位置的下标值，没有则返回string:npos
str3.compare(str4);//比较
str3.compare(6, 5, str4);//从位置6开始的5个字符 与 str4 进行比较
str3.compare(6, 5, str4, 6, 5);//从位置6开始的5个字符 与 str4从位置6开始的5个字符 进行比较
```

* vector
```c++
//1、定义与初始化
vector<char> vec;//默认初始化，vec1为空
vector<char> vec1 = {'h', 'e', 'l', 'l', 'o'};
vector<char> vec2(vec1);
vector<char> vec3(vec1.begin(),vec1.end());
vector<char> vec4(10);//10个值为0的元素
vector<char> vec5(10,'c');//10个值为'c'的元素
vector<string> vec6(10,"null");//10个值为null的元素
vector<string> vec7(10,"hello");//10个值为hello的元素
//2、常见操作
vec1.empty();
vec1.size();
vec1.erase(vec1.begin(),vec1.end());    //删除begin、end之间的元素
vec1.clear();   //清空元素
vec1.push_back('c');//尾部插入元素
vec1.pop_back();//尾部删除元素
vec1.insert(vec1.end(),5,'v');    //在end位置插入5个值为v的元素
//3、遍历搜索
for(int i = 0; i < vec1.size(); i++)//下标法
{
    cout << vec1[i];
}
for(vector<char>::const_iterator iterator = vec1.begin(); iterator != vec1.end(); iterator++)//迭代器法
{
    cout << *iterator;
}
```

* list
```c++
//1、定义与初始化
list<char> lst1;
list<char> lst2(3);//创建含有三个元素的list
list<char> lst3(3, 'a');//创建含有三个元素的值为l的list
list<char> lst4(lst2);
list<char> lst5(lst2.begin(), lst2.end());
//2、常见操作
lst1.empty();
lst1.size();
lst1.erase(lst1.begin(), lst1.end());//删除元素
lst1.clear();
lst1.assign(lst2.begin(), lst2.end());//赋值
lst1.push_back('b');
lst1.pop_back();
lst1.insert(lst1.begin(), 3, 'c');//从指定位置插入3个值为c的元素
lst1.reverse();//反转
lst1.sort();//排序
//3、遍历搜索
for(list<char>::const_iterator iter = lst1.begin(); iter != lst1.end(); iter++)
{
    //cout << *iter;
}
```

* map
```c++
map类型通常被称为关联数组，map容器是键值对（key-value）的容器。与正常数组不同之处在于其下标不是整数，而是一个关键字key值。对于迭代器，可以修改value值，不能修改key值。
map会根据key值自动排序。key值需要支持<操作符。
map与multimap差别仅仅在于multiple允许一个键对应多个值。

//1、定义与初始化
map<int, string> map1;//空map，key值为int型，value值为string型。
//2、常见操作
map1.empty();
map1.size();
map1.clear();
//成功插入一对键值，返回bool为true，iterator指向插入的key值。已经存在，则返回false，且value值不变。
map1.insert({1, "Monday"});
map1.insert(pair<int, string>(2, "Tuesday"));
map1.insert(make_pair(3, "Wednesday"));
map1.insert(map<int, string>::value_type(4, "Thursday"));

string str = map1[1];   //根据key值取得value

map<int, string>::iterator it = map1.find(1);//返回指向key值的迭代器，若不存在则返回超出末端迭代器。
if(it != map1.end())
{
    //对查找到的数据处理
}
map1.erase(it);//删除迭代器指向的数据
map1.erase(2);//根据key值删除value

//3、遍历
for(map<int, string>::const_iterator it = map1.begin(); it!=map1.end(); it++)
{
    cout << it->second << endl;
    if(it->second == "aaa")
    {
        it = map1.erase(it);    //方法一：erase会返回it下一个元素的迭代器
        map1.erase(it++);       //方法二：先把参数传给erase函数，再执行it++，然后执行erase
        map1.erase(it);         //错误方法：执行完erase后，it就是一个非法指针，无法继续使用。
    }
}
```

* set
```c++
set的含义是集合，它是一个有序的容器，里面的元素都是排序好的。set容器的每个键都只能对应一个元素。
当想知道一个值是否存在，set是最有用的。

set<string> set1 = {"111", "222"};
set1.insert("aaa");//添加元素
set1.count("aaa");//返回key值为aaa的元素数量
set<string>::iterator it = set1.find("aaa");//返回指向元素值为aaa的指针；不存在则返回指针set.end()
if(it != set1.end())
{
    cout << "find aaa" << endl;
}
```

* bitset

bitset是一种高效位集合操作容器。bitset是一种非标准STL容器，可以认为是容器，但并不满足容器的所有要求。
```c++
//bitset定义和初始化
bitset<16> b1;              //b有16位，每位都为0
bitset<13> b2(0xbfff);      //1111111111111 b是unsigned long型的低n位的拷贝。b比初始值小，初始值的高位被丢弃。
bitset<20> b3(0xbfff);      //00001011111111111111 b比初始值大，b的高位被置为0。
string s("1111111100000000");
bitset<16> b4(s);           //1111111100000000 b是string对象s中含有的位串的副本
bitset<16> b5("111000");    //0...0111000
bitset<16> b6(s, 6, 4);     //0...01100 b是s中从位置pos开始的n个位的副本

//bitset操作
b1.any();   //b中是否存在置位（1）
b1.all();   //b中是否全部置位
b1.none();  //b中是否不存在置位
b1.count(); //b中置位的位数
b1.size();  //b的位数
b1[3];      //访问b中位置3的位
b1.test(3); //若b中位置3置位，返回true
b1.set(3);  //对位置3置位
b1.set();   //对所有位置位
b1.reset(3);//对位置3复位
b1.reset(); //对所有位复位
b1.flip(3); //改变位置3位状态
b1.flip();  //改变所有位状态
```

# 智能指针
1. 智能指针的设计思想
```
void remodel(std::string & str)
{
    std::string * ps = new std::string(str);
    ...
    if (weird_thing())
        throw exception();//当出现异常时，delete将不被执行，因此将导致内存泄露。 
    str = *ps; 
    delete ps;
    return;
}
```

* 我们不能保证申请的内存被正确释放，所以需要使用智能指针来管理。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域时，类会自动调用析构函数，析构函数会自动释放资源。
* 智能指针通过类模板将基本类型指针封装为类对象指针，并在析构函数里编写delete语句删除指针指向的内存空间，这样内存也被自动释放了。

2. C++智能指针介绍
* STL提供的智能指针：shared_ptr、unique_ptr、weak_ptr、auto_ptr（被摒弃）
* 智能指针实质是一个类模版，定义的对象行为表现像指针，使用时和普通指针类似。
* 智能指针类都有一个explicit构造函数，以指针作为参数。因此不能自动将指针转换为智能指针对象，必须显式调用：
```cpp
double *p_reg = new double;
shared_ptr<double> pshared = p_reg;       // not allowed (implicit conversion)
shared_ptr<double> pshared(p_reg);        // allowed (explicit conversion)
```
* 对于智能指针都要避免一点：不能将delete作用于非堆的内存  

```cpp
//使用例子
#include <iostream>
#include <string>
#include <memory>

class report
{
private:
    std::string str;
public:
     report(const std::string s) : str(s) {
          std::cout << "Object created.\n";
     }
     ~report() {
          std::cout << "Object deleted.\n";
     }
     void comment() const {
     	std::cout << str << "\n";
     }
};

int main() {
{
	std::auto_ptr<report> ps(new report("using auto ptr"));
	ps->comment();
}

{
	std::shared_ptr<report> ps(new report("using shared ptr"));
	ps->comment();
}

{
	std::unique_ptr<report> ps(new report("using unique ptr"));
	ps->comment();
}
return 0;
}
```

3. shared_ptr

允许多个share_ptr指针指向同个对象。每个share_ptr有一个关联的计数器，称为**引用计数**。  
当拷贝一个share_ptr，计数器会递增；  
当一个share_ptr被赋新值或share_ptr被销毁，计数器会递减；  
当一个share_ptr的计数器为0时，它就会自动释放所管理的对象。  

4. unique_ptr

```
//unique_ptr独占所指对象
//当程序试图将一个 unique_ptr 赋值给另一个时，如果源 unique_ptr 是个临时右值，编译器允许这么做；如果源 unique_ptr 将存在一段时间，编译器将禁止这么做。
auto_ptr<string> p1(new string ("auto"));
auto_ptr<string> p2;
p2 = p1;			//p2接管string对象的所有权后，p1是空指针。再使用p1会内存崩溃
unique_ptr<string> pu1(new string ("hello world"));
unique_ptr<string> pu2;
pu2 = pu1;			//编译器会禁止报错
unique_ptr<string> pu3;
pu3 = unique_ptr<string>(new string ("You"));   //允许
```
5. auto_ptr
```
string *p = new string("aaaa")
auto_ptr<string> p1(p);
auto_ptr<string> p2;
p2 = p1;    //p1将所有权赋给p2，p1变成NULL指针，若访问会异常，所以auto_ptr被摒弃。
```


# 类型转换
类型转换运算符：static_cast、dynamic_cast、reinterpret_cast、const_cast  
xxxx_cast <type-id> (expression)
* static_cast
> 用于基本类型之间的转换  
> 用于类层次间的上下行转换，下行转换没有运行时类型检测，不安全。（下行类型转换：基类指针转换成派生类指针 ）
* dynamic_cast
> 用于类层次间的上下行转换，下行转换有运行时类型检测，转换失败则返回NULL，比static_cast更安全。
* reinterpret_cast
> 用于指针类型和整形之间的转换
* const_cast
> 用于修改类型的const或volatile属性

* typeid运算符
> #include <typeinfo.h>  
> Base *p = new Derived();  
> typeid(*p).name();    //指针所指对象类型名称  

# 模版
# Effective C++

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

---
**extern**关键字：定义只能一次，声明可以多次。
1. 全局变量 
> 常见用法：在一个源文件中声明定义全局变量（下面3种形式都可行），在使用的源文件（或包含的头文件）中声明全局变量后，即可使用。
```
extern int i;		声明
extern int i = 0;	声明并定义
int i;				声明并定义
int i = 0;			声明并定义
```

2. 全局函数
> 函数定义和声明的区别是有无函数体，所以定义和声明时可省略extern。  
常见用法：在一个源文件中声明定义了全局函数，在使用的源文件（或包含的头文件）中声明全局函数（通常加上extern）后，即可使用。
```
(extern) void func()	声明并定义
{
	printf("hello\n");
}
(extern) void func();	声明
```


3. extern "C" 链接指示符
> 如果要在一个cpp源文件中要使用一个C的函数，需要告诉编译器使用C语言的方式进行编译和链接。  

**常见使用1**
```c
//1.c
void func(){};
```
```c
//main.cpp
extern "C" void func();
int main()
{
	func();
}
```

**常见使用2**
```c
//1.h
#ifdef  __cplusplus（__cplusplus是C++中定义的宏，使用后的头文件可兼容c/cpp文件）
extern "C" {
#endif
	void func1();
	void func2();
#ifdef  __cplusplus
}
#endif
```
```c
//1.c
#include "1.h"
void func1(){};
void func2(){};
```
```c
//main.cpp
#include "1.h"
int main()
{
	func1();
	func2();
}
```
> gcc -c 1.c -o 1.o  
> g++ main.cpp 1.o

---

void assert(int expression);  
计算表达式expression，如果值为假，则向stderr打印一条错误信息，然后调用abort终止程序。 一般对一些偶然性事件进行判断。  
assert仅仅是个报错函数，实际上，它是一个宏。

---

volatile 关键字声明的变量，每次访问时都必须从内存中取出值（没有被 volatile 修饰的变量，可能由于编译器的优化，从CPU寄存器中取值）。所以使用 volatile 告诉编译器不应对这样的对象进行优化。

---

```
int func(bool a, const char *p)
{··· return 1;}
int i = func(true, &addr);
```
* 参数  
bool a = true;
const char *p = &addr;
* 返回值  
int temp = 1;
int i = temp;

---
时序图：时序图是显示对象之间交互的图，这些对象是按照时间顺序排列的。
* 时序图的基本元素：对象、生命线、控制焦点、消息（同步消息、异步消息、返回消息、自关联消息）、创建/销毁对象
* 同步消息：发送者把消息发送给接收者后，通知活动等待返回消息，才继续执行。
* 异步消息：发送者把消息发送给接受者后，继续自己的活动。
* 同步：A调用B后，A停止，等到B完成后返回到A，A才继续执行。
* 异步：A调用B后，A继续执行，不受B影响。

---
主机字节序又叫 CPU 字节序，其不是由操作系统决定的，而是由 CPU 指令集架构决定的。

数据存放到内存，都是由低地址到高地址。32 位整数 `0x12345678` 是从起始位置为 `0x00` 的地址开始存放，则：

内存地址 | 0x00 | 0x01 | 0x02 | 0x03
---|---|---|---|---
大端|12|34|56|78
小端|78|56|34|12

* 大端：先存储高位字节数据  ARM、IBM大型机
* 小端：先存储低位字节数据  Intel

---
在C语言中，NULL、0、‘\0’的值都是一样的，但是它们的实质并不相同。
NULL用于指针和对象，表示指向空地址的指针，或不指向任何实际对象。

任何指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的。所以指针定义时应该初始化，要么将指针设为NULL，要么让它指向合法的内存。

---
堆栈打印
```
#include <execinfo.h>
void *buffer[16];
char **string;
int nptr = backtrace(buffer, 16);
string = backtrace_symbols(buffer, 16);
for(int i = 0; i < nptr; i++)
    printf("%s\n", string[i]);
```

---
do{...}while(0)作用

* 帮助定义复杂的宏函数
* 通过break替换goto，控制程序流。

---
结构体内存对齐规则

* 第一个数据成员存储offset=0位置，之后每个成员的起始地址需从自己大小的整数倍开始存储。
* 结构体作成员，以内部的最大基本类型的整数倍地址开始存储。
* 联合体作成员，以内部的最大基本类型作为size。
* 结构体的总大小，是内部最宽基本类型的整数倍，不足要补齐。

---
指针和引用

* 引用是对象的别名，不占用内存空间，必须初始化且不能修改。（有时理解为const指针）
* 指针是一个对象，存放的是一个地址，来操作地址上的对象。
