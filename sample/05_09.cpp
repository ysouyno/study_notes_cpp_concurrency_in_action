#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

struct data
{
  int val;
};

std::atomic<int> data[5];
std::atomic<bool> sync1(false), sync2(false);

void thread_1()
{
  data[0].store(42, std::memory_order_relaxed);
  data[1].store(97, std::memory_order_relaxed);
  data[2].store(17, std::memory_order_relaxed);
  data[3].store(-141, std::memory_order_relaxed);
  data[4].store(2003, std::memory_order_relaxed);
  sync1.store(true, std::memory_order_release); // 1
}

void thread_2()
{
  while (!sync1.load(std::memory_order_acquire)); // 2
  sync2.store(true, std::memory_order_release); // 3
}

void thread_3()
{
  while (!sync2.load(std::memory_order_acquire)); // 4

  std::cout << "data[0]: " << data[0].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[1]: " << data[1].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[2]: " << data[2].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[3]: " << data[3].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[4]: " << data[4].load(std::memory_order_relaxed)
            << std::endl;

  assert(data[0].load(std::memory_order_relaxed) == 42);
  assert(data[1].load(std::memory_order_relaxed) == 97);
  assert(data[2].load(std::memory_order_relaxed) == 17);
  assert(data[3].load(std::memory_order_relaxed) == -141);
  assert(data[4].load(std::memory_order_relaxed) == 2003);
}

int main(int argc, char *argv[])
{
  std::thread t1(thread_1);
  std::thread t2(thread_2);
  std::thread t3(thread_3);
  t1.join();
  t2.join();
  t3.join();

  return 0;
}
