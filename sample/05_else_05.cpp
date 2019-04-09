#include <iostream>
#include <atomic>
#include <cassert>

void test_fetch_add0()
{
  class Foo {};
  Foo some_array[5];
  std::atomic<Foo *> p(some_array);

  Foo *x = p.fetch_add(2);
  assert(x == some_array);
  assert(p.load() == &some_array[2]);

  x = (p -= 1);
  assert(x == &some_array[1]);
  assert(p.load() == &some_array[1]);
}

void test_fetch_add1()
{
  int some_array[5] = {0, 1, 2, 3, 4};
  std::atomic<int *> p(some_array);

  int *x = p.fetch_add(2);
  std::cout << "*x: " << *x << std::endl;
  std::cout << "*p: " << *p << std::endl;
  std::cout << "*(p.load()): " << *(p.load()) << std::endl;
  assert(*x == 0);
  assert(*p == 2);

  x = (p -= 1);
  std::cout << "*x: " << *x << std::endl;
  std::cout << "*p: " << *p << std::endl;
  std::cout << "*(p.load()): " << *(p.load()) << std::endl;
  assert(*x == 1);
  assert(*p == 1);
}

int main(int argc, char *argv[])
{
  test_fetch_add0();
  test_fetch_add1();

  return 0;
}
