#include "cpp_stl.h"

static bool IsShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void StringDemo()
{
    // 1、定义与初始化
    string s1; //默认初始化，一个空字符串
    string s2("s2");
    string s3 = "s3";
    string s4(4, 's');
    string s5 = string(5, 's');
    string s6(s5);
    string s7 = s5;
    const char cs[] = "123456789";
    string s8(cs, 8); // 复制cs前3个字符到string中
    string s9(s8, 6); // 复制s8前4个字符到string中
    string s10(s8, 2, 5); // 复制s8下标2开始的5个字符到string中。若超出s8长度，则抛出out_of_range异常
    
    // 2、常见操作
    string str("abcdefg");
    string str2("ABCDEFG");
    str.empty();
    str.size(); // str中的字符的个数：7
    str.length(); // 字符串使用与size()作用相同
    str[2]; // str中第2个字符的引用：c（从0计起）
    if (str == str2) LOGINFO("str and str2 is equal");
    str + str2;
    str = str2;
    str.substr(0,3); // abcd（返回一个子string）
    str.substr(4); // efg
    str.insert(5, 6, '!'); // 在str的第5个字符后插入6个'!'
    str.erase(4, 2); // 在str的第4个字符后删除2个字符
    const char *cp = "123456789";
    str.assign(cp, 3); // 赋值
    str.append("abcd"); // 添加
    str.replace(2, 3, "sssss"); // 替换：删除第2个字符后的3个字符，替换成"sssss"
    
    // 3、算法
    string str3("hello world");
    string str4("HELLO world");
    string::size_type pos;
    pos = str3.find("ll"); // 查找str3中第一次出现'll'的位置的下标值，没有则返回string:npos
    pos = str3.rfind("l"); // 查找str3中最后一次出现'l'的位置的下标值，没有则返回string:npos
    str3.compare(str4); // 比较
    str3.compare(6, 5, str4); // 从位置6开始的5个字符 与 str4 进行比较
    str3.compare(6, 5, str4, 6, 5); // 从位置6开始的5个字符 与 str4从位置6开始的5个字符 进行比较
}

// stringstream通常是用来做数据转换
void StringStreamDemo()
{
    std::stringstream stream;
    std::string result;
    int i = 1000;
    stream << i;  // 将int输入流
    stream >> result;
    LOGINFO("result:%s", result.c_str());
}

// 通常使用vector是最好的选择
void VectorDemo()
{
    // 1、定义与初始化
    vector<char> vec; // 默认初始化，vec1为空
    vector<char> vec1 = {'h', 'e', 'l', 'l', 'o'};
    vector<char> vec2(vec1);
    vector<char> vec3(vec1.begin(),vec1.end());
    vector<char> vec4(10); // 10个值为0的元素
    vector<char> vec5(10,'c'); // 10个值为'c'的元素
    vector<string> vec6(10,"null"); // 10个值为null的元素
    vector<string> vec7(10,"hello"); // 10个值为hello的元素
    
    // 2、常见操作
    vec1.empty();
    vec1.size();
    vec1.erase(vec1.begin(),vec1.end()); // 删除begin、end之间的元素
    vec1.clear(); // 清空元素
    vec1.push_back('c'); // 尾部插入元素
    vec1.pop_back(); // 尾部删除元素
    vec1.insert(vec1.end(),5,'v'); // 在end位置插入5个值为v的元素
    //vec1.swap(vec2);
    //swap(vec1, vec2);

    // 3、遍历
    for(int i = 0; i < vec1.size(); i++) {
        LOGINFO("%c", vec1[i]);
    }
    for(vector<char>::const_iterator iter = vec1.cbegin(); iter != vec1.cend(); iter++) { // 
        LOGINFO("%c", *iter);
    } 
    for(auto &v : vec1) { // 如果不增删容器数据，可考虑使用范围for语句。
        LOGINFO("%c", v);
    }

    // 4、泛型算法
    auto res = find(vec7.cbegin(), vec7.cend(), "hello");
    if (res != vec7.cend()) {
        LOGINFO("find result");
    }

    // to fix
    //fill(vec7.cbegin(), vec7.cend(), "a"); // 将每个元素重置为a

    //sort(vec7.cbegin(), vec7.cend(), IsShorter); // 按长度排序字符串
}

void ListDemo()
{
    // 1、定义与初始化
    list<char> lst1;
    list<char> lst2(3); // 创建含有三个元素的list
    list<char> lst3(3, 'a'); // 创建含有三个元素的值为l的list
    list<char> lst4(lst2);
    list<char> lst5(lst2.begin(), lst2.end());

    // 2、常见操作
    lst1.empty();
    lst1.size();
    lst1.erase(lst1.begin(), lst1.end()); // 删除元素
    lst1.clear();
    lst1.assign(lst2.begin(), lst2.end()); // 赋值
    lst1.push_back('b');
    lst1.pop_back();
    lst1.insert(lst1.begin(), 3, 'c'); // 从指定位置插入3个值为c的元素
    lst1.reverse(); // 反转
    lst1.sort(); // 排序

    // 3、遍历
    for(list<char>::const_iterator iter = lst1.begin(); iter != lst1.end(); iter++) {
        LOGINFO("%c", *iter);
    }
}

void StackDemo()
{
    stack<int> stack1;
    for (int i = 0; i <= 10; i++){
        stack1.push(i);
    }
    LOGINFO("stack size %d", stack1.size());
    while (!stack1.empty()) {
        LOGINFO("stack top %d", stack1.top());
        stack1.pop();
    }
}

void QueueDemo()
{
    queue<int> queue1;
    for (int i = 0; i < 10; i++) {
        queue1.push(i); // 末尾加入一个元素
    }
    int front = queue1.front(); // 第一个元素
    int back = queue1.back(); // 最后一个元素
    LOGINFO("front %d, back %d", front, back);
    
    while (!queue1.empty()) {
        queue1.pop(); // 删除第一个元素
    }
}

// map类型通常被称为关联数组，map容器是键值对（key-value）的容器。与正常数组不同之处在于其下标不是整数，而是一个关键字key值。对于迭代器，可以修改value值，不能修改key值。
// map会根据key值自动排序。key值需要支持<操作符。
// map与multimap差别仅仅在于multiple允许一个键对应多个值。
void MapDemo()
{
    // 1、定义与初始化
    map<int, string> map1; // 空map，key值为int型，value值为string型。
    
    // 2、常见操作
    map1.empty();
    map1.size();
    map1.clear();
    map1.insert({1, "Monday"}); // 成功插入一对键值，返回bool为true，iterator指向插入的key值。已经存在，则返回false，且value值不变。
    map1.insert(pair<int, string>(2, "Tuesday"));
    map1.insert(make_pair(3, "Wednesday"));
    map1.insert(map<int, string>::value_type(4, "Thursday"));

    string str = map1[1]; //下标操作，根据key值取得value

    map<int, string>::iterator it = map1.find(1); // 返回指向key值的迭代器，若不存在则返回超出末端迭代器。
    if(it != map1.end()) {
        //对查找到的数据处理
    }
    map1.erase(it); // 删除迭代器指向的数据
    map1.erase(2); // 根据key值删除value

    // 3、遍历
    for (map<int, string>::const_iterator it = map1.begin(); it!=map1.end(); it++) {
        cout << it->second << endl;
        if (it->second == "aaa") {
            it = map1.erase(it);    //方法一：erase会返回it下一个元素的迭代器
            map1.erase(it++);       //方法二：先把参数传给erase函数，再执行it++，然后执行erase
            map1.erase(it);         //错误方法：执行完erase后，it就是一个非法指针，无法继续使用。
        }
    }
}

// set的含义是集合，它是一个有序的容器，里面的元素都是排序好的。set容器的每个键都只能对应一个元素。当想知道一个值是否存在，set是最有用的。
void SetDemo()
{
    set<string> set1 = {"111", "222"};
    set1.insert("aaa"); // 添加元素
    set1.count("aaa"); // 返回key值为aaa的元素数量
    set<string>::iterator it = set1.find("aaa"); // 返回指向元素值为aaa的指针；不存在则返回指针set.end()
    if (it != set1.end()) {
        LOGINFO("find %s", (*it).c_str());
    }
}

void LambdaDemo()
{
    vector<int> myvec{ 3, 2, 5, 7, 3, 2};
    sort(myvec.begin(), myvec.end(), [](int a, int b) -> bool { return a < b; }); // Lambda表达式

    int a = 123;
    auto f_a = [a] { cout << a << endl; }; 
    a = 321;
    f_a(); // 输出：123

    int b = 123;
    auto f_b = [&b] { cout << b << endl; }; 
    b = 321;
    f_b(); // 输出：321

    // to fix 
    //auto x = [](int c){cout << c << endl;}(123); // 或通过“函数体”后面的‘()’传入参数
    //x();

}

