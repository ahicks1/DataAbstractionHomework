#include <iostream>
#include "HashMap.h"

using namespace std;
int main() {
  auto hf = [](int x){return x;};
  HashMap<int,int,decltype(hf)> hm(hf);
  hm[125] = 30;
  hm[25] = 60;
  //hm.erase(25);
  cout << hm[125] << endl;

  for(int i = 0; i < 20000; i++) {
    hm[i] = i*2;
  }
  for(int i = 0; i < 20000; i++) {
    cout << hm[i] << endl;
  }
  hm.insert(pair<int,int>(3,89));
  auto hm2 = hm;
  for(auto elem:hm2){
    cout << elem.second << endl;
  }
  if(hm2 == hm) {
    cout << "Equality check True" << endl;
  }
}
