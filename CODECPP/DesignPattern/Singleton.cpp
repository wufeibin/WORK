/*
 * 单例模式：使用最广泛的设计模式，其意图是保证一个类仅有一个实例，并提供一个全局访问接口。
 */

#include "../common.h"

// 饿汉模式：立即加载，在类初始化时主动创建实例。由于在所有线程执行前初始化，不用考虑线程安全。但在部分情况下，可能使用不到单例也被初始化了，造成性能浪费。
class SingleHungry {
private:
    SingleHungry() {}
    ~SingleHungry() {}
    static SingleHungry ins;

public:
    static SingleHungry* GetInstance() {
        return &ins;
    }
    
    void print() {
        printf("SingleHungry this:%p\n", this);
    }
};
SingleHungry SingleHungry::ins; // 静态成员变量，main执行前静态初始化过程中对象已经被分配。


// 懒汉模式：延迟加载，第一次使用时创建实例。
class SingleLazy {
private:
    SingleLazy() {}
    ~SingleLazy() {}

public:
    // 方法一：使用局部静态变量
    static SingleLazy* GetInstance1() {
        static SingleLazy ins; // C++11标准保证了static变量初始化的线程安全
        return &ins;
    }

    // 方法二：通过new对象，存在线程安全问题
    static SingleLazy* GetInstance2() {
        static SingleLazy* pIns = NULL;
        if (pIns == NULL) { // 多个线程同时进入，可能会创建出多个对象实例
            pIns = new SingleLazy();
        }
        return pIns;
    }

    // 方法三：双检查锁
    static SingleLazy* GetInstance3() {
        static std::mutex insMutex;
        static SingleLazy* pIns = NULL;
        if (pIns == NULL) { // 防止多个线程获取单例时阻塞，添加此判断，提高效率
            std::lock_guard<std::mutex> lk(insMutex); // 加锁，防止多个线程同时进入创建实例，解决线程安全问题
            if (pIns == NULL) {
                // 此处仍存在问题。第一个线程开始new对象实例时，分配了对象内存空间后，指针指向了对象，但是还未将对象初始化；此时第二个线程来获取单例，能获取成功，但是去访问单例对象时会出错。
                pIns = new SingleLazy();	
            }
        }
        return pIns;
    }

    void print() {
        printf("SingleLazy this:%p\n", this);
    }
};


int main()
{
    SingleHungry::GetInstance()->print();
    SingleLazy::GetInstance1()->print();
    SingleLazy::GetInstance2()->print();
    SingleLazy::GetInstance3()->print();
    return 0;
}
