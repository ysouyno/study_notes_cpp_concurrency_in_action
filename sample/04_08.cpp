#include <iostream>
#include <list>
#include <algorithm>
#include <future>
#include <type_traits>

template<typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type> spawn_task(F&& f, A&& a)
{
  typedef typename std::result_of<F(A&&)>::type result_type;
  std::packaged_task<result_type(A&&)> task(std::move(f));
  std::future<result_type> res(task.get_future());
  std::thread t(std::move(task), std::move(a));
  t.detach();
  return res;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();

  auto divide_point = std::partition(input.begin(),
                                     input.end(),
                                     [&](const T& t){return t < pivot;}
                                     );

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(),
                    input,
                    input.begin(),
                    divide_point
                    );

  /*
  std::future<std::list<T> > new_lower(std::async(
                                                  &parallel_quick_sort<T>,
                                                  std::move(lower_part)
                                                  )
                                                  );*/

  auto new_lower(spawn_task(&parallel_quick_sort<T>, std::move(lower_part)));

  auto new_higher(parallel_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());

  return result;
}

int main(int argc, char *argv[])
{
  std::list<int> list_int {3, 2, 1, 4, 5};
  std::list<int> result = parallel_quick_sort(list_int);

  for (std::list<int>::iterator it = result.begin();
       it != result.end();
       ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
