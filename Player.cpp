#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Player::Player(float startX, float startY) {
	// loads in main character image
	if (!playerPic.loadFromFile("MainCharacter.png")) {
		cout << "Couldn't load MainCharacter.png!" << endl;
	}
	
	// means the player hasnt been killed
	// yet...
	playerKilled = false;

	// set position 
	// good for every respawn
	position = new Vector2f(startX, startY);

	// similar to bomb, uses rectangleshape to map image
	// set size and position too
	playerForm.setTexture(&playerPic);
	playerForm.setSize(Vector2f(playerWidth, playerHeight));
	playerForm.setPosition(*position);
}

// Now this handles the player movement
// I purposefully made it so that the player 
// moves left slower, making it harder to go backward
void Player::move_left() {
	position->x -= playerSpeed + 1;
}

// player moves faster when going to the right...
void Player::move_right() {
	position->x += playerSpeed + 3;
}

// moves slightly faster when going up
void Player::move_up() {
	position->y -= playerSpeed + 1;
}

// and moves down as normal
void Player::move_down() {
	position->y += playerSpeed ;
}

// gets fhape of player and returns pointer
RectangleShape* Player::getForm() {
	RectangleShape* pointer = &playerForm;
	return pointer;
}

// gets position
Vector2f Player::getPosition() {
	return *(position);
}

void Player::setPosition(Vector2f newPosition) {
	// positions for both x and y coords
	position->x = newPosition.x;
	position->y = newPosition.y;
}

// when the player has died
void Player::deleteP() {
	playerForm.rotate(90);
}

// updates 
void Player::update() {
	playerForm.setPosition(*position);
	//float frameTimes;
	frameTimes += 0.2f;
}