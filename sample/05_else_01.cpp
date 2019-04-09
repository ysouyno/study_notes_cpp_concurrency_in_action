#include <iostream>
#include <string>

struct my_data
{
  int i;             // 4
  double d;          // 16
  unsigned bf1 : 10; // 24
  int bf2 : 25;      // 24
  int /*bf3*/ : 0;   // 24
  int bf4 : 9;       // 32
  int i2;            // 32
  char c1, c2;       // 40
  std::string s;     // 72
};

int main(int argc, char *argv[])
{
  std::cout << "sizeof(my_data): " << sizeof(my_data) << std::endl;

  return 0;
}
