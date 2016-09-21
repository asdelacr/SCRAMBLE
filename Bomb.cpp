#include "stdafx.h"
#include "Bomb.h"

using namespace sf;

Bomb::Bomb(Vector2f newPos) {
	// loads the bomb picture
	if (!bombPic.loadFromFile("BOMB.png")) {
		cout << "Couldn't load BOMB.png!" << endl;
	}

	// Create position and set direction for
	// both x and y direction
	position = newPos;
	moveDir = *(new Vector2f(0, 1));

	// use Rectangleshape to set picture, size, and position
	bombForm.setTexture(&bombPic);
	bombForm.setSize(Vector2f(bombWidth, bombHeight));
	bombForm.setPosition(position);
}

// Here is where the bomb actually drops down
void Bomb::move() {
	// 'moves' shape of bomb
	// set a speed, not too fast or slow
	bombForm.move(moveDir * (0.5f));
	// in order for the bomb to appear as if
	// it is being dropped from the character's ship
	// we need to update the y position in the direction
	// of movement. 
	position.y += (moveDir.y * (0.5f));
}

// returns shape of bomb
RectangleShape* Bomb::getShape() {
	return &bombForm;
}