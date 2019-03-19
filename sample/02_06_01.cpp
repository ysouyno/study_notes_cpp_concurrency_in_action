#include <iostream>
#include <thread>

class scoped_thread
{
  std::thread t;

public:
  explicit scoped_thread(std::thread t_) :
    t(std::move(t_))
  {
    std::cout << "scoped_thread constructor" << std::endl;

    if (!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }

  ~scoped_thread()
  {
    t.join();
  }

  scoped_thread(const scoped_thread &) = delete;
  scoped_thread& operator=(const scoped_thread &) = delete;
};

struct func
{
  int &i;

  func(int &i_) : i(i_)
  {
    std::cout << "func constructor" << std::endl;
  }

  void operator()()
  {
    for (unsigned n = 0; n < 100; ++n) {
      std::cout << i;
      i++;
    }

    std::cout << std::endl;
  }
};

void f()
{
  int some_local_state = 0;
  scoped_thread t(std::thread(func(some_local_state)));

  std::cout << "press any key to quit" << std::endl;
  getchar();
}

int main(int argc, char *argv[])
{
  f();

  return 0;
}
