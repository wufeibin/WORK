/*
观察者模式：一个被观察者对象Subject的状态发生改变，通知所有的观察者Observer对象。 
*/

#include "../common.h"

class Observer { // 抽象观察者
protected:
    string name;
public:
    Observer(string name) {
        this->name = name;
    }

    virtual void update(string action) = 0;
};

class StockObserver : public Observer { // 具体的观察者，看股票的
public:
    StockObserver(string name) : Observer(name) {}

    void update(string action) {
        cout << name << " 收到消息：" << action << endl;
        if (action == "梁所长来了！") {
            cout << "我马上关闭股票，装做很认真工作的样子！" << endl;
        }
    }
};

class NBAObserver : public Observer { // 具体的观察者，看NBA的
public:
    NBAObserver(string name) : Observer(name) {}

    void update(string action) {
        cout << name << " 收到消息：" << action << endl;
        if (action == "梁所长来了！") {
            cout << "我马上关闭NBA，装做很认真工作的样子！" << endl;
        }
    }
};


class Subject { // 抽象被观察者
protected:
    list<Observer*> observers;
public:
    virtual void attach(Observer*) = 0;
    virtual void detach(Observer*) = 0;
    virtual void notify(string action) = 0;
};

class SecretarySubject : public Subject { // 具体被观察者，秘书发出通知
    void attach(Observer *observer) {
        observers.push_back(observer);
    }

    void detach(Observer *observer) {
        list<Observer *>::iterator iter = observers.begin();
        while (iter != observers.end()) {
            if ((*iter) == observer) {
                observers.erase(iter);
            }
            ++iter;
        }
    }
    
    void notify(string action) {
        list<Observer *>::iterator iter = observers.begin();
        while (iter != observers.end()) {
            (*iter)->update(action);
            ++iter;
        }
    }
};

 
int main()
{
    Subject *sub = new SecretarySubject();
    Observer *xs = new NBAObserver("xiaoshuai");
    Observer *zy = new NBAObserver("zouyue");
    Observer *lm = new StockObserver("limin");

    sub->attach(xs);
    sub->attach(zy);
    sub->attach(lm);

    sub->notify("去吃饭了！");
    sub->notify("梁所长来了！");
    return 0;
}