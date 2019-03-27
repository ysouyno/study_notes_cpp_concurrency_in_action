#include <mutex>

class Y
{
private:
  int some_detail;
  mutable std::mutex m;

  int get_detail() const
  {
    std::lock_guard<std::mutex> lock_a(m);
    return some_detail;
  }

public:
  Y(int sd) : some_detail(sd) {}

  friend bool operator==(const Y& lhs, const Y& rhs)
  {
    if (&lhs == &rhs) {
      return true;
    }

    const int lhs_value = lhs.get_detail();
    const int rhs_value = rhs.get_detail();

    return lhs_value == rhs_value;
  }
};

int main(int argc, char *argv[])
{
  return 0;
}
