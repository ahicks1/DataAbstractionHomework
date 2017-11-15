#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  FILE * f = fopen("text.bin", "w+");
  if(f == nullptr) {
    cout <<"Open file failed\n";
    return -1;
  }
  int i = 42;

  fwrite(&i, sizeof(int), 1, f);

  fseek(f, 0, SEEK_SET);

  int j;
  fread(&j, sizeof(int), 1, f);

  cout<<j <<endl;

  fclose(f);
}
