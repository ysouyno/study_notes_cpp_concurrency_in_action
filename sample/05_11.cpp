#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

std::vector<int> queue_data;
std::atomic<int> count;

void wait_for_more_items(int tid)
{
  using namespace std::chrono_literals;
  std::cout << "thread" << tid << ": wait_for_more_items() wait 3s"
            << std::endl;
  std::this_thread::sleep_for(3s);
}

void process(int val, int tid)
{
  std::cout << "thread" << tid << ": process(" << val << ")"
            << std::endl;
}

void populate_queue()
{
  const unsigned number_of_items = 20;
  queue_data.clear();

  for (unsigned i = 0; i < number_of_items; ++i) {
    queue_data.push_back(i);
  }

  count.store(number_of_items, std::memory_order_release);
}

void consume_queue_items(int tid)
{
  while (true) {
    int item_index;

    if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) {
      wait_for_more_items(tid);
      continue;
    }

    process(queue_data[item_index - 1], tid);
  }
}

int main(int argc, char *argv[])
{
  std::thread a(populate_queue);
  std::thread b(consume_queue_items, 1);
  std::thread c(consume_queue_items, 2);
  a.join();
  b.join();
  c.join();

  return 0;
}
