#include "stack.h"

//cosntructor
template<class T>
Stack<T>::Stack()
{
    top = NULL;
}//END Stack()


//return true if the stack is empty
template<class T>
bool Stack<T>::isEmpty()
{
    return top == NULL; 
}//END isEmpty()


template<class T>
//pre-condition: Stack cannot be empty
T& Stack<T>::pop()
{
    if(!isEmpty())
    {
        Node<T>* tmp = new Node<T>;
        tmp = top;
        top = top->next;
        return tmp->value;
     }
     else
     {
        cout<<"\n Error:Empty Stack "<<endl;
        exit(0);
     }
}//END pop()


//return the top value of the stack
//precondition: stack must not be empty
template<class T>
T& Stack<T>::peek()
{
	return top->value;
}//End peek()


//FILO, built stack serves as stack
template<class T>
bool Stack<T>::push(const T& item)
{
    Node<T>* current = new Node<T>;
    current -> value = item;
    current -> next = NULL;
   
    if(isEmpty())
         top = current;
    else
    {
        current ->next = top;
        top = current;
    }//end else
 
    return true;
}//END push()


//FIFO, to built a queue
template<class T>
bool Stack<T>::qpush(const T& item)
{
	Node<T>* current = new Node<T>;
	current -> value = item;
	current -> next = NULL;

	if(isEmpty())
		top = current;
	else
	{
		Node<T>* tmp = top;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = current;
	}
	return true;
}//end of qpush()


//return true when the item is in the stack
template<class T>
bool Stack<T>::isInStack(const T& item)
{
	Node<T>* current = top;
	while(current)
	{
		if(current->value == item)
			return true;
		current = current->next;
	}
	return false;
}//END isInStack()


//return the index'th item of the stack
template<class T>
T& Stack<T>::peekIndex(const int& index)
{
	//if index is out bound, stop program
	if(index>size())
	{
		cout<<"\nError:out of bound"<<endl;
		exit(0);
	}
	Node<T>* current = top;
	
	for(int i = 1; i<index; ++i)
	       current = current->next;

	return current->value;
}//END of the peekIndex()


//return the size of the stack
template<class T>
int Stack<T>::size()
{
	int count = 0;
	Node<T>* tmp = top;
	while(tmp)
	{
		tmp = tmp->next;
		++count;
	}
	return count;
}//END of the size()



