#include <iostream>
#include <atomic>

void test_std_atomic_bool()
{
  std::atomic<bool> b;

  bool x = b.load(std::memory_order_acquire);
  std::cout << "x: " << std::boolalpha << x
            << ", b: " << b << std::endl;

  b.store(true);
  std::cout << "x: " << std::boolalpha << x
            << ", b: " << b << std::endl;

  x = b.exchange(false, std::memory_order_acq_rel);
  std::cout << "x: " << std::boolalpha << x
            << ", b: " << b << std::endl;
}

int main(int argc, char *argv[])
{
  test_std_atomic_bool();

  return 0;
}
