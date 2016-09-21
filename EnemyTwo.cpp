#include "stdafx.h"
#include "EnemyTwo.h"

using namespace sf;

// process similar to enemryRocket
// just another enemy
// sorry if i put less comments for this file
// when im tired, i can be pretty sarcastic

EnemyTwo::EnemyTwo(float startX, float startY) {
	// image is important
	if (!enemytwoPic.loadFromFile("EnemyTwo.png")) {
		cout << "Couldn't load EnemyTwo.png!" << endl;
	}

	position = new Vector2f(startX, startY);

	// set texture form, size poisition 
	enemytwoForm.setTexture(&enemytwoPic);
	enemytwoForm.setSize(Vector2f(enemytwoWidth, enemytwoHeight));
	enemytwoForm.setPosition(*position);
}

FloatRect EnemyTwo::getPosition() {
	// return position
	return enemytwoForm.getGlobalBounds();
}

RectangleShape* EnemyTwo::getForm() {
	// returns value poitiner
	RectangleShape* pointer = &enemytwoForm;
	return pointer;
}

void EnemyTwo::deleteInst() {
	// same with enemyrockets
	position->y = -2000; 
	enemytwoForm.setPosition(*position); 
}

void EnemyTwo::reAppear(Vector2f startPosition) {
	// respawn
	*position = startPosition;
	enemytwoForm.setPosition(*position);
}

void EnemyTwo::move() {
	// like enemy rocket, move with landscape
	// so not be stuck
	Vector2f dir(-1 * SCROLLSPEED, 0);
	enemytwoForm.move(dir);
}