#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
  x.store(true, std::memory_order_release);
}

void write_y()
{
  y.store(true, std::memory_order_release);
}

void read_x_then_y()
{
  while (!x.load(std::memory_order_acquire));
  if (y.load(std::memory_order_acquire)) // 1
    ++z;
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_acquire));
  if (x.load(std::memory_order_acquire)) // 2
    ++z;
}

int main(int argc, char *argv[])
{
  x = false;
  y = false;
  z = 0;

  std::thread a(write_x);
  std::thread b(write_y);
  std::thread c(read_x_then_y);
  std::thread d(read_y_then_x);
  a.join();
  b.join();
  c.join();
  d.join();

  std::cout << "z: " << z.load() << std::endl;
  assert(z.load() != 0); // 3

  return 0;
}
