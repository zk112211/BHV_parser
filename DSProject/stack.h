#ifndef STACK_H
#define STACK_H
#include<assert.h>
#include<iostream>

using namespace std;
const int stackIncreacement = 50;
//enum bool{false,true};
template <class T>
class Stack{
public:
    Stack(int sz = 50);
    void Push(const T& x);
    bool Pop(T &x);
    bool getTop(T& x);
    bool IsEmpty()const {return (top == -1) ? true: false;}
    bool IsFull()const {return (top == maxSize-1) ? true: false;}
    int getSize()const {return top+1;}
    void makeEmpty() {top = -1;}
    friend ostream& operator << (ostream& os, Stack<T>& s);
private:
    T* elements;
    int top;
    int maxSize;
    void overflowProcess();
};

template<class T>
Stack<T>::Stack(int sz):top(-1), maxSize(sz){
    elements = new T[maxSize];
    assert(elements != NULL);
};

template<class T>
void Stack<T>::overflowProcess(){
    T* newArray = new T[maxSize + stackIncreacement];
    if (newArray == NULL) {cerr<<"储存分配失败"<<endl;exit(1);}
    for(int i = 0; i<=top; i++) newArray[i] = elements[i];
    maxSize = maxSize + stackIncreacement;
    delete []elements;
    elements = newArray;
};

template<class T>
void Stack<T>::Push(const T& x){
    if(IsFull() == true) overflowProcess();
    elements[++top] = x;
};

template<class T>
bool Stack<T>::Pop(T& x){
    if (IsEmpty() == true) return false;
    x = elements[top];
    return true;
};

template<class T>
bool Stack<T>::getTop(T& x){
    if (IsEmpty() == true) return false;
    x = elements[top];
    return true;
};

template<class T>
ostream& operator<<(ostream& os, Stack<T>& s){
    os<<"top="<<s.top<<endl;
    for (int i = 0; i <= s.top;i++)
        os<<i<<":"<<s.elements[i]<<endl;
    return os;
};    
#endif
