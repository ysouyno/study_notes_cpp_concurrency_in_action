#include <iostream>
#include <string>
#include <future>

struct X
{
  void foo(int i, const std::string &s)
  {
    std::cout << "foo(" << i << ", " << s << ")" << std::endl;
  }

  std::string bar(const std::string &s)
  {
    std::cout << "bar(" << s << ")" << std::endl;
    return s;
  }
};

struct Y
{
  double operator()(double d)
  {
    std::cout << "Y(" << d << ")" << std::endl;
    return d;
  }
};

X baz(X& x)
{
  std::cout << "baz(x)" << std::endl;
  return x;
}

class move_only
{
public:
  move_only()
  {
    std::cout << "move_only constructor" << std::endl;
  }

  move_only(move_only&&) {}

  move_only(const move_only&) = delete;
  move_only& operator=(move_only&&) = delete;
  move_only& operator=(const move_only&) = delete;

  void operator()()
  {
    std::cout << "move_only::operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  X x;
  auto f1 = std::async(&X::foo, &x, 42, "hello");
  auto f2 = std::async(&X::bar, x, "goodbye");

  Y y;
  auto f3 = std::async(Y(), 3.141);
  auto f4 = std::async(std::ref(y), 2.718);

  std::async(baz, std::ref(x));

  auto f5 = std::async(move_only());

  auto f6 = std::async(std::launch::async, Y(), 1.2);
  auto f7 = std::async(std::launch::deferred, baz, std::ref(x));
  auto f8 = std::async(std::launch::deferred | std::launch::async,
                       baz, std::ref(x)
                       );
  auto f9 = std::async(baz, std::ref(x));

  f7.wait();

  return 0;
}
