#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Landscape.h"

// set everything here
// well not everything, most things tho
#define enemyHeight 70
#define enemyWidth 50
#define enemySpeed 0.5f
#define enemyScoreIn 50
#define startOffPoint 200

using namespace sf;
using namespace std;

class EnemyRocketOne {

private:
	// get image and pisition
	// along with shape, size, pos
	// sorry after awhile i cant type anymore
	// tired
	Texture enemyPic;
	Vector2f* position;
	RectangleShape enemyForm;

public:
	// Constructor
	EnemyRocketOne(float startX, float startY);
	// always move in ydirection
	Vector2f moveDir; 
	// get position and shape
	FloatRect getPosition(); 
	RectangleShape* getForm(); 

    // functions
	// deletes after hit
	// respawns
	// and moves along with scrolling
	// in that order respectively
	void deleteInst(); 
	void reAppear(Vector2f start_position); 
	void move(); 
};