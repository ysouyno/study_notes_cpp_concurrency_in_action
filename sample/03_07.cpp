#include <iostream>
#include <mutex>
#include <climits>

class hierarchical_mutex
{
  std::mutex internal_mutex;

  const unsigned long hierarchy_value;
  unsigned long previous_hierarchy_value;

  static thread_local unsigned long this_thread_hierarchy_value;

  void check_for_hierarchy_violation()
  {
    if (this_thread_hierarchy_value <= hierarchy_value) {
      throw std::logic_error("mutex hierarchy violated");
    }
  }

  void update_hierarchy_value()
  {
    previous_hierarchy_value = this_thread_hierarchy_value;
    this_thread_hierarchy_value = hierarchy_value;
  }

public:
  explicit hierarchical_mutex(unsigned long value)
    : hierarchy_value(value)
    , previous_hierarchy_value(0)
  {}

  void lock()
  {
    check_for_hierarchy_violation();
    internal_mutex.lock();
    update_hierarchy_value();
  }

  void unlock()
  {
    this_thread_hierarchy_value = previous_hierarchy_value;
    internal_mutex.unlock();
  }

  bool try_lock()
  {
    check_for_hierarchy_violation();

    if (!internal_mutex.try_lock()) {
      return false;
    }

    update_hierarchy_value();
    return true;
  }
};

thread_local unsigned long
hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int low_level_stuff()
{
  std::cout << "low_level_stuff()" << std::endl;
  return 2;
}

int low_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return low_level_stuff();
}

void high_level_stuff(int some_param)
{
  std::cout << "high_level_stuff(" << some_param << ")" << std::endl;
}

void hight_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  high_level_stuff(low_level_func());
}

void thread_a()
{
  hight_level_func();
}

hierarchical_mutex other_mutex(100);

void other_level_stuff()
{
  std::cout << "other_level_stuff()" << std::endl;
}

void other_level_func()
{
  hight_level_func();
  other_level_stuff();
}

void thread_b()
{
  std::lock_guard<hierarchical_mutex> lk(other_mutex);
  other_level_func();
}

int main(int argc, char *argv[])
{
  thread_a();
  thread_b();

  return 0;
}
