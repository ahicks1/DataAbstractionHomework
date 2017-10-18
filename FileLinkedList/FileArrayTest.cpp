#include "FileLinkedList.h"
#include <iostream>

using namespace std;

int main() {
  FileLinkedList<int> fa("fal.bin");
  fa.clear();
  bool test = true;
  fa.push_back(3);
  fa.push_back(4);
  fa.pop_back();
  if(fa.size() != 1) {test = false;}
  fa.clear();
  if(fa.size() != 0) {test = false;}
  fa.push_back(3);
  fa.insert(fa.begin(), 5);
  if(fa[0] != 5) {test = false;}
  fa.erase(fa.begin());
  if(fa[0] != 3) {test = false;}
  fa.set(6, 0);
  if(fa[0] != 6) {test = false;}
  if (test)
    cout << "simple test passed!\n";
  else
    cout << "simple test failed\n";
  fa.clear();

  FileLinkedList<string> fastr("falstr.bin");
  fastr.clear();
  test = true;
  fastr.push_back("3");
  fastr.push_back("4");
  fastr.pop_back();
  if(fastr.size() != 1) {test = false;}
  fastr.clear();
  if(fastr.size() != 0) {test = false;}
  fastr.push_back("3");
  fastr.insert(fastr.begin(), "5");
  if(fastr[0] != "5") {test = false;}
  fastr.erase(fastr.begin());
  if(fastr[0] != "3") {test = false;}
  fastr.set("6", 0);
  if(fastr[0] != "6") {test = false;}
  if (test)
    cout << "string test passed!\n";
  else
    cout << "string test failed\n";
  for(int i = 0; i < 20000; i++) {
    fa.push_back(i);
  }
  int x = 0;
  test = true;
  for(auto elem:fa){
    if(elem != x) test = false;
    x++;
  }
  if (test)
    cout << "big push test passed!\n";
  else {
    cout << "big push test failed\n";
    return -1;
  }

  FileLinkedList<int> fa2(fa.begin(),fa.end(),"fal2.bin");
  test = true;
  x = 0;
  for(auto elem:fa){
    if(elem != x) test = false;
    x++;
  }
  if (test)
    cout << "big copy test passed!\n";
  else {
    cout << "big copy test failed\n";
    return -1;
  }
  for(int i = 0; i < 20000; i++) {
    fa.pop_back();
  }





}
