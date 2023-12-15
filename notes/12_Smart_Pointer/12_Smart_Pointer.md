# <center>Smart Pointer

+ Class `UCObject` holds the count —— 最内部的那个类，包含了引用计数：
  + "Use-counted object", `UCPointer` is a smart pointer to a `UCObject`
+ Class `UCPointer` A smart pointer is an object defined by a class —— 这个类的对象是一个指针，引用计数只能放在被指的 `UCObject` 中，而不能放在 `UCPoniter` 之中，因为这样更新会很麻烦：
  + Implemented **using a template**, Overloads `operator->` and unary `operator*`

## 1 Reference Counts in Action

+ Each sharable object has a counter, and its initial value is $0$;

+ Whenever a pointer is assigned:

  ```c++
  p = q;		// both p and q are smart pointer
  ```

  + Have to do the following things:

    ```c++
    p->decrement();		// p's count will decrease
    p = q;
    q->increment();		// q/p's count will increase
    ```

### 1.1 The four classes involved

1. `String` 是一个最外面的给用户使用的类，这个类里面有一个 `UCPointer`;
2. `UCPointer` 是一个模板智能指针类，它里面有一个

