# <center>Personal Diary

本次实验要求使用重定向以及管道的方式来实现，但是重定向和管道的方法都会导致一个问题：只能使用重定向的内容或者管道的输入，因为这样的输入会带有 `EOF`，导致不能再通过控制台来进一步输入需要的数据，而我们这次需要实现的 `pdadd`, `pdlist`, `pdshow`, `pdremove` 其实都是需要额外的数据输入的，于是：

+ 对于 `pdlist`, `pdshow`, `pdremove`：我使用了**命令行参数**的方式来传递额外的参数，即**指定日期**数据，这样就是的这三个程序之间是可以通过文件重定向以及管道进行输入输出交互的；
+ 对于 `pdadd`：因为这个程序要增加一条日记，而一条日记包括了日期以及内容两部分，内容可能会非常复杂，用命令行参数来做显然不合适，所以我实现的 `pdadd` 是在程序内打开文件，通过控制台输入数据，最后写入文件；

+ [x] 所有的日期的输入格式都必须要满足 `xxxx-xx-xx`，月份以及日期必须要是两位数字。



## `pdadd`

`pdadd` 的实现和另外三个不一样，是在程序内使用 

1. `ifstream` 对象来打开文件，读入日记；
2. 直接在控制台输出提示信息，得到控制台输入；
3. `ofstream` 对象来将添加了的新日记写入到文件；

+ 编译命令如下：

  ```c++
  g++ -std=c++11 ./pdadd.cpp ./diary.cpp -o pdadd.exe
  ```

+ 测试 `pdadd.exe` ：

  ```c++
  pdadd.exe
  ```

  + 直接运行 `pdadd.exe`，然后根据提示信息进行日记的添加：


## `pdlist`

`pdlist` 与 `pdadd` 不一样：

1. 读入已有的日记采用的是文件重定向或者管道的方式；

2. `pdlist` 本身的参数需要通过命令行参数的方式传入，有下面两种格式参数：
   + `all`：表示直接列出所有的日记；
   + `part xxxx-xx-xx xxxx-xx-xx`：后面两个是用空格隔开的起始日期和结束日期；

+ 编译命令如下：

  ```c++
  g++ -std=c++11 ./pdlist.cpp ./diary.cpp -o pdlist.exe
  ```

+ 测试 `pdlist.exe`：

  + 重定向 + 命令行参数测试：

    1. 列出全部的日记：

       ```c++
       pdlist.exe all < ./test.txt
       ```

       + 结果是输出了原本日记文件中的所有日记，一共有五个日记，**且是排好序的**。

    2. 列出部分日记：

       ```c++
       pdlist.exe part 2020-01-01 2021-05-02 < ./test.txt
       ```

       + 结果是输出了在两个日期之间的日记，只有两个满足要求，**且是排好序的**。

  + 管道 + 命令行参数 ( `type` 输出 `test.txt` 内容作为 `pdlist.exe` 的输入 )：

    1. 列出全部日记：

       ```c++
       type test.txt | pdlist.exe all
       ```

       + 结果是输出了原本日记文件中的所有日记，一共有五个日记，**且是排好序的**。

    2. 列出部分日记：

       ```c++
       type test.txt | pdlist.exe part 2020-01-01 2021-05-02
       ```

       + 结果是输出了在两个日期之间的日记，只有两个满足要求，**且是排好序的**。



## `pdshow`

`pdshow` 和 `pdlist` 是基本一致的，可以采用文件重定向或者管道的方式读入原始文件内容，`pdshow` 本身的日期参数是通过命令行参数来传递的。

+ 编译命令如下：

  ```c++
  g++ -std=c++11 ./pdshow.cpp ./diary.cpp -o pdshow.exe
  ```

+ 测试 `pdshow.exe`：

  + 重定向 + 命令行参数：

    1. 要查询的日记存在：

       ```c++
       pdshow.exe 2021-05-07 < ./test.txt
       ```

       + 结果输出的是日期为 `2021-05-07` 那一天的日记。

    2. 要查询的文件不存在：

       ```c++
       pdshow.exe 2020-05-07 < ./test.txt
       ```

       + 结果输出：`There is no diary at this day!!!`

  + 管道 + 命令行参数：

    ```c++
    type test.txt | pdshow.exe 2021-05-07	// 和重定向第一个结果一样
    type test.txt | pdshow.exe 2020-05-07	// 和重定向第二个结果一样
    ```



## `pdremove`

`pdremove` 我实现了可以通过管道的方式**将 `pdlist` 的输出当作 `pdremove` 的输入**传递进来，然后通过命令行参数的方式传递进需要删除的日记的日期。

+ 编译命令如下：

  ```c++
  g++ -std=c++11 ./pdremove.cpp ./diary.cpp -o pdremove.exe
  ```

+ 测试 `pdremove.exe`：

  + 管道将 `pdlist.exe` 的输出作为 `pdremove` 的输入，命令行参数传日期：

    ```c++
    pdlist.exe all < ./test.txt | pdremove.exe 2020-01-12
    ```

    + 结果命令行输出 `Delete successfully!`，然后删除之后的内容被写入了 `test_pdremove_out.txt` 文件中；

  + 如果传递进去的日期没有对应的日记，那么命令行会输出 `Delete fails!`，原来的日记被写入 `test_pdremove_out.txt` 文件中；

