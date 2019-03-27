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

<!-- markdown-toc end -->

# <2019-03-11 周一> 《C++并发编程实战》读书笔记（一）

## 第1章 你好，C++的并发世界

这章内容看得很累，好多地方读不懂，不知道想表达什么，书中有下面这段代码：

```
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

```
% g++ 01_01.cpp
/usr/bin/ld: /tmp/ccWuVkAr.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```

为什么`std::thread`需要去链接`pthread_create`呢？标准库的东西还得依赖平台支持吗？即使使用`g++ -std=c++11 01_01.cpp`进行编译也同样出错。

```
% g++ -std=c++11 01_01.cpp
/usr/bin/ld: /tmp/cchBMGkl.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```

**使用下面的命令可以编译通过，必须要加上“-pthread”参数。**

```
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

<span id="background_task"></span>

下面的代码编译出错，因为**如果你传递了一个临时变量，而不是一个命名变量，C++编译器会将其解析为函数声明，而不是对象定义**，通过下面的编译出错信息确实可以看到是这样子的。

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
```
% g++ 02_else_01.cpp -pthread
02_else_01.cpp: In function ‘int main(int, char**)’:
02_else_01.cpp:27:13: error: request for member ‘join’ in ‘my_thread’, which is of non-class type ‘std::thread(background_task (*)())’
   my_thread.join();
             ^~~~
```

可以通过下面两种方法来解决上面的临时变量问题，将对象的定义改为下面二者之一即可。

```
// 使用多组括号
std::thread my_thread((background_task()));

// 使用新统一的初始化语法（即初始化列表方法），可以通过`std::initializer_list`实现
std::thread my_thread{background_task()};
```

还有第三种方法，那就是使用C++11的新特性**右值引用**，见：[启动线程（二）](#启动线程二)

完整测试代码如下：

```
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

```
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
// output
operator()
```

继续进行下面的内容，下面这段代码使线程分离执行`detach()`，访问局部变量，可能引起**悬挂引用**问题。

```
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

```
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

```
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

```
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
```
// output
% ./02_else_03
i: 3
s: hello
```

这里就像“关于函数参数中常量引用的再理解”说的一样，产生了临时对象，它将`const char *`转化为`std::string`

这里有个问题留着下次解决：上面的代码如果将`t.join();`注释掉程序运行崩溃，我想知道原因，输出如下：

```
% ./02_else_03
terminate called without an active exception
[1]    6430 abort (core dumped)  ./a.out
```

#### 传指针

补全书中代码如下：

```
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
```
// output
% ./02_else_04
i: 3
s: 23
```

我将书中的代码的`detach()`改为了`join()`，不然我无法看到输出，**函数有很大的可能会在字面值转化成`std::string`对象之前崩溃，不懂什么意思**，解决方案是传递到`std::string`构造函数之前将字面值转化为`std::string`对象，修改上面的代码如下：

```
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
```
// output
% ./02_else_04
i: 3
s: 23
i: 3
s: 32
```

**这里也不懂什么意思，书中所言，见P30**，上面这种情况的问题是，想要依赖隐式转换将字面值转换为函数期待的`std::string`对象，但因`std::string`的构造函数会复制提供的变量，就只复制了没有转换成期望类型的字符串字面值。

#### 传引用（一）

补全书中代码，不知道为啥，下面这段代码编译有问题，一堆错误，先贴上再说。

```
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

```
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

```
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

```
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
// output
class_string(const char *value)
class_string(const char *value)
~class_string()
~class_string()
```

代码理解如下：在“1”处使用的是常量引用，可以看到构造和析构被调用了两次，一次是调用`test_ref_to_const(str);`，另一次是“cs”建立对象，当然如果直接使用`test_ref_to_const(cs);`，则构造和析构仅调用一次（这是我希望的），注意到`class_string`的有参构造函数其实不安全的，因为存在隐式转换，正因为隐式转换的存在才让`test_ref_to_const(str);`有了建立临时对象的可能性。

那么添上`explicit`后会怎么样呢？

```
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
```
error C2664: 'void test_ref_to_const(const class_string &)':
cannot convert argument 1 from 'char [6]' to 'const class_string &'
```

**果然编译出错，那么可以看出`explicit`有防止建立临时对象的作用**，如果仍保持隐式转换的存在，即不增加`explicit`，而是将函数的参数改为非常量引用，这就是大前年文章中提到的那样将会出现编译错误，算了代码不贴了，没有意义。

总结：如果使用常量引用，那么关闭隐式转换，避免产生临时对象而影响性能的可能性。

# <2019-03-13 周三> 《C++并发编程实战》读书笔记（三）

## 第2章 线程管理（二）

### 向线程函数传递参数（二）

越看问题越多，还是[传引用（一）](#传引用一)中提到的代码，通过将`update_data_for_widget`的参数修改为传值可以编译成功，但是输出结果让人费解，完整的测试代码如下：

```
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
```
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

```
void update_data_for_widget(widget_id w, widget_data data);
```

而不是在找

```
void update_data_for_widget(widget_id w, widget_data &data);
```

所以编译的时候报错，但是在我的“Archlinux”下编译好像又另外一个意思，输出不贴了，太长。

# <2019-03-15 周五> 《C++并发编程实战》读书笔记（四）

## 第2章 线程管理（三）

### 向线程函数传递参数（三）

#### 传引用（二）

为了确定不是我上面为了补全书中代码而写出来的问题，我将“02_else_03.cpp”的代码修改为，如下：

```
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

```
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
```
// output
% ./02_else_05
widget_data()
data.id: 3
~widget_data()
```

其中关于我上面遇到的问题在书中已做了讲解，但是我并没有完全看懂，我只是认为那段代码可以编译通过，书中所说：“`update_data_for_widget`的第二个参数期待传入一个引用，但是`std::thread`的构造函数并不知晓，构造函数**无视**函数期待的参数类型，并盲目的拷贝已提供的变量。当线程调用`update_data_for_widget`函数时**，传递给函数的参数是`data`变量内部拷贝的引用，而非数据本身的引用**。因此当线程结束时，内部拷贝数据将会在数据更新阶段被销毁。”，“**使用`std::ref`将参数转换成引用的形式**”。

可能提供一个成员函数指针作为线程函数，并提供一个合适的对象指针作为线程函数的第一个参数：

```
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
```
// output
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

```
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
```
// output
% ./02_05_01
some_function
some_other_function(42)
some_function
some_other_function(42)
```

#### `std::thread`线程所有权在函数内转换

当所有权可以在函数内部传递，就允许`std::thread`实例可作为参数进行传递，代码如下：

```
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
```
// output
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

```
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

```
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

```
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
```
// output
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

```
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
```
// output
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

```
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

```
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

```
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

```
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

```
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

```
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

```
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

```
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
```
// output
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

```
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
```
// output
% ./03_else_01 
prepare_data()
do_something()
```

`process_data()`函数直接转移`std::unique_lock`实例的所有权，调用`do_something()`可使用的正确数据（数据没有受到其他线程的修改）。**`std::unique_lock`是可移动，但不可赋值的类型**。

`std::unique_lock`的灵活性同样也允许实例在销毁之前放弃其拥有的锁。这对于应用性能来说很重要，因为持有锁的时间增加会导致性能下降，其他线程会等待这个锁的释放，避免超越操作。

#### 锁的粒度

```
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
