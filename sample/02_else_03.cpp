#include <iostream>
#include <string>
#include <thread>

void f(int i, const std::string &s)
{
  std::cout << "i: " << i << std::endl;
  std::cout << "s: " << s << std::endl;
}

int main(int argc, char *argv[])
{
  std::thread t(f, 3, "hello");
  t.join();

  return 0;
}
