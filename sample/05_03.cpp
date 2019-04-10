#include <iostream>

void foo(int a, int b)
{
  std::cout << a << ", " << b << std::endl;
}

int get_num()
{
  static int i = 0;
  return ++i;
}

int main(int argc, char *argv[])
{
  foo(get_num(), get_num());

  return 0;
}
