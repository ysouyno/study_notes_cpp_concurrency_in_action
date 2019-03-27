#include <iostream>
#include <mutex>

std::mutex some_mutex;

void prepare_data()
{
  std::cout << "prepare_data()" << std::endl;
}

void do_something()
{
  std::cout << "do_something()" << std::endl;
}

std::unique_lock<std::mutex> get_lock()
{
  extern std::mutex some_mutex;
  std::unique_lock<std::mutex> lk(some_mutex);
  prepare_data();
  return lk;
}

void process_data()
{
  std::unique_lock<std::mutex> lk(get_lock());
  do_something();
}

int main(int argc, char *argv[])
{
  process_data();

  return 0;
}
