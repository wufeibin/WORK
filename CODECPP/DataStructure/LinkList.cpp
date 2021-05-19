// 单链表
#include<string>
#include<iostream>
using namespace std;

template<typename Type>
struct ListNode {
    ListNode(Type x) : next(NULL), val(x) {}
    ListNode *next;
    Type val;
};

template<typename Type>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void insert(Type val, int pos);
    void remove(Type val);
    int find(const Type &val);
    void reverse();
    const int size();
    void print();

private:
    ListNode<Type> *head;
    int length;
};

template<typename Type>
LinkedList<Type>::LinkedList() {
    head = NULL;
    length = 0;
}

template<typename Type>
LinkedList<Type>::~LinkedList()
{
    ListNode<Type> *del = head;
    while (head->next!= NULL) {
        del = head->next;
        head->next = del->next;
        delete del;
    }
    delete head;
    cout << "析构函数" << endl;
}

template<typename Type>
void LinkedList<Type>::insert(Type val, int pos) {
    if (pos < 0) {
        cout << "The n must be positive" << endl;
        return;
    }
    ListNode<Type> *temp = head;
    ListNode<Type> *node = new ListNode<Type>(val);

    if (head == NULL) {
        head = node;
        ++length;
        return;
    }

    if (pos == 0) {
        node->next= temp;
        head = node;
        ++length;
        return;
    }

    for (int i = 1; i != pos; ++i) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "insert failed" << endl;
        return;
    }
    node->next = temp->next;
    temp->next = node;
    ++length;
}

template<typename Type>
void LinkedList<Type>::remove(Type val)
{
    int pos = find(val);
    if (pos == -1) {
        return;
    }

    if (pos == 1) {
        head = head->next;
        --length;
        return;
    }

    ListNode<Type> *temp = head;
    for (int i = 2; i < pos; ++i) {
        temp = temp->next;
    }
    temp->next = temp->next->next;
    --length;
}

template<typename Type>
int LinkedList<Type>::find(const Type & val)
{
    if (head == NULL)
        return -1;
    ListNode<Type> *temp = head;
    int count = 1;
    while ((temp->val) != val) {
        ++count;
        temp = temp->next;
        if (temp == NULL)
            return -1;
    }
    cout << "LinkedList find : " << count << endl;
    return count;
}

template<typename Type>
void LinkedList<Type>::reverse()
{
    if(head==NULL)
            return;
    ListNode<Type> *froTemp = head, *nextTemp = head->next, *temp;
    while (nextTemp != NULL) {
        temp = nextTemp->next;
        nextTemp->next = froTemp;
        froTemp = nextTemp;
        nextTemp = temp;
    }
    head->next = NULL;
    head = froTemp;
}

template<typename Type>
const int LinkedList<Type>::size()
{
    return length;
}

template<typename Type>
void LinkedList<Type>::print()
{
    cout << "LinkedList print : ";
    ListNode<Type> *temp = head;
    while (temp != NULL) {
        cout << temp->val << " "; // 内置类型
        temp = temp->next;
    }
    cout << endl;
}



int main()
{
	LinkedList<int> list;
	for (int i = 0; i != 10; ++i) {
		list.insert(i, i);
	}
	list.print();

	list.find(1);
	list.remove(2);
	list.print();

	list.reverse();
	list.print();
	cout << "list size : " << list.size() << endl;
    return 0;
}

/* 
LinkedList print : 0 1 2 3 4 5 6 7 8 9 
LinkedList find : 2
LinkedList find : 3
LinkedList print : 0 1 3 4 5 6 7 8 9 
LinkedList print : 9 8 7 6 5 4 3 1 0 
list size : 9
析构函数
 */
