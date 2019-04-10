#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>

int data;
std::atomic<bool> flag(false);

void producer()
{
  data = 42;            // 1
  flag.store(true);     // 2
}

void consume()
{
  while (!flag.load()); // 3
  assert(data == 42);   // 4
}

int main(int argc, char *argv[])
{
  std::thread ta(producer);
  std::thread tb(consume);
  ta.join();
  tb.join();

  return 0;
}
