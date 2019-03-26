#include <iostream>
#include <deque>

template<typename T, typename Container = std::deque<T> >
class stack
{
public:
  explicit stack(const Container&);
  explicit stack(Container&& = Container());
  template <class Alloc> explicit stack(const Alloc&);
  template <class Alloc> stack(const Container&, const Alloc&);
  template <class Alloc> stack(Container&&, const Alloc&);
  template <class Alloc> stack(stack&&, const Alloc&);

  bool empty() const;
  size_t size() const;
  T& top();
  const T& top() const;
  void push(const T&);
  void push(T&&);
  void pop();
  void swap(stack&&);
};

template<typename T, typename Container>
stack<T, Container>::stack(Container &&)
{
}

template<typename T, typename Container>
bool stack<T, Container>::empty() const
{
  return false;
}

template<typename T, typename Container>
T& stack<T, Container>::top()
{
  T *t = new T;
  return *t;
}

template<typename T, typename Container>
void stack<T, Container>::pop()
{
}

void do_something(int value)
{
  std::cout << "do_something(" << value << ")" << std::endl;
}

void test()
{
  stack<int> s;
  if (!s.empty()) {
    const int value = s.top();
    s.pop();
    do_something(value);
  }
}

int main(int argc, char *argv[])
{
  test();

  return 0;
}
