#include "Stack.h"
template<typename T>
class ArrayStack: public Stack<T> {
    public:
        ArrayStack():array{new T[arraySize]}{}
        ~ArrayStack(){
            delete[] array;
        };
        void push(const T &t){
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
        T pop(){
            if(size <= 0) throw "No elements in stack";
            T& ret = array[size-1];
            size -= 1;
            return ret;
        };
        T peek() const{
            if(size <= 0) throw "No elements in stack";
            return array[size-1];
        };
        bool isEmpty() const{
            return (size == 0);
        };

    private:
        int size = 0;
        int arraySize = 10;
        T *array;
};
