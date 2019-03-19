<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [<2019-03-11 Mon>读书笔记（一）](#2019-03-11-mon读书笔记一)
    - [第1章 你好，C++的并发世界](#第1章-你好c的并发世界)
    - [第2章 线程管理（一）](#第2章-线程管理一)
        - [启动线程（一）](#启动线程一)
- [<2019-03-12 Tue>读书笔记（二）](#2019-03-12-tue读书笔记二)
    - [第2章 线程管理（二）](#第2章-线程管理二)
        - [启动线程（二）](#启动线程二)
        - [向线程函数传递参数（一）](#向线程函数传递参数一)
            - [传值](#传值)
            - [传指针](#传指针)
            - [传引用（一）](#传引用一)
    - [理解临时对象的来源<2016-11-21 Mon>](#理解临时对象的来源2016-11-21-mon)
    - [关于函数参数中常量引用的再理解](#关于函数参数中常量引用的再理解)
- [<2019-03-13 Wed>读书笔记（三）](#2019-03-13-wed读书笔记三)
    - [第2章 线程管理（二）](#第2章-线程管理二-1)
        - [向线程函数传递参数（二）](#向线程函数传递参数二)
- [<2019-03-15 周五> 读书笔记（四）](#2019-03-15-周五-读书笔记四)
    - [第2章 线程管理（三）](#第2章-线程管理三)
        - [向线程函数传递参数（三）](#向线程函数传递参数三)
            - [传引用（二）](#传引用二)
        - [转移线程所有权（一）](#转移线程所有权一)
            - [`std::thread`线程所有权在函数外转换](#stdthread线程所有权在函数外转换)
            - [`std::thread`线程所有权在函数内转换](#stdthread线程所有权在函数内转换)
- [<2019-03-19 周二> 读书笔记（五）](#2019-03-19-周二-读书笔记五)
    - [第2章 线程管理（四）](#第2章-线程管理四)
        - [转移线程所有权（二）](#转移线程所有权二)
        - [运行时决定线程数量](#运行时决定线程数量)

<!-- markdown-toc end -->

# <2019-03-11 Mon>读书笔记（一）

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

# <2019-03-12 Tue>读书笔记（二）

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

# <2019-03-13 Wed>读书笔记（三）

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

# <2019-03-15 周五> 读书笔记（四）

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

# <2019-03-19 周二> 读书笔记（五）

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

即将``修改为`scoped_thread t(std::thread{func(some_local_state)});`

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
