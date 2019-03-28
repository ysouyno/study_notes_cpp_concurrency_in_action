#include <iostream>
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>
#include <unistd.h>

std::mutex m;
std::deque<std::packaged_task<void()> > tasks;

bool gui_shutdown_message_received()
{
  static int i = 0;
  usleep(500000);

  if (i++ == 10) {
    return true;
  }

  return false;
}

void get_and_process_gui_message()
{
  std::cout << "get_and_process_gui_message()" << std::endl;
}

void gui_thread()
{
  while (!gui_shutdown_message_received()) {
    get_and_process_gui_message();
    std::packaged_task<void()> task;
    {
      std::lock_guard<std::mutex> lk(m);
      if (tasks.empty()) {
        continue;
      }

      task = std::move(tasks.front());
      tasks.pop_front();
    }

    task();
  }
}

std::thread gui_bg_thread(gui_thread);

void test_func1()
{
  std::cout << "test_func()1" << std::endl;
}

void test_func2()
{
  std::cout << "test_func()2" << std::endl;
}

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
  std::packaged_task<void()> task(f);
  std::future<void> res = task.get_future();
  std::lock_guard<std::mutex> lk(m);
  tasks.push_back(std::move(task));
  return res;
}

int main(int argc, char *argv[])
{
  post_task_for_gui_thread(test_func1);
  post_task_for_gui_thread(test_func2);
  gui_bg_thread.join();

  return 0;
}
