<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [<2019-03-11 Mon>《C++并发编程实战》读书笔记（一）](#2019-03-11-monc并发编程实战读书笔记一)
    - [第1章 你好，C++的并发世界](#第1章-你好c的并发世界)
    - [第2章 线程管理（一）](#第2章-线程管理一)
        - [启动线程（一）](#启动线程一)
- [<2019-03-12 Tue>《C++并发编程实战》读书笔记（二）](#2019-03-12-tuec并发编程实战读书笔记二)
    - [第2章 线程管理（二）](#第2章-线程管理二)
        - [启动线程（二）](#启动线程二)
        - [向线程函数传递参数（一）](#向线程函数传递参数一)

<!-- markdown-toc end -->

# <2019-03-11 Mon>《C++并发编程实战》读书笔记（一）

## 第1章 你好，C++的并发世界
  * 这章内容看得很累，好多地方读不懂，不知道想表达什么，书中有下面这段代码
```
#include <iostream>
#include <thread>

void hello()
{
  std::cout << "Hello Concurrent World!\n";
}

int main(int argc, char *argv[])
{
  std::thread t(hello);
  t.join();

  return 0;
}
```
  * 链接出错，如下
```console
% g++ 01_01.cpp
/usr/bin/ld: /tmp/ccWuVkAr.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```
  * 为什么“std::thread”需要去链接“pthread_create”呢？标准库的东西还得依赖平台支持吗？
  * 即使使用“g++ -std=c++11 01_01.cpp”进行编译也同样出错
```console
% g++ -std=c++11 01_01.cpp
/usr/bin/ld: /tmp/cchBMGkl.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```
  * **使用下面的命令可以编译通过，必须要加上“-pthread”参数**
```console
% g++ 01_01.cpp -pthread
```
  * 查看“g++”的手册页中关于“-pthread”的解释
```
-pthread 
    Add support for multithreading using the POSIX threads library. This option sets flags for both the
    preprocessor and linker. It does not affect the thread safety of object code produced by the compiler
    or that of libraries supplied with it. These are HP-UX specific flags.
```
  * 上面表示要使用“POSIX threads library”，查看“pthread_create”的手册页也可以看到
```
SYNOPSIS
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.
```
  * **问题：“std::thread”在linux平台下必须使用“-pthread”才能正常编译成功吗？**
  * 我的环境是
```console
gcc version 8.2.1 20181127 (GCC)
4.20.12-arch1-1-ARCH
```
## 第2章 线程管理（一）
### 启动线程（一）
  * 这里有坑，往下看，首先这里可以正确执行线程函数
  * 下面的代码可以正确输出（函数对象）
    * 这里为什么能正确执行，居然能显示出“operator()”的输出结果，我有点不太理解
    * 书中解释“background_task”是一个“函数对象”，新名词对我来说
    * 看“background_task”的实现，是不是类中带有“operator()()”的对象不是函数对象呢？
```
#include <iostream>
#include <thread>

class background_task
{
public:
  void operator()() const
  {
    std::cout << "operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  background_task f;

  // output: operator()
  std::thread my_thread(f);
  my_thread.join();

  return 0;
}
```
```
// output
operator()
```
  * 下面的代码编译出错
    * **如果你传递了一个临时变量，而不是一个命名变量，C++编译器会将其解析为函数声明，而不是对象定义**
    * 通过下面的编译出错信息确实可以看到是这样子的
```
#include <iostream>
#include <thread>

class background_task
{
public:
  void operator()() const
  {
    std::cout << "operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  // output nothing
  std::thread my_thread(background_task());
  my_thread.join();

  return 0;
}
```
```console
% g++ 02_else_01.cpp -pthread
02_else_01.cpp: In function ‘int main(int, char**)’:
02_else_01.cpp:27:13: error: request for member ‘join’ in ‘my_thread’, which is of non-class type ‘std::thread(background_task (*)())’
   my_thread.join();
             ^~~~
```
  * 可以通过下面两种方法来解决上面的临时变量问题，将对象的定义改为下面二者之一即可
  * 还有第三种方法，那就是使用C++11的新特性“右值引用”，见我的测试代码：
```
// 使用多组括号
std::thread my_thread((background_task()));

// 使用新统一的初始化语法（即初始化列表方法），可以通过“std::initializer_list”实现
std::thread my_thread{background_task()};
```
  * 完整测试代码如下
```
#include <iostream>
#include <thread>

class background_task
{
public:
  void operator()() const
  {
    std::cout << "operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  background_task f;

  // output: operator()
  // std::thread my_thread(f);

  // output: nothing
  // std::thread my_thread(background_task());

  // output: operator()
  // std::thread my_thread((background_task()));

  // output: operator()
  std::thread my_thread{background_task()};

  my_thread.join();

  return 0;
}
```

# <2019-03-12 Tue>《C++并发编程实战》读书笔记（二）
## 第2章 线程管理（二）
### 启动线程（二）
  * 在上面“[[ccia_2_1_1_0][启动线程（一）]]”中提到的函数对象现在回忆起来了，非常简单，就是重载了“()”操作符
  * 因为临时变量的原因导致“std::thread my_thread(background_task());”变成函数声明的问题
  * 可以通过“std::move”的“右值引用”实现，如下<<ccia_2_1_1_1>>
```
#include <iostream>
#include <thread>

class background_task
{
public:
  void operator()() const
  {
    std::cout << "operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  std::thread my_thread(std::move(background_task()));
  my_thread.join();

  return 0;
}
```
```
// output
operator()
```
  * 继续进行下面的内容，下面这段代码使线程分离执行（detach），访问局部变量，可能引起“悬挂引用”
```
#include <iostream>
#include <thread>

struct func
{
  int &i;

  func(int &i_) : i(i_) {}

  void operator()()
  {
    for (unsigned n = 0; n < 10000; ++n) {
      std::cout << i;
      i++;
    }

    std::cout << std::endl;
  }
};

void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();
}

int main(int argc, char *argv[])
{
  oops();

  return 0;
}
```
  * 如果想分离一个线程，可以在线程启动后直接使用“detach”进行分离，如果打算等待则“join”的位置要精心挑选
  * 因为假如线程运行之后产生异常，此时“join”还没有调用，这意味着这次调用会被跳过
  * **当倾向于在无异常情况下使用“join”时，需要在异常处理过程中调用“join”，从而避免生命周期的问题**
```
#include <iostream>
#include <thread>

struct func
{
  int &i;

  func(int &i_) : i(i_) {}

  void operator()()
  {
    for (unsigned n = 0; n < 10000; ++n) {
      std::cout << i;
    }

    std::cout << std::endl;
  }
};

void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);

  try {
    some_local_state = 2;
  } catch (...) {
    my_thread.join();
    throw;
  }

  my_thread.join();
}

int main(int argc, char *argv[])
{
  oops();

  return 0;
}
```
  * 上面的这段代码使用了异常捕获，很容易理解不是吗！
  * 也可以通过“RAII”的方式提供一个类来解决这个问题，代码如下
```
#include <iostream>
#include <thread>

class thread_guard
{
  std::thread &t;

public:
  explicit thread_guard(std::thread &t_)
    : t(t_)
  {}

  ~thread_guard()
  {
    if (t.joinable()) {
      t.join();
    }
  }

  thread_guard(const thread_guard &) = delete;
  thread_guard& operator=(const thread_guard &) = delete;
};

struct func
{
  int &i;

  func(int &i_) : i(i_) {}

  void operator()()
  {
    for (unsigned n = 0; n < 10000; ++n) {
      std::cout << i;
    }

    std::cout << std::endl;
  }
};

void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  thread_guard g(my_thread);
  some_local_state = 2; // 1
} // 2

int main(int argc, char *argv[])
{
  oops();

  return 0;
}
```
  * 对上面的代码说明
    * 刚开始不太理解为什么能确保在“1”处即使发生异常也能调用“thread_guard”的析构函数？
    * 是不是因为当发生异常的时候程序流程将跳到“2”处，C++能确保已经生成的对象会被正确析构？
    * 对异常不太了解，如果书上的意思是这样的话，那么上行的猜测应该也是正确的
    * **“join”只能调用一次，再次调用将会导致错误，所以必须判断“joinable”**
  * **如果不想等待线程结束，可以分离线程，从而避免异常安全问题**
  * 不过“detach”也打破了线程和“std::thread”对象的联系，即使线程仍然在后台运行着
  * **分离操作也能确保“std::terminate”在“std::thread”对象销毁才被调用**
  * “detach”会让线程在后台运行，这就意味着主线程不能与之产生直接交互
  * 如果有线程分离，那么主不可能有“std::thread”对象能引用它
  * 分离线程的确在后台运行，所以分离线程不能被加放（join）
  * 不过C++运行库保证当线程退出时相关资源能够正确回收，后台线程的归属和控制，C++运行库都会处理
  * 分离线程为守护线程，它的另一方面只能确定线程什么时候结束，“发后即忘”（fire and forget）
  * “detach”的使用
    * 不能对没有执行线程的“std::thread”对象使用“detach”
    * 当“joinable”返回真时，就可以使用“detach”
### 向线程函数传递参数（一）
  * 这翻译看得真是云里雾里，不过大概意思我懂了，传递参数无非就是传值、传指引和传引用嘛
  * 先看传值，补全书中代码如下
```
#include <iostream>
#include <string>
#include <thread>

void f(int i, const std::string &s)
{
  std::cout << "i: " << i << std::endl;
  std::cout << "s: " << s << std::endl;
}

int main(int argc, char *argv[])
{
  std::thread t(f, 3, "hello");
  t.join();

  return 0;
}
```
```
// output
% ./a.out
i: 3
s: hello
```
  * 这里就像“[[ref_to_const_understand][关于函数参数中常量引用的再理解]]”说的一样，产生了临时对象
  * 它将“const char*”转化为“std::string”
  * **这里有个问题留着下次解决：上面的代码如果将“t.join();”注释掉程序运行崩溃，我想知道原因，输出如下**
```
% ./a.out
terminate called without an active exception
[1]    6430 abort (core dumped)  ./a.out
```
  * 再看传指针，补全书中代码
```
#include <iostream>
#include <string>
#include <thread>

void f(int i, const std::string &s)
{
  std::cout << "i: " << i << std::endl;
  std::cout << "s: " << s << std::endl;
}

void oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, buffer);
  t.join();
}

int main(int argc, char *argv[])
{
  oops(23);

  return 0;
}
```
```
// output
% ./a.out
i: 3
s: 23
```
  * 我将书中的代码的“detach”改为了“join”，不然我无法看到输出
  * **这里书中说“函数有很大的可能会在字面值转化成‘std::string’对象之前崩溃”，不懂什么意思**
  * 解决方案是传递到“std::string”构造函数之前将字面值转化为“std::string”对象
  * 修改上面的代码
```
#include <iostream>
#include <string>
#include <thread>

void f(int i, const std::string &s)
{
  std::cout << "i: " << i << std::endl;
  std::cout << "s: " << s << std::endl;
}

void oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, buffer);
  t.join();
}

void not_oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  std::thread t(f, 3, std::string(buffer));
  t.join();
}

int main(int argc, char *argv[])
{
  oops(23);
  not_oops(32);

  return 0;
}
```
```
// output
% ./a.out 
i: 3
s: 23
i: 3
s: 32
```
  * **这里也不懂什么意思，书中所言P30**
    * 上面这种情况的问题是，想要依赖隐式转换将字面值转换为函数期待的“std::string”对象
    * 但因“std::string”的构造函数会复制提供的变量，就只复制了没有转换成期望类型的字符串字面值
  * 再看传引用，补全书中代码，不知道为啥，下面这段代码编译有问题，一堆错误，先贴上再说
```
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
```
