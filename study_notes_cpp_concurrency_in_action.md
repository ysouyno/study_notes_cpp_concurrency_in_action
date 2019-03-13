《C++并发编程实战》读书笔记

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
            - [传引用](#传引用)
    - [理解临时对象的来源<2016-11-21 Mon>](#理解临时对象的来源2016-11-21-mon)
    - [关于函数参数中常量引用的再理解](#关于函数参数中常量引用的再理解)

<!-- markdown-toc end -->

# <2019-03-11 Mon>读书笔记（一）

## 第1章 你好，C++的并发世界

这章内容看得很累，好多地方读不懂，不知道想表达什么，书中有下面这段代码

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

链接出错，如下

```console
% g++ 01_01.cpp
/usr/bin/ld: /tmp/ccWuVkAr.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```

为什么“std::thread”需要去链接“pthread_create”呢？标准库的东西还得依赖平台支持吗？即使使用“g++ -std=c++11 01_01.cpp”
进行编译也同样出错

```console
% g++ -std=c++11 01_01.cpp
/usr/bin/ld: /tmp/cchBMGkl.o: in function `std::thread::thread<void (&)(), , void>(void (&)())':
01_01.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x2f): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status
```

**使用下面的命令可以编译通过，必须要加上“-pthread”参数**

```console
% g++ 01_01.cpp -pthread
```

查看“g++”的手册页中关于“-pthread”的解释

```
-pthread
    Add support for multithreading using the POSIX threads library. This option sets flags for both the
    preprocessor and linker. It does not affect the thread safety of object code produced by the compiler
    or that of libraries supplied with it. These are HP-UX specific flags.
```

上面表示要使用“POSIX threads library”，查看“pthread_create”的手册页也可以看到

```
SYNOPSIS
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.
```

我的环境是

```console
gcc version 8.2.1 20181127 (GCC)
4.20.12-arch1-1-ARCH
```

**问题：“std::thread”在linux平台下必须使用“-pthread”才能正常编译成功吗？**

## 第2章 线程管理（一）

### 启动线程（一）

首先这里可以正确执行线程函数，“background_task”是一个“函数对象”，因为它的内部重载了括号操作符“operator()”

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

下面的代码编译出错，因为**如果你传递了一个临时变量，而不是一个命名变量，C++编译器会将其解析为函数声明，而不是对象
定义**，通过下面的编译出错信息确实可以看到是这样子的

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

可以通过下面两种方法来解决上面的临时变量问题，将对象的定义改为下面二者之一即可
还有第三种方法，那就是使用C++11的新特性“右值引用”，见我的测试代码：

```
// 使用多组括号
std::thread my_thread((background_task()));

// 使用新统一的初始化语法（即初始化列表方法），可以通过“std::initializer_list”实现
std::thread my_thread{background_task()};
```

完整测试代码如下

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

# <2019-03-12 Tue>读书笔记（二）

## 第2章 线程管理（二）

### 启动线程（二）

因为临时变量的原因导致“std::thread my_thread(background_task());”变成了函数声明的问题，可以通过“std::move”的“右值引
用”解决

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

继续进行下面的内容，下面这段代码使线程分离执行（detach），访问局部变量，可能引起“悬挂引用”

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

如果想分离一个线程，可以在线程启动后直接使用“detach”进行分离，如果打算等待则“join”的位置要精心挑选，因为假如线程运行
之后产生异常，此时“join”还没有调用，这意味着这次调用会被跳过，**当倾向于在无异常情况下使用“join”时，需要在异常处
理过程中调用“join”，从而避免生命周期的问题**

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

上面的这段代码使用了异常捕获，很容易理解不是吗！也可以通过“RAII”的方式提供一个类来解决这个问题，代码如下

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

对上面的代码说明，刚开始不太理解为什么能确保在“1”处即使发生异常也能调用“thread_guard”的析构函数？是不是因为当发生异
常的时候程序流程将跳到“2”处，C++能确保已经生成的对象会被正确析构？对异常不太了解，如果书上的意思是这样的话，那么上行的
猜测应该也是正确的，**“join”只能调用一次，再次调用将会导致错误，所以必须判断“joinable”，如果不想等待线程结束，
可以分离线程，从而避免异常安全问题**，不过“detach”也打破了线程和“std::thread”对象的联系，即使线程仍然在后台运行着
。**分离操作也能确保“std::terminate”在“std::thread”对象销毁才被调用**

“detach”会让线程在后台运行，这就意味着主线程不能与之产生直接交互，如果有线程分离，那么主不可能有“std::thread”对象能
引用它。分离线程的确在后台运行，所以分离线程不能被加入（join），不过C++运行库保证当线程退出时相关资源能够正确回收，后台
线程的归属和控制，C++运行库都会处理。分离线程为守护线程，它的另一方面只能确定线程什么时候结束，“发后即忘”（fire and forget）

“detach”的使用：不能对没有执行线程的“std::thread”对象使用“detach”；当“joinable”返回真时，就可以使用“detach”

### 向线程函数传递参数（一）

这里大概意思我懂了，传递参数无非就是传值、传指针和传引用嘛

#### 传值

补全书中代码如下

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

这里就像“[[ref_to_const_understand][关于函数参数中常量引用的再理解]]”说的一样，产生了临时对象，它将“const char*”
转化为“std::string”

**这里有个问题留着下次解决：上面的代码如果将“t.join();”注释掉程序运行崩溃，我想知道原因，输出如下**

```
% ./a.out
terminate called without an active exception
[1]    6430 abort (core dumped)  ./a.out
```

#### 传指针

补全书中代码如下

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

我将书中的代码的“detach”改为了“join”，不然我无法看到输出，**“函数有很大的可能会在字面值转化成‘std::string’对象
之前崩溃”，不懂什么意思**，解决方案是传递到“std::string”构造函数之前将字面值转化为“std::string”对象，修改上面的代
码如下

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

**这里也不懂什么意思，书中所言，见P30**，上面这种情况的问题是，想要依赖隐式转换将字面值转换为函数期待的“std::string”
对象，但因“std::string”的构造函数会复制提供的变量，就只复制了没有转换成期望类型的字符串字面值

#### 传引用

补全书中代码，不知道为啥，下面这段代码编译有问题，一堆错误，先贴上再说

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

## 理解临时对象的来源<2016-11-21 Mon>

仅当通过传值（by value）方式传递对象或传递常量引用（reference-to-const）参数时，才会发生这些类型转换，当传递一个非常量引
用（reference-to-non-const）参数对象，就不会发生，如下：

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

代码改成如下，果然编译通过

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

对上面代码的理解表述如下：假设建立一个临时对象，那么临时对象将被传递到“upeercasify”中，其会修改这个临时对象，把它的字
符改成大写，但是对“subtleBookPlug”函数调用的真正参数没有任何影响，仅仅改变了临时从“subtleBookPlug”生成的“string”
对象，无疑这不是程序员所希望的，程序员传递“subtleBookPlug”参数到“uppercasify”函数中，期望修改“subtleBookPlug”的值，
当程序员期望修改非临时对象时，对非常量引用（references-to-non-const）进行的隐式类型转换却修改临时对象，这就是为什么C++语
言禁止为非常量引用（reference-to-non-const）产生临时对象，这样非常量引用参数就不会遇到这种问题

临时对象是有开销的，所以你应该尽可能地去除它们，然而更重要的是训练自己寻找可能建立临时对象的地方，**在任何时候只要见到
常量引用（reference-to-const）参数，就存在建立临时对象而绑定在参数上的可能性；在任何时候只要见到函数返回对象，就
会有一个临时对象被建立（以后被释放）**，学会寻找这些对象构造，你就能显著地增强透过编译器表面动作而看到其背后开销的能力

## 关于函数参数中常量引用的再理解

因为之前写过，但是在不同的笔记文件中，所以我把笔记拷贝过来了，见：

前段时间写代码一直使用常量引用，已经习惯了，但是其实常量引用会造成临时对象的生成导致影响效率，今天写个测试代码再理解一次

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

代码理解如下：在“1”处使用的是常量引用，可以看到构造和析构被调用了两次，一次是调用“test_ref_to_const(str);”，另一次是
“cs”建立对象，当然如果直接使用“test_ref_to_const(cs);”，则构造和析构仅调用一次（这是我希望的），注意到“class_string”
的有参构造函数其实不安全的，因为存在隐式转换，正因为隐式转换的存在才让“test_ref_to_const(str);”有了建立临时对象的可能性

那么添上“explicit”后会怎么样呢？

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

**果然编译出错，那么可以看出“explicit”有防止建立临时对象的作用**，如果仍保持隐式转换的存在，即不增加“explicit”，
而是将函数的参数改为非常量引用，这就是大前年文章中提到的那样将会出现编译错误，算了代码不贴了，没有意义

**总结就是：如果使用常量引用，那么关闭隐式转换，避免产生临时对象而影响性能**