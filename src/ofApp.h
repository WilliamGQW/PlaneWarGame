#pragma once

#include "ofMain.h"
#include "Bullet.h"
#include "Enemy.h"
#include <string>
#include <sstream>

class ofApp : public ofBaseApp {

public:
	void setup(); // Function used for one time setup

	// Main event loop functions called on every frame
	void update();
	void draw();

	// Event driven functions, called on appropriate user action
	void keyPressed(int key);
	void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);

	// helper functions
	void draw_scores(); //draw the real-time score on the up left corner on the screen
	void detect_enemy_hero_collision(); // detect the collision between enemies and the hero
	void detect_bullet_enemey_collision(); // detect the collsion between bullets and enemies
	void setEnemySpeed(); //set the speed of enemies (including bosses)
	void updateEnemyPosition(); // update the postion of enemies
	void updateBossPosition(); // update the position of bosses
	void drawHero(); //draw hero
	void drawBullets(); //draw bullets
	void drawEnemy(); //draw enemies
	void drawBoss(); // draw bosses
	bool isInclude(Enemy enemy, int x, int y); // a helper function to tell whether there is a collision


        // Load auido into the game
	// ofSoundPlayer handles simple playback of sound files, with controls
        // for volume, pan, speed, seeking and multiplay.
        // Refer to http://openframeworks.cc/documentation/sound/ofSoundPlayer/
	ofSoundPlayer  beats;
	ofSoundPlayer  synth;
	ofSoundPlayer  vocals;
	ofSoundPlayer  use_bomb;
	ofSoundPlayer  achievement;
	ofSoundPlayer  beat;
	ofSoundPlayer  bullet;
	ofSoundPlayer  button;
	ofSoundPlayer  enemy0_down;
	ofSoundPlayer  big_spaceship_flying;
	ofSoundPlayer  enemy1_down;
	ofSoundPlayer  enemy2_down;
	ofSoundPlayer  game_music;
	ofSoundPlayer  game_over;
	ofSoundPlayer  get_bomb;
	ofSoundPlayer  get_double_laser;
	ofSoundPlayer  out_prop;

	// Load images into the game
	// The ofImage is a useful object for loading, saving and drawing images in openFrameworks.
	// Refer to http://openframeworks.cc/documentation/graphics/ofImage/
	ofImage  background;
	ofImage  bullet1;
	ofImage  enemy0;
	ofImage  enemy1;
	ofImage  enemy2;
	ofImage  enemy3;
	ofImage  enemy4;
	ofImage  enemyBoss3;
	ofImage  enemyBoss4;
	ofImage  enemyBoss5;
	ofImage  game_loading;
	ofImage  hero1;
	ofImage  hero2;
	ofImage  enemyBoss1;
	ofImage  enemyBoss2;

	int count = 0; // a temperaory helper int to update mouseClickCount
	int mouseClickCount; // count how many times has the mouse been clicked
	int iScore = 0; //the score
	int maxScore = 0;
	int hitCount = 0; //count how many times the enemy has been hit

	//initialize the position of the hero plane
	int iPlayerPositionX = 190;
	int iPlayerPositionY = 600;

	// timers are used to acheive smooth framerate
	int iBulletTimer = 0;
	int iHeroTimer = 0;
	int iHeroIndex = 0;
	int iEnemySpawnTimer = 0;

	// the speed of enemy and boss
	int speed_enemy;
	int speed_boss;

	bool easyLevelPassed = false;
	bool needUpdate = false;
	bool enemyIsMoving = false;
	bool iLose = false;

	// load special font into the game
	//The ofTrueTypeFont class provides an interface to load fonts into openFrameworks.
	//Refer to http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/
	ofTrueTypeFont font;

	const int EASY_LEVEL_POINTS = 50;
	const int HARD_LEVEL_POINTS = 100; // win if you receive HARD_LEVEL_POINTS points
	const int BOSS_POINT = 5; // set the bonus score of the boss
	const int BOSS_HP = 20; // set the HP of the boss
	const int ENEMY_POINT = 1; // set the bonus score of the enemy
	const int ENEMY_SPEED_CONTROLLER = 10; // a controller to change the speed of the enemy
	const int BOSS_SPEED_CONTROLLER = 3; // a controller to change the speed of the boss
	const int BULLET_NUMBER_CONTROLLER = 10; // a controller to change the number of bullets
	const int POINTS_TO_UPGRADE_BULLET = 30; // the points required for the first firepower upgrade
	const int POINTS_TO_MAX_BULLET = 60; // the points required for the second firepower upgrade
	const static int BULLET_NUMBER = 20; // set the number of bullet
	const static int MAXIMUM_BOSS = 5; // set the number of boss
	const static int MAXIMUM_ENEMY = 3; // set the number of enmey
	const static int ENEMY_INITIAL_SPEED = 5; //set the speed of the enemy
	const static int BOSS_INITIAL_SPEED = 2; //set the speed of the boss
	const static int POINTS_TO_GENERATE_BOSS = 20;  // everytime you get 20 points, a boss will be generated

        //Keep track of the mouse cursor (using Windows C++)
        //Refer to this web: http://www.cplusplus.com/forum/general/111898/
	POINT pNowMousePoint;
	POINT pPreMousePoint;

	//create array for bullet, boss, and enemies
	Bullet bulletArray[BULLET_NUMBER]; // an array of objects that represent the bullets
	Enemy boss[MAXIMUM_BOSS]; // an array of objects represents the bosses
	Enemy enemyArray[MAXIMUM_ENEMY]; // an array of objects represents the enemies
	
    /**
     * Build a toString() method.
     * it will be used to convert the score to string, thus the score can be
     * printed.
     *
     * @tparam T
     * @param t
     * @return
     */
    template<typename T> string toString(const T& t) {
             ostringstream oss;
             oss << t;
             return oss.str();
     }
	
};
