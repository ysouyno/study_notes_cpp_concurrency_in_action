#include <iostream>
#include <thread>

void some_function()
{
  std::cout << "some_function\n";
}

void f(std::thread t)
{
  t.join();
}

void g()
{
  f(std::thread(some_function));
  std::thread t(some_function);
  f(std::move(t));
}

int main(int argc, char *argv[])
{
  g();

  return 0;
}
