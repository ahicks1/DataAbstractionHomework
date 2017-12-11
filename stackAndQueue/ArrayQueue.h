#include "Queue.h"
#include <iostream>

using namespace std;
template<typename T>
class ArrayQueue: public Queue<T> {
    public:
        ArrayQueue();
        ArrayQueue(const ArrayQueue<T> &obj);
        ~ArrayQueue();
        void enqueue(const T &t);
        T dequeue();
        T peek() const;
        bool isEmpty() const;

    private:
        int size;
        int position;
        int arraySize;
        T* array;
};

//Default Constructor
template<typename T>
ArrayQueue<T>::ArrayQueue():size{0},position{0},arraySize{10},array{new T[arraySize]}{};

template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T> &obj){
  size = obj.size;
  position = obj.position;
  arraySize = obj.arraySize;
  array = new T[arraySize];
  for(int i = 0; i<arraySize; i++)
  {
    array[i] = obj.array[i];
  }
  

};

template<typename T>
ArrayQueue<T>::~ArrayQueue(){delete[] array;};

template<typename T>
void ArrayQueue<T>::enqueue(const T &t){
  if( size >= arraySize)
  {
    T* newArr = new T[arraySize*2];
    for(int i = 0; i < arraySize; i++)
    {
      newArr[i] = array[(position+i)%arraySize];
    }
    delete[] array;
    array = newArr;
    arraySize = arraySize * 2;
    position = 0;
  }
  array[(position + size) % arraySize] = t;
  size += 1;
};

template<typename T>
T ArrayQueue<T>::dequeue(){
  if(size < 0) throw "No elements in queue";
  T tmp = array[position];
  position = (position + 1) % arraySize;
  size -= 1;
  return tmp;
};

template<typename T>
T ArrayQueue<T>::peek() const{
  if(size < 0) throw "No elements in queue";
  return array[position];
};

template<typename T>
bool ArrayQueue<T>::isEmpty() const{
  return (size <= 0);
};
