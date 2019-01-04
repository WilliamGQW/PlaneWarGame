#include "Bullet.h"

/**
* Load the image of bullet and draw a signle bullet.
*/
void Bullet::draw() {
    bullet1.load("image/bullet1.bmp");
    bullet1.draw(x, y);
}

/**
*upgrade firepower by adding one more queue of bullets
*/
void Bullet::addSecondBullet(){
    bullet1.load("image/bullet1.bmp");
    bullet1.draw(x + 10, y);
}

/**
*upgrade firepower by adding another queue of bullets
*/
void Bullet::addThirdBullet(){
    bullet1.load("image/bullet1.bmp");
    bullet1.draw(x + 20, y);
}
