#pragma once

#include <SFML/Graphics.hpp>
// define important factors here
// aka game window and player size parameters 
#define gameWIDTH 1100
#define gameHEIGHT 475
#define playerWidth 80.0f
#define playerHeight 60.0f

using namespace sf;

class Player {

private:
	// set player character image, shape, and position
	// also how fast they will travel
	// not too fast or slow
	Vector2f* position;
	Texture playerPic;
	RectangleShape playerForm;
	const float playerSpeed = 1.4f;

public:
	// class constructor
	Player(float startX, float startY); 
	// boolean variable that helps us determine
	// how and when player is 'killed'
	// as well as counting frames
	bool playerKilled = false;
	float frameTimes = 0;
	
	// allows us to get position of player
	// helps with when player has hit or been hit with
	// an object
	Vector2f getPosition(); 

	// this helps keep the position of when the player was
	// killed, therefore respawning it in same place
	void setPosition(Vector2f newPosition); 
	RectangleShape* getForm(); 

	// movements of the ship
	// will expain more in cpp file
	void move_left(); 
	void move_right(); 
	void move_up(); 
	void move_down(); 
	
	// when player dies and updates as always
	void deleteP(); 
	void update(); 
};