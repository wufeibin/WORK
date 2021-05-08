/*
 * 单例模式：使用最广泛的设计模式，其意图是保证一个类仅有一个实例，并提供一个全局访问接口。
 */


// 饿汉模式：立即加载，在类初始化时主动创建实例。由于在所有线程执行前初始化，不用考虑线程安全。但在部分情况下，可能使用不到单例也被初始化了，造成性能浪费。
class Single {
private:
    Single() {}
    ~Single() {}
    static Single ins;

public:
    static Single* GetInstance() {
        return &ins;
    }
};
Single Single::ins; // 静态成员变量，main执行前静态初始化过程中对象已经被分配。


// 懒汉模式：延迟加载，第一次使用时创建实例。
class Single {
private:
    Single() {}
    ~Single() {}
    std::mutex insMutex;

public:
    // 方法一：使用局部静态变量
    static Single* GetInstance1() {
        static Single ins; // C++11标准保证了static变量初始化的线程安全
        return &ins;
    }

    // 方法二：通过new对象，存在线程安全问题
    static Single* GetInstance2() {
        static Single* pIns = NULL;
        if (pIns == NULL) { // 多个线程同时进入，可能会创建出多个对象实例
            pIns = new Single();
        }
        return pIns;
    }

    // 方法三：双检查锁
    static Single* GetInstance3() {
        static Single* pIns = NULL;
        if (pIns == NULL) { // 防止多个线程获取单例时阻塞，添加此判断，提高效率
            std::lock_guard<std::mutex> lk(insMutex); // 加锁，防止多个线程同时进入创建实例，解决线程安全问题
            if (pIns == NULL) {
                // 此处仍存在问题。第一个线程开始new对象实例时，分配了对象内存空间后，指针指向了对象，但是还未将对象初始化；此时第二个线程来获取单例，能获取成功，但是去访问单例对象时会出错。
                pIns = new Single();	
            }
        }
        return pIns;
    }

    void print() {
        printf("Single print\n");
    }
};


int main(int argc, char *argv[])
{
    Single::GetInstance1()->print();
    return 0;
}
