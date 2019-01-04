#pragma once
#include "ofMain.h"

class Bullet
{
public:
    void draw(); // the function to draw a signle bullet object
    void addSecondBullet(); //upgrade firepower by adding one more queue of bullets
    void addThirdBullet(); // upgrade firepower by adding another quue of bullets
    int x;  //x position of the bullet
    int y;  //y position of the bullet
    bool isExist = false; // set existence to false
    ofImage  bullet1;  // load the image of bullet into the game
};
