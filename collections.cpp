#include <vector>
#include <iostream>

template<typename C>
typename C::value_type mymax(C& coll) {
  typename C::value_type best = *coll.begin();
  for(auto e: coll) {
    if(best < e) best = e;
  }
  return best;
}

int main(){
  std::vector<int> = {3,1,4,5,2};
  std::cout << mymax(v);
}
