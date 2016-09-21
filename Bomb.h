#pragma once

#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>

// shape is square like
#define bombHeight 45
#define bombWidth 45

using namespace sf;
using namespace std;

class Bomb {

public:
	// Bomb is the constructor
	Bomb(Vector2f newPos); 
	// Next is the image of the bomb and the shape and pos
	Texture bombPic;
	RectangleShape bombForm;
	Vector2f position;
	
	// move direction
	Vector2f moveDir; 
	// use a pointer for drawing purposes
	RectangleShape* getShape(); 
	
	// function for which the bomb 'drops' straight down
	void move(); 
};