#include <iostream>
#include <string>
#include <thread>

void f(int i, const std::string &s)
{
  std::cout << "i: " << i << std::endl;
  std::cout << "s: " << s << std::endl;
}

void oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, buffer);
  t.join();
}

void not_oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, std::string(buffer));
  t.join();
}

int main(int argc, char *argv[])
{
  oops(23);
  not_oops(32);

  return 0;
}
