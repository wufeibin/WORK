/*
单例模式：使用最广泛的设计模式，其意图是保证一个类仅有一个实例，并提供一个全局访问接口。
*/

// 饿汉模式：立即加载，在类初始化时主动创建实例。由于在所有线程执行前初始化，不用考虑线程安全。但在部分情况下，可能使用不到单例也被初始化了，造成性能浪费。
class Single
{
private:
	Single(){};
	~Single(){};
	static Single m_Ins;
public:
	static Single* GetInstance();
	{
		return &m_Ins;
	}
}
Single Single::m_Ins;	//定义为静态成员变量，main执行前静态初始化过程中对象已经被分配


// 懒汉模式：延迟加载，第一次使用时创建实例。
class Single
{
private:
	Single(){};
	~Single(){};
	Single m_Ins;
public:
	Single* GetInstance()	//方法一：new对象时，存在线程安全问题
	{
		static Single* m_Ins = NULL;
		if(m_Ins == NULL)	//多个线程同时进入，可能会创建出多个对象实例
		{
			m_Ins = new Single();
		}
		return m_Ins;
	}
	Single* GetInstance()	//方法二：使用局部静态变量
	{
		static Single m_Ins;	//C++11标准保证了static变量初始化的线程安全
		return &m_Ins;
	}
	Single* GetInstance()	//方法三：双检查锁
	{
		static Single* m_Ins = NULL;
		if(m_Ins == NULL)	//防止多个线程获取单例时阻塞，添加此判断，提高效率
		{
			Lock()	//加锁，防止多个线程同时进入创建实例，解决线程安全问题
			if(m_Ins == NULL)
			{
				m_Ins = new Single();	
				//但其实此处仍存在问题。第一个线程开始new对象实例时，分配了对象内存空间后，指针指向了对象，但是还未将对象初始化；此时第二个线程来获取单例，能获取成功，但是去访问单例对象时会出错。
			}
			UnLock()
		}
		return m_Ins;
	}
}