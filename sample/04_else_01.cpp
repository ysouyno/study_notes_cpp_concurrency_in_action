#include <cmath>
#include <stdexcept>
#include <future>

double square_root(double x)
{
  if (x < 0) {
    throw std::out_of_range("x < 0");
  }

  return sqrt(x);
}

int main(int argc, char *argv[])
{
  // double y = square_root(-1);
  std::future<double> f = std::async(square_root, -1);
  double y = f.get();

  return 0;
}
