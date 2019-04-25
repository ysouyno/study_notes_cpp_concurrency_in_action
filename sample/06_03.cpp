#include <iostream>
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

template<typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  std::queue<std::shared_ptr<T> > data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue() {}

  void wait_and_pop(T &value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value = std::move(*data_queue.front()); // 1
    data_queue.pop();
  }

  bool try_pop(T &value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return false;
    }

    value = std::move(*data_queue.front()); // 2
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    std::shared_ptr<T> res = data_queue.front(); // 3
    data_queue.pop();
    return res;
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> res = data_queue.front(); // 4
    data_queue.pop();
    return res;
  }

  void push(T new_value)
  {
    std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value))); // 5
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};

int main(int argc, char *argv[])
{
  return 0;
}
