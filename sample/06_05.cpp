// A simple queue with a dummy node

#include <iostream>
#include <memory>

template <typename T>
class queue
{
private:
  struct node
  {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };

  std::unique_ptr<node> head;
  node *tail;

public:
  queue() :
    head(new node), tail(head.get())
  {}

  queue(const queue& other) = delete;
  queue &operator=(const queue& other) = delete;

  std::shared_ptr<T> try_pop() {
    if (head.get() == tail) {
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> const res(head->data);
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }

  void push(T new_value) {
    std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
    std::unique_ptr<node> p(new node);
    tail->data = new_data;
    node * const new_tail = p.get();
    tail->next = std::move(p);
    tail = new_tail;
  }
};

int main()
{
  queue<int> qi;
  qi.push(3);
  qi.push(2);
  qi.push(1);
  std::shared_ptr<int> val = qi.try_pop();
  std::cout << "val: " << *val << '\n';
}
