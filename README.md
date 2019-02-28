# CS 126 FinalProject: Plane War
# Demo Link: [https://www.youtube.com/watch?v=dMNQnxF3fbs&feature=youtu.be](https://www.youtube.com/watch?v=dMNQnxF3fbs&feature=youtu.be)

## Tech/framework used:
[openframeworks](http://openframeworks.cc/)

## Description of the Project:
This Plane War project is a 2D shooting game. The logic and rule for the game is straight forward. The user can use mouse to control a hero plane to shoot down enemy planes. Boss will also be automatically generated based on the score received. 
#### Interesting features
1. The game have two different levels: easy level and hard level. Certain points is required to enter the hard level;
2. The user can press "p" to pause the game and press again to continue;
3. The real-time score will be printed at the up-left corner on the screen;
4. The fire power will be upgraded if the user earn enough points;
5. Cool background music and sound effect are included inside this game.

## How to build? 
1. Firstly, since this game used a feature (mouse input) in [WindowsAPI](https://msdn.microsoft.com/en-us/library/windows/desktop/ff818516(v=vs.85).aspx) which is included in `windows.h`, the user have to open the game by using an IDE which supports Windows system. I built this game on Visual Studio 2017 with openframeworks plugin installed.

2. After generating the game project by using the projectGenerator provided by openframework, the user can simply copy the source files into the project. And then click the run button, the game window should automatically be generated.

## How to use and how to play? (Game Instructions)
1. After the game window shows up, the user can see the message "PLANE WAR, CLICK TO START" on the screen. So, just follow the instruction and click the mouse once.;
2. Now, after the first step, the game should start. Then the user will be required to click again to locate the hero plane;
3. Now, just control the hero plane by using the mouse. Bullet will be automatically generated in the process, so just shoot the enemies.
4. Be CAREFUL. You will lose if you crash into an enemy plane. If you do, game over and the final score will be printed;
5. The game has two different levels: a easy one and a hard one. The user have to earn enough points to enter the hard level. If the user    receive enough points to enter the hard level, a message "Click to Hard Level" will be printed on the screen. So the user has to click    again to enter next level. In the easy level, the speed of enemies will be relatively slow. In the hard level, the speed of
   enemies will be much faster;
6. Since almost all the parameteres can be changed to modify the game, so the user can make a little change to the provided source file;
   For example, the user can change the points required to win the game or the points required to enter the hard level;
7. During the game process, if the user has won enough points, the fire power will be automatically upgraded.
8. At the up left corner, the real-time score will be printed during the game process.
9. The points to win the game has been set in the game, so the user has to reach that point to win the game. Also, the user can change the    point as their wish.

## Description of the files:
1. `Bullet.cpp` and `Bullet.h` implement the Bullet class, they contain a draw function for bullets and two functions to upgrade firepower
2. `Enemy.cpp` and `Enemy.h` implement the Enemy class (including bosses), they contain a draw funtion for enemies (based on different images).
3. `ofApp.cpp` and `ofApp.h` contains the most important part. I set up the game project inside these two files.
4. `main.cpp` is the main entrance and set up the game window.
