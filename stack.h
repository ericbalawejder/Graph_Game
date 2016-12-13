// stack class in template format

#include<iostream>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<new>
#include<ctime>

using namespace std;

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

// constructor
template<class Type>
Stack<Type>::Stack()
{
    top = NULL;
}

// return true if the stack is empty
template<class Type>
bool Stack<Type>::isEmpty()
{
    return top == NULL; 
}

template<class Type>
// pre-condition: Stack cannot be empty
Type& Stack<Type>::pop()
{
    if(!isEmpty())
    {
        Node<Type>* temp = new Node<Type>;
        temp = top;
        top = top->next;
        return temp->value;
     }
     else
     {
        cout << "\n Error:Empty Stack " << endl;
        exit(0);
     }
}

// return the top value of the stack
// precondition: stack must not be empty
template<class Type>
Type& Stack<Type>::peek()
{
	return top->value;
}

// FILO, built stack serves as stack
template<class Type>
bool Stack<Type>::push(const Type& item)
{
    Node<Type>* current = new Node<Type>;
    current -> value = item;
    current -> next = NULL;
   
    if(isEmpty())
	{
         top = current;
	}
    else
    {
        current ->next = top;
        top = current;
    }
 
    return true;
}

// FIFO, to built a queue
template<class Type>
bool Stack<Type>::queuePush(const Type& item)
{
	Node<Type>* current = new Node<Type>;
	current -> value = item;
	current -> next = NULL;

	if(isEmpty())
	{
		top = current;
	}
	else
	{
		Node<Type>* temp = top;
		while(temp->next)
		{
			temp = temp->next;
		}
		temp->next = current;
	}
	return true;
}

// return true when the item is in the stack
template<class Type>
bool Stack<Type>::isInStack(const Type& item)
{
	Node<Type>* current = top;
	while(current)
	{
		if(current->value == item)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

// return the index item of the stack
template<class Type>
Type& Stack<Type>::peekIndex(const int& index)
{
	// if index is out bound, stop program
	if(index>size())
	{
		cout << "\nError:out of bound" << endl;
		exit(0);
	}
	Node<Type>* current = top;
	
	for(int i = 1; i<index; ++i)
	{
		current = current->next;
	}

	return current->value;
}

// return the size of the stack
template<class Type>
int Stack<Type>::size()
{
	int count = 0;
	Node<Type>* temp = top;
	while(temp)
	{
		temp = temp->next;
		++count;
	}
	return count;
}