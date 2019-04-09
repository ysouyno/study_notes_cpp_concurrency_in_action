#include <iostream>
#include <atomic>

void test_compare_exchange_weak()
{
  bool expected = false;
  std::atomic<bool> b;
  bool x = b.compare_exchange_weak(expected, true);
  std::cout << "x: " << std::boolalpha << x << ", b: " << b
            << ", expected: " << expected << std::endl;
}

int main(int argc, char *argv[])
{
  test_compare_exchange_weak();

  return 0;
}
