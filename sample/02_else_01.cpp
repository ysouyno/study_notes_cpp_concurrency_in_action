#include <iostream>
#include <thread>

class background_task
{
public:
  void operator()() const
  {
    std::cout << "operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  background_task f;

  // output: operator()
  // std::thread my_thread(f);

  // output: nothing
  // std::thread my_thread(background_task());

  // output: operator()
  // std::thread my_thread((background_task()));

  // output: operator()
  std::thread my_thread{background_task()};

  my_thread.join();

  return 0;
}
