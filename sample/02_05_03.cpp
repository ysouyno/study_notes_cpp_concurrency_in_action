#include <iostream>
#include <thread>

void some_function() { std::cout << "some_function()\n"; }

void some_other_function() { std::cout << "some_other_function()\n"; }

int main(int argc, char *argv[]) {
  std::thread t1(some_function);
  std::thread t2 = std::move(t1);
  t1 = std::thread(some_other_function);
  std::thread t3;
  t3 = std::move(t2);
  t1 = std::move(t3);
  std::cout << "main exit\n";

  return 0;
}
