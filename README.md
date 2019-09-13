# 8GEI311 Lab 1
By Jean-Michel Plourde and Manon Michelet.

Video player that implements the Microsoft DirectShow library  and that can be  controlled with the keyboard.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
* A Windows environment
* The Microsoft DirectShow library installed
* Visual Studio

### Installing
- Clone this repo with HTTP or SSH
```
git clone git@github.com:giant995/6GEI311_Lab_1.git
```
* Open the project folder in visual studio 
* Right-click on the project name in the solution explorer, in _properties_ > _Linker_ > _Input_ > _Additionnal dependencies_ 
    * add _Strmiids.lib_ to the line
* At line 31 in **MediaPlayer.cpp**, change the parameter of the function *RenderFile* that is the string path, for the complete path of a video you wish to play.
* Run **main.cpp** by pressing F5 or Ctrl+F5 to run without debugging.

## Controlling the video player
You have several functionalities that can be used by pressing the corresponding keys.

* **P** : Play or pause accordingly to the actual state of the video. It will pause if it's playing, and vice versa 
* **A** : Fast forward (x2). Press again to go back to the normal rate.
* **R** : Rewinds the video to the beginning with respect to the current playing state. If the video was playing, the video rewinds and automatically plays. If paused, the video will not play until you press P again.
* **Q** : Quit the program and the video

## How does it work
The program check for a pressed key every 1  millisecond. If a key is pressed,  it is read and the correct functionnality is called, otherwise another 1ms of video is played with respect to the plyaing state.
