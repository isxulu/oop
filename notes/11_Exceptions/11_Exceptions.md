# <center>Exceptions

+ The significant benefit of exceptions is that they **clean up error handling code**.
+ It separates the code that describes what you want to do from the code that is executed.

## 1 How to raise an exception

```c++
template <class T>
T& Vector<T>::operator[](int indx) {
    if (indx < 0 || indx >= m_size) {
        // VectorIndexError e(indx);
        // throw e;
        throw VectorIndexError(indx);	// !!! we throw a VectorIndexError object
    }
    return m_elements[indx];
}
```

+ The thing that we `throw` should be <font color=red>**a class object**</font> —— 我们 `throw` 出来的需要是我们定义的对象；

  ```c++
  class VectorIndexError {
  public:
      VectorIndexError(int v) : m_badValue(v) { }
      ~VectorIndexError() { }
      void diagnostic() {
          cerr << "index " << m_ badValue
          << "out of range!"; }
  private:
  	int m_badValue;
  };
  ```



## 2 What does caller do

1. Doesn't care, code never even suspects a problem:

   ```c++
   int func() {
       Vector<int> v(12);
       v[3] = 5;
       int i = v[42]; // out of range
       // control never gets here!
       return i * 5;
   }
   -----------------------------------------------------------------------------------
   terminate called after throwing an instance of 'VIE'
   ```

   + 输出一句宏定义的语句，然后程序直接终止执行；

2. Cares deeply, <font color=red size=5>**`try, catch`**</font> keywords:

   ```c++
   void outer() {
   	try {
       	func(); func2();
       } catch (VectorIndexError& e) {
       	e.diagnostic();
       	// This exception does not propagate
       }
       cout << "Control is here after exception";
   }
   ----------------------------------------------------------------------------------
   things that e.diagnostic() will output
   Control is here after exception
   ```

   1. 首先程序顺序执行 `try{}` 中的语句块，执行到 `func()` 的时候发现有错误，并 `throw` 了一个 `VectorIndexError` 对象；
   2. 然后 `catch (VectorIndexError& e)` 捕捉到了 `throw` 的 `VectorIndexError` 对象，开始执行 `catch{}` 内部的语句；
   3. 执行完 `catch{}` 中的语句后，程序不会停止而是继续执行 `catch{}` 块下面的指令。

3. Mildly interested:

   ```c++
   void outer2() {
       String err("exception caught");
       try {
           func();
       } catch (VectorIndexError) {
           cout << err;
           throw; // propagate the exception
       }
   }
   ```

4. Doesn’t care about the particulars:

   ```c++
   void outer3() {
       try {
       	outer2();
       } catch (...) {
           // ... catches ALL exceptions!
           cout << "The exception stops here!";
       }
   }
   ```

   + `catch(...)` 是关键字，<font color=red>**`...` 表示会 `catch` 所有的 `throw` 对象**</font>，并执行 `catch{}` 中的语句。



## 3 Check `throw` Table

+ 在 `throw` 的一直往外执行的过程中，如果是像 `for, if` 在类的语句块，那这整个语句块就相当于是一个大的 `throw` 语句，并且在**这个语句块中的局部对象会被析构掉**；
+ 如果到了 `try{}` 语句块，那么会尝试去匹配一个 `catch{}` 语句块，如果匹配上了就执行 `catch{}` 中的语句块，并且之后的语句，如果没匹配上就直接终止程序；
+ [x] 注意 `thrwo` 出来的这个对象在过程中是不会被析构的，即使它外面的局部变量都被析构了，栈指针都已经到很上面了，这个 `throw` 对象还是在栈下面没有被析构。

## 4 Review

### 4.1 throw

**Throw** statement **raises the exception**;

+ Control propagates back to first handler for that exception;
  + Propagation follows the `call` chain;
  + Objects on **stack** are properly destroyed.

1. `throw exp;`：throw value for matching;

2. `throw;`：re-raises the exception being handled.

### 4.2 try block:

```c++
try { ... }
catch ...
catch ...
```

+ Establishes any number of handlers, and not needed if you don’t use any handlers.

### 4.3 Summary

Exceptions provide the mechanism:

+ Propagated dynamically;
+ Objects on stack destroyed properly;
+ Act to terminate the problematic function;



## 5 Exception handlers

Select exception by type, and <font color=blue>**can re-raise exceptions**</font>:

+ Two forms:

  ```c++
  catch (SomeType v) {	// handler code
  }
  catch (...) {			// handler code
  }
  ```

+ Can have any number of handlers, handlers are checked <font color=red>**in order(由窄到宽) of appearance**</font>:

  1. Check for **exact match**;
  2. Apply **base class conversions**;
  3. Ellipses **`(...)`** match all —— **这个东西必须放在最后**；

+ Inheritance can be used to structure exceptions:

  ```c++
  class MathErr {
      ...
      virtual void diagnostic();
  };
  class OverflowErr : public MathErr { ... }
  class UnderflowErr : public MathErr { ... }
  class ZeroDivideErr : public MathErr { ... }
  
  try {
      // code to exercise math options
      throw UnderFlowErr();
  } catch (ZeroDivideErr& e) {
  	// handle zero divide case
  } catch (MathErr& e) {
  	// handle other math errors
  } catch (...) {
  	// any other exceptions
  }
  ```

  + `...` 必须放在所有 `catch` 的最后一个，并且 `catch` 父类要写在 `catch` 子类的前面；



## 6 Exception Specifications

Declare which exceptions function might raise:

```c++
void abc(int a) throw(MathErr) {
	...
}
```

+ `throw(MathErr)` 表示的是这个函数可能抛出来的异常，<font color=red>**注意两者之间不能有 `:`**</font>,
  + Not checked at compile time;
  + At runtime, if an exception <font color=blue>**not in the list**</font> propagates out, the <font color=blue>**`unexpected` exception**</font> is raised.

+ 如果没有指明的话，就是抛任何异常都可以；

<center><font color=red size=6>Exceptions should indicate errors</font></center>


