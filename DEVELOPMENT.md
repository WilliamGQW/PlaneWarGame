1. The first problem I had during the process is that the compiler kept saying 'cannot load file from...'. At very first, I created a new folder called 'data' which is inside the src folder to store the image and the music I will be using. But it failed. Then I tried to move the 'data' file outside the src folder. But it still failed. In the end, I firgured out this problem by putting all these files under the 'data' folder under the 'data' in 'bin'. 

2. The second problem I came across is that when I tried to display some messages at the beginning or the end of the game, I wanted to use special front instead of the default one. Afterwards, I found something called 'ofTrueTypeFront' in openframeworks. I used this feature to load a much cooler front into my game.

3. I found that if I load the background music in the setUp() method, the bgm will only be played once. And I fixed this problem by moving `game_music.play();` to the mousePressed method, so that the bgm will keep playing as long as the game is on-going.

4. I used a feature of Windows API to keep track of the mouse cursor. I learned how to use this feature from this [website](http://www.cplusplus.com/forum/general/111898/) 

5. One problem I often encountered with in the process was that it was extremely easy to forget to modify the game status. It took my a lot of trouble to debug this problem. And at first, I used `flag` and `flag2` to represent the game status, which are confusing readers. So, later, I changed them to boolean variables `easyLevelPassed` and `needUpdate`. 

6. When I was dealing with generating enemy planes, I found it was difficult control the generating speed. So I created a timer `iEnemySpawnTimer` to solve this problem. I tried many sets of numbers and found out a appropriate rate. So I set a `ENEMY_SPEED-CONTROLLER` and a `BOSS_SPEED_CONTROLLER` to control the rate of generating enemies. The user can later change these constant int to modify how the game looks like.

7. Inside the game, there should be a reasonable collision area for different objects. At first, I did not consider this. So, when my hero plane have a collision with an enemy (only collide at the margin though), it does not crash. Therefore, to solve this problem and make the game more reasonable, I build a helper function `isInclude()`. Inside this function, I set a reasonable collision area.

8. After first week's work, my code was unorganized since I put almost everything inside the `draw()` function. The compiler accpet this, but in order to have a better code style, I split my code into different class, such as `Bullet`, `Enemy`. So that I could just call these functions in these classes in the `draw() `function in `ofApp.cpp`.

9. And also, when I read my code again after finishing most of the work, I found some loops are too long to read and understand. Therefore, I split some of them into different helper functions and add more comments to explain what I was doing.

10. And, as my moderator suggested, I still had problem with variable naming. So I spent some time to go over all my code and changed some variables to better names.
