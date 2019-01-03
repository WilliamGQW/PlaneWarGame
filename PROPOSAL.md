# Project Proposal
## The project I plan to do is a **Plane War**  game, which will be a openFrameworks application as required. 

## Interface
1.  Users can click key "P" to pause the game and click "P" again to continue the game;
2.  When the game is in process, it should print the real-time score on the screen;
4.  Background music and background picture will be implemented.

## Game Design
**Basic Rule:** When the game begins, one fighter plane will be created . The plane will keep shooting out a queue of bullet. Users have to use mouse(touch borad) to control the plane and shoot down enemies. Defeating enemies will give back corresponding points and upgrade the fire power of the plane. However, when the fighter crashes into an enemy plane, it will crash too. The maximum HP of the fighter is 5 (may be I will adjust this number later).

- Hero Plane:
 1.  The Hero plane can be controlled by using mouse(or touch board);
 2.  When the hero plane crash into an enemy plane, game over;
 3. The Hero plane should keep shooting during the entire game. At the beginning of the game, it should shoot out a single queue of bullets. After winning enough points, the plane will be upgraded.  Each time it levels up, the number of queue of the bullets will increase by one. To make the game more reasonable, the maximum queues of the bullets is around.

- Enemy Plane (Two types: Soldiers and Bosses):
 1.  Both soldiers and bosses have their own fixed HP and experience points. For sure, bosses should have much more HP points and deserve      experience points;
 2.  Soldiers and bosses have different appearance and size;
 3.  Enemy planes will keep showing up. 

## Library
The library I will be using for implementing this game is [Windows API](https://msdn.microsoft.com/en-us/library/windows/desktop/ff818516(v=vs.85).aspx). 

1. Input and Output. The Windows API offers programmers with a nice feature in [Mouse Input](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645533(v=vs.85).aspx). I am planning tp apply this feature in order to control the Hero plane by using mouse. 

2. For the image and audio part, I will explore how to implement them by using features provided by Openframeworks.
