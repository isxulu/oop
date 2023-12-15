### About compile and run the program

You can compile the sources by the command below:

```c++
g++ -std=c++11 main.cpp student.cpp -o main.exe
```

Then you can run the executable file by:

```c++
./main.exe < sample1.txt	// or sample2, 3...
```

 I provide 3 samples, you can run the program to check the output.



### About the program itself

There is something you need to know:

+ The program I wrote accept input in the following type:

  ```
  [stuID stuName courseName1 courseScore1 ...]
  ```

  + Each part is separated by a space `' '`;
  + There is **no need** to input a `int` type number that tell the program how many students will be input.

+ For simplification, I use a single line of `#` to represent the end of input.

+ For output format, if one student does not take a course, then I use **a `*` in the position of the score of that course** to represent that this student **does not take that course.**

