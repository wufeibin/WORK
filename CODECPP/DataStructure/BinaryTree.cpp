#include<iostream>
#include<stack>
#include<queue>
using namespace std;

// 节点结构体
struct Node {
    Node(int value) : value(value), left(NULL), right(NULL) {}
    int value;
    Node *left;
    Node *right;
};

// 构建二叉树
void inertNode(Node *node, int value)
{
    if (value <= node->value) {
        if (!node->left) {
            node->left = new Node(value);
        } else {
            inertNode(node->left, value);
        }
    } else {
        if (!node->right) {
            node->right = new Node(value);
        } else {
            inertNode(node->right, value);
        }
    }
}

// 前序遍历递归实现
void preOrder(Node *node)
{
    if (node) {
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

// 中序遍历递归实现
void inOrder(Node *node)
{
    if (node) {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }
}

// 后序遍历递归实现
void posOrder(Node *node)
{
    if (node) {
        posOrder(node->left);
        posOrder(node->right);
        cout << node->value << " ";
    }
}

// 前序遍历非递归实现
void preOrder1(Node *node)
{
    if (!node) {
        return;
    }

    stack<Node *> _stack;
    _stack.push(node);
    while (!_stack.empty()) {
        Node *temp = _stack.top();
        cout << temp->value << " ";
        _stack.pop();
        if (temp->right) {
            _stack.push(temp->right);
        }
        if (temp->left) {
            _stack.push(temp->left);
        }
    }
}

// 中序遍历非递归实现
void inOrder1(Node *node)
{
    if (!node) {
        return;
    }

    stack<Node *> _stack;
    Node *temp = node;
    while (temp || !_stack.empty()) {
        if (temp) {
            _stack.push(temp);
            temp = temp->left;
        } else {
            temp = _stack.top();
            cout << temp->value << " ";
            _stack.pop();
            temp = temp->right;
        }
    }
}

// 后序遍历非递归实现
void posOrder1(Node *node)
{
    if (!node) {
        return;
    }

    stack<Node *> _stack1, _stack2;
    _stack1.push(node);
    while (!_stack1.empty()) {
        Node *temp = _stack1.top();
        _stack1.pop();
        _stack2.push(temp);
        if (temp->left) {
            _stack1.push(temp->left);
        }
        if(temp->right) {
           _stack1.push(temp->right);
        }
    }

    while (!_stack2.empty()) {
        cout << _stack2.top()->value << " ";
        _stack2.pop();
    }
}

// 广度优先遍历
void broadOrder(Node *node)
{
    if (!node) {
        return;
    }
    
    queue<Node *> _qnode;
    _qnode.push(node);
    while (!_qnode.empty()) {
        Node * temp = _qnode.front();
        cout << temp->value << " ";
        _qnode.pop();
        if (temp->left) {
            _qnode.push(temp->left);
        }
        if (temp->right) {
            _qnode.push(temp->right);
        }
    }
}



int main()
{
    int array[10] = {5, 3, 7, 2, 4, 6, 8, 1, 9, 10};
    Node root(array[0]);
    for (int i = 1; i < 10; ++i) {
        inertNode(&root, array[i]);
    }
    
    cout << "preOrder : ";
    preOrder(&root);
    cout << endl;

    cout << "inOrder : ";
    inOrder(&root);
    cout << endl;

    cout << "posOrder : ";
    posOrder(&root);
    cout << endl;
    
    cout << "preOrder1 : ";
    preOrder1(&root);
    cout << endl;
    
    cout << "inOrder1 : ";
    inOrder1(&root);
    cout << endl;
    
    cout << "posOrder1 : ";
    posOrder1(&root);
    cout << endl;
    
    cout << "broadOrder : ";
    broadOrder(&root);
    cout << endl;

    return 0;
}

/* 
preOrder : 5 3 2 1 4 7 6 8 9 10 
inOrder : 1 2 3 4 5 6 7 8 9 10 
posOrder : 1 2 4 3 6 10 9 8 7 5 
preOrder1 : 5 3 2 1 4 7 6 8 9 10 
inOrder1 : 1 2 3 4 5 6 7 8 9 10 
posOrder1 : 1 2 4 3 6 10 9 8 7 5 
broadOrder : 5 3 7 2 4 6 8 1 9 10 
 */