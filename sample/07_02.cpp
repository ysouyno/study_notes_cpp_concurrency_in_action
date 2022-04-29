#include <atomic>

template <typename T> class lock_free_stack {
private:
  struct node {
    T data;
    node *next;

    node(T const &data_) : data(data_) {}
  };

  std::atomic<node *> head;

public:
  void push(T const &data) {
    node *const new_node = new node(data);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node))
      ;
  }
};

int main() {
  lock_free_stack<int> lfs;
  lfs.push(1);
  lfs.push(2);
  lfs.push(3);
  return 0;
}
