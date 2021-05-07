/*
观察者模式：一个被观察者对象Subject的状态发生改变，通知所有的观察者Observer对象。 
*/

#include <iostream>
#include <string>
#include <list>
using namespace std;
 
class Subject;
class Observer	//抽象观察者
{
protected:
	string name;
	Subject *sub;
public:
	Observer(string name, Subject *sub)
	{
		this->name = name;
		this->sub = sub;
	}
	virtual void update() = 0;
};
class StockObserver :public Observer	//具体的观察者，看股票的
{
public:
	StockObserver(string name, Subject *sub) :Observer(name, sub){}
	void update()
	{
		cout << name << " 收到消息：" << sub->action << endl;
		if (sub->action == "梁所长来了！")
		{
			cout << "我马上关闭股票，装做很认真工作的样子！" << endl;
		}
	}
};
class NBAObserver :public Observer	//具体的观察者，看NBA的
{
public:
	NBAObserver(string name, Subject *sub) :Observer(name, sub){}
	void update()
	{
		cout << name << " 收到消息：" << sub->action << endl;
		if (sub->action == "梁所长来了！")
		{
			cout << "我马上关闭NBA，装做很认真工作的样子！" << endl;
		}
	}
};


class Subject	//抽象被观察者
{
protected:
	list<Observer*> observers;
public:
	string action;
	virtual void attach(Observer*) = 0;
	virtual void detach(Observer*) = 0;
	virtual void notify() = 0;
};
class SecretarySubject :public Subject	//具体被观察者，秘书发出通知
{
	void attach(Observer *observer)
	{
		observers.push_back(observer);
	}
	void detach(Observer *observer)
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			if ((*iter) == observer)
			{
				observers.erase(iter);
			}
			++iter;
		}
	}
	void notify()
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			(*iter)->update();
			++iter;
		}
	}
};

 
int main()
{
	Subject *sub = new SecretarySubject();
	Observer *xs = new NBAObserver("xiaoshuai", sub);
	Observer *zy = new NBAObserver("zouyue", sub);
	Observer *lm = new StockObserver("limin", sub);

	sub->attach(xs);
	sub->attach(zy);
	sub->attach(lm);

	sub->action = "去吃饭了！";
	sub->notify();

	sub->action = "梁所长来了！";
	sub->notify();
	return 0;
}