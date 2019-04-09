#include <iostream>
#include <atomic>

void test_compare_exchange_weak()
{
  bool expected = false;
  std::atomic<bool> b;
  // b.compare_exchange_weak(expected, true);
  while (!b.compare_exchange_weak(expected, true) && !expected);
  std::cout << std::boolalpha << "b: " << b
            << ", expected: " << expected << std::endl;
}

int main(int argc, char *argv[])
{
  test_compare_exchange_weak();

  return 0;
}
