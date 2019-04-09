#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

class spinlock_mutex
{
  std::atomic_flag flag;

public:
  spinlock_mutex() :
    flag(ATOMIC_FLAG_INIT)
  {}

  void lock()
  {
    while (flag.test_and_set(std::memory_order_acquire));
  }

  void unlock()
  {
    flag.clear(std::memory_order_release);
  }
};

void f(int n)
{
  static spinlock_mutex sm;

  for (int cnt = 0; cnt < 100; ++cnt) {
    sm.lock();
    std::cout << "output from thread " << n << std::endl;
    sm.unlock();
  }
}

void test_spinlock_mutex()
{
  std::vector<std::thread> v;

  for (int n = 0; n < 10; ++n) {
    v.emplace_back(f, n);
  }

  for (auto& t : v) {
    t.join();
  }
}

int main(int argc, char *argv[])
{
  test_spinlock_mutex();

  return 0;
}
