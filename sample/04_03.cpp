#include <iostream>
#include <future>
#include <unistd.h>

int find_the_answer_to_ltuae()
{
  std::cout << "find_the_answer_to_ltuae()" << std::endl;
  sleep(1);
  return 1;
}

void do_other_stuff()
{
  std::cout << "do_other_stuff()" << std::endl;
}

int main(int argc, char *argv[])
{
  std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
  do_other_stuff();
  std::cout << "the answer is " << the_answer.get() << std::endl;

  return 0;
}
