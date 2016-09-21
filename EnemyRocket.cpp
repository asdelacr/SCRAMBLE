#include "stdafx.h"
#include "EnemyRocket.h"

using namespace sf;

EnemyRocketOne::EnemyRocketOne(float startX, float startY) {
	// load image
	if (!enemyPic.loadFromFile("EnemyRocket.png")) {
		cout << "Couldn't load EnemyRocket.png!" << endl;
	}

	// create position onscreen 
	// set direction
	// negative in y direct
	position = new Vector2f(startX, startY);
	moveDir = *(new Vector2f(0, -1));

	// like with others, use retangle
	// set forms, size, pisition of image of ENemyRocket
	enemyForm.setTexture(&enemyPic);
	enemyForm.setSize(Vector2f(enemyWidth, enemyHeight));
	enemyForm.setPosition(*position);
}

// get the poisition and returns
FloatRect EnemyRocketOne::getPosition() {
	return enemyForm.getGlobalBounds();
}

// for shape
RectangleShape* EnemyRocketOne::getForm() {
	RectangleShape* pointer = &enemyForm;
	return pointer;
}

// Function makes the enemyrocket disappear after impact
// Initially had troubles with deleting
// But I then found something off of Stack Overflow about this problem
// One way to 'delete' it is to push it off the screen entirely
// was running out of time so I did it this way
void EnemyRocketOne::deleteInst() {
	position->y = -2000;
	enemyForm.setPosition(*position); 
}

void EnemyRocketOne::reAppear(Vector2f start_position) {
	// respawns
	*position = start_position;
	enemyForm.setPosition(*position);
}

// i gave up with this
// i cant make it fly anymore 
// because of time constraints 
//  :(

// move the ship along with the scroll
// so it doesnt look stuck
void EnemyRocketOne::move() {
	Vector2f dir(-1 * SCROLLSPEED, 0);
	enemyForm.move(dir);
}