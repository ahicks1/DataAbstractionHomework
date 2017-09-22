#include <iostream>
#include <string>

#include "ArrayList.h"

using namespace std;

bool TestConstructors ();
bool TestIntPush (ArrayList<int>* lst, int* ints, int num);
bool TestIntPop (ArrayList<int>* lst, int* ints, int num);

int main(int argc, char * argv[]) {
  cout << "Starting test" << endl;
  ArrayList<int> * heapList = new ArrayList<int>();
  ArrayList<int> stackList;
  int singletonList[1] = {5};
  cout << ((TestIntPush(heapList,singletonList,1) && TestIntPush(&stackList,singletonList,1)) ? "Passed push" : "Failed push") << endl;
  cout << ((TestIntPop(heapList,singletonList,1) && TestIntPop(&stackList,singletonList,1)) ? "Passed pop" : "Failed pop") << endl;
}



bool TestIntPush(ArrayList<int>* lst, int* ints, int num) {
  bool passed = true;
  for (int i = 0; i < num; i++) {
    lst->push_back(ints[i]);
  }
  return passed;
}

bool TestIntPop(ArrayList<int>* lst, int* ints, int num) {
  bool passed = true;
  for (int i = 0; i < num; i++) {
    if(lst->pop_back() != ints[i])
      passed = false;
  }
  return passed;
}
