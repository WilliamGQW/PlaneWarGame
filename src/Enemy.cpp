#include "Enemy.h"

/**
* The function to draw enemy objects.
* Since I need to load different images when I want to draw death animation,
* this function take a parameter.
*/
void Enemy::draw(ofImage image) {
    image.draw(x, y);
}

