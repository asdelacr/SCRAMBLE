#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Landscape.h"

#define enemytwoHeight 75
#define enemytwoWidth 90

using namespace sf;
using namespace std;

class EnemyTwo {

private:
	// get pos, image, shape...
	Vector2f* position;
	Texture enemytwoPic;
	RectangleShape enemytwoForm;

public:
	// constructor
	// very similar to enemyRocket
	// so to save time with all the comments
	// yeah you know
	EnemyTwo(float startX, float startY); 
	FloatRect getPosition(); 
	RectangleShape* getForm(); 
	void deleteInst(); 
	void reAppear(Vector2f startPosition); 
	void move(); 
};