#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  int val = 1;
  const int *cp = &val;

  // error: assignment of read-only location ‘* cp’
  // *cp = 2;

  const std::shared_ptr<int> csp = std::make_shared<int>(1);
  std::shared_ptr<int> const scp = std::make_shared<int>(2);
  std::cout << "*csp: " << *csp << std::endl;
  std::cout << "*scp: " << *scp << std::endl;

  *csp = 3;
  std::cout << "*csp: " << *csp << std::endl;
  *scp = 4;
  std::cout << "*scp: " << *scp << std::endl;

  std::shared_ptr<int> sp = std::make_shared<int>(0);

  // error: no match for ‘operator=’
  // (operand types are ‘const std::shared_ptr<int>’ and ‘std::shared_ptr<int>’)
  // csp = sp;

  // error: no match for ‘operator=’
  // (operand types are ‘const std::shared_ptr<int>’ and ‘std::shared_ptr<int>’)
  // scp = sp;

  return 0;
}
