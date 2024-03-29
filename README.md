<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [<2019-03-11 周一> 《C++并发编程实战》读书笔记（一）](#2019-03-11-周一-c并发编程实战读书笔记一)
    - [第1章 你好，C++的并发世界](#第1章-你好c的并发世界)
    - [第2章 线程管理（一）](#第2章-线程管理一)
        - [启动线程（一）](#启动线程一)
- [<2019-03-12 周二> 《C++并发编程实战》读书笔记（二）](#2019-03-12-周二-c并发编程实战读书笔记二)
    - [第2章 线程管理（二）](#第2章-线程管理二)
        - [启动线程（二）](#启动线程二)
        - [向线程函数传递参数（一）](#向线程函数传递参数一)
            - [传值](#传值)
            - [传指针](#传指针)
            - [传引用（一）](#传引用一)
    - [理解临时对象的来源<2016-11-21 Mon>](#理解临时对象的来源2016-11-21-mon)
    - [关于函数参数中常量引用的再理解](#关于函数参数中常量引用的再理解)
- [<2019-03-13 周三> 《C++并发编程实战》读书笔记（三）](#2019-03-13-周三-c并发编程实战读书笔记三)
    - [第2章 线程管理（二）](#第2章-线程管理二-1)
        - [向线程函数传递参数（二）](#向线程函数传递参数二)
- [<2019-03-15 周五> 《C++并发编程实战》读书笔记（四）](#2019-03-15-周五-c并发编程实战读书笔记四)
    - [第2章 线程管理（三）](#第2章-线程管理三)
        - [向线程函数传递参数（三）](#向线程函数传递参数三)
            - [传引用（二）](#传引用二)
        - [转移线程所有权（一）](#转移线程所有权一)
            - [`std::thread`线程所有权在函数外转换](#stdthread线程所有权在函数外转换)
            - [`std::thread`线程所有权在函数内转换](#stdthread线程所有权在函数内转换)
- [<2019-03-19 周二> 《C++并发编程实战》读书笔记（五）](#2019-03-19-周二-c并发编程实战读书笔记五)
    - [第2章 线程管理（四）](#第2章-线程管理四)
        - [转移线程所有权（二）](#转移线程所有权二)
        - [运行时决定线程数量](#运行时决定线程数量)
        - [识别线程](#识别线程)
        - [总结](#总结)
- [<2019-03-26 周二> 《C++并发编程实战》读书笔记（六）](#2019-03-26-周二-c并发编程实战读书笔记六)
    - [第3章 线程间共享数据（一）](#第3章-线程间共享数据一)
        - [使用互斥量保护共享数据（一）](#使用互斥量保护共享数据一)
            - [C++中使用互斥量](#c中使用互斥量)
            - [精心组织代码来保护共享数据](#精心组织代码来保护共享数据)
            - [发现接口内在的条件竞争](#发现接口内在的条件竞争)
                - [选项1 传入一个引用](#选项1-传入一个引用)
                - [选项2 无异常抛出的拷贝构造函数或移动构造函数](#选项2-无异常抛出的拷贝构造函数或移动构造函数)
                - [选项3 返回指向弹出值的指针](#选项3-返回指向弹出值的指针)
                - [选项4 “选项1和2”或“选项1和3”](#选项4-选项1和2或选项1和3)
- [<2019-03-27 周三> 《C++并发编程实战》读书笔记（七）](#2019-03-27-周三-c并发编程实战读书笔记七)
    - [第3章 线程间共享数据（二）](#第3章-线程间共享数据二)
        - [使用互斥量保护共享数据（二）](#使用互斥量保护共享数据二)
            - [死锁问题描述及解决方案](#死锁问题描述及解决方案)
            - [避免死锁的进阶指导](#避免死锁的进阶指导)
            - [不同域中互斥量所有权的传递](#不同域中互斥量所有权的传递)
            - [锁的粒度](#锁的粒度)
        - [保护共享数据的替代设施](#保护共享数据的替代设施)
- [<2019-03-28 周四> 《C++并发编程实战》读书笔记（八）](#2019-03-28-周四-c并发编程实战读书笔记八)
    - [第4章 同步并发操作（一）](#第4章-同步并发操作一)
        - [等待一个事件或其他条件](#等待一个事件或其他条件)
            - [等待条件达成](#等待条件达成)
            - [使用条件变量构建线程安全队列](#使用条件变量构建线程安全队列)
        - [使用期望等待一次性事件](#使用期望等待一次性事件)
            - [带返回值的后台任务](#带返回值的后台任务)
            - [任务与期望](#任务与期望)
            - [使用`std::promises`](#使用stdpromises)
            - [为“期望”存储“异常”](#为期望存储异常)
            - [多个线程的等待](#多个线程的等待)
- [<2019-03-29 周五> 《C++并发编程实战》读书笔记（九）](#2019-03-29-周五-c并发编程实战读书笔记九)
    - [第4章 同步并发操作（二）](#第4章-同步并发操作二)
        - [限定等待时间](#限定等待时间)
        - [使用同步操作简化代码](#使用同步操作简化代码)
            - [使用“期望”的函数化编程](#使用期望的函数化编程)
            - [使用消息传递的同步操作](#使用消息传递的同步操作)
        - [总结](#总结-1)
- [<2019-04-09 周二> 《C++并发编程实战》读书笔记（十）](#2019-04-09-周二-c并发编程实战读书笔记十)
    - [第5章 C++内存模型和原子类型操作（一）](#第5章-c内存模型和原子类型操作一)
        - [内存模型基础](#内存模型基础)
            - [对象和内存位置](#对象和内存位置)
            - [对象、内存位置和并发](#对象内存位置和并发)
            - [修改顺序](#修改顺序)
        - [C++中的原子操作和原子类型](#c中的原子操作和原子类型)
            - [标准原子类型](#标准原子类型)
            - [`std::atomic_flag`的相关操作](#stdatomic_flag的相关操作)
            - [`std::atomic`的相关操作](#stdatomic的相关操作)
            - [`std::atomic<T*>`指针运算](#stdatomict指针运算)
            - [标准的原子整形的相关操作](#标准的原子整形的相关操作)
            - [`std::atomic<>`主要类的模板](#stdatomic主要类的模板)
            - [原子操作的释放函数](#原子操作的释放函数)
- [<2019-04-10 周三> 《C++并发编程实战》读书笔记（十一）](#2019-04-10-周三-c并发编程实战读书笔记十一)
    - [关于对`std::memory_order`的理解（一）](#关于对stdmemory_order的理解一)
        - [Happens-before关系](#happens-before关系)
        - [Synchronizes-with关系](#synchronizes-with关系)
    - [第5章 C++内存模型和原子类型操作（二）](#第5章-c内存模型和原子类型操作二)
        - [同步操作和强制排序（一）](#同步操作和强制排序一)
            - [同步发生（The synchronizes-with relationship）](#同步发生the-synchronizes-with-relationship)
            - [先行发生（The happens-before relationship）](#先行发生the-happens-before-relationship)
            - [原子操作的内存顺序（Memory ordering for atomic operations）（一）](#原子操作的内存顺序memory-ordering-for-atomic-operations一)
                - [SEQUENTIALLY CONSISTENT ORDERING](#sequentially-consistent-ordering)
- [<2019-04-11 周四> 《C++并发编程实战》读书笔记（十二）](#2019-04-11-周四-c并发编程实战读书笔记十二)
    - [第5章 C++内存模型和原子类型操作（三）](#第5章-c内存模型和原子类型操作三)
        - [同步操作和强制排序（二）](#同步操作和强制排序二)
            - [原子操作的内存顺序（Memory ordering for atomic operations）（二）](#原子操作的内存顺序memory-ordering-for-atomic-operations二)
                - [NON-SEQUENTIALLY CONSISTENT MEMORY ORDERINGS](#non-sequentially-consistent-memory-orderings)
                - [RELAXED ORDERING](#relaxed-ordering)
                - [UNDERSTANDING RELAXED ORDERING](#understanding-relaxed-ordering)
                - [ACQUIRE-RELEASE ORDERING](#acquire-release-ordering)
- [<2019-04-13 周六> 《C++并发编程实战》读书笔记（十三）](#2019-04-13-周六-c并发编程实战读书笔记十三)
    - [第5章 C++内存模型和原子类型操作（四）](#第5章-c内存模型和原子类型操作四)
        - [同步操作和强制排序（三）](#同步操作和强制排序三)
            - [原子操作的内存顺序（Memory ordering for atomic operations）（三）](#原子操作的内存顺序memory-ordering-for-atomic-operations三)
                - [TRANSITIVE SYNCHRONIZATION WITH ACQUIRE-RELEASE ORDERING](#transitive-synchronization-with-acquire-release-ordering)
                - [DATA DEPENDENCY WITH ACQUIRE-RELEASE ORDERING AND MEMORY_ORDER_CONSUME](#data-dependency-with-acquire-release-ordering-and-memory_order_consume)
            - [释放队列与同步（Release sequences and synchronizes-with）](#释放队列与同步release-sequences-and-synchronizes-with)
- [<2019-04-23 周二> 《C++并发编程实战》读书笔记（十四）](#2019-04-23-周二-c并发编程实战读书笔记十四)
    - [Chapter 6: Designing lock-based concurrent data structures（一）](#chapter-6-designing-lock-based-concurrent-data-structures一)
        - [What does it mean to design for concurrency?](#what-does-it-mean-to-design-for-concurrency)
            - [Guidelines for designing data structures for concurrency](#guidelines-for-designing-data-structures-for-concurrency)
        - [Lock-based concurrent data structures（一）](#lock-based-concurrent-data-structures一)
            - [A thread-safe stack using locks](#a-thread-safe-stack-using-locks)
- [<2019-04-25 周四> 《C++并发编程实战》读书笔记（十五）](#2019-04-25-周四-c并发编程实战读书笔记十五)
    - [Chapter 6: Designing lock-based concurrent data structures（二）](#chapter-6-designing-lock-based-concurrent-data-structures二)
        - [Lock-based concurrent data structures（二）](#lock-based-concurrent-data-structures二)
            - [A thread-safe queue using locks and condition variables](#a-thread-safe-queue-using-locks-and-condition-variables)
    - [`const std::shared_ptr<>`与`std::shared_ptr<> const`](#const-stdshared_ptr与stdshared_ptr-const)
- [<2022-04-08 Fri> 《C++ Concurrency in Action》读书笔记（十六）](#2022-04-08-fri-c-concurrency-in-action读书笔记十六)
    - [Chapter 6: Designing lock-based concurrent data structures（三）](#chapter-6-designing-lock-based-concurrent-data-structures三)
        - [Lock-based concurrent data structures（三）](#lock-based-concurrent-data-structures三)
            - [A thread-safe queue using fine-grained locks and condition variables](#a-thread-safe-queue-using-fine-grained-locks-and-condition-variables)
- [<2022-04-29 Fri> 《C++ Concurrency in Action》读书笔记（十七）](#2022-04-29-fri-c-concurrency-in-action读书笔记十七)
    - [Chapter 7: Designing lock-free concurrent data structures（一）](#chapter-7-designing-lock-free-concurrent-data-structures一)
        - [7.2.1 Writing a thread-safe stack without locks](#721-writing-a-thread-safe-stack-without-locks)
        - [7.2.2 Stopping those pesky leaks: managing memory in lock-free data structures](#722-stopping-those-pesky-leaks-managing-memory-in-lock-free-data-structures)
- [<2022-04-30 Sat> 《C++ Concurrency in Action》读书笔记（十七）](#2022-04-30-sat-c-concurrency-in-action读书笔记十七)
    - [Chapter 7: Designing lock-free concurrent data structures（二）](#chapter-7-designing-lock-free-concurrent-data-structures二)
        - [7.2.3 Detecting nodes that can't be reclaimed using hazard pointers](#723-detecting-nodes-that-cant-be-reclaimed-using-hazard-pointers)
- [<2022-05-02 Mon> 《C++ Concurrency in Action》读书笔记（十八）](#2022-05-02-mon-c-concurrency-in-action读书笔记十八)
    - [Chapter 7: Designing lock-free concurrent data structures（三）](#chapter-7-designing-lock-free-concurrent-data-structures三)
        - [7.2.4 Detecting nodes in use with reference counting](#724-detecting-nodes-in-use-with-reference-counting)
        - [7.2.6 Writing a thread-safe queue without locks（一）](#726-writing-a-thread-safe-queue-without-locks一)
- [<2022-05-03 Tue> 《C++ Concurrency in Action》读书笔记（十八）](#2022-05-03-tue-c-concurrency-in-action读书笔记十八)
    - [Chapter 7: Designing lock-free concurrent data structures（三）](#chapter-7-designing-lock-free-concurrent-data-structures三-1)
        - [7.2.6 Writing a thread-safe queue without locks（二）](#726-writing-a-thread-safe-queue-without-locks二)
        - [7.2.6 Writing a thread-safe queue without locks（三）](#726-writing-a-thread-safe-queue-without-locks三)
            - [MAKING THE QUEUE LOCK-FREE BY HELPING OUT ANOTHER THREAD](#making-the-queue-lock-free-by-helping-out-another-thread)
- [<2023-06-26 周一> 《C++ Concurrency in Action》读书笔记（十九）](#2023-06-26-周一-c-concurrency-in-action读书笔记十九)
    - [Chapter 3: Sharing data between threads（一）](#chapter-3-sharing-data-between-threads一)
        - [3.1 Problems with sharing data between threads](#31-problems-with-sharing-data-between-threads)
            - [3.1.1 Race conditions](#311-race-conditions)

<!-- markdown-toc end -->

# <2019-03-11 周一> 《C++并发编程实战》读书笔记（一）

## 第1章 你好，C++的并发世界

这章内容看得很累，好多地方读不懂，翻译的也不好，不知道想表达什么，书中有下面这段代码：

``` c++
// 01_01.cpp
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

链接出错，如下：

``` shellsession
% g++ 01_01.cpp
/usr/bin/ld: /tmp/ccWuVkAr.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```

为什么`std::thread`需要去链接`pthread_create`呢？标准库的东西还得依赖平台支持吗？即使使用`g++ -std=c++11 01_01.cpp`进行编译也同样出错。

``` shellsession
% g++ -std=c++11 01_01.cpp
/usr/bin/ld: /tmp/cchBMGkl.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```

**使用下面的命令可以编译通过，必须要加上`-pthread`参数。**

``` shellsession
% g++ 01_01.cpp -pthread
```

查看`g++`的手册页中关于`-pthread`的解释：

```
-pthread
    Add support for multithreading using the POSIX threads library. This option sets flags for both the
    preprocessor and linker. It does not affect the thread safety of object code produced by the compiler
    or that of libraries supplied with it. These are HP-UX specific flags.
```

上面表示要使用`POSIX threads library`，查看`pthread_create`的手册页也可以看到：

```
SYNOPSIS
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.
```

我的环境是：

```
gcc version 8.2.1 20181127 (GCC)
4.20.12-arch1-1-ARCH
```

**问题：`std::thread`在linux平台下必须使用`-pthread`才能正常编译成功吗？**

## 第2章 线程管理（一）

### 启动线程（一）

首先这里可以正确执行线程函数，`background_task`是一个**函数对象**，因为它的内部重载了括号操作符`operator()`。

``` c++
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

<span id="background_task"></span>

下面的代码编译出错，因为**如果你传递了一个临时变量，而不是一个命名变量，C++编译器会将其解析为函数声明，而不是对象定义**，通过下面的编译出错信息确实可以看到是这样子的。

``` c++
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

``` shellsession
% g++ 02_else_01.cpp -pthread
02_else_01.cpp: In function ‘int main(int, char**)’:
02_else_01.cpp:27:13: error: request for member ‘join’ in ‘my_thread’, which is of non-class type ‘std::thread(background_task (*)())’
   my_thread.join();
             ^~~~
```

可以通过下面两种方法来解决上面的临时变量问题，将对象的定义改为下面二者之一即可。

``` c++
// 使用多组括号
std::thread my_thread((background_task()));

// 使用新统一的初始化语法（即初始化列表方法），可以通过`std::initializer_list`实现
std::thread my_thread{background_task()};
```

还有第三种方法，那就是使用C++11的新特性**右值引用**，见：[启动线程（二）](#启动线程二)

完整测试代码如下：

``` c++
// 02_else_01.cpp
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

# <2019-03-12 周二> 《C++并发编程实战》读书笔记（二）

## 第2章 线程管理（二）

### 启动线程（二）

因为临时变量的原因导致`std::thread my_thread(background_task());`变成了函数声明的问题，可以通过`std::move`的**右值引用**来解决。

``` c++
// 02_else_02.cpp
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
operator()
```

继续进行下面的内容，下面这段代码使线程分离执行`detach()`，访问局部变量，可能引起**悬挂引用**问题。

``` c++
// 02_01.cpp
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

如果想分离一个线程，可以在线程启动后直接使用`detach()`进行分离，如果打算等待则`join()`的位置要精心挑选，因为假如线程运行之后产生异常，此时`join()`还没有调用，这意味着这次调用会被跳过。

当倾向于在无异常情况下使用`join()`时，需要在异常处理过程中调用`join()`，从而避免生命周期的问题。

``` c++
// 02_02.cpp
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

上面的这段代码使用了异常捕获，很容易理解不是吗！也可以通过**RAII**的方式提供一个类来解决这个问题，代码如下：

<span id="thread_guard"></span>

``` c++
// 02_03.cpp
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

对上面的代码说明：刚开始不太理解为什么能确保在“1”处即使发生异常也能调用`thread_guard`的析构函数？是不是因为当发生异常的时候程序流程将跳到“2”处，C++能确保已经生成的对象会被正确析构？对异常不太了解，如果书上的意思是这样的话，那么上面我的猜测应该也是正确的。

`join()`只能调用一次，再次调用将会导致错误，所以必须判断`joinable()`，如果不想等待线程结束，可以分离线程，从而避免异常安全问题。

不过`detach()`也打破了线程和`std::thread`对象的联系，即使线程仍然在后台运行着，**分离操作也能确保`std::terminate`在`std::thread`对象销毁才被调用**。

`detach()`会让线程在后台运行，这就意味着主线程不能与之产生直接交互，如果有线程分离，那么就不可能有`std::thread`对象能引用它。分离线程的确在后台运行，所以分离线程不能被加入`join()`，不过C++运行库保证当线程退出时相关资源能够正确回收，后台线程的归属和控制，C++运行库都会处理。分离线程为守护线程，它的另一方面只能确定线程什么时候结束，“发后即忘”（fire and forget）。

`detach()`的使用：不能对没有执行线程的`std::thread`对象使用`detach()`；当`joinable()`返回真时，就可以使用`detach()`。

### 向线程函数传递参数（一）

这里大概意思我懂了，传递参数无非就是传值、传指针和传引用嘛。

#### 传值

补全书中代码如下：

``` c++
// 02_else_03.cpp
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

``` shellsession
% ./02_else_03
i: 3
s: hello
```

这里就像“关于函数参数中常量引用的再理解”说的一样，产生了临时对象，它将`const char *`转化为`std::string`

这里有个问题留着下次解决：上面的代码如果将`t.join();`注释掉程序运行崩溃，我想知道原因，输出如下：

``` shellsession
% ./02_else_03
terminate called without an active exception
[1]    6430 abort (core dumped)  ./a.out
```

#### 传指针

补全书中代码如下：

``` c++
// 02_else_04.cpp
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

``` shellsession
% ./02_else_04
i: 3
s: 23
```

我将书中的代码的`detach()`改为了`join()`，不然我无法看到输出，**函数有很大的可能会在字面值转化成`std::string`对象之前崩溃，不懂什么意思**，解决方案是传递到`std::string`构造函数之前将字面值转化为`std::string`对象，修改上面的代码如下：

``` c++
// 02_else_05.cpp
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

``` shellsession
% ./02_else_04
i: 3
s: 23
i: 3
s: 32
```

**这里也不懂什么意思，书中所言，见P30**，上面这种情况的问题是，想要依赖隐式转换将字面值转换为函数期待的`std::string`对象，但因`std::string`的构造函数会复制提供的变量，就只复制了没有转换成期望类型的字符串字面值。

#### 传引用（一）

补全书中代码，不知道为啥，下面这段代码编译有问题，一堆错误，先贴上再说。

``` c++
// 02_else_05.cpp
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

## 理解临时对象的来源<2016-11-21 Mon>

仅当通过传值（by value）方式传递对象或传递常量引用（reference-to-const）参数时，才会发生这些类型转换，当传递一个非常量引用（reference-to-non-const）参数对象，就不会发生，如下：

``` c++
#include "stdafx.h"
#include <string>

void uppercasify(std::string &str)
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	char subtleBookPlug[] = "Effective C++";

	// error C2664: 'uppercasify' : cannot convert parameter 1 from 'char [14]' to 'std::string &'
	uppercasify(subtleBookPlug);

	return 0;
}
```

代码改成如下，果然编译通过：

``` c++
#include "stdafx.h"
#include <string>

void uppercasify(const std::string &str)
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	char subtleBookPlug[] = "Effective C++";

	uppercasify(subtleBookPlug);

	return 0;
}
```

对上面代码的理解：假设建立一个临时对象，那么临时对象将被传递到`upeercasify`中，其会修改这个临时对象，把它的字符改成大写，但是对`subtleBookPlug`函数调用的真正参数没有任何影响，仅仅改变了临时从`subtleBookPlug`生成的`std::string`对象，无疑这不是程序员所希望的，程序员传递`subtleBookPlug`参数到`uppercasify`函数中，期望修改`subtleBookPlug`的值，当程序员期望修改非临时对象时，对非常量引用（references-to-non-const）进行的隐式类型转换却修改临时对象，这就是为什么C++语言禁止为非常量引用（reference-to-non-const）产生临时对象，这样非常量引用参数就不会遇到这种问题。

临时对象是有开销的，所以你应该尽可能地去除它们，然而更重要的是训练自己寻找可能建立临时对象的地方，**在任何时候只要见到常量引用（reference-to-const）参数，就存在建立临时对象而绑定在参数上的可能性；在任何时候只要见到函数返回对象，就会有一个临时对象被建立（以后被释放）**，学会寻找这些对象构造，你就能显著地增强透过编译器表面动作而看到其背后开销的能力。

## 关于函数参数中常量引用的再理解

因为之前写过，但是在不同的笔记文件中，所以我把笔记拷贝过来了，见：[理解临时对象的来源<2016-11-21 Mon>](#理解临时对象的来源2016-11-21-mon)

前段时间写代码一直使用常量引用，已经习惯了，但是其实常量引用会造成临时对象的生成导致影响效率，今天写个测试代码再理解一次。

``` c++
#include <iostream>

class class_string
{
public:
	class_string() : data(nullptr), len(0)
	{
		std::cout << "class_string()" << std::endl;
	}

	class_string(const char *value)
	{
		std::cout << "class_string(const char *value)" << std::endl;
		data = new char[strlen(value) + 1];
		strcpy_s(data, strlen(value) + 1, value);
	}

	~class_string()
	{
		std::cout << "~class_string()" << std::endl;
		if (data)
		{
			delete data;
		}
	}

	void print_data()
	{
		std::cout << data << std::endl;
	}

private:
	char *data;
	size_t len;
};

void test_ref_to_const(const class_string &cs) // 1
{}

int main()
{
	char str[] = "hello";
	class_string cs(str);

	test_ref_to_const(str);

	return 0;
}
```

```
class_string(const char *value)
class_string(const char *value)
~class_string()
~class_string()
```

代码理解如下：在“1”处使用的是常量引用，可以看到构造和析构被调用了两次，一次是调用`test_ref_to_const(str);`，另一次是“cs”建立对象，当然如果直接使用`test_ref_to_const(cs);`，则构造和析构仅调用一次（这是我希望的），注意到`class_string`的有参构造函数其实不安全的，因为存在隐式转换，正因为隐式转换的存在才让`test_ref_to_const(str);`有了建立临时对象的可能性。

那么添上`explicit`后会怎么样呢？

``` c++
#include <iostream>

class class_string
{
public:
	class_string() : data(nullptr), len(0)
	{
		std::cout << "class_string()" << std::endl;
	}

	explicit class_string(const char *value)
	{
		std::cout << "class_string(const char *value)" << std::endl;
		data = new char[strlen(value) + 1];
		strcpy_s(data, strlen(value) + 1, value);
	}

	~class_string()
	{
		std::cout << "~class_string()" << std::endl;
		if (data)
		{
			delete data;
		}
	}

	void print_data()
	{
		std::cout << data << std::endl;
	}

private:
	char *data;
	size_t len;
};

void test_ref_to_const(const class_string &cs)
{}

int main()
{
	char str[] = "hello";
	class_string cs(str);

	test_ref_to_const(str);

	return 0;
}
```

``` shellsession
error C2664: 'void test_ref_to_const(const class_string &)':
cannot convert argument 1 from 'char [6]' to 'const class_string &'
```

**果然编译出错，那么可以看出`explicit`有防止建立临时对象的作用**，如果仍保持隐式转换的存在，即不增加`explicit`，而是将函数的参数改为非常量引用，这就是大前年文章中提到的那样将会出现编译错误，算了代码不贴了，没有意义。

总结：如果使用常量引用，那么关闭隐式转换，避免产生临时对象而影响性能的可能性。

# <2019-03-13 周三> 《C++并发编程实战》读书笔记（三）

## 第2章 线程管理（二）

### 向线程函数传递参数（二）

越看问题越多，还是[传引用（一）](#传引用一)中提到的代码，通过将`update_data_for_widget`的参数修改为传值可以编译成功，但是输出结果让人费解，完整的测试代码如下：

``` c++
// 02_else_05.cpp
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

void update_data_for_widget(widget_id w, widget_data data) // 修改点
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

``` shellsession
% ./02_else_05
widget_data()
~widget_data()
data.id: 0
~widget_data()
~widget_data()
~widget_data()
```

`widget_data`的析构函数居然被调用了四次。这是什么原因呢？

在[传引用（一）](#传引用一)中提到的那些代码放到“VS2017”中编译，提示：

```
error C2672: 'std::invoke': no matching overloaded function found
```

上面信息好像是在说编译器是在找

``` c++
void update_data_for_widget(widget_id w, widget_data data);
```

而不是在找

``` c++
void update_data_for_widget(widget_id w, widget_data &data);
```

所以编译的时候报错，但是在我的“Archlinux”下编译好像又另外一个意思，输出不贴了，太长。

# <2019-03-15 周五> 《C++并发编程实战》读书笔记（四）

## 第2章 线程管理（三）

### 向线程函数传递参数（三）

#### 传引用（二）

为了确定不是我上面为了补全书中代码而写出来的问题，我将“02_else_03.cpp”的代码修改为，如下：

``` c++
#include <iostream>
#include <string>
#include <thread>

void f(int i, std::string &s)
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

上面的代码，将`f`函数的第二个参数去掉`const`即修改为非常量引用，编译时果然出错，与“02_else_05.cpp”的出错信息完全一样，所以应该确定是`std::thread`我没有使用正确，即`std::thread`不能这么直接传引用，需要使用`std::ref()`或者`std::cref()`，因为上面代码的`"hello"`是常量字符串，所以你会发现即使使用了`std::ref()`或者`std::cref()`也同样报相同的错误，“02_else_05.cpp”中正确使用引用的方法如下：

``` c++
// 02_else_05.cpp
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
  std::thread t(update_data_for_widget, w, std::ref(data));
  t.join();

  std::cout << "data.id: " << data.get_id() << std::endl;
}

int main(int argc, char *argv[])
{
  oops_again(3);

  return 0;
}
```

``` shellsession
% ./02_else_05
widget_data()
data.id: 3
~widget_data()
```

其中关于我上面遇到的问题在书中已做了讲解，但是我并没有完全看懂，我只是认为那段代码可以编译通过，书中所说：“`update_data_for_widget`的第二个参数期待传入一个引用，但是`std::thread`的构造函数并不知晓，构造函数**无视**函数期待的参数类型，并盲目的拷贝已提供的变量。当线程调用`update_data_for_widget`函数时**，传递给函数的参数是`data`变量内部拷贝的引用，而非数据本身的引用**。因此当线程结束时，内部拷贝数据将会在数据更新阶段被销毁。”，“**使用`std::ref`将参数转换成引用的形式**”。

可能提供一个成员函数指针作为线程函数，并提供一个合适的对象指针作为线程函数的第一个参数：

``` c++
// 02_else_06.cpp
#include <iostream>
#include <thread>

class X
{
public:
  void do_lengthy_work()
  {
    std::cout << "X::do_lengthy_work() called\n";
  }
};

int main(int argc, char *argv[])
{
  X my_x;
  std::thread t(&X::do_lengthy_work, &my_x);
  t.join();

  return 0;
}
```

``` shellsession
% ./02_else_06
X::do_lengthy_work() called
```

移动操作可以将对象转换成可接受的类型，**例如：函数参数或函数返回的类型**（可以类型转换？这个高端特性我要了解一下），**当原对象是一个临时变量时，自动进行移动操作，但当原对象是一个命名变量，那么转换的时候就需要使用`std::move()`进行显式移动**。

`DynArray`的面试题中我对“移动语义”和`std::move()`的区别不是太清楚，现在看来，如果在类中实现“移动语义”的话，那应该就是赋值指针，并将原指针设为`nullptr`，这应该是对的。

### 转移线程所有权（一）

C++标准库中有很多资源占有（resource-owning）类型，比如`std::ifstream`，`std::unique_ptr`还有`std::thread`**都是可移动（movable），但不可拷贝（copyable）**。

下面两个小章节是我自己看书分出来的，原书中并不存在

#### `std::thread`线程所有权在函数外转换

`std::thread`支持移动，就意味着线程的所有权可以在函数外进行转移，补全书中代码如下：

``` c++
// 02_05_01.cpp
#include <iostream>
#include <thread>

void some_function()
{
  std::cout << "some_function\n";
}

void some_other_function(int i)
{
  std::cout << "some_other_function(" << i << ")\n";
}

std::thread f()
{
  return std::thread(some_function);
}

std::thread g()
{
  std::thread t(some_other_function, 42);
  return t;
}

int main(int argc, char *argv[])
{
  f().join();
  g().join();

  std::thread t1 = f();
  t1.join();
  std::thread t2 = g();
  t2.join();

  return 0;
}
```

``` shellsession
% ./02_05_01
some_function
some_other_function(42)
some_function
some_other_function(42)
```

#### `std::thread`线程所有权在函数内转换

当所有权可以在函数内部传递，就允许`std::thread`实例可作为参数进行传递，代码如下：

``` c++
#include <iostream>
#include <thread>

void some_function()
{
  std::cout << "some_function\n";
}

void f(std::thread t)
{
  t.join();
}

void g()
{
  f(std::thread(some_function));
  std::thread t(some_function);
  f(std::move(t));
}

int main(int argc, char *argv[])
{
  g();

  return 0;
}
```

``` shellsession
% ./02_05_02
some_function
some_function
```

# <2019-03-19 周二> 《C++并发编程实战》读书笔记（五）

## 第2章 线程管理（四）

### 转移线程所有权（二）

`std::thread`支持移动的好处是可以创建`thread_guard`类的实例（见[`thread_guard`](#thread_guard)），**并且拥有其线程的所有权**，当`thread_guard`对象所拥有的线程已经被引用，移动操作就可以避免很多不必要的麻烦；这意味着，当某个对象转移了线程所有权后，它就不能对线程进行加入或分离。

刚才看这句话的时候脑子还在想为什么会这样？为什么构造函数传入的是`std::thread &t_`，这里却说是移动操作呢？我觉得以后再看的时候也会有这样的想法，所以在这里提醒一下，因为`thread_guard`的构造函数已经删除了默认拷贝构造函数和赋值操作符；此外在上面也提到了关于`std::thread`的这类对象**都是可移动（movable），但不可拷贝（copyable）**，见[转移线程所有权（一）](#转移线程所有权一)，所以关于`thread_guard`的代码就好理解了。

为了确保线程程序退出前完成，下面代码里定义了`scoped_thread`类，补全书中代码如下

``` c++
// 02_06_01.cpp
#include <iostream>
#include <thread>

class scoped_thread
{
  std::thread t;

public:
  explicit scoped_thread(std::thread t_) :
    t(std::move(t_))
  {
    std::cout << "scoped_thread constructor" << std::endl;

    if (!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }

  ~scoped_thread()
  {
    t.join();
  }

  scoped_thread(const scoped_thread &) = delete;
  scoped_thread& operator=(const scoped_thread &) = delete;
};

struct func
{
  int &i;

  func(int &i_) : i(i_)
  {
    std::cout << "func constructor" << std::endl;
  }

  void operator()()
  {
    for (unsigned n = 0; n < 100; ++n) {
      std::cout << i;
      i++;
    }

    std::cout << std::endl;
  }
};

void f()
{
  int some_local_state = 0;
  scoped_thread t(std::thread(func(some_local_state)));

  std::cout << "press any key to quit" << std::endl;
  getchar();
}

int main(int argc, char *argv[])
{
  f();

  return 0;
}
```

上面的程序是原书中的代码，运行将会发现没有任何输出和异常，不合逻辑在我看来，因为我添加了`getchar()`来看下程序输出，但是什么也没有，包括`scoped_thread`和`func`的构造函数信息，说明没有被调用啊。

回想在[`background_task`临时变量问题](#background_task)的问题，即`std::thread(func(some_local_state))`并不是一个`std::thread`的对象定义，而一个函数声明，所以本书中是不是前后矛盾了？如果我进行下面的修改是不是会有好转呢？

即将`scoped_thread t(std::thread(func(some_local_state)));`修改为`scoped_thread t(std::thread{func(some_local_state)});`

``` c++
// 02_06_02.cpp
#include <iostream>
#include <thread>

class scoped_thread
{
  std::thread t;

public:
  explicit scoped_thread(std::thread t_) :
    t(std::move(t_))
  {
    std::cout << "scoped_thread constructor" << std::endl;

    if (!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }

  ~scoped_thread()
  {
    t.join();
  }

  scoped_thread(const scoped_thread &) = delete;
  scoped_thread& operator=(const scoped_thread &) = delete;
};

struct func
{
  int &i;

  func(int &i_) : i(i_)
  {
    std::cout << "func constructor" << std::endl;
  }

  void operator()()
  {
    for (unsigned n = 0; n < 100; ++n) {
      std::cout << i;
      i++;
    }

    std::cout << std::endl;
  }
};

void f()
{
  int some_local_state = 0;
  scoped_thread t(std::thread{func(some_local_state)});

  std::cout << "press any key to quit" << std::endl;
  getchar();
}

int main(int argc, char *argv[])
{
  f();

  return 0;
}
```

这样这就是我所期待的输出，我认为这应该就是本书作者想要表达的意思吧！这里新线程是直接传递到`scoped_thread`中，而非创建一个独立的命名变量。当主线程到达`f()`函数末尾时，`scoped_thread`对象将会销毁，然后线程被`join()`，与`thread_guard`不同的是，这里检查线程的`joinable()`放到了构造函数中，如果线程不可加入，抛出异常。

将`std::thread`放入`std::vector`是向线程自动化管理迈出的第一步：并非为这些线程创建独立的变量，并且将他们直接加入，可以把它们当做一个组

``` c++
// 02_07.cpp
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{
  std::cout << "do_work: " << id << std::endl;
}

void f()
{
  std::vector<std::thread> threads;

  for (unsigned i = 0; i < 20; ++i) {
    threads.push_back(std::thread(do_work, i));
  }

  std::for_each(threads.begin(),
                threads.end(),
                std::mem_fn(&std::thread::join)
                );
}

int main(int argc, char *argv[])
{
  f();

  return 0;
}
```

``` shellsession
% ./02_07
do_work: 4
do_work: 5
do_work: 3
do_work: 7
do_work: 1
do_work: 2
do_work: 6
do_work: 8
do_work: 10
do_work: 11
do_work: 9
do_work: 12
do_work: 13
do_work: 14
do_work: 15
do_work: 16
do_work: 0
do_work: 17
do_work: 19
do_work: 18
```

### 运行时决定线程数量

补全书中代码

``` c++
// 02_08.cpp
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

template<typename Iterator, typename T>
struct accumulate_block
{
  void operator()(Iterator first, Iterator last, T& result)
  {
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  const unsigned long length = std::distance(first, last);

  if (!length) {
    return init;
  }

  const unsigned long min_per_thread = 25;
  const unsigned long max_threads =
    (length + min_per_thread - 1) / min_per_thread;
  std::cout << "min_per_thread: " << min_per_thread << std::endl;
  std::cout << "max_threads: " << max_threads << std::endl;

  const unsigned long hardware_threads =
    std::thread::hardware_concurrency();
  std::cout << "hardware_threads: " << hardware_threads << std::endl;

  const unsigned long num_threads =
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
  std::cout << "num_threads: " << num_threads << std::endl;

  const unsigned long block_size = length / num_threads;
  std::cout << "block_size: " << block_size << std::endl;

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);

    threads[i] = std::thread(accumulate_block<Iterator, T>(),
                             block_start, block_end, std::ref(results[i])
                             );

    block_start = block_end;
  }

  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

  std::for_each(threads.begin(),
                threads.end(),
                std::mem_fn(&std::thread::join)
                );

  return std::accumulate(results.begin(), results.end(), init);
}

void test_accumulate_block()
{
  std::cout << "test_accumulate_block" << std::endl;

  std::vector<int> vec{1, 2, 3};
  int sum = 0;

  std::thread t(accumulate_block<std::vector<int>::iterator, int>(),
                vec.begin(), vec.end(), std::ref(sum)
                );
  t.join();

  std::cout << "sum: " << sum << std::endl;
}

void test_parallel_accumulate()
{
  std::cout << "test_parallel_accumulate" << std::endl;

  std::vector<int> vec;

  for (unsigned i = 1; i <= 100; ++i) {
    vec.push_back(i);
  }

  int sum = parallel_accumulate(vec.begin(), vec.end(), 0);

  std::cout << "sum: " << sum << std::endl;
}

int main(int argc, char *argv[])
{
  test_accumulate_block();
  std::cout << std::endl;
  test_parallel_accumulate();

  return 0;
}
```

``` shellsession
% ./02_08
test_accumulate_block
sum: 6

test_parallel_accumulate
min_per_thread: 25
max_threads: 4
hardware_threads: 1
num_threads: 1
block_size: 100
sum: 5050
```

这段代码确实很简单，但是书中所提到的信息由于我眼光窄，没接触过，还不了解这些知识点。

书中所言：结束这个例子之前，需要明确：`T`类型的加法运算不满足结合律（比如，对于`float`型或`double`型，在进行加法操作之时，系统很可能会做截断操作），因为对范围中元素的分组，会导致`parallel_accumulate`得到的结果可能与`std::accumulate`得到的结果不同。同样的，这里对迭代器的要求更加严格：必须都是向前迭代器（forward iterator），而`std::accumulate`可以在只传入迭代器（input iterator）的情况下工作。对于创建出`result`容器，需要保证`T`有默认构造函数。对于算法并行，通常都要这样的修改；不过，需要根据算法本身的特性，选择不同的并行方式。需要注意：**因为不能直接从一个线程中返回一个值，所以需要传递`result`容器的引用到线程中去。另一个办法，通过地址来获取线程执行结果；第4章中，我们将使用（futures）完成这种方案**。

### 识别线程

略

### 总结

略

# <2019-03-26 周二> 《C++并发编程实战》读书笔记（六）

## 第3章 线程间共享数据（一）

### 使用互斥量保护共享数据（一）

#### C++中使用互斥量

下面这段代码中这个全局的互斥量使得这两个函数中对数据的访问是互斥的：`list_contains()`不可能看到正在被`add_to_list()`修改的列表。但是具有访问能力的指针或引用可以访问（并可能修改）被保护的数据，而不会被互斥锁限制。

``` c++
// 03_01.cpp
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find)
    != some_list.end();
}

int main(int argc, char *argv[])
{
  return 0;
}
```

#### 精心组织代码来保护共享数据

在确保成员函数不会传出指针或引用的同时，检查成员函数是否通过指针或引用的方式来调用也是很重要的（尤其是这个操作不在你的控制下时）。函数可能没在互斥量保护的区域内，存储着指针或者引用，这样就很危险。更危险的是：将保护数据作为一个运行时参数，如同下面代码中所示那样。

``` c++
// 03_02.cpp
#include <iostream>
#include <string>
#include <mutex>

class some_data
{
  int a;
  std::string b;

public:
  void do_something()
  {
    std::cout << "do_something()" << std::endl;
  }
};

class data_wrapper
{
  some_data data;
  std::mutex m;

public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    func(data);
  }
};

some_data *unprotected;

void malicious_function(some_data &protected_data)
{
  unprotected = &protected_data;
}

data_wrapper x;

void foo()
{
  x.process_data(malicious_function);
  unprotected->do_something();
}

int main(int argc, char *argv[])
{
  foo();

  return 0;
}
```

需要保护的数据及互斥锁一般都是类的私有成员，虽然`std::lock_guard`对数据做了很好的保护，但调用用户提供的函数`func`，就意味着`foo`能够绕过保护机制将函数`malicious_function`传递进去，在没有锁定互斥量的情况下调用`do_something()`。这段代码问题在于根本没有保护，只是将所有可访问的数据结构代码标记为互斥。函数`foo()`中调用`unprotected->do_something()`的代码未能被标记为互斥。这种情况下，C++线程库无法提供任何帮助，只能由程序员来使用正确的互斥锁来保护数据。

#### 发现接口内在的条件竞争

这里的内容作者主要是想表达像下面这个`stack<T, Container>`类的**问题发生在接口设计上，所以解决的方法也就是改变接口设计**。

补全书中代码，需要注意的是，缺少的代码太多，我只补全了其中需要用到的四个成员函数，只是为了能使代码可以顺利编译，而且此代码也存在内存泄漏。

``` c++
// 03_03.cpp
#include <iostream>
#include <deque>

template<typename T, typename Container = std::deque<T> >
class stack
{
public:
  explicit stack(const Container&);
  explicit stack(Container&& = Container());
  template <class Alloc> explicit stack(const Alloc&);
  template <class Alloc> stack(const Container&, const Alloc&);
  template <class Alloc> stack(Container&&, const Alloc&);
  template <class Alloc> stack(stack&&, const Alloc&);

  bool empty() const;
  size_t size() const;
  T& top();
  const T& top() const;
  void push(const T&);
  void push(T&&);
  void pop();
  void swap(stack&&);
};

template<typename T, typename Container>
stack<T, Container>::stack(Container &&)
{
}

template<typename T, typename Container>
bool stack<T, Container>::empty() const
{
  return false;
}

template<typename T, typename Container>
T& stack<T, Container>::top()
{
  T *t = new T;
  return *t;
}

template<typename T, typename Container>
void stack<T, Container>::pop()
{
}

void do_something(int value)
{
  std::cout << "do_something(" << value << ")" << std::endl;
}

void test()
{
  stack<int> s;
  if (!s.empty()) {
    const int value = s.top();
    s.pop();
    do_something(value);
  }
}

int main(int argc, char *argv[])
{
  test();

  return 0;
}
```

以上是单线程安全代码，那么上面的代码怎么改才能称为改变接口设计呢？在这个简单的例子中，当调用`top()`时，发现栈已经是空的了，那么就抛出异常。**虽然这能直接解决这个问题，但这是一个笨拙的解决方案**，这样的话，即使`empty()`返回`false`的情况下，你也需要异常捕获机制。**本质上，这样的改变会让`empty()`成为一个多余函数**（这是确实，反正为空会抛出异常，那还要`empty()`做什么呢？）

原书中：说一些大家没有意识到的问题。这个问题概述为在`pop()`时，当拷贝数据的时候抛出一个异常，这时要弹出的数据将会丢失，它的确从栈上移出了，但是拷贝失败了。`std::stack`的设计人员将这个操作分为两部分：先获取顶部元素（top()），然后从栈中移除（pop()）。这样，在不能安全的将元素拷贝出去的情况下，栈中的这个元素还依旧存在，没有丢失。**不幸的是，这样的分割却制造了本想避免或消除的条件竞争**（这里没看懂，这样的分割是怎么制造了条件竞争？）。幸运的是，我们还有别的选项，但是这些选项是要付出代价的。

##### 选项1 传入一个引用

``` c++
std::vector<int> result;
some_stack.pop(result);
```

大多数情况下，这种方式还不错，但有明显的缺点：需要临时构造出一个堆中类型的实例，用于接收目标值。对于一些类型，这样做是不现实的，因为临时构造一个实例，从时间和资源的角度来看都是不划算的。对于其他的类型，这样也不总能行得通，因为构造函数要是需要一些参数呢！最后，需要可赋值的存储类型，这是一个重大的限制：即使支持移动构造，甚至是拷贝构造（从而允许返回一个值），很多用户自定义类型可能都不支持赋值操作。

##### 选项2 无异常抛出的拷贝构造函数或移动构造函数

对于有返回值的`pop(**`函数来说，只有“异常安全”方面的担忧（当返回值时可以抛出一个异常），（就像上面说的那样，弹出的数据拷贝失败了，但它也从栈上移出了）。很多类型都有拷贝构造函数，它们不会抛出异常。一个有用的选项可以限制对线程安全的栈的使用，并且能 让栈安全的返回所需的值，而不会抛出异常。

虽然安全，但非可靠。尽管能在编译时，使用`std::is_nothrow_copy_constructible`和`std::is_nothrow_move_constructible`类型特征，让拷贝或移动构造函数不抛出异常，但是这种方式的局限性太强。因为有很多的用户定义类型有可抛出异常的拷贝构造函数，没有移动构造函数；或是，都不抛出异常的构造函数。如果类型不能存储线程安全的堆栈，想想该是多么的不幸。

##### 选项3 返回指向弹出值的指针

第三个选择是返回一个指向弹出的元素的指针，而不是直接返回值。**指针的优势是自由拷贝，并且不会产生异常**，（原来指针的优势是不会产生异常）。缺点就是返回一个指针需要对对象的内存分配进行管理，对于简单数据类型（比如：`int`），内存管理的开销远大于直接返回值（这种标准类型就直接返回值最好，不要使用指针啦）。对于选择这个方案的接口，使用`std::shared_ptr`是个不错的选择，避免内存泄露，而且标准库能够完全控制内存分配方案。这种优化是很重要的：因为堆栈中的每个对象，都需要`new`进行独立内存分配，相较于非线程安全版本，这个方案的开销相当大。

##### 选项4 “选项1和2”或“选项1和3”

对于通用的代码来说，灵活性不应忽视。当你已经选择了选项2或3时，再去选择1也是很容易的。这些选项提供给用户，让用户自己选择对于他们自己来说最合适最经刘的方案。

下面就一个线程安全的堆栈，它是一个**接口没有条件竞争的堆栈类定义**，它实现了**选项1和选项3**：重载了`pop()`，使用一个局部引用去存储弹出值，并返回一个`std::shared_ptr<>`对象。

``` c++
// 03_04.cpp
#include <exception>
#include <memory>

struct empty_stack : std::exception
{
  const char *what() const throw() { return nullptr; }
};

template<typename T>
class threadsafe_stack
{
public:
  threadsafe_stack();
  threadsafe_stack(const threadsafe_stack&);
  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T);
  std::shared_ptr<T> pop();
  void pop(T&);
  bool empty() const;
};

int main(int argc, char *argv[])
{
  return 0;
}
```

对于上面的代码，消减接口可以获得最大程序的安全，甚至限制对栈的一些操作，比如上面这个栈是不能直接赋值的。简化接口更有利于数据控制，可以保证互斥量将一个操作完全锁住。

一个简单的实现线程安全的堆栈，如下：

<span id="03_05_cpp"></span>

``` c++
// 03_05.cpp
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
  const char *what() const throw()
  {
    return "empty stack!";
  }
};

template<typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack()
    : data(std::stack<int>())
  {}

  threadsafe_stack(const threadsafe_stack& rhs)
  {
    std::lock_guard<std::mutex> lock(rhs.m); // m is private
    data = rhs.data;
  }

  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }

  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }

    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
  }

  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }

    value = data.top();
    data.pop();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

int main(int argc, char *argv[])
{
  threadsafe_stack<int> s1;
  threadsafe_stack<int> s2(s1);

  return 0;
}
```

堆栈可以拷贝，拷贝构造函数对互斥量上锁，再拷贝堆栈。`data = rhs.data;`使用互斥量来确保复制结果的正确性，**这样的方式比成员初始化列表好**。

同时需要注意的是拷贝构造函数中直接调用了私有成员变量`m`，而且居然编译没有出错？这里编译是不会出错的，我只能这么理解：因为它的调用是在类的内部，所以它可以访问私有成员变量`m`，虽然是通过形参的方式。在编程题里也遇到过这种写法，只是当时没有注意而已，见：[dyn_array_demo](https://github.com/ysouyno/dyn_array_demo)

# <2019-03-27 周三> 《C++并发编程实战》读书笔记（七）

## 第3章 线程间共享数据（二）

### 使用互斥量保护共享数据（二）

#### 死锁问题描述及解决方案

避免死锁的一般建议，就是让两个互斥量总以相同的顺序上锁：总在互斥量B之前锁住互斥量A，就永远不会死锁。某些情况下是可以这样用，因为不同的互斥量用于不同的地方。不过，事情没那么简单，比如：当有多个互斥量保护同一个类的独立实例时，一个操作对同一个类的两个不同实例进行<u>数据的交换操作</u>，为了保证数据交换操作的正确性，就要避免数据被并发修改，并确保每个实例上的互斥量都能锁住自己要保护的区域。不过，选择一个固定的顺序（例如，实例提供的第一互斥量作为第一个参数，提供的第二个互斥量为第二个参数），可能会适得其反：在参数交换了之后，两个线程试图在相同的两个实例间进行数据交换时，程序又死锁了！

很幸运，C++标准库有办法解决这个问题，`std::lock`可以一次性锁住多个（两个以上）的互斥量，并且没有副作用（死锁风险）。来看一下下面的代码是怎么在一个简单的交换操作中使用`std::lock`。

``` c++
// 03_06.cpp
#include <iostream>
#include <mutex>

class some_big_object
{
public:
  some_big_object();
};

void swap(some_big_object& lhs, some_big_object& rhs)
{}

class X
{
private:
  some_big_object some_detail;
  std::mutex m;

public:
  X(const some_big_object& sd) : some_detail(sd) {}

  friend void swap(X& lhs, X& rhs)
  {
    if (&lhs == &rhs) {
      return;
    }

    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);

    swap(lhs.some_detail, rhs.some_detail);
  }
};

int main(int argc, char *argv[])
{
  return 0;
}
```

这样就能保证在大多数情况下，函数退出时互斥量能被正确的解锁（保护操作可能会抛出一个异常），也允许使用一个简单的`return`作为返回。**`std::lock`要么将两个锁都锁住，要不一个都不锁**。

#### 避免死锁的进阶指导

那么多建议见原书，下面代码是通过层次锁来避免死锁。

``` c++
// 03_07.cpp
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
```

``` shellsession
% ./03_07
low_level_stuff()
high_level_stuff(2)
terminate called after throwing an instance of 'std::logic_error'
  what():  mutex hierarchy violated
[1]    8278 abort (core dumped)  ./03_07
```

这里重点是使用了`thread_local`的值来代表当前线程的层级值：`this_thread_hierarchy_value`。它被初始化为最大值，所以最初所有线程都能被锁住。因为其声明中有`thread_local`，所以**每个线程都有其拷贝副本**，这样**线程中变量状态完全独立，当从另一个线程进行读取时，变量的状态也完全独立**。

这里有一个问题：<u>类的`static`变量不属于类而`thread_local`又是线程局部变量，那么上述代码中的`static thread_local unsigned long this_thread_hierarchy_value;`这种用法应该怎么理解呢？</u>

#### 不同域中互斥量所有权的传递

补全书中代码，用于理解书中所说的：一种使用可能是允许一个函数去锁住一个互斥量，并且将所有权移到调用者上，所以调用者可以在这个锁保护的范围内执行额外的动作。

``` c++
// 03_else_01.cpp
#include <iostream>
#include <mutex>

std::mutex some_mutex;

void prepare_data()
{
  std::cout << "prepare_data()" << std::endl;
}

void do_something()
{
  std::cout << "do_something()" << std::endl;
}

std::unique_lock<std::mutex> get_lock()
{
  extern std::mutex some_mutex;
  std::unique_lock<std::mutex> lk(some_mutex);
  prepare_data();
  return lk;
}

void process_data()
{
  std::unique_lock<std::mutex> lk(get_lock());
  do_something();
}

int main(int argc, char *argv[])
{
  process_data();

  return 0;
}
```

``` shellsession
% ./03_else_01
prepare_data()
do_something()
```

`process_data()`函数直接转移`std::unique_lock`实例的所有权，调用`do_something()`可使用的正确数据（数据没有受到其他线程的修改）。**`std::unique_lock`是可移动，但不可赋值的类型**。

`std::unique_lock`的灵活性同样也允许实例在销毁之前放弃其拥有的锁。这对于应用性能来说很重要，因为持有锁的时间增加会导致性能下降，其他线程会等待这个锁的释放，避免超越操作。

#### 锁的粒度

``` c++
// 03_08.cpp
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
```

在这个例子中，比较操作符首先通过调用`get_detail()`成员函数检索要比较的值，函数在索引值时被一个锁保护着。比较操作符会在之后比较索引出来的值。注意：虽然这样能减少锁持有的时间，一个锁只持有一次（这样能消除死锁的可能性），这里有一个**微妙的语义操作同时对两个锁住的值进行比较**，当操作符返回`true`时，那就意味着在这个时间点上的`lhs.some_detail`与在另一个时间点的`rhs.some_detail`相同。这两个值在读取之后，可能会被任意的方式所修改；两个值会进行交换，**这样就会失去比较的意义**。

有时，只是没有一个合适粒度级别，因为并不是所有对数据结构的访问都需要同一级的保护。这个例子中，就需要寻找一个合适的机制，去替换`std::mutex`。

### 保护共享数据的替代设施

略

# <2019-03-28 周四> 《C++并发编程实战》读书笔记（八）

## 第4章 同步并发操作（一）

### 等待一个事件或其他条件

#### 等待条件达成

C++标准库对条件变量有两套实现：`std::condition_variable`和`std::condition_variable_any`。前者仅限于与`std::mutex`一起工作，而后者可以和任何满足最低标准的互斥量一起工作，从而加上了`_any`的后缀。因为`std::condition_variable_any`更加通用，这就可能从体积、性能，以及系统资源的使用方面产生额外的开销，所以`std::condition_variable`一般作为首选的类型，当对灵活性有硬性要求时，我们才会去考虑`std::condition_variable_any`。

下面代码使用`std::condition_variable`处理数据等待，补全书中代码如下：

``` c++
// 04_01.cpp
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <unistd.h>

typedef int data_chunk;
const data_chunk MAX_DATA = 9;

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare()
{
  static int i = 0;
  usleep(500000);

  if (i++ == MAX_DATA) {
    return false;
  }

  return true;
}

data_chunk prepare_data()
{
  static data_chunk d = 0;
  return ++d;
}

void process(data_chunk data)
{
  std::cout << "process(" << data << ")" << std::endl;
}

bool is_last_chunk(data_chunk data)
{
  if (data == MAX_DATA) {
    return true;
  }

  return false;
}

void data_preparation_thread()
{
  while (more_data_to_prepare()) {
    const data_chunk data = prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();
  }
}

void data_processing_thread()
{
  while (true) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, []{return !data_queue.empty();});
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk(data)) {
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  std::thread t1(data_preparation_thread);
  std::thread t2(data_processing_thread);

  t1.join();
  t2.join();

  return 0;
}
```

``` shellsession
% ./04_01
process(1)
process(2)
process(3)
process(4)
process(5)
process(6)
process(7)
process(8)
process(9)
```

这里需要理解`wait()`和行为，我觉得很重要。`wait()`会去检查这些条件（通过调用所提供的`lambda`函数），当条件满足（`lambda`函数返回`true`）时返回。如果条件不满足（`lambda`函数返回`false`），`wait()`函数将**解锁互斥量**，并且将这个线程（上段提到的处理数据的线程）置于阻塞或等待状态。当准备数据的线程调用`notify_one()`通知条件变量时，处理数据的线程从睡眠状态中苏醒，**重新获取互斥锁**，并且**对条件再次检查**，在条件满足的情况下，从`wait()`返回**并继续持有锁**。当条件不满足时，线程将对**互斥量解锁**，并且**重新开始等待**。

自己的理解：如果条件不满足的情况下，即数据为空，`wait()`函数会解锁互斥量，并阻塞线程，当`notify_one()`通知时，则线程从睡眠中醒来，重新获得互斥锁，并检查条件，条件满足时，此时`wait()`函数返回继续执行下面的代码，返回的`wait()`函数是持有互斥锁的，条件不满足时，线程解锁互斥量并重新开始等待。

关于上面的代码为什么`std::unique_lock`要比`std::lock_guard`更合适呢？因为等待中的线程必须在等待期间解锁互斥量，并在这之后对互斥量再次上锁，而`std::lock_guard`没有这么灵活，因为他没办法调用`unlock()`函数。如果互斥量在线程休眠期间保持锁住状态，准备数据的线程将无法锁住互斥量，也无法添加数据到队列中；同样的，等待线程也永远不会知道条件何时满足。

在调用`wait()`的过程中，一个条件变量可能会去检查给定条件若干次；然而，它总是在互斥量被锁定时这样做，当且仅当提供测试条件的函数返回`true`时，它就会立即返回。

#### 使用条件变量构建线程安全队列

使用条件变量的线程安全队列（完整版）：

<span id="04_02_cpp"></span>

``` c++
// 04_02.cpp
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue() {}

  threadsafe_queue(const threadsafe_queue &other)
  {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue = other.data_queue;
  }

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }

  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return false;
    }

    value = data_queue.front();
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
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
```

代码抄完啦，但是我不知道如何使用及测试，这是个大问题呀。

这是为什么要加`mutable`关键字的原因吗？<u>如果锁住互斥量是一个可变操作，那么这个互斥量对象就会被标记为可变的，之后可以在`empty()`和拷贝构造函数中上锁了</u>。哦，写到这里我想起来了，因为`empty()`和拷贝构造函数都存在`const`修饰，它们内部不能修改任何类的成员变量，所以要加上`mutable`关键字。

### 使用期望等待一次性事件

#### 带返回值的后台任务

使用`std::future`从异步任务中获取返回值。如下：

``` c++
// 04_03.cpp
#include <iostream>
#include <future>
#include <unistd.h>

int find_the_answer_to_ltuae()
{
  std::cout << "find_the_answer_to_ltuae()" << std::endl;
  sleep(1);
  return 1;
}

void do_other_stuff()
{
  std::cout << "do_other_stuff()" << std::endl;
}

int main(int argc, char *argv[])
{
  std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
  do_other_stuff();
  std::cout << "the answer is " << the_answer.get() << std::endl;

  return 0;
}
```

``` shellsession
% ./04_03
do_other_stuff()
the answer is find_the_answer_to_ltuae()
1
```

使用`std::async`向函数传递参数。如下：

``` c++
// 04_04.cpp
#include <iostream>
#include <string>
#include <future>

struct X
{
  void foo(int i, const std::string &s)
  {
    std::cout << "foo(" << i << ", " << s << ")" << std::endl;
  }

  std::string bar(const std::string &s)
  {
    std::cout << "bar(" << s << ")" << std::endl;
    return s;
  }
};

struct Y
{
  double operator()(double d)
  {
    std::cout << "Y(" << d << ")" << std::endl;
    return d;
  }
};

X baz(X& x)
{
  std::cout << "baz(x)" << std::endl;
  return x;
}

class move_only
{
public:
  move_only()
  {
    std::cout << "move_only constructor" << std::endl;
  }

  move_only(move_only&&) {}

  move_only(const move_only&) = delete;
  move_only& operator=(move_only&&) = delete;
  move_only& operator=(const move_only&) = delete;

  void operator()()
  {
    std::cout << "move_only::operator()" << std::endl;
  }
};

int main(int argc, char *argv[])
{
  X x;
  auto f1 = std::async(&X::foo, &x, 42, "hello");
  auto f2 = std::async(&X::bar, x, "goodbye");

  Y y;
  auto f3 = std::async(Y(), 3.141);
  auto f4 = std::async(std::ref(y), 2.718);

  std::async(baz, std::ref(x));

  auto f5 = std::async(move_only());

  auto f6 = std::async(std::launch::async, Y(), 1.2);
  auto f7 = std::async(std::launch::deferred, baz, std::ref(x));
  auto f8 = std::async(std::launch::deferred | std::launch::async,
                       baz, std::ref(x)
                       );
  auto f9 = std::async(baz, std::ref(x));

  f7.wait();

  return 0;
}
```

``` shellsession
% ./04_04
baz(x)
move_only constructor
baz(x)
Y(3.141)
Y(2.718)
bar(goodbye)
foo(42, hello)
baz(x)
baz(x)
Y(1.2)
move_only::operator()
```

上面代码的输出顺序不是相同的，可以多次运行程序看看。

`std::launch::defered`，用来表明函数调用被延迟到`wait()`或`get()`函数调用时才执行，`std::launch::async`表明函数必须在其所在的独立线程上执行，`std::launch::deferred | std::launch::async`表明实现可以选择这两种方式的一种。最后一个选项是默认的。当函数调用被延迟，它可能不会再运行了。如下：

``` c++
// 在新线程上执行
auto f6 = std::async(std::launch::async, Y(), 1.2);

// 在`wait()`或`get()`时执行
auto f7 = std::async(std::launch::deferred, baz, std::ref(x));

// 实现选择执行方式
auto f8 = std::async(std::launch::deferred | std::launch::async,
                     baz, std::ref(x)
                     );

auto f9 = std::async(baz, std::ref(x));

// 调用延迟函数，如果没有这行代码，上面的将少一行输出
f7.wait();
```

#### 任务与期望

使用`std::packaged_task`执行一个图形界面线程，补全书中代码如下：

``` c++
// 04_05.cpp
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
```

``` shellsession
% ./04_05
get_and_process_gui_message()
test_func()1
get_and_process_gui_message()
test_func()2
get_and_process_gui_message()
get_and_process_gui_message()
get_and_process_gui_message()
get_and_process_gui_message()
get_and_process_gui_message()
get_and_process_gui_message()
get_and_process_gui_message()
get_and_process_gui_message()
```

这段代码确实很简单，但好像其中的深意我还不能体会出来，大概的意思是：他能在队列中提取出一个任务，然后释放队列上的锁（因为锁在`{}`中，所以退出时锁被释放），并且执行任务`task();`。这里，“期望”与任务相关，当任务执行完成时，其状态会被置为“就绪”状态。

将一个任务传入队列也很简单：`std::packaged_task<void()> task(f);`可以提供一个打包好的任务，可以通过这个任务调用`task.get_future()`获取“期望”对象，**并且在任务被推入列表之前，“期望”将返回调用函数**。当需要知道线程执行完任务时，向图形界面线程发布消息的代码，会等待“期望”改变状态；否则，则会丢弃这个“期望”。

#### 使用`std::promises`

略，书中代码缺太多，无法补全，只能看着伪代码自己理解。

#### 为“期望”存储“异常”

补全书中代码如下：

``` c++
// 04_else_01.cpp
#include <cmath>
#include <stdexcept>
#include <future>

double square_root(double x)
{
  if (x < 0) {
    throw std::out_of_range("x < 0");
  }

  return sqrt(x);
}

int main(int argc, char *argv[])
{
  // double y = square_root(-1);
  std::future<double> f = std::async(square_root, -1);
  double y = f.get();

  return 0;
}
```

``` shellsession
% ./04_else_01
terminate called after throwing an instance of 'std::out_of_range'
  what():  x < 0
[1]    17601 abort (core dumped)  ./04_else_01
```

函数作为`std::async`的一部分时，当在调用时抛出一个异常，那么这个异常就会存储到“期望”的结果数据中，之后“期望”的状态被置为“就绪”，之后调用`get()`会抛出这个存储的异常。（注意：标准级别没有指定重新抛出的这个异常是原始的异常对象，还是一个拷贝；不同的编译器和库将会在这方面做出不同的选择）。当你将函数打包入`std::packaged_task`任务包中后，在这个任务被调用时，同样的事情也会发生；当打包函数抛出一个异常，这个异常将被存储在“期望”的结果中，准备在调用get()再次抛出。

当然，通过函数的显式调用，`std::promise`也能提供同样的功能。当你希望存入的是一个异常而非一个数值时，你就需要调用`set_exception()`成员函数，而非`set_value()`。这通常是用在一个`catch`块中，并作为算法的一部分，为了捕获异常，使用异常填充“承诺”。

直到现在，所有例子都在用`std::future`。不过，`std::future`也有局限性，在很多线程在等待的时候，只有一个线程能获取等待结果。当多个线程需要等待相同的事件的结果，你就需要使用`std::shared_future`来替代`std::future`了。

#### 多个线程的等待

这个说得比较好：虽然`std::future`可以处理所有在线程间数据转移的必要同步，但是调用某一特殊`std::future`对象的成员函数，就会让这个线程的数据和其他**相同等待**线程的数据不同步。当多线程在没有额外同步的情况下，访问一个独立的`std::future`对象时，就会有数据竞争和未定义的行为。这是因为：`std::future`模型独享同步结果的所有权，并且通过调用`get()`函数，一次性的获取数据，这就让并发访问变的毫无意义——只有一个线程可以获取结果值，因为在第一次调用`get()`后，就没有值可以再获取了。

如果你的并行代码没有办法让多个线程等待同一个事件，先别太失落；`std::shared_future`可以来帮你解决。因为`std::future`是只移动的，所以其所有权可以在不同的实例中互相传递，但是只有一个实例可以获得特定的同步结果；而`std::shared_future`实例是可拷贝的，所以多个对象可以引用同一关联“期望”的结果。

在每一个`std::shared_future`的独立对象上成员函数调用返回的结果还是不同步的，所以为了在多个线程访问一个独立对象时，避免数据竞争，必须使用锁来对访问进行保护。

# <2019-03-29 周五> 《C++并发编程实战》读书笔记（九）

## 第4章 同步并发操作（二）

### 限定等待时间

略

### 使用同步操作简化代码

#### 使用“期望”的函数化编程

函数不会改变任何外部状态，这个函数是纯粹函数，那些非纯粹的函数是要对共享数据进行修改的。

一个“期望”对象可以在线程间互相传递，并允许其中一个计算结果依赖于另外一个的结果，而非对共享数据的显式访问。

快速排序（顺序实现版），补全书中代码如下：

``` c++
// 04_06.cpp
#include <iostream>
#include <list>
#include <algorithm>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();

  auto divide_point = std::partition(input.begin(),
                                     input.end(),
                                     [&](const T& t){return t < pivot;}
                                     );

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(),
                    input,
                    input.begin(),
                    divide_point
                    );

  auto new_lower(sequential_quick_sort(std::move(lower_part)));
  auto new_higher(sequential_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower);

  return result;
}

int main(int argc, char *argv[])
{
  std::list<int> list_int {3, 2, 1, 4, 5};
  std::list<int> result = sequential_quick_sort(list_int);

  for (std::list<int>::iterator it = result.begin();
       it != result.end();
       ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
```

``` shellsession
% ./04_06
1
2
3
4
5
```

虽然接口的形式是FP模式的，但当你使用FP模式时，你需要做大量的拷贝操作，所以在内部你会使用“普通”的命令模式。这里使用了一个引用`const T& pivot = *result.begin();`，为了避免过多的拷贝。同时lambda表达式也是使用引用的方式传递以避免对“中间”值的拷贝。

因为还是使用函数化模式，所以使用“期望”很容易将其转化为并行的版本，如下面的程序清单所示。其中的操作与前面相同，不同的是它们现在并行运行。

``` c++
// 04_07.cpp
#include <iostream>
#include <list>
#include <algorithm>
#include <future>

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();

  auto divide_point = std::partition(input.begin(),
                                     input.end(),
                                     [&](const T& t){return t < pivot;}
                                     );

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(),
                    input,
                    input.begin(),
                    divide_point
                    );

  std::future<std::list<T> > new_lower(std::async(
                                                  &parallel_quick_sort<T>,
                                                  std::move(lower_part)
                                                  )
                                       );

  auto new_higher(parallel_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());

  return result;
}

int main(int argc, char *argv[])
{
  std::list<int> list_int {3, 2, 1, 4, 5};
  std::list<int> result = parallel_quick_sort(list_int);

  for (std::list<int>::iterator it = result.begin();
       it != result.end();
       ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
```

``` shellsession
% ./04_07
1
2
3
4
5
```

上面的代码通过递归调用`parallel_quick_sort()`，你就可以利用可用的硬件并发了。`std::async()`会启动一个新线程，这样当你递归三次时，就会有八个线程在运行了。当任务过多时（已影响性能），**这些任务应该在使用`get()`函数获取的线程上运行，而不是在新线程上运行，这样就能避免任务向线程传递的开销**。值的注意的是，这完全符合`std::async`的实现，为每一个任务启动一个线程（甚至在任务超额时，在`std::launch::deferred`没有明确规定的情况下）；或为了同步执行所有任务（在`std::launch::async`有明确规定的情况下）。当你依赖运行库的自动缩放，建议你去查看一下你的实现文档，了解一下将会有怎么样的行为表现。

比起使用`std::async()`，你可以写一个`spawn_task()`函数对`std::packaged_task`和`std::thread`做简单的包装，如下的代码所示，你需要为函数结果创建一个`std::packaged_task`对象，可以从这个对象中获取“期望”，或在线程中执行它，返回“期望”。其本身并不提供太多的好处（并且事实上会造成大规模的超额任务），但是它会为转型成一个更复杂的实现铺平道路，将会实现向一个队列添加任务，而后使用线程池的方式来运行它们。使用`std::async`更适合于当你知道你在干什么，并且要完全控制在线程池中构建或执行过任务的线程。

``` c++
// 04_08.cpp
#include <iostream>
#include <list>
#include <algorithm>
#include <future>
#include <type_traits>

template<typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type> spawn_task(F&& f, A&& a)
{
  typedef typename std::result_of<F(A&&)>::type result_type;
  std::packaged_task<result_type(A&&)> task(std::move(f));
  std::future<result_type> res(task.get_future());
  std::thread t(std::move(task), std::move(a));
  t.detach();
  return res;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *result.begin();

  auto divide_point = std::partition(input.begin(),
                                     input.end(),
                                     [&](const T& t){return t < pivot;}
                                     );

  std::list<T> lower_part;
  lower_part.splice(lower_part.end(),
                    input,
                    input.begin(),
                    divide_point
                    );

  /*
  std::future<std::list<T> > new_lower(std::async(
                                                  &parallel_quick_sort<T>,
                                                  std::move(lower_part)
                                                  )
                                                  );*/

  auto new_lower(spawn_task(&parallel_quick_sort<T>, std::move(lower_part)));

  auto new_higher(parallel_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());

  return result;
}

int main(int argc, char *argv[])
{
  std::list<int> list_int {3, 2, 1, 4, 5};
  std::list<int> result = parallel_quick_sort(list_int);

  for (std::list<int>::iterator it = result.begin();
       it != result.end();
       ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
```

``` shellsession
% ./04_08
1
2
3
4
5
```

这段代码中需要提到的是原书中的代码会产生编译错误：

``` shellsession
04_08.cpp:8:41: error: type/value mismatch at argument 1 in template parameter list for ‘template<class _Res> class std::future’
 std::future<std::result_of<F(A&&)>::type> spawn_task(F&& f, A&& a)
                                         ^
```

如何修改？需要在`std::result_of`前加上`typename`关键字，参考：[Using C++ template parameter as argument to another template? [duplicate]](https://stackoverflow.com/questions/22355398/using-c-template-parameter-as-argument-to-another-template)，因此需要正确的写法如下：

``` c++
template<typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type> spawn_task(F&& f, A&& a)
{
  typedef typename std::result_of<F(A&&)>::type result_type;
  std::packaged_task<result_type(A&&)> task(std::move(f));
  std::future<result_type> res(task.get_future());
  std::thread t(std::move(task), std::move(a));
  t.detach();
  return res;
}
```

同时需要注意的是`spawn_task`是如何调用的：

``` c++
auto new_lower(spawn_task(&parallel_quick_sort<T>, std::move(lower_part)));
```

#### 使用消息传递的同步操作

CSP（Communicating Sequential Processer）的概念十分简单：当没有共享数据，每个线程就可以进行独立思考，其行为纯粹基于其所接收到的信息。

### 总结

同步操作对于使用并发编写一款多线程应用来说，是很重要的一部分：如果没有同步，线程基本上就是独立的，也可写成单独的应用，因其任务之间的相关性，它们可作为一个群体直接执行。本章，我们讨论了各式各样的同步操作，从基本的条件变量，到“期望”、“承诺”，再到打包任务。我们也讨论了替代同步的解决方案：函数化模式编程，完全独立执行的函数，不会受到外部环境的影响；还有，消息传递模式，以消息子系统为中介，向线程异步的发送消息。

# <2019-04-09 周二> 《C++并发编程实战》读书笔记（十）

## 第5章 C++内存模型和原子类型操作（一）

### 内存模型基础

#### 对象和内存位置

分解一个`struct`，展示不同对象的内存位置，补全书中代码如下：

``` c++
// 05_else_01.cpp
#include <iostream>
#include <string>

struct my_data
{
  int i;             // 4
  double d;          // 16
  unsigned bf1 : 10; // 24
  int bf2 : 25;      // 24
  int /*bf3*/ : 0;   // 24
  int bf4 : 9;       // 32
  int i2;            // 32
  char c1, c2;       // 40
  std::string s;     // 72
};

int main(int argc, char *argv[])
{
  std::cout << "sizeof(my_data): " << sizeof(my_data) << std::endl;

  return 0;
}
```

注释的意思是从上到下逐渐取消成员注释，取`sizeof()`得到的结构体内存大小。（注：`bf3`是一个错误展示，在C++和C中规定，宽度为0的一个未命名位域强制下一位域对齐到其下一`type`边界，其中`type`是该成员的类型。这里使用命名变量为0的位域，可能只是想展示其与bf4是如何分离的。）

关于宽度为0的位域，借用“[C/C++位域结构深入解析](https://jocent.me/2017/07/24/bit-field-detail.html)”中的代码：

``` c++
struct BitField_1
{
  unsigned a : 4; // 在第一个unsigned int中存放，占四位
  unsigned   : 0; // 未命名位域
  unsigned b : 4; // 在第二个unsigned int中存放，占四位
  unsigned c : 4; // 在第二个unsigned int中存放，占四位
};
```

#### 对象、内存位置和并发

如果不去规定两个不同线程对同一内存地址访问的顺序，那么访问就不是原子的。

当程序中的对同一内存地址中的数据访问存在竞争，你可以使用原子操作来避免未定义行为。当然，这不会影响竞争的产生**原子操作并没有指定访问顺序**但原子操作把程序拉回了定义行为的区域内。

#### 修改顺序

每一个在C++程序中的对象，都有（由程序中的所有线程对象）确定好的修改顺序（modification order），在初始化开始阶段确定。在大多数情况下，这个顺序不同于执行中的顺序，但是在给定的执行程序中，所有线程都需要遵守这顺序。如果对象不是一个原子类型，你必要确保有足够的同步操作，来确定每个线程都遵守了变量的修改顺序。

### C++中的原子操作和原子类型

原子操作是一类不可分割的操作，当这样操作在任意线程中进行一半的时候，你是不能查看的；它的状态要不就是完成，要不就是未完成。

#### 标准原子类型

标准原子类型（atomic types）可以在头文件中找到。所有在这种类型上的操作都是原子的，虽然可以使用互斥量去达到原子操作的效果，但只有在这些类型上的操作是原子的（语言明确定义）。实际上，标准原子类型都很相似：它们（大多数）都有一个`is_lock_free()`成员函数，这个函数允许用户决定是否直接对一个给定类型使用原子指令（`x.is_lock_free()`返回`true`），或对编译器和运行库使用内部锁（`x.is_lock_free()`返回`false`）。

看了那么多的类型，我只能感叹C++真的是太复杂了。

通常，标准原子类型是不能拷贝和赋值，他们没有拷贝构造函数和拷贝赋值操作。但是，因为可以隐式转化成对应的内置类型，所以这些类型依旧支持赋值，可以使用`load()`和`store()`成员函数，`exchange()`、`compare_exchange_weak()`和`compare_exchange_strong()`。

原书内容不易消化，再理解请见原书P114。

#### `std::atomic_flag`的相关操作

`std::atomic_flag`是最简单的标准原子类型，它表示了一个布尔标志。这个类型的对象可以在两个状态间切换：设置和清除。

你不能拷贝构造另一个`std::atomic_flag`对象；并且，你不能将一个对象赋予另一个`std::atomic_flag`对象。这并不是`std::atomic_flag`特有的，而是所有原子类型共有的。一个原子类型的所有操作都是原子的，因赋值和拷贝调用了两个对象，这就破坏了操作的原子性。在这样的情况下，拷贝构造和拷贝赋值都会将第一个对象的值进行读取，然后再写入另外一个。对于两个独立的对象，这里就有两个独立的操作了，合并这两个操作必定是不原子的。因此，操作就不被允许。

使用`std::atomic_flag`实现自旋互斥锁，补全书中代码如下：

``` c++
// 05_01.cpp
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

class spinlock_mutex
{
  std::atomic_flag flag;

public:
  spinlock_mutex() :
    flag(ATOMIC_FLAG_INIT)
  {}

  void lock()
  {
    while (flag.test_and_set(std::memory_order_acquire));
  }

  void unlock()
  {
    flag.clear(std::memory_order_release);
  }
};

void f(int n)
{
  static spinlock_mutex sm;

  for (int cnt = 0; cnt < 100; ++cnt) {
    sm.lock();
    std::cout << "output from thread " << n << std::endl;
    sm.unlock();
  }
}

void test_spinlock_mutex()
{
  std::vector<std::thread> v;

  for (int n = 0; n < 10; ++n) {
    v.emplace_back(f, n);
  }

  for (auto& t : v) {
    t.join();
  }
}

int main(int argc, char *argv[])
{
  test_spinlock_mutex();

  return 0;
}
```

这里使用了`static spinlock_mutex sm;`，可以看到输出效果：每个线程都等待其它线程运行完后再执行，而不是同时执行。

这样的互斥量是最最基本的，但是它已经足够`std::lock_guard<>`使用了（详见第3章）。其本质就是在`lock()`中等待，所以这里几乎不可能有竞争的存在，并且可以确保互斥。

由于`std::atomic_flag`局限性太强，因为它没有非修改查询操作，它甚至不能像普通的布尔标志那样使用。所以，你最好使用`std::atomic<bool>`。

#### `std::atomic`的相关操作

``` c++
// 05_else_02.cpp
#include <iostream>
#include <atomic>

void test_std_atomic_bool()
{
  std::atomic<bool> b;

  bool x = b.load(std::memory_order_acquire);
  std::cout << "x: " << std::boolalpha << x
            << ", b: " << b << std::endl;

  b.store(true);
  std::cout << "x: " << std::boolalpha << x
            << ", b: " << b << std::endl;

  x = b.exchange(false, std::memory_order_acq_rel);
  std::cout << "x: " << std::boolalpha << x
            << ", b: " << b << std::endl;
}

int main(int argc, char *argv[])
{
  test_std_atomic_bool();

  return 0;
}
```

``` shellsession
% ./05_else_02
x: false, b: false
x: false, b: true
x: true, b: false
```

`std::atomic<bool>`提供的`exchange()`，不仅仅是一个“读-改-写”的操作；它还介绍了一种新的存储方式：当当前值与预期值一致时，存储新值的操作。这是一种新型操作，叫做“比较/交换”，它的形式表现为`compare_exchange_weak()`和`compare_exchange_strong()`成员函数。

“比较/交换”操作是原子类型编程的基石；它比较原子变量的当前值和提供的预期值，当两值相等时，存储预期值。当两值不等，预期值就会被更新为原子变量中的值。“比较/交换”函数值是一个`bool`变量，（注意这里是对于上面的代码而言，尼玛）当返回`true`时执行存储操作，当`false`则更新期望值。

对于`compare_exchange_weak()`函数，很难理解为什么要这么做，而且书中P118页提到的“伪失败”（spurious failure）是可能发生在缺少独立“比较-交换”指令的机器上。这个感觉非常虚幻，我要怎么去理解它呢？我看了“[C++11 CAS无锁函数compare_exchange_weak的使用](https://www.cnblogs.com/muhe221/articles/5089918.html)”的前一段儿，感觉好理解，所以将文章链接贴在这里。

补全书中代码如下：

``` c++
// 05_else_03.cpp
#include <iostream>
#include <atomic>

void test_compare_exchange_weak()
{
  bool expected = false;
  std::atomic<bool> b;
  bool x = b.compare_exchange_weak(expected, true);
  std::cout << "x: " << std::boolalpha << x << ", b: " << b
            << ", expected: " << expected << std::endl;
}

int main(int argc, char *argv[])
{
  test_compare_exchange_weak();

  return 0;
}
```

``` shellsession
% ./05_else_03
x: true, b: true, expected: false
```

因为**`compare_exchange_weak()`可以“伪失败”**，所以**这里通常使用一个循环**，补全书中代码如下：

``` c++
// 05_else_04.cpp
#include <iostream>
#include <atomic>

void test_compare_exchange_weak()
{
  bool expected = false;
  std::atomic<bool> b;
  // b.compare_exchange_weak(expected, true);
  while (!b.compare_exchange_weak(expected, true) && !expected);
  std::cout << std::boolalpha << "b: " << b
            << ", expected: " << expected << std::endl;
}

int main(int argc, char *argv[])
{
  test_compare_exchange_weak();

  return 0;
}
```

``` shellsession
% ./05_else_04
b: true, expected: false
```

在这个例子中，循环中`expected`的值始终是`false`，表示`compare_exchange_weak()`会莫名的失败。

另一方面，如果实际值与期望值不符，`compare_exchange_strong()`就能保证值返回`false`。这就能消除对循环的需要，就可以知道是否成功的改变了一个变量，或已让另一个线程完成。

接下来的这段儿比较难理解，见原书P118页。

`std::atomic<bool>`和`std::atomic_flag`的不同之处在于，`std::atomic<bool>`不是无锁的；为了保证操作的原子性，其实现中需要一个内置的互斥量。当处于特殊情况时，你可以使用`is_lock_free()`成员函数，去检查`std::atomic<bool>`上的操作是否无锁。这是另一个，除了`std::atomic_flag`之外，所有原子类型都拥有的特征。

#### `std::atomic<T*>`指针运算

补全书中代码如下：

``` c++
// 05_else_05.cpp
#include <iostream>
#include <atomic>
#include <cassert>

void test_fetch_add0()
{
  class Foo {};
  Foo some_array[5];
  std::atomic<Foo *> p(some_array);

  Foo *x = p.fetch_add(2);
  assert(x == some_array);
  assert(p.load() == &some_array[2]);

  x = (p -= 1);
  assert(x == &some_array[1]);
  assert(p.load() == &some_array[1]);
}

void test_fetch_add1()
{
  int some_array[5] = {0, 1, 2, 3, 4};
  std::atomic<int *> p(some_array);

  int *x = p.fetch_add(2);
  std::cout << "*x: " << *x << std::endl;
  std::cout << "*p: " << *p << std::endl;
  std::cout << "*(p.load()): " << *(p.load()) << std::endl;
  assert(*x == 0);
  assert(*p == 2);

  x = (p -= 1);
  std::cout << "*x: " << *x << std::endl;
  std::cout << "*p: " << *p << std::endl;
  std::cout << "*(p.load()): " << *(p.load()) << std::endl;
  assert(*x == 1);
  assert(*p == 1);
}

int main(int argc, char *argv[])
{
  test_fetch_add0();
  test_fetch_add1();

  return 0;
}
```

``` shellsession
% ./05_else_05
*x: 0
*p: 2
*(p.load()): 2
*x: 1
*p: 1
*(p.load()): 1
```

好好看看上面的代码进行理解，**`fetch_add()`返回的是原始值**，即数组的首地址。注意代码`p.fetch_add(2);`中`p`的值发生了变化。

#### 标准的原子整形的相关操作

略

#### `std::atomic<>`主要类的模板

主模板的存在，在除了标准原子类型之外，允许用户使用自定义类型创建一个原子变量。不是任何自定义类型都可以使用`std::atomic<>`的：需要满足一定的标准才行。为了使用`std::atomic<UDT>`（UDT是用户定义类型），这个类型必须有拷贝赋值运算符。这就意味着这个类型不能有任何虚函数或虚基类，以及必须使用编译器创建的拷贝赋值操作。不仅仅是这些，自定义类型中所有的基类和非静态数据成员也都需要支持拷贝赋值操作。这（基本上）就允许编译器使用`memcpy()`，或赋值操作的等价操作，因为它们的实现中没有用户代码。

最后，这个类型必须是“位可比的”（bitwise equality comparable）。这与对赋值的要求差不多；你不仅需要确定，一个UDT类型对象可以使用`memcpy()`进行拷贝，还要确定其对象可以使用`memcmp()`对位进行比较。之所以要求这么多，是为了保证“比较/交换”操作能正常的工作。

以上严格的限制都是依据第3章中的一个建议：不要将锁定区域内的数据，以引用或指针的形式，作为参数传递给用户提供的函数。

以下内容略，见原书。（不能理解其中的深意）

#### 原子操作的释放函数

略

# <2019-04-10 周三> 《C++并发编程实战》读书笔记（十一）

## 关于对`std::memory_order`的理解（一）

### Happens-before关系

关于happens-before关系这篇文章讲得我能看懂：“[C++ Memory Order 与 Atomic 学习小记](https://zhuanlan.zhihu.com/p/31386431)”。

A、B是两个在多核CPU上执行的操作。如果A happens-before B，那么A所产生的内存变化会在B操作执行之前被看到（visible）。不管我们使用什么编程语言，在同一个线程下的顺序语句总是遵循happens-before原则的。

但程序语义上的happens-before不能代表操作是真的happened-before了。这段话如果不理解可以看上面的链接，简短来说编译器可能会指令重排。

### Synchronizes-with关系

仍然是这篇文章：“[C++ Memory Order 与 Atomic 学习小记](https://zhuanlan.zhihu.com/p/31386431)”，有如下测试代码：

``` c++
// 05_else_06.cpp
#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>

int data;
std::atomic<bool> flag(false);

void producer()
{
  data = 42;            // 1
  flag.store(true);     // 2
}

void consume()
{
  while (!flag.load()); // 3
  assert(data == 42);   // 4
}

int main(int argc, char *argv[])
{
  std::thread ta(producer);
  std::thread tb(consume);
  ta.join();
  tb.join();

  return 0;
}
```

虽然我们使用原子量`flag`作为“同步信号”，而且同一个线程中happens-before原则也一定会被遵循，但我们并不能保证注释4执行时注释1的修改一定会被线程看到。这是由于现代处理器对于程序可能会采取指令重排来提高运行效率。所以，企图在多线程环境中通过某原子量来做非原子量的Synchronization并不是可靠的（当没有Memory Order的约束）。

当然，上面的代码在你的机器上可能也不会出现，因为C++默认使用`memory_order_seq_cst`顺序约束。而且<u>x86架构中也做不到松弛`memory_order_relaxed`内存模型</u>。

## 第5章 C++内存模型和原子类型操作（二）

### 同步操作和强制排序（一）

翻译的确实有点烂，还不如直接看英文原版，比中文版好懂。在这里我找到了英文版：“[www.bogotobogo.com](https://www.bogotobogo.com/cplusplus/files/)”。

从不同线程读写变量，补全书中代码如下：

``` c++
// 05_02.cpp
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
```

现在来看看“happens-before”和“synchronizes-with”。

> The write of the data 3 happens-before the write to the `data_ready` flag 4, and the read of the flag 1 happens-before the read of the data 2. When the value read from `data_ready` 1 is true, the write synchronizes-with that read, creating a happens-before relationship. Because happens-before is transitive, the write to the data 3 happens-before the write to the flag 4, which happens-before the read of the `true` value from the flag 1, which happens-before the read of the data 2, and you have an enforced ordering: the write of the data happens-before the read of the data and everything is OK.

看了上面的内容再结合[关于对`std::memory_order`的理解（一）](#关于对stdmemoryorder的理解一)就可以更好的理解“happens-before”和“synchronizes-with”了。

#### 同步发生（The synchronizes-with relationship）

同步关系只在原子类型之间产生。这种关系只能来自于对原子类型的操作。

#### 先行发生（The happens-before relationship）

> The happens-before relationship is the basic building block of operation ordering in a program; it specifies which operations see the effects of which other operations. For a single thread, it’s largely straightforward: if one operation is sequenced before another, then it also happens-before it. This means that if one operation (A) occurs in a statement prior to another (B) in the source code, then A happens-before B. You saw that in "05_02.cpp": the write to `data` 3 happens-before the write to `data_ready` 4. If the operations occur in the same statement, in general there’s no happens-before relationship between them, because they’re unordered. This is just another way of saying that the ordering is unspecified. You know that the program in the following listing will output “1,2” or “2,1”, but it’s unspecified which, because the order of the two calls to `get_num()`is unspecified.

``` c++
// 05_03.cpp
#include <iostream>

void foo(int a, int b)
{
  std::cout << a << ", " << b << std::endl;
}

int get_num()
{
  static int i = 0;
  return ++i;
}

int main(int argc, char *argv[])
{
  foo(get_num(), get_num());

  return 0;
}
```

``` shellsession
% ./05_03
2, 1
```

为什么这里我的输出总是“2, 1”呢？没看到“1, 2”的情况？

“Inter-thread happens-before”关系是可以传递的，同时“Inter-thread happens-before also combines with the sequenced-before relation”。

#### 原子操作的内存顺序（Memory ordering for atomic operations）（一）

> Although there are six ordering options, they represent three models: sequentially consistent ordering (`memory_order_seq_cst`), acquire-release ordering (`memory_order_consume`, `memory_order_acquire`, `memory_order_release`, and `memory_order_acq_rel`), and relaxed ordering (`memory_order_relaxed`).

为了选择要使用哪个排序模型，或者为了理解使用不同模型的代码中的排序关系，了解这些选择如何影响程序行为是很重要的。因此，让我们看看每种操作排序和同步选择的结果。

##### SEQUENTIALLY CONSISTENT ORDERING

<span id="05_04_cpp"></span>

``` c++
// 05_04.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
  x.store(true, std::memory_order_seq_cst); // 1
}

void write_y()
{
  y.store(true, std::memory_order_seq_cst); // 2
}

void read_x_then_y()
{
  while (!x.load(std::memory_order_seq_cst));
  if (y.load(std::memory_order_seq_cst)) // 3
    ++z;
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_seq_cst));
  if (x.load(std::memory_order_seq_cst)) // 4
    ++z;
}

int main(int argc, char *argv[])
{
  x = false;
  y = false;
  z = 0;

  std::thread a(write_x);
  std::thread b(write_y);
  std::thread c(read_x_then_y);
  std::thread d(read_y_then_x);
  a.join();
  b.join();
  c.join();
  d.join();

  assert(z.load() != 0); // 5
  std::cout << "z: " << z << std::endl;

  return 0;
}
```

``` shellsession
% ./05_04
z: 2
```

``` shellsession
% ./05_04
z: 1
```

注释5处永远都会成功，下面的说明讲得很好：

> The assert 5 can never fire, because either the store to `x` 1 or the store to `y` 2 must happen first, even though it’s not specified which. If the load of `y` in `read_x_then_y` 3 returns false, the store to `x` must occur before the store to `y`, in which case the load of `x` in `read_y_then_x` 4 must return true, because the `while` loop ensures that the `y` is true at this point. Because the semantics of `memory_order_seq_cst` require a single total ordering over all operations tagged `memory_order_seq_cst`, there’s an implied ordering relationship between a load of `y` that returns false 3 and the store to `y` 1. For there to be a single total order, if one thread sees `x==true` and then subsequently sees `y==false`, this implies that the store to `x` occurs before the store to `y` in this total order.

> Of course, because everything is symmetrical, it could also happen the other way around, with the load of `x` 4 returning false, forcing the load of `y` 3 to return true. In both cases, `z` is equal to 1. Both loads can return true, leading to `z` being 2, butunder no circumstances can `z` be zero.

关于书中的插图理解可以见原书P126，不难理解。

# <2019-04-11 周四> 《C++并发编程实战》读书笔记（十二）

## 第5章 C++内存模型和原子类型操作（三）

### 同步操作和强制排序（二）

#### 原子操作的内存顺序（Memory ordering for atomic operations）（二）

##### NON-SEQUENTIALLY CONSISTENT MEMORY ORDERINGS

略，见原文。

##### RELAXED ORDERING

<span id="05_05_cpp"></span>

``` c++
// 05_05.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x, y;
std::atomic<int> z;

void wirte_x_then_y()
{
  x.store(true, std::memory_order_relaxed); // 1
  y.store(true, std::memory_order_relaxed); // 2
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_relaxed)); // 3
  if (x.load(std::memory_order_relaxed)) // 4
    ++z;
}

int main(int argc, char *argv[])
{
  x = false;
  y = false;
  z = 0;

  std::thread a(wirte_x_then_y);
  std::thread b(read_y_then_x);
  a.join();
  b.join();

  std::cout << "z: " << z.load() << std::endl;
  assert(z.load() != 0); // 5

  return 0;
}
```

``` shellsession
% ./05_05
z: 1
```

这里我没有能重现出注释5处的断言失败的情况，即使我加了一万次的循环来执行它。这个添加循环的方法应该也不是正确的测试方法。

> This time the assert 5 can fire, because the load of `x` 4 can read false, even though the load of `y` 3 reads true and the store of `x` 1 happens-before the store of `y` 2. `x` and `y` are different variables, so there are no ordering guarantees relating to the visibility of values arising from operations on each.

上面引用原文的解释，这里不打算想如何重现它，因为注释1和注释2是不同的两个变量，所以对于每个操作产生的值的可见性，没有顺序保证。

多线程中的松散操作，如下代码所示：

``` c++
// 05_06.cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x(0), y(0), z(0);
std::atomic<bool> go(false);

const unsigned loop_count = 9;

struct read_values
{
  int x, y, z;
};

read_values values1[loop_count];
read_values values2[loop_count];
read_values values3[loop_count];
read_values values4[loop_count];
read_values values5[loop_count];

void increment(std::atomic<int> *var_to_inc, read_values *values)
{
  while (!go) {
    std::this_thread::yield();
  }

  for (unsigned i = 0; i < loop_count; ++i) {
    values[i].x = x.load(std::memory_order_relaxed);
    values[i].y = y.load(std::memory_order_relaxed);
    values[i].z = z.load(std::memory_order_relaxed);
    var_to_inc->store(i + 1, std::memory_order_relaxed);
    std::this_thread::yield();
  }
}

void read_vals(read_values *values)
{
  while (!go) {
    std::this_thread::yield();
  }

  for (unsigned i = 0; i < loop_count; ++i) {
    values[i].x = x.load(std::memory_order_relaxed);
    values[i].y = y.load(std::memory_order_relaxed);
    values[i].z = z.load(std::memory_order_relaxed);
    std::this_thread::yield();
  }
}

void print(read_values *v)
{
  for (unsigned i = 0; i < loop_count; ++i) {
    if (i) {
      std::cout << ", ";
    }

    std::cout << "(" << v[i].x << ", " << v[i].y << ", " << v[i].z << ")";
  }

  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  std::thread t1(increment, &x, values1);
  std::thread t2(increment, &y, values2);
  std::thread t3(increment, &z, values3);
  std::thread t4(read_vals, values4);
  std::thread t5(read_vals, values5);

  go = true;

  t5.join();
  t4.join();
  t3.join();
  t2.join();
  t1.join();

  print(values1);
  print(values2);
  print(values3);
  print(values4);
  print(values5);

  return 0;
}
```

输出是可变的，下面的程序可能的输出：

``` shellsession
% ./05_06
(0, 9, 9), (1, 9, 9), (2, 9, 9), (3, 9, 9), (4, 9, 9), (5, 9, 9), (6, 9, 9), (7, 9, 9), (8, 9, 9)
(0, 0, 0), (0, 1, 1), (0, 2, 1), (0, 3, 1), (0, 4, 1), (0, 5, 1), (0, 6, 1), (0, 7, 1), (0, 8, 1)
(0, 1, 0), (0, 9, 1), (0, 9, 2), (0, 9, 3), (0, 9, 4), (0, 9, 5), (0, 9, 6), (0, 9, 7), (0, 9, 8)
(0, 1, 0), (0, 9, 1), (0, 9, 2), (0, 9, 3), (0, 9, 4), (0, 9, 5), (0, 9, 6), (0, 9, 7), (0, 9, 8)
(0, 1, 0), (0, 1, 1), (0, 2, 1), (0, 3, 1), (0, 4, 1), (0, 5, 1), (0, 6, 1), (0, 7, 1), (0, 8, 1)
```

上面的代码很简单，但是我对输出很费解，引用原文：

> The first set of values shows `x` increasing by one with each triplet, the second set has `y` increasing by one, and the third has `z` increasing by one.

> The `x` elements of each triplet only increase within a given set, as do the `y` and `z` elements, but the increments are uneven, and the relative orderings vary between all threads.

> Thread 3 doesn’t see any of the updates to `x` or `y`; it sees only the updates it makes to `z`. This doesn’t stop the other threads from seeing the updates to `z` mixed in with the updates to `x` and `y` though.

##### UNDERSTANDING RELAXED ORDERING

原文举的例子很有意思，见英文版P132，此处略过。

##### ACQUIRE-RELEASE ORDERING

> Acquire-release ordering is a step up from relaxed ordering; there’s still no total order of operations, but it does introduce some synchronization. Under this ordering model, atomic loads are acquire operations (`memory_order_acquire`), atomic stores are release operations (`memory_order_release`), and atomic read-modify-write operations (such as `fetch_add()` or `exchange()`) are either acquire, release, or both (`memory_order_acq_rel`). Synchronization is pairwise, between the thread that does the release and the thread that does the acquire. A release operation synchronizes-with an acquire operation that reads the value written. This means that different threads can still see different orderings, but these orderings are restricted.

对于上面原文中的内容，我提取出我想要的重点：

| atomic operation         | operation        | std::memory_order    |
| :---                     | :---             | :---                 |
| atomic loads             | acquire          | memory_order_acquire |
| atomic stores            | release          | memory_order_release |
| atomic read-modify-write | acquire, release | memory_order_acq_rel |

下面代码是对“[05_04.cpp](#05_04_cpp)”的一次重写，使用“acquire-release semantics”而不是（rather than）“sequentially consistent”，代码如下：

``` c++
// 05_07.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
  x.store(true, std::memory_order_release);
}

void write_y()
{
  y.store(true, std::memory_order_release);
}

void read_x_then_y()
{
  while (!x.load(std::memory_order_acquire));
  if (y.load(std::memory_order_acquire)) // 1
    ++z;
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_acquire));
  if (x.load(std::memory_order_acquire)) // 2
    ++z;
}

int main(int argc, char *argv[])
{
  x = false;
  y = false;
  z = 0;

  std::thread a(write_x);
  std::thread b(write_y);
  std::thread c(read_x_then_y);
  std::thread d(read_y_then_x);
  a.join();
  b.join();
  c.join();
  d.join();

  std::cout << "z: " << z.load() << std::endl;
  assert(z.load() != 0); // 3

  return 0;
}
```

``` shellsession
% ./05_07
z: 1
```

``` shellsession
% ./05_07
z: 2
```

> In this case the assert 3 can fire (just like in the relaxed-ordering case), because it’s possible for both the load of `x` 2 and the load of `y` 1 to read false. `x` and `y` are written by different threads, so the ordering from the release to the acquire in each case has no effect on the operations in the other threads.

这里断言能触发的原因是因为它们都位于不同的线程中，因为不存在像前面描述的那样强制排序的“happens-before”关系。

为了看到“acquire-release”的好处，需要考虑将两个存储放到同一个线程中，就像“[05_05.cpp](#05_05_cpp)”代码中的那样，见下面的代码：

``` c++
// 05_08.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y()
{
  x.store(true, std::memory_order_relaxed); // 1
  y.store(true, std::memory_order_release); // 2
}

void read_y_then_x()
{
  while (!y.load(std::memory_order_acquire)); // 3
  if (x.load(std::memory_order_relaxed)) // 4
    ++z;
}

int main(int argc, char *argv[])
{
  x = false;
  y = false;
  z = 0;

  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);
  a.join();
  b.join();

  std::cout << "z: " << z.load() << std::endl;
  assert(z.load() != 0); // 5

  return 0;
}
```

``` shellsession
% ./05_08
z: 1
```

上面代码的断言永远不会触发，因为：

> Eventually, the load from `y` 3 will see `true` as written by the store 2. Because the store uses `memory_order_release` and the load uses `memory_order_acquire`, the store synchronizes-with the load. The store to `x` 1 happens-before the store to `y` 2, because they’re in the same thread. Because the store to `y` synchronizes-with the load from `y`, the store to `x` also happens-before the load from `y` and by extension happensbefore the load from `x` 4. Thus the load from `x` must read true, and the assert 5 can’t fire.

原文中继续使用隔间中的人来举例，讲得不错，见原书P136。

# <2019-04-13 周六> 《C++并发编程实战》读书笔记（十三）

## 第5章 C++内存模型和原子类型操作（四）

### 同步操作和强制排序（三）

#### 原子操作的内存顺序（Memory ordering for atomic operations）（三）

##### TRANSITIVE SYNCHRONIZATION WITH ACQUIRE-RELEASE ORDERING

这里现在有点好理解了，补全书中代码如下：

``` c++
// 05_09.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

struct data
{
  int val;
};

std::atomic<int> data[5];
std::atomic<bool> sync1(false), sync2(false);

void thread_1()
{
  data[0].store(42, std::memory_order_relaxed);
  data[1].store(97, std::memory_order_relaxed);
  data[2].store(17, std::memory_order_relaxed);
  data[3].store(-141, std::memory_order_relaxed);
  data[4].store(2003, std::memory_order_relaxed);
  sync1.store(true, std::memory_order_release); // 1
}

void thread_2()
{
  while (!sync1.load(std::memory_order_acquire)); // 2
  sync2.store(true, std::memory_order_release); // 3
}

void thread_3()
{
  while (!sync2.load(std::memory_order_acquire)); // 4

  std::cout << "data[0]: " << data[0].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[1]: " << data[1].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[2]: " << data[2].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[3]: " << data[3].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[4]: " << data[4].load(std::memory_order_relaxed)
            << std::endl;

  assert(data[0].load(std::memory_order_relaxed) == 42);
  assert(data[1].load(std::memory_order_relaxed) == 97);
  assert(data[2].load(std::memory_order_relaxed) == 17);
  assert(data[3].load(std::memory_order_relaxed) == -141);
  assert(data[4].load(std::memory_order_relaxed) == 2003);
}

int main(int argc, char *argv[])
{
  std::thread t1(thread_1);
  std::thread t2(thread_2);
  std::thread t3(thread_3);
  t1.join();
  t2.join();
  t3.join();

  return 0;
}
```

``` shellsession
% ./05_09
data[0]: 42
data[1]: 97
data[2]: 17
data[3]: -141
data[4]: 2003
```

`thread_3`中的断言不会触发，见原谅的解释：

> Even though `thread_2` only touches the variables `sync1` 2 and `sync2` 3, this is enough for synchronization between `thread_1` and `thread_3` to ensure that the `asserts` don’t fire. First off, the stores to `data` from `thread_1` happens-before the store to `sync1` 1, because they’re sequenced-before it in the same thread. Because the load from `sync1` 1 is in a while loop, it will eventually see the value stored from `thread_1` and thus form the second half of the release-acquire pair. Therefore, the store to `sync1` happens-before the final load from `sync1` in the `while` loop. This load is sequenced-before (and thus happens-before) the store to `sync2` 3, which forms a release-acquire pair with the final load from the `while` loop in `thread_3` 4. The store to `sync2` 3 thus happens-before the load 4, which happens-before the loads from `data`. Because of the transitive nature of happens-before, you can chain it all together: the stores to `data` happen-before the store to `sync1` 1, which happens-before the load from `sync1` 1, which happens-before the store to `sync2` 3, which happensbefore the load from `sync2` 4, which happens-before the loads from `data`. Thus the stores to `data` in `thread_1` happen-before the loads from `data` in `thread_3`, and the asserts can’t fire.

上面的代码使用了两个变量`sync1`和`sync2`，现在来尝试一下使用一个变量，这样的话就需要用到`std::memory_order_acq_rel`（read-modify-write）和`compare_exchange_strong()`了，补全书中代码如下：

``` c++
// 05_else_07.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

struct data
{
  int val;
};

std::atomic<int> data[5];
std::atomic<int> sync(0);

void thread_1()
{
  data[0].store(42, std::memory_order_relaxed);
  data[1].store(97, std::memory_order_relaxed);
  data[2].store(17, std::memory_order_relaxed);
  data[3].store(-141, std::memory_order_relaxed);
  data[4].store(2003, std::memory_order_relaxed);
  sync.store(1, std::memory_order_release);
}

void thread_2()
{
  int expected = 1;
  while (!sync.compare_exchange_strong(expected,
                                       2,
                                       std::memory_order_acq_rel
                                       )) {
    expected = 1;
  }
}

void thread_3()
{
  while (sync.load(std::memory_order_acquire) < 2);

  std::cout << "data[0]: " << data[0].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[1]: " << data[1].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[2]: " << data[2].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[3]: " << data[3].load(std::memory_order_relaxed)
            << std::endl;
  std::cout << "data[4]: " << data[4].load(std::memory_order_relaxed)
            << std::endl;

  assert(data[0].load(std::memory_order_relaxed) == 42);
  assert(data[1].load(std::memory_order_relaxed) == 97);
  assert(data[2].load(std::memory_order_relaxed) == 17);
  assert(data[3].load(std::memory_order_relaxed) == -141);
  assert(data[4].load(std::memory_order_relaxed) == 2003);
}

int main(int argc, char *argv[])
{
  std::thread t1(thread_1);
  std::thread t2(thread_2);
  std::thread t3(thread_3);
  t1.join();
  t2.join();
  t3.join();

  return 0;
}
```

``` shellsession
% ./05_else_07
data[0]: 42
data[1]: 97
data[2]: 17
data[3]: -141
data[4]: 2003
```

如果你使用“read-modify-write”操作，选择您想要的语义是很重要的。比如说：

> A `fetch_sub` operation with `memory_order_acquire` semantics doesn’t synchronize-with anything, even though it stores a value, because it isn’t a release operation. Likewise, a store can’t synchronize-with a `fetch_or` with `memory_order_release` semantics, because the read part of the `fetch_or` isn’t an acquire operation.

##### DATA DEPENDENCY WITH ACQUIRE-RELEASE ORDERING AND MEMORY_ORDER_CONSUME

这里讲得关于`memory_order_consume`好像更多的是用在有指针出现的需要同步的地方，如原文所说：

> One important use for this kind of memory ordering is where the atomic operation loads a pointer to some data. By using `memory_order_consume` on the load and `memory_order_release` on the prior store, you ensure that the pointed-to data is correctly synchronized, without imposing any synchronization requirements on any other nondependent data. The following listing shows an example of this scenario.

``` c++
// 05_10.cpp
#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <cassert>
#include <chrono>

struct X
{
  int i;
  std::string s;
};

std::atomic<X *> p;
std::atomic<int> a;

void create_x()
{
  X *x = new X;
  x->i = 42;
  x->s = "hello";
  a.store(99, std::memory_order_relaxed); // 1
  p.store(x, std::memory_order_release); // 2
}

void use_x()
{
  using namespace std::chrono_literals;

  X *x;
  while (!(x = p.load(std::memory_order_consume))) // 3
    std::this_thread::sleep_for(1s);

  std::cout << "x->i: " << x->i << std::endl;
  std::cout << "x->s: " << x->s << std::endl;
  std::cout << "a.load(): " << a.load() << std::endl;

  assert(x->i == 42); // 4
  assert(x->s == "hello"); // 5
  assert(a.load(std::memory_order_relaxed) == 99); // 6
}

int main(int argc, char *argv[])
{
  std::thread t1(create_x);
  std::thread t2(use_x);
  t1.join();
  t2.join();

  return 0;
}
```

``` shellsession
% ./05_10
x->i: 42
x->s: hello
a.load(): 99
```

这里的注释6处的断言可能会被触发，因为它使用的是`memory_order_relaxed`。原文中的具体解释如下：

> Even though the store to `a` 1 is sequenced before the store to `p` 2, and the store to `p` is tagged `memory_order_release`, the load of `p` 3 is tagged `memory_order_consume`. This means that the store to `p` only happens-before those expressions that are dependent on the value loaded from `p`. This means that the asserts on the data members of the `X` structure 4, 5 are guaranteed not to fire, because the load of `p` carries a dependency to those expressions through the variable `x`. On the other hand, the assert on the value of `a` 6 may or may not fire; this operation isn’t dependent on the value loaded from `p`, and so there’s no guarantee on the value that’s read. This is particularly apparent because it’s tagged with `memory_order_relaxed`, as you’ll see.

关于`std::kill_dependency()`的理解，见原文P140，反正我目前是没有看懂。

#### 释放队列与同步（Release sequences and synchronizes-with）

本段没看懂，但是自测书中的代码可能会让我明白一些什么，补全书中代码如下：

``` c++
// 05_11.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

std::vector<int> queue_data;
std::atomic<int> count;

void wait_for_more_items(int tid)
{
  using namespace std::chrono_literals;
  std::cout << "thread" << tid << ": wait_for_more_items() wait 3s"
            << std::endl;
  std::this_thread::sleep_for(3s);
}

void process(int val, int tid)
{
  std::cout << "thread" << tid << ": process(" << val << ")"
            << std::endl;
}

void populate_queue()
{
  const unsigned number_of_items = 20;
  queue_data.clear();

  for (unsigned i = 0; i < number_of_items; ++i) {
    queue_data.push_back(i);
  }

  count.store(number_of_items, std::memory_order_release);
}

void consume_queue_items(int tid)
{
  while (true) {
    int item_index;

    if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) {
      wait_for_more_items(tid);
      continue;
    }

    process(queue_data[item_index - 1], tid);
  }
}

int main(int argc, char *argv[])
{
  std::thread a(populate_queue);
  std::thread b(consume_queue_items, 1);
  std::thread c(consume_queue_items, 2);
  a.join();
  b.join();
  c.join();

  return 0;
}
```

``` shellsession
% ./05_11
thread2: wait_for_more_items() wait 3s
thread1: wait_for_more_items() wait 3s
thread1: process(19)
thread1: process(18)
thread1: process(17)
thread1: process(16)
thread1: process(15)
thread1: process(14)
thread1: process(13)
thread1: process(12)
thread1: process(11)
thread1: process(10)
thread1: process(9)
thread1: process(8)
thread1: process(7)
thread1: process(6)
thread1: process(5)
thread1: process(4)
thread1: process(3)
thread1: process(2)
thread1: process(1)
thread1: process(0)
thread1: wait_for_more_items() wait 3s
thread2: wait_for_more_items() wait 3s
thread2: wait_for_more_items() wait 3s
thread1: wait_for_more_items() wait 3s
```

``` shellsession
% ./05_11
thread2: wait_for_more_items() wait 3s
thread1: wait_for_more_items() wait 3s
thread2: process(19)
thread2: process(18)
thread2: process(17)
thread2: process(16)
thread2: process(15)
thread2: process(14)
thread2: process(13)
thread2: process(12)
thread2: process(11)
thread2: process(10)
thread2: process(9)
thread2: process(8)
thread2: process(7)
thread2: process(6)
thread2: process(5)
thread2: process(4)
thread2: process(3)
thread2: process(2)
thread2: process(1)
thread2: process(0)
thread2: wait_for_more_items() wait 3s
thread1: wait_for_more_items() wait 3s
thread2: wait_for_more_items() wait 3s
thread1: wait_for_more_items() wait 3s
```

<u>这个中文翻译真的不能再看了，都翻译错了，还是老老实实的看英文吧！</u>

这里的意思我大概知道了：当只有一个线程读时是`fetch_sub()`是同步的，**但是当两个线程时，第二个线程的`fetch_sub()`看到的修改值是第一个线程修改的而不是`store`修改的**。

> Without the rule about the release sequence, this second thread wouldn’t have a happens-before relationship with the first thread, and it wouldn’t be safe to read the shared buffer unless the first `fetch_sub()` also had `memory_order_release` semantics, which would introduce unnecessary synchronization between the two consumer threads. Without the release sequence rule or `memory_order_release` on the `fetch_sub` operations, there would be nothing to require that the stores to the `queue_data` were visible to the second consumer, and you would have a data race. Thankfully, the first `fetch_sub()` does participate in the release sequence, and so the `store()` synchronizes-with the second `fetch_sub()`. There’s still no synchronizes-with relationship between the two consumer threads.

我的翻译：没有“release sequence”的规则限制，那么第二个线程与第一个线程之间不存在“happens-before”关系，这样第二个线程读共享数据时是不安全的，除非第一个线程的`fetch_sub()`也是`memory_order_release`语义，这将引进不必要的同步在两个线程之间。没有“release sequence”规则或者`fetch_sub()`操作上没有指定为`memory_order_release`，这样就无需要求`queue_data`的存储对第二个线程可见，这就产生了数据竞争。幸运的是，第一个线程`fetch_sub()`确实参与了“release sequence”，因此`store()`与第二线程个fetch_sub()同步。两个线程之间仍然没有同步关系。

至此，本小节内容仍然没有看懂。

# <2019-04-23 周二> 《C++并发编程实战》读书笔记（十四）

## Chapter 6: Designing lock-based concurrent data structures（一）

### What does it mean to design for concurrency?

#### Guidelines for designing data structures for concurrency

略

### Lock-based concurrent data structures（一）

#### A thread-safe stack using locks

补全书中代码如下：

``` c++
// 06_01.cpp
#include <iostream>
#include <exception>
#include <stack>
#include <mutex>
#include <memory>

struct empty_stack : std::exception
{
  const char *what() const throw()
  {
    return "empty stack";
  }
};

template<typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack() {}

  threadsafe_stack(const threadsafe_stack &other)
  {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  threadsafe_stack &operator=(const threadsafe_stack &) = delete;

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value)); // 1
  }

  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack(); // 2
    }

    const std::shared_ptr<T>
      res(std::make_shared<T>(std::move(data.top()))); // 3

    data.pop(); // 4
    return res;
  }

  void pop(T &value)
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }

    value = std::move(data.top()); // 5
    data.pop(); // 6
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

int main(int argc, char *argv[])
{
  return 0;
}
```

这里的代码与“[03_05.cpp](#03_05_cpp)”稍微有点区别，原文解释了上面的代码是如何做到线程安全和异常安全的，解释的还是很清楚的，请见英文版的P152。

# <2019-04-25 周四> 《C++并发编程实战》读书笔记（十五）

## Chapter 6: Designing lock-based concurrent data structures（二）

### Lock-based concurrent data structures（二）

#### A thread-safe queue using locks and condition variables

补全书中代码如下：

``` c++
// 06_02.cpp
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
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue() {}

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(std::move(new_value));
    data_cond.notify_one(); // 1
  }

  void wait_and_pop(T &value) // 2
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value = std::move(data_queue.front());
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop() // 3
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();}); // 4
    std::shared_ptr<T>
      res(std::make_shared<T>(std::move(data_queue.front())));
    data_queue.pop();
    return res;
  }

  bool try_pop(T &value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return false;
    }

    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty()) {
      return std::shared_ptr<T>(); // 5
    }

    std::shared_ptr<T>
      res(std::make_shared<T>(std::move(data_queue.front())));
    data_queue.pop();
    return res;
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
```

这里的代码与“[04_02.cpp](#04_02_cpp)”几乎相同，关于代码的解释还是见原文P156。可以从书中了解到在异常安全方面，上面的代码可能会有小小的转折（There’s a slight twist），当一个条目被推入队列的时候，有多个线程在等待时，只能有一个线程被`data_cond.notify_one()`唤醒，如果被唤醒的这个线程在`wait_and_pop()`中抛出了一个异常，比如在注释4处，当新`std::shared_ptr<>`被构造，其它线程都不会被唤醒。如果这个不能被接受，那么可以使用`data_cond.notify_all()`唤醒所有等待的线程，但是需要付出一点代价，就是当队列仍为空时，其它线程还得回去继续休眠。

第二种方法：在`wait_and_pop()`中如果发生异常的话调用`notify_one()`，这样的话另外的线程就可以获得被唤醒的机会。

第三种方法：将`std::shared_ptr<>`初始化移动到`push()`调用中并存储`std::shared_ptr<>`实例而不是直接的数据值。将`std::shared_ptr<>`复制出内部`std::queue<>`然后不能抛出异常，所以`wait_and_pop()`再次安全。代码如下：

``` c++
// 06_03.cpp
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
```

这个讲得好，作者不提起的话还真不会发现，注释5处构造`std::shared_ptr<>`被放在了锁的外面，正如原文所说，我觉得这也确实是个额外的好处。

> If the data is held by `std::shared_ptr<>`, there’s an additional benefit: the allocation of the new instance can now be done outside the lock in `push()` 5, whereas inlisting 6.2 it had to be done while holding the lock in `pop()`. Because memory allocation is typically quite an expensive operation, this can be very beneficial for the per-formance of the queue, because it reduces the time the mutex is held, allowing otherthreads to perform operations on the queue in the meantime.

## `const std::shared_ptr<>`与`std::shared_ptr<> const`

在抄写《C++并发编程实战》书中代码的时候遇到`std::shared_ptr<> const`我总是习惯性的把它改写成`const std::shared_ptr<>`，今天忽然想起来`const`修饰智能指针与修饰原始指针是不是会不一样？因此写了下面的测试代码来验证一下自己的有关想法。

``` c++
// 06_else_01.cpp
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  int val = 1;
  const int *cp = &val;

  // error: assignment of read-only location ‘* cp’
  // *cp = 2;

  const std::shared_ptr<int> csp = std::make_shared<int>(1);
  std::shared_ptr<int> const scp = std::make_shared<int>(2);
  std::cout << "*csp: " << *csp << std::endl;
  std::cout << "*scp: " << *scp << std::endl;

  *csp = 3;
  std::cout << "*csp: " << *csp << std::endl;
  *scp = 4;
  std::cout << "*scp: " << *scp << std::endl;

  std::shared_ptr<int> sp = std::make_shared<int>(0);

  // error: no match for ‘operator=’
  // (operand types are ‘const std::shared_ptr<int>’ and ‘std::shared_ptr<int>’)
  // csp = sp;

  // error: no match for ‘operator=’
  // (operand types are ‘const std::shared_ptr<int>’ and ‘std::shared_ptr<int>’)
  // scp = sp;

  return 0;
}
```

``` shellsession
% ./06_else_01
*csp: 1
*scp: 2
*csp: 3
*scp: 4
```

众所周知，上面的代码中`const int *cp = &val;`是修饰指针所指向的值的，所以`*cp = 2;`会报错。而`const std::shared_ptr<int> csp = std::make_shared<int>(1);`与`const int *cp = &val;`不同，因为`*csp = 3;`没有报错，而且成功的将值修改成功，修改为`3`，同样`std::shared_ptr<int> const scp = std::make_shared<int>(2);`的`*scp = 4;`也是成功的，从这点来看`const std::shared_ptr<>`与`std::shared_ptr<> const`应该是等价的，但是`const`修饰智能指针与修饰原始指针是不一样的。

不解的是从`csp = sp;`和`scp = sp;`的报错信息来看它们编译不通过的原因与`const`没有关系，而是因为没有找到合适的`operator=`函数。但是从文档来看`std::shared_ptr<>`确实可以相互赋值，因此有下面的测试代码：

``` c++
// 06_else_02.cpp
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  std::shared_ptr<int> sp1 = std::make_shared<int>(1);
  std::shared_ptr<int> sp2 = std::make_shared<int>(2);
  std::cout << "*sp1: " << *sp1 << std::endl;
  std::cout << "*sp2: " << *sp2 << std::endl;

  sp1 = sp2;
  std::cout << "*sp1: " << *sp1 << std::endl;

  return 0;
}
```

``` shellsession
% ./06_else_02
*sp1: 1
*sp2: 2
*sp1: 2
```

因此目前的总结就是：**`const std::shared_ptr<>`和`std::shared_ptr<> const`是等价的，但是`const std::shared_ptr<>`与`const int *`是完全不同的**。

# <2022-04-08 Fri> 《C++ Concurrency in Action》读书笔记（十六）

## Chapter 6: Designing lock-based concurrent data structures（三）

### Lock-based concurrent data structures（三）

#### A thread-safe queue using fine-grained locks and condition variables

三年之后，又重新拾起了这本书，从大概<2022-03-19 Sat>那天开始重头阅读，到今天差不多第二十一天，终于赶上了之前的阅读进度了。

# <2022-04-29 Fri> 《C++ Concurrency in Action》读书笔记（十七）

## Chapter 7: Designing lock-free concurrent data structures（一）

### 7.2.1 Writing a thread-safe stack without locks

``` c++
// Listing 7.2
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
```

1. `head`指针其实是`prev`的意思，每`push()`一个元素它都会被修改
2. 不用每次都去`head.load()`值，因为`compare_exchange_weak()`是位于循环中，编译器帮你完成这个操作
3. 为什么可以用`weak`版，因为它在循环中测试`false`的情况，同时`weak`比`strong`更具优化性（在某些平台）
4. `head`每次指向新`push()`的元素，`pop()`时，`head`会被删除（按我的理解方式，`tail`更直观）

### 7.2.2 Stopping those pesky leaks: managing memory in lock-free data structures

``` c++
// Listing 7.5
#include <atomic>
#include <memory>
#include <iostream>

template <typename T> class lock_free_stack {
private:
  struct node {
    std::shared_ptr<T> data;
    node *next;

    node(T const &data_) : data(std::make_shared<T>(data_)) {}
  };

  std::atomic<node *> head;
  std::atomic<unsigned> threads_in_pop;
  std::atomic<node *> to_be_deleted;

  static void delete_nodes(node *nodes) {
    while (nodes) {
      node *next = nodes->next;
      delete nodes;
      nodes = next;
    }
  }

  void try_reclaim(node *old_head) {
    if (threads_in_pop == 1) {
      node *nodes_to_delete = to_be_deleted.exchange(nullptr);
      if (!--threads_in_pop) {
        delete_nodes(nodes_to_delete);
      } else if (nodes_to_delete) {
        chain_pending_nodes(nodes_to_delete);
      }
      delete old_head;
    } else {
      chain_pending_node(old_head);
      --threads_in_pop;
    }
  }

  void chain_pending_nodes(node *nodes) {
    node *last = nodes;
    while (node *const next = last->next) {
      last = next;
    }
    chain_pending_nodes(nodes, last);
  }

  void chain_pending_nodes(node *first, node *last) {
    last->next = to_be_deleted;
    while (!to_be_deleted.compare_exchange_weak(last->next, first))
      ;
  }

  void chain_pending_node(node *n) { chain_pending_nodes(n, n); }

public:
  void push(T const &data) {
    node *const new_node = new node(data);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node))
      ;
  }

  std::shared_ptr<T> pop() {
    ++threads_in_pop;
    node *old_head = head.load();
    while (old_head && !head.compare_exchange_weak(old_head, old_head->next))
      ;
    std::shared_ptr<T> res;
    if (old_head) {
      res.swap(old_head->data);
    }
    try_reclaim(old_head);
    return res;
  }
};

int main() {
  lock_free_stack<int> lfs;
  lfs.push(1);
  lfs.push(2);
  lfs.push(3);
  std::cout << "pop: " << *lfs.pop() << '\n';
  std::cout << "pop: " << *lfs.pop() << '\n';
  std::cout << "pop: " << *lfs.pop() << '\n';
  return 0;
}
```

在低负载下工作的较好，但在高负载下可能因为没有窗口期去删除`to_be_deleted`，导致它无限增长而导致内存泄漏，这里这么说是因为要引出`7.2.3`，这里的代码也算好理解。

# <2022-04-30 Sat> 《C++ Concurrency in Action》读书笔记（十七）

## Chapter 7: Designing lock-free concurrent data structures（二）

### 7.2.3 Detecting nodes that can't be reclaimed using hazard pointers

``` c++
std::shared_ptr<T> pop() {
  std::atomic<void *> &hp = get_hazard_pointer_for_current_thread();
  node *old_head = head.load();

  do {
    node *temp;
    do {
      temp = old_head;
      hp.store(old_head);
      old_head = head.load();
    } while (old_head != temp);
  } while (old_head &&
           !head.compare_exchange_strong(old_head, old_head->next));

  hp.store(nullptr);
  std::shared_ptr<T> res;
  if (old_head) {
    res.swap(old_head->data);
    if (outstanding_hazard_pointers_for(old_head)) {
      reclaim_later(old_head);
    } else {
      delete old_head;
    }
    delete_nodes_with_no_hazards();
  }
  return res;
}
```

1. 最内层的那个`do-while`循环的作用是：一直循环直到将`head`赋值给`hazard pointer`
2. 接着`CAS`，这个操作完成后将`hazard pointer`清掉，说明你已经拿到了`old_head`，此时的`head`已经变成了`old_head->next`了，说明之后的其它线程无法再获取你获取到的`head`的值了，即`old_head`，这时说明安全了，所以这里要清掉刚才设置的`hazard pointer`，然后你要做的就是看`old_head`有没有被其它线程使用
3. 为什么这里要用`compare_exchange_strong()`？我的理解是：首先`spurious failure`指的是原始值与期望值相等，而新值没有赋值成功进原始值，返回`false`，如果使用`compare_exchange_weak()`的话，当产生`spurious failure`时返回`false`，`while`循环再次执行，如果此地`head`值被其它线程修改，可能是`push`或者`pop`操作，那么此时原始值与期望值不等，`old_head`会被设置成新的`head`值，即书中所说的`hp`变量被不必要的修改了（`hp`是指向`old_head`的），所以这里用`compare_exchange_strong()`，这里的问题是`hp`并没有`store()`操作，为什么`old_head`被修改会影响`hp`呢？难道也是编译器做了什么操作？

值得注意的是`hazard pointer`不能自由使用，由于`IBM`的专利保护。

``` c++
#include <atomic>
#include <memory>
#include <iostream>
#include <thread>
#include <functional>

unsigned const max_hazard_pointers = 100;

struct hazard_pointer {
  std::atomic<std::thread::id> id;
  std::atomic<void *> pointer;
};

hazard_pointer hazard_pointers[max_hazard_pointers];

class hp_owner {
  hazard_pointer *hp;

public:
  hp_owner(hp_owner const &) = delete;
  hp_owner operator=(hp_owner const &) = delete;

  hp_owner() : hp(nullptr) {
    for (unsigned i = 0; i < max_hazard_pointers; ++i) {
      std::thread::id old_id;
      if (hazard_pointers[i].id.compare_exchange_strong(
              old_id, std::this_thread::get_id())) {
        hp = &hazard_pointers[i];
        break;
      }
    }
    if (!hp) {
      throw std::runtime_error("No hazard pointers available");
    }
  }

  std::atomic<void *> &get_pointer() { return hp->pointer; }

  ~hp_owner() {
    hp->pointer.store(nullptr);
    hp->id.store(std::thread::id());
  }
};

std::atomic<void *> &get_hazard_pointer_for_current_thread() {
  thread_local static hp_owner hazard;
  return hazard.get_pointer();
}

bool outstanding_hazard_pointers_for(void *p) {
  for (unsigned i = 0; i < max_hazard_pointers; ++i) {
    if (hazard_pointers[i].pointer.load() == p) {
      return true;
    }
  }
  return false;
}

template <typename T> void do_delete(void *p) { delete static_cast<T *>(p); }

struct data_to_reclaim {
  void *data;
  std::function<void(void *)> deleter;
  data_to_reclaim *next;

  template <typename T>
  data_to_reclaim(T *p) : data(p), deleter(&do_delete<T>), next(0) {}

  ~data_to_reclaim() { deleter(data); }
};

std::atomic<data_to_reclaim *> nodes_to_reclaim;

void add_to_reclaim_list(data_to_reclaim *node) {
  node->next = nodes_to_reclaim.load();
  while (!nodes_to_reclaim.compare_exchange_weak(node->next, node))
    ;
}

template <typename T> void reclaim_later(T *data) {
  add_to_reclaim_list(new data_to_reclaim(data));
}

void delete_nodes_with_no_hazards() {
  data_to_reclaim *current = nodes_to_reclaim.exchange(nullptr);
  while (current) {
    data_to_reclaim *const next = current->next;
    if (!outstanding_hazard_pointers_for(current->data)) {
      delete current;
    } else {
      add_to_reclaim_list(current);
    }
    current = next;
  }
}

template <typename T> class lock_free_stack {
private:
  struct node {
    std::shared_ptr<T> data;
    node *next;

    node(T const &data_) : data(std::make_shared<T>(data_)) {}
  };

  std::atomic<node *> head;

public:
  void push(T const &data) {
    node *const new_node = new node(data);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node))
      ;
  }

  std::shared_ptr<T> pop() {
    std::atomic<void *> &hp = get_hazard_pointer_for_current_thread();
    node *old_head = head.load();

    do {
      node *temp;
      do {
        temp = old_head;
        hp.store(old_head);
        old_head = head.load();
      } while (old_head != temp);
    } while (old_head &&
             !head.compare_exchange_strong(old_head, old_head->next));

    hp.store(nullptr);
    std::shared_ptr<T> res;
    if (old_head) {
      res.swap(old_head->data);
      if (outstanding_hazard_pointers_for(old_head)) {
        reclaim_later(old_head);
      } else {
        delete old_head;
      }
      delete_nodes_with_no_hazards();
    }
    return res;
  }
};

int main() {
  lock_free_stack<int> lfs;
  lfs.push(1);
  lfs.push(2);
  lfs.push(3);
  std::cout << "pop: " << *lfs.pop() << '\n';
  std::cout << "pop: " << *lfs.pop() << '\n';
  std::cout << "pop: " << *lfs.pop() << '\n';
  return 0;
}
```

# <2022-05-02 Mon> 《C++ Concurrency in Action》读书笔记（十八）

## Chapter 7: Designing lock-free concurrent data structures（三）

### 7.2.4 Detecting nodes in use with reference counting

五一假期第一天“<2022-04-30 Sat>”那天看了这节的内容，没有看懂，因为完全没有见过双引用计数的用法，一直在心里问为什么指针被读时增加外部引用计数，而读操作结束后减少内部引用计数？现在我觉得答案就是策略。

书中的代码算理解，但似懂非懂：

1. 目前不理解如何选择`weak`和`strong`，代码中`push()`函数用的是`weak`，其它都用`strong`
2. 可以理解外部计数为什么减`2`，正如所说：因为你从列表中移除了节点，要减`1`；然后你不再将从现在的这个线程再去访问这个节点，再减`1`，怎么理解？因为`pop()`函数结束后，你再调用`pop()`时这个节点你将再也读不到了，因为它已经从列表中删除了。
3. 可能是因为用了自定义的类型`std::atomic<counted_node_ptr> head;`，产生链接错误，需要加上`-latomic`选项

``` c++
#include <atomic>
#include <memory>
#include <thread>
#include <iostream>

template <typename T> class lock_free_stack {
private:
  struct node;

  struct counted_node_ptr {
    int external_count;
    node *ptr;
  };

  struct node {
    std::shared_ptr<T> data;
    std::atomic<int> internal_count;
    counted_node_ptr next;

    node(T const &data_)
        : data(std::make_shared<T>(data_)), internal_count(0) {}
  };

  std::atomic<counted_node_ptr> head;

  void increase_head_count(counted_node_ptr &old_counter) {
    counted_node_ptr new_counter;
    do {
      new_counter = old_counter;
      ++new_counter.external_count;
    } while (!head.compare_exchange_strong(old_counter, new_counter));
    old_counter.external_count = new_counter.external_count;
  }

public:
  ~lock_free_stack() {
    while (pop())
      ;
  }

  void push(T const &data) {
    counted_node_ptr new_node;
    new_node.ptr = new node(data);
    new_node.external_count = 1;
    new_node.ptr->next = head.load();
    while (!head.compare_exchange_weak(new_node.ptr->next, new_node))
      ;
  }

  std::shared_ptr<T> pop() {
    counted_node_ptr old_head = head.load();
    for (;;) {
      increase_head_count(old_head);
      node *const ptr = old_head.ptr;
      if (!ptr) {
        return std::shared_ptr<T>();
      }

      if (head.compare_exchange_strong(old_head, ptr->next)) {
        std::shared_ptr<T> res;
        res.swap(ptr->data);

        int const count_increase = old_head.external_count - 2;
        if (ptr->internal_count.fetch_add(count_increase) == -count_increase) {
          delete ptr;
        }

        return res;
      } else if (ptr->internal_count.fetch_sub(1) == 1) {
        delete ptr;
      }
    }
  }
};

lock_free_stack<int> g_lfs;

void thread_proc(int n) {
  g_lfs.push(n++);
  g_lfs.push(n++);
  g_lfs.push(n++);
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
}

int main() {
  int n = 0;
  std::thread thread_arr[4];

  for (int i = 0; i < 4; ++i) {
    thread_arr[i] = std::thread(thread_proc, n += 10);
  }

  for (int i = 0; i < 4; ++i) {
    thread_arr[i].join();
  }

  return 0;
}
```

### 7.2.6 Writing a thread-safe queue without locks（一）

反复看了`Listing 7.13`的代码两三遍终于回忆起来`queue`的代码结构，要不然`push()`这个函数真看不懂：

1. `queue`内部实现使用了一个`dummy node`，是为了防止`pop()`时队列为空发生错误，这样也不用处理异常和增加`empty()`函数了，看它的构造函数，`head`是申请的`dummy`指针，而`tail`就是`head`，即新创建`queue`时就只有一个元素`dummy node`，`head`和`tail`都指向它
2. 当`push()`一个元素后，`tail`指向`dummy node`

``` c++
// Listing 7.13
#include <atomic>
#include <memory>
#include <iostream>

template <typename T> class lock_free_queue {
private:
  struct node {
    std::shared_ptr<T> data;
    node *next;

    node() : next(nullptr) {}
  };

  std::atomic<node *> head;
  std::atomic<node *> tail;

  node *pop_head() {
    node *const old_head = head.load();
    if (old_head == tail.load()) {
      return nullptr;
    }
    head.store(old_head->next);
    return old_head;
  }

public:
  lock_free_queue() : head(new node), tail(head.load()) {}

  lock_free_queue(const lock_free_queue &) = delete;
  lock_free_queue &operator=(const lock_free_queue &) = delete;

  ~lock_free_queue() {
    while (node *const old_head = head.load()) {
      head.store(old_head->next);
      delete old_head;
    }
  }

  std::shared_ptr<T> pop() {
    node *old_head = pop_head();
    if (!old_head) {
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> const res(old_head->data);
    delete old_head;
    return res;
  }

  void push(T new_value) {
    std::shared_ptr<T> new_data = std::make_shared<T>(std::move(new_value));
    node &p = new node;
    node *const old_tail = tail.load();
    old_tail->data.swap(new_data);
    old_tail->next = p;
    tail.store(p);
  }
};

int main() {}
```

# <2022-05-03 Tue> 《C++ Concurrency in Action》读书笔记（十八）

## Chapter 7: Designing lock-free concurrent data structures（三）

### 7.2.6 Writing a thread-safe queue without locks（二）

这里有点难懂的！`Listing 7.13`的代码理解了它的解释，对于单个生产者和单个消费者来说运行的很好，但是并发运行`push()`或者`pop()`时，可能多线程时`tail.load()`，`head.load()`会操作同一个节点导致问题发生。

1. `pop()`：你不但要确保只有一个线程`pop`了一个指定的`data`，你还要确保其他线程可以安全的访问他们从`head`节点读取到的`next`成员
2. `push()`：`push()`和`pop()`之间要有一个`happen-before`的关系，问题是在设置`tail`指针之前，你要设置`dummy node`上的`data`成员，这样的话并发调用`push()`时就会发生多线程重复覆盖`data`的值，因为多线程时你读取的是同一个`tail`

从`Listing 7.15`一直到`Listing 7.19`都是将要实现的`lock_free_queue`的代码，将它们放到一起，运行将会出错`segmentation fault (core dumped)`，因为空指针。附上代码：

``` c++
// Listing 7.15
#include <atomic>
#include <memory>
#include <thread>
#include <iostream>

template <typename T> class lock_free_queue {
private:
  struct node;

  struct counted_node_ptr {
    int external_count;
    node *ptr;
  };

  std::atomic<counted_node_ptr> head;
  std::atomic<counted_node_ptr> tail;

  struct node_counter {
    unsigned internal_count : 30;
    unsigned external_counters : 2;
  };

  struct node {
    std::atomic<T *> data;
    std::atomic<node_counter> count;
    counted_node_ptr next;

    node() {
      node_counter new_count;
      new_count.internal_count = 0;
      new_count.external_counters = 2;
      count.store(new_count);

      next.ptr = nullptr;
      next.external_count = 0;
    }

    void release_ref() {
      node_counter old_counter = count.load(std::memory_order_relaxed);
      node_counter new_counter;

      do {
        new_counter = old_counter;
        --new_counter.internal_count;
      } while (!count.compare_exchange_strong(old_counter, new_counter,
                                              std::memory_order_acquire,
                                              std::memory_order_relaxed));

      if (!new_counter.internal_count && !new_counter.external_counters) {
        delete this;
      }
    }
  };

  static void increase_external_count(std::atomic<counted_node_ptr> &counter,
                                      counted_node_ptr &old_counter) {
    counted_node_ptr new_counter;

    do {
      new_counter = old_counter;
      ++new_counter.external_count;
    } while (!counter.compare_exchange_strong(old_counter, new_counter,
                                              std::memory_order_acquire,
                                              std::memory_order_relaxed));

    old_counter.external_count = new_counter.external_count;
  }

  static void free_external_counter(counted_node_ptr &old_node_ptr) {
    node *const ptr = old_node_ptr.ptr;
    int const count_increase = old_node_ptr.external_count - 2;
    node_counter old_counter = ptr->count.load(std::memory_order_relaxed);
    node_counter new_counter;

    do {
      new_counter = old_counter;
      --new_counter.external_counters;
      new_counter.internal_count += count_increase;
    } while (!ptr->count.compare_exchange_strong(old_counter, new_counter,
                                                 std::memory_order_acquire,
                                                 std::memory_order_relaxed));

    if (!new_counter.internal_count && !new_counter.external_counters) {
      delete ptr;
    }
  }

public:
  void push(T new_value) {
    std::unique_ptr<T> new_data(new T(new_value));
    counted_node_ptr new_next;
    new_next.ptr = new node;
    new_next.external_count = 1;
    counted_node_ptr old_tail = tail.load();

    for (;;) {
      increase_external_count(tail, old_tail);
      T *old_data = nullptr;
      if (old_tail.ptr->data.compare_exchange_strong(old_data,
                                                     new_data.get())) {
        old_tail.ptr->next = new_next;
        old_tail = tail.exchange(new_next);
        free_external_counter(old_tail);
        new_data.release();
        break;
      }
      old_tail.ptr->release_ref();
    }
  }

  std::unique_ptr<T> pop() {
    counted_node_ptr old_head = head.load(std::memory_order_relaxed);
    for (;;) {
      increase_external_count(head, old_head);
      node *const ptr = old_head.ptr;
      if (ptr == tail.load().ptr) {
        ptr->release_ref();
        return std::unique_ptr<T>();
      }

      if (head.compare_exchange_strong(old_head, ptr->next)) {
        T *const res = ptr->data.exchange(nullptr);
        free_external_counter(old_head);
        return std::unique_ptr<T>(res);
      }
      ptr->release_ref();
    }
  }
};

lock_free_queue<int> g_lfs;

void thread_proc(int n) {
  g_lfs.push(n++);
  g_lfs.push(n++);
  g_lfs.push(n++);
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
}

int main() {
  int n = 0;
  // std::thread thread_arr[4];

  // for (int i = 0; i < 4; ++i) {
  //   thread_arr[i] = std::thread(thread_proc, n += 10);
  // }

  // for (int i = 0; i < 4; ++i) {
  //   thread_arr[i].join();
  // }

  g_lfs.push(n++);
  g_lfs.push(n++);
  g_lfs.push(n++);
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';

  return 0;
}
```

### 7.2.6 Writing a thread-safe queue without locks（三）

还没读本节之前我先看了下书中的代码，也在想`push()`时它为什么和`nullptr`比较？如果此时别的线程修改了`tail`的值，那么这里肯定会失败了呀，因为新的`tail`不可能是`nullptr`。书中现在既然也提到了这点儿，就是导致了这里的代码没有实现`lock-free`，它就是一个锁，还不是互斥锁，至少系统会为互斥锁提供一个优先级，而在上面的`Listing 7.15`这里，你只能等其它线程结束操作以后才能继续。

#### MAKING THE QUEUE LOCK-FREE BY HELPING OUT ANOTHER THREAD

这里的思路也变得清晰起来：因为`dummy node`都是一样的，在设置了`next`成员后就可以设置新的`tail`为`dummy node`了，这里使用`weak`版本的循环，由谁设置无所谓，如果`weak`发现`tail`已经被设置了`dummy node`那肯定是其它线程干的，那任务完成，这个线程就不用操作了。

``` c++
// Listing 7.21
#include <atomic>
#include <memory>
#include <thread>
#include <iostream>

template <typename T> class lock_free_queue {
private:
  struct node;

  struct counted_node_ptr {
    int external_count;
    node *ptr;
  };

  std::atomic<counted_node_ptr> head;
  std::atomic<counted_node_ptr> tail;

  struct node_counter {
    unsigned internal_count : 30;
    unsigned external_counters : 2;
  };

  struct node {
    std::atomic<T *> data;
    std::atomic<node_counter> count;
    std::atomic<counted_node_ptr> next;

    node() {
      node_counter new_count;
      new_count.internal_count = 0;
      new_count.external_counters = 2;
      count.store(new_count);

      counted_node_ptr new_next;
      new_next.ptr = nullptr;
      new_next.external_count = 0;
      next.store(new_next);
    }

    void release_ref() {
      node_counter old_counter = count.load(std::memory_order_relaxed);
      node_counter new_counter;

      do {
        new_counter = old_counter;
        --new_counter.internal_count;
      } while (!count.compare_exchange_strong(old_counter, new_counter,
                                              std::memory_order_acquire,
                                              std::memory_order_relaxed));

      if (!new_counter.internal_count && !new_counter.external_counters) {
        delete this;
      }
    }
  };

  static void increase_external_count(std::atomic<counted_node_ptr> &counter,
                                      counted_node_ptr &old_counter) {
    counted_node_ptr new_counter;

    do {
      new_counter = old_counter;
      ++new_counter.external_count;
    } while (!counter.compare_exchange_strong(old_counter, new_counter,
                                              std::memory_order_acquire,
                                              std::memory_order_relaxed));

    old_counter.external_count = new_counter.external_count;
  }

  static void free_external_counter(counted_node_ptr &old_node_ptr) {
    node *const ptr = old_node_ptr.ptr;
    int const count_increase = old_node_ptr.external_count - 2;
    node_counter old_counter = ptr->count.load(std::memory_order_relaxed);
    node_counter new_counter;

    do {
      new_counter = old_counter;
      --new_counter.external_counters;
      new_counter.internal_count += count_increase;
    } while (!ptr->count.compare_exchange_strong(old_counter, new_counter,
                                                 std::memory_order_acquire,
                                                 std::memory_order_relaxed));

    if (!new_counter.internal_count && !new_counter.external_counters) {
      delete ptr;
    }
  }

  void set_new_tail(counted_node_ptr &old_tail,
                    counted_node_ptr const &new_tail) {
    node *const current_tail_ptr = old_tail.ptr;
    while (!tail.compare_exchange_weak(old_tail, new_tail) &&
           old_tail.ptr == current_tail_ptr)
      ;
    if (old_tail.ptr == current_tail_ptr)
      free_external_counter(old_tail);
    else
      current_tail_ptr->release_ref();
  }

public:
  void push(T new_value) {
    std::unique_ptr<T> new_data(new T(new_value));
    counted_node_ptr new_next;
    new_next.ptr = new node;
    new_next.external_count = 1;
    counted_node_ptr old_tail = tail.load();

    for (;;) {
      increase_external_count(tail, old_tail);
      T *old_data = nullptr;
      if (old_tail.ptr->data.compare_exchange_strong(old_data,
                                                     new_data.get())) {
        counted_node_ptr old_next = {0};
        if (!old_tail.ptr->next.compare_exchange_strong(old_next, new_next)) {
          delete new_next.ptr;
          new_next = old_next;
        }
        set_new_tail(old_tail, new_next);
        new_data.release();
        break;
      } else {
        counted_node_ptr old_next = {0};
        if (old_tail.ptr->next.compare_exchange_strong(old_next, new_next)) {
          old_next = new_next;
          new_next.ptr = new node;
        }
        set_new_tail(old_tail, old_next);
      }
    }
  }

  std::unique_ptr<T> pop() {
    counted_node_ptr old_head = head.load(std::memory_order_relaxed);
    for (;;) {
      increase_external_count(head, old_head);
      node *const ptr = old_head.ptr;
      if (ptr == tail.load().ptr) {
        ptr->release_ref();
        return std::unique_ptr<T>();
      }

      counted_node_ptr next = ptr->next.load();
      if (head.compare_exchange_strong(old_head, ptr->next)) {
        T *const res = ptr->data.exchange(nullptr);
        free_external_counter(old_head);
        return std::unique_ptr<T>(res);
      }
      ptr->release_ref();
    }
  }
};

lock_free_queue<int> g_lfs;

void thread_proc(int n) {
  g_lfs.push(n++);
  g_lfs.push(n++);
  g_lfs.push(n++);
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
}

int main() {
  int n = 0;
  // std::thread thread_arr[4];

  // for (int i = 0; i < 4; ++i) {
  //   thread_arr[i] = std::thread(thread_proc, n += 10);
  // }

  // for (int i = 0; i < 4; ++i) {
  //   thread_arr[i].join();
  // }

  g_lfs.push(n++);
  g_lfs.push(n++);
  g_lfs.push(n++);
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';
  std::cout << "arg n: " << n << ", g_lfs.pop(): " << *g_lfs.pop() << '\n';

  return 0;
}
```

连滚带爬把第七章读完了！算阶段性的胜利吧。

# <2023-06-26 周一> 《C++ Concurrency in Action》读书笔记（十九）

## Chapter 3: Sharing data between threads（一）

### 3.1 Problems with sharing data between threads

我觉得翻译成“不变性”更好，“不变量”让我想起`const`关键字。不变性（`invariants`）的理解有点意思：

> One concept that’s widely used to help programmers reason about their code is that of invariants—statements that are always true about a particular data structure, such as “this variable contains the number of items in the list.” These invariants are often broken during an update, especially if the data structure is of any complexity or the update requires modification of more than one value.

就是说比如一个变量表示列表的成员数量，那它就一直表示这个意思，并且它的值是可以变化的。当然用双端列表的例子更方便理解：

>  Consider a doubly linked list, where each node holds a pointer to both the next node in the list and the previous one. One of the invariants is that if you follow a “next” pointer from one node (A) to another (B), the “previous” pointer from that node (B) points back to the first node (A). In order to remove a node from the list, the nodes on either side have to be updated to point to each other. Once one has been updated, the invariant is broken until the node on the other side has been updated too; after the update has completed, the invariant holds again.

#### 3.1.1 Race conditions

通常的`race condition`指的是“有问题的条件竞争”（`a problematic race condition`），`C++`标准为这种“有问题的条件竞争”专门定义了一个专有名词`data race`。

我理解的条件竞争是多个线程修改同一个数据，这个理解看来是不全面的，“有问题的条件竞争”通常是指一个操作需要同时修改两个或者两个以上的独立数据块，因为修改两个数据块必然要用到两条指令。此时另一个线程可能就会有机可乘。
