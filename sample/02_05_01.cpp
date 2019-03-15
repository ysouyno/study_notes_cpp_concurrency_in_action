#include <iostream>
#include <thread>

void some_function()
{
  std::cout << "some_function\n";
}

void some_other_function(int i)
{
  std::cout << "some_other_function(" << i << ")\n";
}

std::thread f()
{
  return std::thread(some_function);
}

std::thread g()
{
  std::thread t(some_other_function, 42);
  return t;
}

int main(int argc, char *argv[])
{
  f().join();
  g().join();

  std::thread t1 = f();
  t1.join();
  std::thread t2 = g();
  t2.join();

  return 0;
}
