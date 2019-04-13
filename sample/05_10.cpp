#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <cassert>
#include <chrono>

struct X
{
  int i;
  std::string s;
};

std::atomic<X *> p;
std::atomic<int> a;

void create_x()
{
  X *x = new X;
  x->i = 42;
  x->s = "hello";
  a.store(99, std::memory_order_relaxed); // 1
  p.store(x, std::memory_order_release); // 2
}

void use_x()
{
  using namespace std::chrono_literals;

  X *x;
  while (!(x = p.load(std::memory_order_consume))) // 3
    std::this_thread::sleep_for(1s);

  std::cout << "x->i: " << x->i << std::endl;
  std::cout << "x->s: " << x->s << std::endl;
  std::cout << "a.load(): " << a.load() << std::endl;

  assert(x->i == 42); // 4
  assert(x->s == "hello"); // 5
  assert(a.load(std::memory_order_relaxed) == 99); // 6
}

int main(int argc, char *argv[])
{
  std::thread t1(create_x);
  std::thread t2(use_x);
  t1.join();
  t2.join();

  return 0;
}
