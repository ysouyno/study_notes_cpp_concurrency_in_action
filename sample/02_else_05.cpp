#include <iostream>
#include <thread>

typedef int widget_id;

class widget_data
{
public:
  widget_data() : id(0)
  {
    std::cout << "widget_data()" << std::endl;
  }

  ~widget_data()
  {
    std::cout << "~widget_data()" << std::endl;
  }

  widget_id get_id() const
  {
    return id;
  }

  void set_id(widget_id id)
  {
    this->id = id;
  }

private:
  widget_id id;
};

void update_data_for_widget(widget_id w, widget_data &data)
{
  data.set_id(w);
}

void oops_again(widget_id w)
{
  widget_data data;
  std::thread t(update_data_for_widget, w, data);
  std::cout << "data.id: " << data.get_id() << std::endl;
  t.join();
}

int main(int argc, char *argv[])
{
  oops_again(3);

  return 0;
}
