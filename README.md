# 8GEI311 Lab 1
Program to play videos with Microsoft DirectShow and to control it thanks to keypad.

# Running the program
First of all, you can change the path to the video in line 31 of **MediaPlayer.cpp**, as parameter of the function *RenderFile*.
Then, you just have to run the **main.cpp** program with F5.

# How to use the program
You have several functionalities. Just press the corresponding key to use it.

- *P* : Play or pause accordingly to the actual state of the video. It will pause if it's playing, and vice versa 
- *A* : Fast forward (x2). Press it again if you want back the original rate
- *R* : Come back to the beginning of the video with the same current state. If the video was playing, it will play back the video from the beginning. But if it was in pause, the video won't play until you press P
- *Q* : Quit the program and the video

# How does it work
The program just check if you press a key every millisecond. If you do, it will read it and do what it is supposed to, but if you don't, program display 1ms of the video (only if the state is "play", otherwise it does nothing)
