#include "common.h"
#include "cpp_class.h"
#include "cpp_basic.h"
#include "file.h"

/*
 * 类型命名风格：
 * 【大驼峰】类类型、结构体类型、枚举类型、联合体类型、作用域名称
 * 【大驼峰】函数（包括全局函数，作用域函数，成员函数）
 * 【小驼峰】全局变量（包括全局和命名空间域下的变量，类静态变量）、局部变量、函数参数、类/结构体/联合体中的成员变量 
 * 【全大写，下划线分割】宏、常量、枚举值、goto标签
 */


// 函数指针回调
void CallbackTest();
typedef int (*FUNC_PTR)(int, string);
class CallBack {
public:
    CallBack() : m_call_back_ptr(nullptr) {};
    ~CallBack() {};
    void Register(FUNC_PTR call_back_ptr);
    void Test();

private:
    FUNC_PTR m_call_back_ptr;
};

static int CallbackFunc(int i, string str)
{
    LOGINFO("%d, %s", i, str.c_str());
    return 0;
}

void CallbackTest()
{
    CallBack cb;
    cb.Register(&CallbackFunc);
    cb.Test();
}

void CallBack::Register(FUNC_PTR call_back_ptr)
{
    m_call_back_ptr = call_back_ptr;
}

void CallBack::Test()
{
    if (m_call_back_ptr) {
        (*m_call_back_ptr)(1, "test1");
        m_call_back_ptr(1, "test2");
    }
}

int main(int argc, char *argv[])
{
    LOGINFO("main start ...");
    CallbackTest();
    LOGINFO("main end ...");
    return 0;
}


/* 线程池
#include <iostream>
#include <vector>
#include <chrono>
#include "ThreadPool.h"

int main()
{
    // create thread pool with 4 worker threads
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}

*/



/* 

2. Mat类

cv::Mat 类由两个数据部分组成：矩阵头（包含矩阵尺寸，存储方法，存储地址等信息）和一个指向存储所有像素值矩阵的指针。OpenCV函数中输出图像的内存分配是自动完成的，使用OpenCV的C++接口时不需要考虑内存释放问题。赋值运算符和拷贝构造函数只拷贝信息头，使用函数 clone()  或者 copyTo() 来拷贝一副图像的矩阵。

cv::Mat 类的对象有一个成员函数 type() 用来返回矩阵元素的数据类型，返回值是 int 类型，不同的返回值代表不同的类型。

  类型    	C1  	C2  	C3  	C4  
  CV_8U 	0   	8   	16  	24  
  CV_8S 	1   	9   	17  	25  
  CV_16U	2   	10  	18  	26  
  CV_16S	3   	11  	19  	27  
  CV_32S	4   	12  	20  	28  
  CV_32F	5   	13  	21  	29  
  CV_64F	6   	14  	22  	30  

- C1、C2、C3、C4 指的是通道Channel数。如灰度图像只有1个通道，是C1；JPEG格式 的 RGB 彩色图像就是3个通道，是 C3；PNG 格式的彩色图像除了 RGB 3个通道外，还有一个透明度通道，所以是C4。
- 8U 表示 8 位无符号整数，16S 表示 16 位有符号整数，64F 表示 64 位浮点数。

常用构造函数：

1. Mat::Mat() 无参数构造方法。
2. Mat::Mat(int rows, int cols, int type) 创建行数为 rows，列数为 cols，类型为 type 的图像。
3. Mat::Mat(Size size, int type) 创建大小为 size，类型为 type 的图像。
4. Mat::Mat(int rows, int cols, int type, const Scalar& s) 创建行数为 rows，列数为 cols，类型为 type 的图像，并将所有元素初始化为值 s。（Scalar是个short型vector）
5. Mat::Mat(Size size, int type, const Scalar& s) 创建大小为 size，类型为 type 的图像，并将所有元素初始化为值 s。
6. Mat::Mat(const Mat& m) 将m赋值给新创建的对象，不会对图像数据进行复制，m和新对象共用图像数据。
7. Mat::Mat(int rows, int cols, int type, void* data, size_t step=AUTO_STEP)  创建行数为 rows，列数为 cols，类型为 type 的图像，此构造函数不创建图像数据所需内存，而是直接使用 data 所指内存，图像的行步长由 step 指定。
8. Mat::Mat(Size size, int type, void* data, size_t step=AUTO_STEP)  创建大小为 size，类型为 type 的图像，此构造函数不创建图像数据所需内存，而是直接使用 data 所指内存，图像的行步长由 step 指定。
9. Mat::Mat(const Mat& m, const Range& rowRange, const Range& colRange) 创建的新图像为 m 的一部分，具体的范围由 rowRange 和 colRange 指定，此构造函数也不进行图像数据的复制操作，新图像与 m 共用图像数据。
10. Mat::Mat(const Mat& m, const Rect& roi) 创建的新图像为 m 的一部分，具体的范围 roi 指定，此构造函数也不进行图像数据的复制操作，新图像与 m 共用图像数据。

    class CV_EXPORTS Mat {
    public:
        int flags; // 包含许多关于矩阵的信息，如：Mat的标识、数据是否连续、深度、通道数目
        int dims; // 矩阵的维数，大于或等于2
        int rows, cols; // 矩阵的行数和列数
        uchar* data; // 指向数据的指针
        int* refcount; // 指向引用计数的指针
        ···
    };

单行/单列操作：

    Mat Mat::row(int i) const 
    Mat Mat::col(int j) const
    Mat line = A.row(i);

多行或多列操作：

    Mat A = Mat::eye(10, 10, CV_32S);
    Mat B = A(Range::all(), Range(1, 3));
    Mat C = B(Range(5, 9), Range::all());

区域操作：

    Mat img(Size(320,240),CV_8UC3);
    Mat roi(img, Rect(10,10,100,100));
    Mat roi2 = img(Rect(10,10,100,100));
    Mat roi3 = img(Range(10,100),Range(10,100));

读写像素图片：

    Mat grayim(600, 800, CV_8UC1);
    Mat colorim(600, 800, CV_8UC3);
    
    for (int i = 0; i < grayim.rows; i++) {
        for (int j = 0; j < grayim.cols; j++) {
            grayim.at<uchar>(i, j) = (i + j) % 255; // at读写矩阵中的像素
        }
    }
    
    for (int i = 0; i < colorim.rows; i++) {
        for (int j = 0; j < colorim.cols; j++) {
            Vec3b pixel;
            pixel[0] = i % 255; // Blue
            pixel[1] = j % 255; // Green
            pixel[2] = 0; // Red
            colorim.at<Vec3b>(i, j) = pixel;
        }
    }

编解码操作：imdecode、imencode




 */