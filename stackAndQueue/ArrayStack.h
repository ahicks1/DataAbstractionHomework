#include "Stack.h"
template<typename T>
class ArrayStack: public Stack<T> {
    public:
        ArrayStack();
        ArrayStack(const ArrayStack<T> &obj);
        ~ArrayStack();
        void push(const T &t);
        T pop();
        T peek() const;
        bool isEmpty() const;

    private:
        int size;
        int arraySize;
        T* array;
};

//Default Constructor
template<typename T>
ArrayStack<T>::ArrayStack():array{new T[arraySize]},size{0},arraySize{10}{}

//Copy Constructor
template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &obj){
  size = obj.size;
  arraySize = obj.arraySize;
  array = new T[arraySize];
  for(int i = 0; i<arraySize; i++)
  {
    array[i] = obj.array[i];
  }

};

//Deconstructor
template<typename T>
ArrayStack<T>::~ArrayStack()
{
    delete[] array;
};

template<typename T>
void ArrayStack<T>::push(const T &t){
    if( size >= arraySize)
    {
        T* bigger = new T[arraySize*2];
        for(int i =0; i<size; i++)
        {
            bigger[i] = array[i];
        };
        delete[] array;
        array = bigger;
        arraySize = arraySize*2;
    }
    array[size] = t;
    size += 1;
};

template<typename T>
T ArrayStack<T>::pop(){
    if(size <= 0) throw "No elements in stack";
    T& ret = array[size-1];
    size -= 1;
    return ret;
};

template<typename T>
T ArrayStack<T>::peek() const{
    if(size <= 0) throw "No elements in stack";
    return array[size-1];
};

template<typename T>
bool ArrayStack<T>::isEmpty() const{
   return (size == 0);
};
