#include "../common.h" 

/* 
1. 打开文件
    FILE *fopen(const char *filename, const char *mode);
        "r"，只读。
        "w"，只写。如果文件不存在则创建，如果存在则重写
        "a"，追加数据。如果文件不存在则创建
        "r+"，读和写。文件必须存在
        "w+"，读和写。如果文件不存在，则创建，如果存在则重写
        "a+"，追加数据。如果文件不存在则创建
        "b"，二进制文件。
2. 关闭文件
    int fclose(FILE *fp);
3. 读取字符串（一行）
    char *fgets(char *str, int count, FILE *stream);
4. 写入字符串
    int fputs(const char *str, FILE *stream);
5. 读取数据
    size_t fread(void *buffer, size_t size, size_t count, FILE *stream);
        size：要操作的单个数据的大小。例如，int型数据的大小就是sizeof(int)
        count：数据个数
6. 写入数据
    sint fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
7. 成功返回当前读写位置
    long ftell(FILE *stream);
        SEEK_CUR：文件指针当前位置
        SEEK_END：文件末尾处
        SEEK_SET：文件开始处
8. 设置读写位置
    int fseek(FILE *strean, long offset, int whence); 
9. 重置读写位置０
    void rewind(FILE *stream);
 */

void ReadFile()
{
    const char *filename = "./read_file.txt";
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        LOGINFO("fopen failed");
        return;
    }

    if (ftell(fp) != SEEK_END) {
        char data[128] = {0};
        fgets(data, sizeof(data), fp); // 读取一行数据
        LOGINFO("read file ... fgets: %s", data);
        fread(data, sizeof(data), 1, fp); // 读取制定大小数据
        LOGINFO("read file ... fread: %s", data);
    }
    fclose(fp);
}

void WriteFile()
{
    const char *filename = "./wrtie_file.txt";
    FILE* fp = fopen(filename, "a");
    if (!fp) {
        LOGINFO("fopen failed");
        return;
    }

    for (int i = 0; i < 5; i++) {
        char data[128] = {0};
        sprintf(data, "This is wrtie file test[%d]!\n", i);
        fputs(data, fp);
        LOGINFO("wrtie file ..."); 
    }
    fclose(fp);
}




/* 
C++文件操作类
    ifstream：读取文件流
    ofstream：文件写入流
    fstream：文件读取/写入流
1. 打开文件
    void open(const char *filename, ios_base::openmode mode = ios_base::in | ios_base::out);
        ios::in     为输入(读)而打开文件                                                     
        ios::out    为输出(写)而打开文件   
        ios::ate	初始位置为文件末尾
        ios::app	所有输出追加在文件末尾             
        ios::trunc	如果文件已存在则清空
        ios::binary	二进制方式
2. 获得流指针位置
    long tellg();
    long tellp();
        ios::cur    文件流当前位置
        ios::beg    文件开始位置
        ios::end    文件末尾位置
3. 设置流指针位置
    seekg(off_type offset, seekdir direction);
    seekp(off_type offset, seekdir direction);
 */

void ReadFileCpp()
{
    const char *filename = "./read_file.txt";
    ifstream readfile(filename);
    // ifstream readfile;
    // readfile.open(filename);
    if (!readfile.is_open()) {
        LOGINFO("open failed");
        return;
    }

    while (!readfile.eof()) {
        string data;
        readfile >> data; // 按空格、换行符分割
        LOGINFO("read file: %s", data.c_str());
    }
    readfile.close();
}

void WriteFileCpp()
{
    const char *filename = "./wrtie_file.txt";
    ofstream writefile(filename);
    // ofstream writefile;
    // writefile.open(filename);
    if (!writefile.is_open()) {
        LOGINFO("open failed");
        return;
    }

    for (int i = 0; i < 5; i++) {
        char data[128] = {0};
        sprintf(data, "This is wrtie file test[%d]!\n", i);
        writefile << data;
        LOGINFO("wrtie file ..."); 
    }
    writefile.close();
}

int main(int argc, char *argv[])
{
    ReadFile();
    WriteFile();
    ReadFileCpp();
    WriteFileCpp();
    return 0;
}

/* g++ -std=c++11 File.cpp */