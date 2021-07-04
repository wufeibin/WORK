#include <stdio.h>
#include <iostream>
#include <cstring>
#include "tinyxml.h"
using namespace std;

/* 
TinyXML是一个开源的解析XML的解析库，能够用于C++，能够在Windows或Linux中编译。这个解析库的模型通过解析XML文件，然后在内存中生成DOM模型，从而让我们很方便的遍历这棵XML树。
DOM模型即文档对象模型，是将整个文档分成多个元素（如书、章、节、段等），并利用树型结构表示这些元素之间的顺序关系以及嵌套包含关系。

TiXmlDocument：文档类，它代表了整个xml文件
TiXmlDeclaration：声明类，它表示文件的声明部分
TiXmlComment：注释类，它表示文件的注释部分
TiXmlElement：元素类，它是文件的主要部分，并且支持嵌套结构，一般使用这种结构来分类的存储信息，它可以包含属性类和文本类
TiXmlAttribute/TiXmlAttributeSet：元素属性，它一般嵌套在元素中，用于记录此元素的一些属性
TiXmlText：文本对象，它嵌套在某个元素内部
 */

// 创建xml文件
int writeXmlFile()
{
    TiXmlDocument *writeDoc = new TiXmlDocument; // xml文档指针
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "yes"); // 文档格式声明
    writeDoc->LinkEndChild(decl); // 写入文档

    int n = 3; // 父节点个数
    TiXmlElement *RootElement = new TiXmlElement("Info"); // 根元素
    RootElement->SetAttribute("num", n); // 设置属性
    writeDoc->LinkEndChild(RootElement);
    
    for (int i = 0; i < n; i++) { // n个父节点
        TiXmlElement *StuElement = new TiXmlElement("Stu");
        StuElement->SetAttribute("class", "A"); // 设置属性
        if (2 == i) {
            StuElement->SetAttribute("class", "B");
        }

        StuElement->SetAttribute("id", i + 1);
        StuElement->SetAttribute("flag", (i + 1) * 10);
        RootElement->LinkEndChild(StuElement); // 父节点写入文档

        TiXmlElement *nameElement = new TiXmlElement("name");
        StuElement->LinkEndChild(nameElement);
        TiXmlText *nameContent = new TiXmlText("mike");
        nameElement->LinkEndChild(nameContent);

        TiXmlElement *scoreElement = new TiXmlElement("score");
        StuElement->LinkEndChild(scoreElement);
        TiXmlText *scoreContent = new TiXmlText("88");
        scoreElement->LinkEndChild(scoreContent);

        TiXmlElement *cityElement = new TiXmlElement("city");
        StuElement->LinkEndChild(cityElement);
        TiXmlText *cityContent = new TiXmlText("Shenzhen");
        cityElement->LinkEndChild(cityContent);
    }
    
    writeDoc->SaveFile("demo.xml");
    delete writeDoc;
    return 1;
}
 
//解析xml文件
int readXmlFile()
{
    TiXmlDocument mydoc("demo.xml"); // xml文档对象
    bool loadOk = mydoc.LoadFile(); // 加载文档
    if (!loadOk) {
        cout << "could not load the test file. Error:" << mydoc.ErrorDesc() << endl;
        return -1;
    }

    TiXmlElement *RootElement = mydoc.RootElement(); // 根元素, Info
    cout<< "root : " << RootElement->Value() << endl;
    TiXmlElement *pEle = RootElement;
 
    for (TiXmlElement *StuElement = pEle->FirstChildElement(); StuElement != NULL; StuElement = StuElement->NextSiblingElement()) {
        cout << StuElement->Value() << " ";
        TiXmlAttribute *pAttr = StuElement->FirstAttribute(); // 第一个属性
        while (NULL != pAttr) { // 输出所有属性
            cout << pAttr->Name() << ":" << pAttr->Value() << " ";
            pAttr = pAttr->Next();
        }
        cout << endl;
        
        // 输出子元素的值
        for (TiXmlElement *sonElement = StuElement->FirstChildElement(); sonElement != NULL; sonElement=sonElement->NextSiblingElement()) {
            cout << sonElement->FirstChild()->Value() << endl;
        }
    }
    return 1;
}
 
int main(int argc, char *argv[])
{
    writeXmlFile();
    readXmlFile();
    return 0;
}

/* 
g++ -fPIC -shared tiny*.cpp -o libtinyxml.so
g++ -o main.o -c demo.cpp -I./src
g++ -o demo -L./src -ltinyxml demo.o
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./src/
./demo
 */