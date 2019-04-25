#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  std::shared_ptr<int> sp1 = std::make_shared<int>(1);
  std::shared_ptr<int> sp2 = std::make_shared<int>(2);
  std::cout << "*sp1: " << *sp1 << std::endl;
  std::cout << "*sp2: " << *sp2 << std::endl;

  sp1 = sp2;
  std::cout << "*sp1: " << *sp1 << std::endl;

  return 0;
}
