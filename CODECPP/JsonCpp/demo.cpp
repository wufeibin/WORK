#include <string>
#include <iostream>
#include <fstream>
#include <json/json.h>
using namespace std;

/* 
JSON是一个轻量级的数据定义格式，比起XML易学易用，而扩展功能不比XML差多少，用之进行数据交换是一个很好的选择。
JSON的全称为：JavaScript Object Notation
 */

// 从字符串中读取JSON
void readStrJson() 
{
    Json::Reader reader;
    Json::Value root;

    const char* str = "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\",\"born\":-100,\"died\":-44}";
    if (reader.parse(str, root)) { // 从字符串中读取数据
        string praenomen = root["praenomen"].asString();
        string nomen = root["nomen"].asString();
        string cognomen = root["cognomen"].asString();
        int born = root["born"].asInt();
        int died = root["died"].asInt();
    }

    string str2 = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";
    if (reader.parse(str2, root)) {
        string out = root["name"].asString();
        const Json::Value arrayObj = root["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++) {
            if (arrayObj[i].isMember("cpp")) {
                out = arrayObj[i]["cpp"].asString();
            }
        }
    }
}

// 从文件中读取JSON
void readFileJson()
{
    // 从文件中读取
    ifstream in("read.json", ios::binary);
    if (!in.is_open()) { 
        cout << "Error open read.json\n"; 
        return; 
    }

    Json::Reader reader;
    Json::Value root;
    if (reader.parse(in, root)) {
        //读取根节点信息
        string name = root["name"].asString();
        int age = root["age"].asInt();
        bool sex_is_male = root["sex_is_male"].asBool();
        //读取子节点信息
        string partner_name = root["partner"]["partner_name"].asString();
        int partner_age = root["partner"]["partner_age"].asInt();
        bool partner_sex_is_male = root["partner"]["partner_sex_is_male"].asBool();
        //读取数组信息
        for (unsigned int i = 0; i < root["achievement"].size(); i++) {
            string ach = root["achievement"][i].asString();
        }
    }
    in.close();
}

// 将信息保存为JSON格式
void writeFileJson()
{
    Json::Value root; // 根节点
    root["name"] = Json::Value("Mike Jiang");
    root["age"] = Json::Value(23);
    root["sex_is_male"] = Json::Value(true);

    Json::Value partner; // 子节点
    partner["partner_name"] = Json::Value("Galatea");
    partner["partner_age"] = Json::Value(21);
    partner["partner_sex_is_male"] = Json::Value(false);
    root["partner"] = Json::Value(partner); // 子节点挂到根节点上

    root["achievement"].append("ach1"); // 数组形式
    root["achievement"].append("ach2");
    root["achievement"].append("ach3");

    Json::FastWriter fw;
    cout << "FastWriter : " << endl << fw.write(root) << endl; // 直接输出

    Json::StyledWriter sw;
    cout << "StyledWriter : " << endl << sw.write(root) << endl; // 缩进输出

    ofstream os;
    os.open("write.json");
    os << sw.write(root); // 输出到文件
    os.close();
}

int main(int argc, char *argv[]) 
{
    readStrJson();
    readFileJson();
    writeFileJson();
    return 0;
}

/* 
g++ -o demo -I./ demo.cpp ./json_src/*.cpp
./demo
 */



Json::Value

// 勾造函数
Value(ValueType type=nullValue);
Value(Int value);
Value(UInt value);
Value(Int64 value);
Value(UInt64 value);
Value(double value);
Value(const char *value);
Value(const char *beginValue, const char *endValue);
Value(const StaticString &value);
Value(const std::string &value);
Value(bool value);
Value(const Value &other);
    
// 获取满足相应条件的Value
Value get( Uint index, const Value &defaultValue ) const;
Value get( const char *key, const Value &defaultValue) const;
Value get( const std::string &key, const Value &defaultValue ) const;

// Value转基本格式
Int asInt() const;
UInt asUInt() const;
Int64 asInt64() const;
LargestInt asLargesInt() const;
LargestUInt asLargestUInt() const;
float asFloat() const;
double asDouble() const;
bool asBool() const;
std::string asString() const;
const char* asCString() const;
std::string toStyledString() const;


// 判断Value格式
bool isNull() const;
bool isBool() const;
bool isDouble() const;
bool isInt() const;
bool isString() const;
bool isArrar() const;
bool isObject() const;
bool isMember (const char *key) const
bool isMember (const std::string &key) const




Json::Reader

// 串或者输入流转换为JSON的Value对象
bool parse( const std::string &document, Value &root, bool collectComments = true );
bool parse( const char *beginDoc, const char *endDoc, Value &root,bool collectComments = true );
bool parse( std::istream &is, Value &root, bool collectComments = true ); // 从文件流中读取
