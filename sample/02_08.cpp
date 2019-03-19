#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

template<typename Iterator, typename T>
struct accumulate_block
{
  void operator()(Iterator first, Iterator last, T& result)
  {
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  const unsigned long length = std::distance(first, last);

  if (!length) {
    return init;
  }

  const unsigned long min_per_thread = 25;
  const unsigned long max_threads =
    (length + min_per_thread - 1) / min_per_thread;
  std::cout << "min_per_thread: " << min_per_thread << std::endl;
  std::cout << "max_threads: " << max_threads << std::endl;

  const unsigned long hardware_threads =
    std::thread::hardware_concurrency();
  std::cout << "hardware_threads: " << hardware_threads << std::endl;

  const unsigned long num_threads =
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
  std::cout << "num_threads: " << num_threads << std::endl;

  const unsigned long block_size = length / num_threads;
  std::cout << "block_size: " << block_size << std::endl;

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);

    threads[i] = std::thread(accumulate_block<Iterator, T>(),
                             block_start, block_end, std::ref(results[i])
                             );

    block_start = block_end;
  }

  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

  std::for_each(threads.begin(),
                threads.end(),
                std::mem_fn(&std::thread::join)
                );

  return std::accumulate(results.begin(), results.end(), init);
}

void test_accumulate_block()
{
  std::cout << "test_accumulate_block" << std::endl;

  std::vector<int> vec{1, 2, 3};
  int sum = 0;

  std::thread t(accumulate_block<std::vector<int>::iterator, int>(),
                vec.begin(), vec.end(), std::ref(sum)
                );
  t.join();

  std::cout << "sum: " << sum << std::endl;
}

void test_parallel_accumulate()
{
  std::cout << "test_parallel_accumulate" << std::endl;

  std::vector<int> vec;

  for (unsigned i = 1; i <= 100; ++i) {
    vec.push_back(i);
  }

  int sum = parallel_accumulate(vec.begin(), vec.end(), 0);

  std::cout << "sum: " << sum << std::endl;
}

int main(int argc, char *argv[])
{
  test_accumulate_block();
  std::cout << std::endl;
  test_parallel_accumulate();

  return 0;
}
