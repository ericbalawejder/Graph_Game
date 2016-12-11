#ifndef STACK_H
#define STACK_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<new>
#include<ctime>

using namespace std;

#define TRUE 1;
#define FALSE 0;

template<class Type>
struct Node
{
    Type value;
    Node<Type>* next;
};

template<class Type>
class Stack
{
    public:
        Stack();
        bool isEmpty();
		int size();
        Type& pop();
		Type& peek();
		Type& peekIndex(const int&);
        bool push(const Type& item);
		bool queuePush(const Type& item);
		bool isInStack(const Type&);

    private:
        Node<Type>* top;
   
};
#endif