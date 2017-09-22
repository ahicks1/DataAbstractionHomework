#include <iostream>
#include <string>
#include <assert.h>

#include "ArrayList.h"

using namespace std;

bool TestConstructors ();
bool TestIntPush (ArrayList<int>& lst, int* ints, int num);
bool TestIntPop (ArrayList<int>& lst, int* ints, int num);

int main(int argc, char * argv[]) {
  cout << "Starting test" << endl;
  ArrayList<int> * heapList = new ArrayList<int>();
  ArrayList<int> stackList;
  int BigArray;
  int singletonList[10] = {0,1,2,3,4,5,6,7,8,9};
  cout << ((TestIntPush(*heapList,singletonList,10)) ? "Passed push" : "Failed push") << endl;
  //copyConstructor
  ArrayList<int> listCp = *heapList;
  //default Constructor
  ArrayList<int> emptyList;
  //assignment operator
  emptyList = *heapList;
  assert(listCp[2] == 2);

  TestIntPush(stackList,singletonList,10);
  cout << ((TestIntPop(*heapList,singletonList,10)) ? "Passed pop" : "Failed pop") << endl;
  cout << ((TestIntPop(listCp,singletonList,10)) ? "Passed pop" : "Failed pop") << endl;
  cout << ((TestIntPop(emptyList,singletonList,10)) ? "Passed pop" : "Failed pop") << endl;

  for(int i = 0; i<10000; i++) {
    heapList->insert(i,i);
    listCp.insert(i,i);
    emptyList.push_back(i);
    assert((*heapList)[i] == i);
  }
  assert(heapList->size() == 10000);
  assert(listCp.size() == 10000);
  emptyList.clear();
  assert(emptyList.size() == 0);
  for(int i = 0; i<10000; i++) {
    assert( listCp[0] == i);
    listCp.remove(0);
  }
  for(auto i = heapList->cbegin(); i != heapList->cend(); i++){
    emptyList.push_back(*i);
  }



}



bool TestIntPush(ArrayList<int>& lst, int* ints, int num) {
  bool passed = true;
  for (int i = 0; i < num; i++) {
    lst.push_back(ints[i]);
  }
  for (auto elem:lst)
  {
    cout << elem << endl;
  }
  cout << lst.size() << endl;
  return passed;
}

bool TestIntPop(ArrayList<int>& lst, int* ints, int num) {
  bool passed = true;
  for (int i = num-1; i >= 0; i--) {
    assert(lst[i] == ints[i]);
    lst.pop_back();
      //passed = false;
  }
  return passed;
}
