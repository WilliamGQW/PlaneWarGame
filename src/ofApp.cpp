#include "ofApp.h"

//--------------------------------------------------------------
// Setup method
void ofApp::setup() {

	//set up the title of the window
	// Refer from the snakegame project
	ofSetWindowTitle("PlaneWar");
	srand(static_cast<unsigned>(time(0))); // Seed random with current time

	mouseClickCount = 0; // set the mouse click count to zero at first

    //load sound into the game
	synth.load("sounds/synth.wav");
	beats.load("sounds/1085.mp3");
	vocals.load("sounds/Violet.mp3");
	use_bomb.load("sounds/use_bomb.wav");
	achievement.load("sounds/achievement.wav");
	beat.load("sounds/beat.wav");
	bullet.load("sounds/bullet.wav");
	button.load("sounds/button.wav");
	enemy0_down.load("sounds/enemy0_down.wav");
	enemy1_down.load("sounds/enemy1_down.wav");
	enemy2_down.load("sounds/enemy2_down.wav");
	game_music.load("sounds/game_music.wav");
	game_over.load("sounds/game_over.wav");

	//load images into the game
	background.load("image/background.bmp");
	bullet1.load("image/bullet1.bmp");
	enemy0.load("image/enemy0.bmp");
	enemy1.load("image/enemy1.bmp");
	enemy2.load("image/enemy2.bmp");
	enemy3.load("image/enemy3.bmp");
	enemy4.load("image/enemy4.bmp");
	enemyBoss3.load("image/enemyBoss3.bmp");
	enemyBoss4.load("image/enemyBoss4.bmp");
	enemyBoss5.load("image/enemyBoss5.bmp");
	game_loading.load("image/game_loading.bmp");
	hero1.load("image/hero1.bmp");
	hero2.load("image/hero2.bmp");
	enemyBoss1.load("image/enemyBoss1.bmp");
	enemyBoss2.load("image/enemyBoss2.bmp");

	//Sets the volume of the sound. 0.0 - 1.0 range. 0.0 is silent and 1.0 is full volume.
	//Refer to http://openframeworks.cc/documentation/sound/ofSoundPlayer/#show_setVolume
	synth.setVolume(0.75f);
	beats.setVolume(0.75f);
	vocals.setVolume(0.5f);

	//Loads the font specified by filename, allows you to control size, aliasing, and other parameters.
	//Refer to http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/#show_load
	font.load("Sudbury_Basin_3D.ttf", 32);
	beats.setMultiPlay(false);
	vocals.setMultiPlay(true); 
}

//--------------------------------------------------------------
/**
*Update function called before every draw
*1. if the game has entered into the hard level, increase the speed of enemies
*2. keep modifying the position of the enemies (including bosses), so that the enemies won't show up 
*   at the same place; thus more reasonable.
*3. update the soundplayer, etc
*/
void ofApp::update() {

	ofBackground(255, 255, 255); //set the backgroung color

	if (!needUpdate) {
		// Call in my app's update() to update FMOD-based sound player
		// Refer to http://openframeworks.cc/documentation/sound/ofSoundPlayer/#show_ofSoundUpdate
		ofSoundUpdate();

		//set the timers
		iBulletTimer++;
		iHeroTimer++;
		iEnemySpawnTimer++;

		setEnemySpeed(); //SET the speed of the enemy object (including boss)

		updateEnemyPosition(); //update the position of enemies

		updateBossPosition(); //update the position of bosses
	}
}

//--------------------------------------------------------------
/** Main event loop function
* 1. IF the game is not started (mouseClickCount == 0), draw the welcome interface;
* 2. IF the game is in process, draw the hero, enemies and bosses;
* 3. ALSO draw the death animation of enemies and bosses when they are being hit;
* 4. THE game have two levels: the first one is in easy mode, and there is also a hard level, in which
*    the speed od enemies will be faster;
* 5. KEEP track the game status: if the game is in progess or not; if the game is in the easy level or the hard level;
* 6. Instructions will be printed on the screen in different cases.
*/
void ofApp::draw() {

	// draw the background colors:
	ofSetColor(255);
	background.draw(0, 0);
	
	draw_scores(); //print the current score at the up left corner

	if (mouseClickCount == 0) { // if the game is not started yet
		if (iScore >= HARD_LEVEL_POINTS) {
			// win if you receive HARD_LEVEL_POINTS points
			// RESET the score and mouseclickcount to zero when the user win the game
			iScore = 0;
			mouseClickCount = 0;
		}

		if (synth.isPlaying()) {
			ofSetHexColor(0xFF0000);
		}
		else {
			ofSetHexColor(0x000000);
		}

		//set up the interface
		//print message by using special font
		//Reder to http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/#show_drawString for more info
		font.drawString("Plane War", 50, ofGetHeight() / 3);
		string tempStr = "click to start";
		font.drawString(tempStr, 50, ofGetHeight() / 2);
	}

	else { //game start!!!
		if (!easyLevelPassed) {

			drawHero();//draw the hero
			drawBullets();//draw bullets	
			drawEnemy();// Draw enemies
			drawBoss();//draw boss

			detect_bullet_enemey_collision(); //detect collision between bullets and enemies
			detect_enemy_hero_collision(); //detect collision between enmeies and the hero

			// print the message when the user win the game
			if (iScore >= HARD_LEVEL_POINTS) {
				background.draw(0, 0);
				font.drawString("You Win !", 100, ofGetHeight() / 3);
				font.drawString("Click to Restart!", 30, ofGetHeight() / 2 );
				needUpdate = true;
			}

			//the user have enough points to enter the hard level
			if (iScore >= EASY_LEVEL_POINTS && iScore % EASY_LEVEL_POINTS == 0 && iScore < HARD_LEVEL_POINTS) {
				easyLevelPassed = true;
				needUpdate = true;
			}

			//print the message when the user lose the game
			if (iLose) {
				background.draw(0, 0);
				font.drawString("You Lose !", 100, ofGetHeight() / 2);
				font.drawString("Score: " + toString(iScore), 120, ofGetHeight() / 2 - 100);
				font.drawString("Click to Restart ", 30, ofGetHeight() / 3);
				needUpdate = true;
			}
		}
		else {
			//Congrats! Enter the hard level
			//print the message when the user have enough points to enter the hard level
			//if (synth.isPlaying()) ofSetHexColor(0xFF0000);
			//else ofSetHexColor(0x000000);
			ofSetHexColor(0x000000);
			font.drawString("Click to", 50, ofGetHeight() / 3);
			font.drawString("Hard Level", 50, ofGetHeight() / 2 - 100);
			needUpdate = true;

		}
	}
}

/**----------------------------------------------------------------------------------------------
* The isInclude() function is used to tell if there is a collision between objects
* Return true if there is a collision, otherwise return false.
* @param enemy
* @param x
* @param y
* @return
*/
bool ofApp::isInclude(Enemy enemy, int x, int y) {
	if ((x > enemy.x) && (y > enemy.y) && (x < enemy.x + 51) && (y < enemy.y + 39))
	{
		return true;
	}
	return false;
}

/**----------------------------------------------------------------------------------------------
* Add the PAUSE key: Press 'P' to pause, press again to continue.
* @param key
*/
void ofApp::keyPressed(int key) {
	if (key == 'p') {
		if (!needUpdate) {
			needUpdate = true;
		}
		else {
			needUpdate = false;
		}
	}
}


/**-----------------------------------------------------------------------------------------------
* This function gets whenever the mouse moves. You receive the x and y coordinates of the mouse.
* Refer to this web: http://www.cplusplus.com/forum/general/111898/
* Clarify the logic of the mouseClickCount: After openning the game window,
* the user is required to click once to start the game first.
* Then the user is requied to click again to locate the position of the hero plane,
* so at this time mouseClickCount = 2.
* Then 
* @param x
* @param y
*/
void ofApp::mouseMoved(int x, int y) {
	pNowMousePoint.x = x;
	pNowMousePoint.y = y;
	if (mouseClickCount == 2) {
		int xOffset = pNowMousePoint.x - pPreMousePoint.x;
		int yOffset = pNowMousePoint.y - pPreMousePoint.y;
		iPlayerPositionX += xOffset;
		iPlayerPositionY += yOffset;
		pPreMousePoint = pNowMousePoint;
		if (iPlayerPositionX < 0)
		{
			iPlayerPositionX = 0;
		}
		if (iPlayerPositionX > ofGetWidth() - 100)
		{
			iPlayerPositionX = ofGetWidth() - 100;
		}
		if (iPlayerPositionY < 0)
		{
			iPlayerPositionY = 0;
		}
		if (iPlayerPositionY > ofGetHeight() - 124)
		{
			iPlayerPositionY = ofGetHeight() - 124;
		}
	}
}

/**---------------------------------------------------------------------------------------------
* This function gets called when the mouse is pushed down.
* Inside this function, I also update the game status based on the mouseClickCount.
* Refer to: http://openframeworks.cc/documentation/application/ofBaseApp/#show_mousePressed
* @param x
* @param y
* @param button
*/
void ofApp::mousePressed(int x, int y, int button) {
	int iHeroIndex = 0;
	int iHeroTimer = 0;
	game_music.play();

	if (y < ofGetHeight() - 50) {
		mouseClickCount = 1;
		count++;
	}

	if (count > 1) {
		mouseClickCount = 2;
		pPreMousePoint.x = x;
		pPreMousePoint.y = y;
	}

	if (iScore >= HARD_LEVEL_POINTS) {
		iScore = 0;
		mouseClickCount = 0;
	}

	if (easyLevelPassed) {
		iScore++;
		easyLevelPassed = false;
		needUpdate = false;
	}

	if (needUpdate) {
		needUpdate = false;
	}

	if (iLose) {
		iLose = false;
		iScore = 0;
		mouseClickCount = 0;
	}
}

/**-------------------------------------------------------------------------------------
* This function will print the real-time score at the up left corner on the screen.
*/
void ofApp::draw_scores() {
	font.drawString(toString(iScore), 50, 50);
}

/**--------------------------------------------------------------------------------------
* This function is used to detect collision between enemies and the hero.
* Three bool variables are used to set the collison area between enemies and the hero
*/
void ofApp::detect_enemy_hero_collision() {
	for (int i = 0; i < MAXIMUM_ENEMY; i++)
	{
		if (enemyArray[i].isExist && !enemyArray[i].isDie) {
			//set a resonable collision area
			bool isCenterInclude = isInclude(enemyArray[i], iPlayerPositionX + 50, iPlayerPositionY);
			bool isLeftInclude = isInclude(enemyArray[i], iPlayerPositionX - 10, iPlayerPositionY + 84);
			bool isRightInclude = isInclude(enemyArray[i], iPlayerPositionX + 90, iPlayerPositionY + 84);
			if (isCenterInclude || isLeftInclude || isRightInclude)
			{
				game_over.play(); // play the game over audio
				iLose = true;
				break;
			}
		}
	}
}

/**---------------------------------------------------------------------------------------
* This function is used to detect collision between enemies and bullets.
*/
void ofApp::detect_bullet_enemey_collision() {
	for (int i = 0; i < MAXIMUM_ENEMY; i++)
	{
		if (enemyArray[i].isExist == true && enemyArray[i].isDie == false)
		{
			for (int j = 0; j < BULLET_NUMBER; j++)
			{
				if (bulletArray[j].isExist) {
					if (isInclude(enemyArray[i], bulletArray[j].x + 4, bulletArray[j].y + 10))
					{
						bulletArray[j].isExist = false;  //delete the bullets that hit the enemies
						enemyArray[i].isDie = true;

						//Play the audio effect when an enemy crashes
						iScore += ENEMY_POINT;
						if (maxScore < iScore)
							maxScore++;
						enemy0_down.play();
						break;
					}
				}
			}
		}
	}
}

/**--------------------------------------------------------------------------
* A helper function to set the speed of the enemies and bosses
*/
void ofApp::setEnemySpeed() {
	//if the score is over EASY_LEVEL_POINTS, increase the spead of enemies.
	if (iScore > EASY_LEVEL_POINTS) {
		speed_enemy = ENEMY_INITIAL_SPEED * 2;
		speed_boss = BOSS_INITIAL_SPEED * 2 ;
	}
	else { //otherwis, set the normal spead
		speed_enemy = ENEMY_INITIAL_SPEED;
		speed_boss = BOSS_INITIAL_SPEED;
	}
}

/**--------------------------------------------------------------------------
* A helper function to update the position of enemies.
* When it is alive, it will move at its normal speed. And its y-position will be updated 
* based on its speed.
* When it is dead, set its existence to false.
*/
void ofApp::updateEnemyPosition() {
	// modify the movement of soldier plane
	if (iEnemySpawnTimer % ENEMY_SPEED_CONTROLLER == 0)
	{
		if (enemyIsMoving) {
			for (int i = 0; i < MAXIMUM_ENEMY; i++) {
				if (enemyArray[i].isExist == true && enemyArray[i].isDie == false)
				{
					enemyArray[i].y += speed_enemy;
					// if the enemy plane is out of the boundary, it just doesn't exist
					if (enemyArray[i].y > ofGetHeight())
						enemyArray[i].isExist = false;
				}
			}
		}
	}
}

/**--------------------------------------------------------------------------
* A helper function to update the position of bosses.
* When it is alive, it will move at its normal speed. And its y-position will be updated
* based on its speed.
* Whne it is dead, set its existence to false.
*/
void ofApp::updateBossPosition() {

	// modify the movement of BOSS
	if (iEnemySpawnTimer % BOSS_SPEED_CONTROLLER == 0)
	{
		for (int i = 0; i < MAXIMUM_BOSS; i++) {
			if (boss[i].isExist == true && boss[i].isDie == false)
			{
				boss[i].y += speed_boss;
				// if the boss plane is out of the boundary, it just doesn't exist
				if (boss[i].y > ofGetHeight())
					boss[i].isExist = false;
			}
		}
	}
}

/**----------------------------------------------------------------------------
* A helper function to draw the hero. Will be called inside the draw() function
*/
void ofApp::drawHero() {
	if (iHeroTimer >= 5) {
		iHeroIndex++;
		iHeroIndex %= 2;
	}
	if (iHeroIndex == 1) {
		hero1.draw(iPlayerPositionX, iPlayerPositionY);
	}
	else
	{
		hero2.draw(iPlayerPositionX, iPlayerPositionY);
	}
}

/**------------------------------------------------------------------------------
* A helper function to draw the bullets.
* 1. first loop to generate bullets and set their initial position;
* 2. then draw then bullet, and delete those out of the screen;
* 3. Also handle how to upgrade firepower.
*/
void ofApp::drawBullets() {
	//first define the position of each bullet and set other related parameters
	if (iBulletTimer % BULLET_NUMBER_CONTROLLER == 0) {
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			if (bulletArray[i].isExist == false) {
				int x = iPlayerPositionX + 50;
				bulletArray[i].x = x;
				bulletArray[i].y = iPlayerPositionY;
				bulletArray[i].isExist = true;  //ready to shoot!
				break;
			}
		}
	}

	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		if (bulletArray[i].isExist == true) {
			bulletArray[i].y -= 20;
			if (bulletArray[i].y < -20)
			{
				//delete the bullet if it is out of the screen
				bulletArray[i].isExist = false;
				continue;
			}

			bulletArray[i].draw();  //call the draw() function in the bullet class

			//upgrade firepower if reach certain points
			if (iScore > POINTS_TO_UPGRADE_BULLET)
				bulletArray[i].addSecondBullet();
			if (iScore > POINTS_TO_MAX_BULLET)
				bulletArray[i].addThirdBullet();
		}
	}
}

/**----------------------------------------------------------------------------
* A helper function to draw enemies.
* 1. loop to generate enemies and initialize their positions (their paths are randomly generated).
* 2. draw enmey iff it is exist and alive; draw dealth animation if it is exist but being hit.
*    delete enemy if it is dead.
*/
void ofApp::drawEnemy() {
	if (iEnemySpawnTimer % ENEMY_SPEED_CONTROLLER == 0)
	{
		//Initialize the parameters of the enemies before being generated
		for (int i = 0; i < MAXIMUM_ENEMY; i++)
		{
			if (enemyArray[i].isExist == false) {
				int y = -39;
				int x = rand() % (ofGetWidth() - 51); //the x-postion of enemies should be random
				enemyArray[i].x = x;
				enemyArray[i].y = y;
				enemyArray[i].isExist = true;
				enemyArray[i].isDie = false;
				enemyArray[i].iDieAnimationIndex = 0;
				enemyArray[i].iDieAnimationTimer = 0;
				enemyIsMoving = true;
				break;
			}
		}
	}

	//draw enemy and death animation
	for (int i = 0; i < MAXIMUM_ENEMY; i++)
	{
		if (enemyArray[i].isExist == true)
		{
			if (enemyArray[i].isDie == true)
			{
				enemyArray[i].iDieAnimationTimer++;
				enemyArray[i].iDieAnimationIndex = enemyArray[i].iDieAnimationTimer / 5;
				if (enemyArray[i].iDieAnimationIndex > 4)
				{
					enemyArray[i].isExist = false;
					enemyArray[i].isDie = false;
					continue;
				}

				if (enemyArray[i].iDieAnimationIndex == 3)
				{
					enemyArray[i].draw(enemy3);
				}
				else
				{
					switch (enemyArray[i].iDieAnimationIndex) {
					case 0:
						enemyArray[i].draw(enemy0); // draw the pic of enemy
						break;
					case 1:
						enemyArray[i].draw(enemy1); //draw the enemy on fire
						break;
					case 2:
						enemyArray[i].draw(enemy2); // draw the enemy on fire
						break;
					case 4:
						enemyArray[i].draw(enemy4); // draw the enemy which is going to explode
						break;
					default:
						break;
					}
				}
			}
			else
			{
				//draw the enemy if it is exist and alive
				enemyArray[i].draw(enemy0);
			}
		}
	}
}

/**-------------------------------------------------------------------------------------------
* A helper function to draw boss.
* 1. loop to generate bosses and initialize their positions (their paths are randomly generated).
* 2. draw boss iff it is exist and alive; draw dealth animation if it is exist but being hit.
*    delete boss if it is dead.
*/
void ofApp::drawBoss() {
	//Initialize the parameters of the bosses before being generated
	for (int i = 0; i < MAXIMUM_BOSS; i++) {
		if (iScore == (i + 1) * POINTS_TO_GENERATE_BOSS && boss[i].isExist == false && boss[i].dieTime == 0) {
			int y = 50;
			int x = rand() % (ofGetWidth() - 51);
			boss[i].x = x;
			boss[i].y = y;
			boss[i].isExist = true;
			boss[i].isDie = false;
			boss[i].dieTime = 0;
			boss[i].iDieAnimationIndex = 0;
			boss[i].iDieAnimationTimer = 0;
		}
	}

	//draw boss and death animation
	for (int i = 0; i < MAXIMUM_BOSS; i++) {
		if (boss[i].isExist == true) {
			boss[i].draw(enemyBoss1); // call the draw function from the Enemy class
		}
		if (boss[i].isExist == true && boss[i].isDie == false)
		{
			for (int j = 0; j < BULLET_NUMBER; j++)
			{
				if (bulletArray[j].isExist) {
					//detect the collision between bullets and boss
					if (isInclude(boss[i], bulletArray[j].x, bulletArray[j].y))
					{
						bulletArray[j].isExist = false; //delete the bullet if it hits an enemy
						hitCount++;
						switch (hitCount)
						{
						case 1:
							boss[i].draw(enemyBoss1); //draw the pic of boss
							break;
						case 2:
							boss[i].draw(enemyBoss2); //draw the boss on fire
							break;
						default:
							break;
						}
					}
					if (hitCount == BOSS_HP) {
						hitCount = 0;
						boss[i].isDie = true;
						boss[i].dieTime = 1;
						boss[i].isExist = false;
						boss[i].draw(enemyBoss4);  //draw the boss which is going to explode
						iScore += BOSS_POINT; //UPDATE the score after defeating a boss
						if (maxScore < iScore)
						maxScore += BOSS_POINT;
						enemy0_down.play(); //Play the audio effect when an enemy crashes
						break;
					}
				}
			}
		}
	}
}
