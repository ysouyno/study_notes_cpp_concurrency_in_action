#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

std::vector<int> data;
std::atomic<bool> data_ready(false);

void reader_thread()
{
  while (!data_ready.load()) { // 1
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
  }

  std::cout << "The answer = " << data[0] << "\n"; // 2
}

void writer_thread()
{
  data.push_back(42); // 3
  data_ready = true; // 4
}

int main(int argc, char *argv[])
{
  std::thread t0(reader_thread);
  std::thread t1(writer_thread);
  t0.join();
  t1.join();

  return 0;
}
