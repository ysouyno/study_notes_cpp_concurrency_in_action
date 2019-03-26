#include <exception>
#include <memory>

struct empty_stack : std::exception
{
  const char *what() const throw() { return nullptr; }
};

template<typename T>
class threadsafe_stack
{
public:
  threadsafe_stack();
  threadsafe_stack(const threadsafe_stack&);
  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T);
  std::shared_ptr<T> pop();
  void pop(T&);
  bool empty() const;
};

int main(int argc, char *argv[])
{
  return 0;
}
