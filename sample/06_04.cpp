#include <iostream>
#include <memory>

template<typename T>
class queue
{
private:
  struct node
  {
    T data;
    std::unique_ptr<node> next;

    node(T data_) :
      data(std::move(data_))
    {}
  };

  std::unique_ptr<node> head; // 1
  node *tail; // 2

public:
  queue() {}

  queue(const queue &other) = delete;
  queue &operator=(const queue &other) = delete;

  std::shared_ptr<T> try_pop()
  {
    if (!head) {
      return std::shared_ptr<T>();
    }

    const std::shared_ptr<T>
      res(std::make_shared<T>(std::move(head->data)));
    const std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next); // 3
    return res;
  }

  void push(T new_value)
  {
    std::unique_ptr<node> p(new node(std::move(head->data)));
    node *const new_tail = p.get();
    if (tail) {
      tail->next = std::move(p); // 4
    }
    else {
      head = std::move(p); // 5
    }

    tail = new_tail; // 6
  }
};

int main(int argc, char *argv[])
{
  return 0;
}
