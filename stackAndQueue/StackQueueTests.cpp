#include <iostream>
#include <string>
#include "ArrayStack.h"
#include "ArrayQueue.h"

using namespace std;

int testStack();
int testQueue();
void checkStackEmpty(ArrayStack<int> &stack);
template<typename T>
void checkEmpty(T &stack);
int main(int argc, char * argv[])
{
    //cout << "Testing Stack:\n";

    testQueue();
    testStack();
    return 1;
}

int testQueue()
{
  bool passed = true;
  cout << "Creating new Queue" << endl;
  ArrayQueue<int> queue;
  queue.enqueue(-1);

  for(int i = 0; i < 10000; i++)
  {
      queue.enqueue(i);
      if (queue.peek() != i-1) passed = false;
      if (queue.dequeue() != i-1) passed = false;
  }
  queue.dequeue();
  if(passed) { cout << "Passed int test! "<< endl;}
  else {cout << "Failed int test!" << endl;}
  checkEmpty(queue);


  cout << "Enqueueing 10,000 ints" << endl;
  passed = true;
  for(int i = 0; i < 10000; i++)
  {
    if(i % 2 == 0)
    {
      queue.enqueue(-1);
    } else {
      queue.enqueue(i);
    }
  }

  checkEmpty(queue);
  ArrayQueue<int> queueCpy = queue;
  cout << "Dequeueing 10,000 ints" << endl;
  for(int i = 0; i < 10000; i++)
  {
    if(i % 2 == 0)
    {
      if (queue.dequeue() != -1) passed = false;
    } else
    {
      if (queue.dequeue() != i) passed = false;
    }

  }
  checkEmpty(queue);
  checkEmpty(queueCpy);
  if(passed) { cout << "Passed enque dequeue int test! "<< endl;}
  else {cout << "Failed enqueue dequeue large test!" << endl;}
  passed = true;
  cout << "Dequeueing 10,000 ints from deep copy" << endl;
  for(int i = 0; i < 10000; i++)
  {
    if(i % 2 == 0)
    {
      if (queueCpy.dequeue() != -1) passed = false;
    } else
    {
      if (queueCpy.dequeue() != i) passed = false;
    }

  }
  if(passed) { cout << "Passed enque dequeue int test! "<< endl;}
  else {cout << "Failed enqueue dequeue large test!" << endl;}

  ArrayQueue<string> fancyQueue;
  fancyQueue.enqueue("World");
  fancyQueue.enqueue("Hello");
  ArrayQueue<string> fancyQueueCpy = fancyQueue;
  cout << fancyQueue.peek() << endl;
  cout << fancyQueue.dequeue() << endl;
  cout << fancyQueue.peek() << endl;
  cout << fancyQueue.dequeue() << endl;

  cout << fancyQueueCpy.peek() << endl;
  cout << fancyQueueCpy.dequeue() << endl;
  cout << fancyQueueCpy.peek() << endl;
  cout << fancyQueueCpy.dequeue() << endl;
  return 1;
}

int testStack()
{
    bool passed = true;
    cout << "Creating new Stack\n";
    ArrayStack<int> stack;
    checkEmpty(stack);
    try
    {
        cout << "popping the stack: " << stack.pop() << "\n";
    }
    catch (char const* e)
    {
        cout << "An execption occured: " << e <<"\n";
    }
    cout << "pushing 10,000 ints to stack:\n";
    for(int i =0; i< 10000; i++)
    {
        stack.push(i);
    }
    checkEmpty(stack);
    cout << "popping 10,000 ints from stack:\n";
    for(int i =0; i< 10000; i++)
    {
        if (stack.peek() != 9999 - i) passed = false ;
        if (stack.pop() != 9999 - i) passed = false ;
    }
    checkEmpty(stack);
    if(passed) { cout << "Passed peek pop int test! "<< endl;}
    else {cout << "Failed peek pop large test!" << endl;}

    //delete stack;

    ArrayStack<string> fancyStack;
    fancyStack.push("World");
    fancyStack.push("Hello");
    ArrayStack<string> fancyStackCpy = fancyStack;
    cout << fancyStack.peek() << endl;
    cout << fancyStack.pop() << endl;
    cout << fancyStack.peek() << endl;
    cout << fancyStack.pop() << endl;

    cout << fancyStackCpy.peek() << endl;
    cout << fancyStackCpy.pop() << endl;
    cout << fancyStackCpy.peek() << endl;
    cout << fancyStackCpy.pop() << endl;

    return 1;
}
template<typename T>
void checkEmpty(T &stack)
{
    cout << "Is Empty:  "<< (stack.isEmpty() ? "True" : "False") <<"\n";
}
