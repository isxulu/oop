# <center>Adventure

+ For this homework, I set **eight** different kind of rooms, and **total number** of rooms is **ten**, and the castle has **three floors**.

+ The map is pre-designed by me and will not change, but the position of the monster and princess are randomly chosen, you may find this if you run the `main.exe` a few times.

+ You can compile my project by:

  ```
  g++ .\main.cpp .\game.cpp .\room.cpp -o main.exe
  ```

  And run the executable file by:

  ```
  .\main.exe
  ```

  + Once you run the game, you will see:

    ```c++
    Get ready. The rescue operation is about to begin!
    Welcome to the lobby. There are 1 exits: west.    
    Enter you command: 
    ```

    + The <font color=red>**standard input**</font> is simply the direction name: **`up`, `down`, `south`, `north`, `west`, `east`.**

    + If you type the invalid direction or direction that current room can not reach, my program will output this prompt message:

      ```c++
      Please enter valid direction: 
      ```

      which ask you to input a valid direction again.

    + If the current round ends, then it will output this prompt message:

      ```c++
      Enter 'c' to continue or 'q' to exit:
      ```

      