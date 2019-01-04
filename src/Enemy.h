#pragma once
#include "ofMain.h"

class Enemy
{
public:
    void draw(ofImage image); //the function to draw enemies
    ofImage  enemyBoss1; //load the image of boss
    ofImage enemy1; // load the image of enemy
    int x; //x position
    int y; //y position
    bool isExist = false;
    bool isDie = false;
    int iDieAnimationIndex = 0;
    int iDieAnimationTimer = 0;
    int dieTime = 0;
};
