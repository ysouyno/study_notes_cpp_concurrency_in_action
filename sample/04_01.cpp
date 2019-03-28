#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <unistd.h>

typedef int data_chunk;
const data_chunk MAX_DATA = 9;

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare()
{
  static int i = 0;
  usleep(500000);

  if (i++ == MAX_DATA) {
    return false;
  }

  return true;
}

data_chunk prepare_data()
{
  static data_chunk d = 0;
  return ++d;
}

void process(data_chunk data)
{
  std::cout << "process(" << data << ")" << std::endl;
}

bool is_last_chunk(data_chunk data)
{
  if (data == MAX_DATA) {
    return true;
  }

  return false;
}

void data_preparation_thread()
{
  while (more_data_to_prepare()) {
    const data_chunk data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();
  }
}

void data_processing_thread()
{
  while (true) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, []{return !data_queue.empty();});
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk(data)) {
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();

  return 0;
}
