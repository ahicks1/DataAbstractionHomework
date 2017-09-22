
template<typename T>
void swap(T& a, T& b)
{
  T temp = a;
  a = b;
  b = temp;
}


int main()
{
  int i = 7;
  int j = 8;

  swap(i,j);
  return 1;
}
