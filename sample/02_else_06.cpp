#include <iostream>
#include <thread>

class X
{
public:
  void do_lengthy_work()
  {
    std::cout << "X::do_lengthy_work() called\n";
  }
};

int main(int argc, char *argv[])
{
  X my_x;
  std::thread t(&X::do_lengthy_work, &my_x);
  t.join();

  return 0;
}
