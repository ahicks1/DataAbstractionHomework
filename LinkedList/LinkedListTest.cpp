#import <iostream>
#import <string>
#import "LinkedList.h"

using namespace std;

int main() {
  LinkedList<int> lst;
  cout << "Constructor\n";

  cout << "Push_back x10\n";
  for(int i = 0; i < 10; i++) {
    lst.push_back(i);
  }
  cout << "iterators\n";
  for(auto itr = lst.begin(); itr != lst.end(); itr++) {
    cout<<*itr<<endl;
  }
  auto witr = lst.cbegin();
  while(witr != lst.cend()){
      cout<< *(witr++);
  }


  LinkedList<int> newList = lst;
  cout << "Copy Constructor\n";
  cout << "elem at 3 = " << lst[3] << endl;
  cout << "insert at 4 " << endl;
  lst[4] = 9;
  auto itr = lst.begin();
  itr++;
  itr++;
  itr++;
  lst.insert(itr,99);
  itr = lst.erase(itr);
  cout << *itr <<endl;
  cout << "elem at 3 = " << lst[3] << endl;
  for(auto elem:lst){
    cout<<elem<<endl;
  }
  cout << "Clear List\n";
  lst.clear();
  for(auto elem:lst){
    cout<<elem<<endl;
  }
  for(auto elem:newList){
    cout<<elem<<endl;
  }

  LinkedList<string> strlst = LinkedList<string>();
  for(int i = 0; i<20; i++) {
    strlst.push_back("Hello");
  }
  for(auto elem:strlst) {
    cout << elem;
  }
  cout <<endl;

  LinkedList<int> biglst;
  for(int i = 0; i<20000; i++) {
    biglst.push_back(i);
  }
  bool passed = true;
  for(int i = 0; i<20000; i++)
  {
    if(biglst[i] != i) passed = false;
  }
  cout << (passed ? "True" : "False") << endl;



}
