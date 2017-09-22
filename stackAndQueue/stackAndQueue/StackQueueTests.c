#include <iostream>
#include "ArrayStack.h"
//#include "ArrayQueue.h"

using namespace std;

int testStack();
void checkStackEmpty(ArrayStack<int> *stack);
int main(int argc, char * argv[])
{
    cout << "Testing Stack:\n";
    testStack();
    return 1;
}

int testStack() 
{
    cout << "Creating new Stack\n";
    ArrayStack <int>* stack = new ArrayStack<int>();
    checkStackEmpty(stack);
    cout << "pushing to the stack:\n";
    stack->push(21);
    checkStackEmpty(stack);
    cout << "peeking the stack: " << stack->peek() << "\n";
    checkStackEmpty(stack);
    cout << "popping the stack: " << stack->pop() << "\n";
    checkStackEmpty(stack);
    try
    { 
        cout << "popping the stack: " << stack->pop() << "\n";
    } 
    catch (char const* e)
    {
        cout << "An execption occured: " << e <<"\n";
    }
    checkStackEmpty(stack);
    cout << "pushing 100 ints to stack:\n";
    for(int i =0; i< 100; i++)
    {
        stack->push(i);
    }
    cout << "popping 100 ints from stack:\n";
    for(int i =0; i< 100; i++)
    {
        cout << stack->pop() << ", ";
    }
    cout << "\n";
    checkStackEmpty(stack);


    delete stack; 
}

void checkStackEmpty(ArrayStack<int> *stack)
{
    cout << "stack is Empty:  "<< (stack->isEmpty() ? "True" : "False") <<"\n";
}
