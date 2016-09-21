#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Landscape.h"

#define gastankHeight 60
#define gastankWidth 40
#define gastankSize 40
#define gastankScoreIn 100

using namespace sf;
using namespace std;

class GasTank {

private:
	// get image, shape, and pos
	Texture gastankPic;
	RectangleShape gastankForm;
	Vector2f* position;

public:
	// constructor
	GasTank(float startX, float startY);
	// similat to enemy 
	// only gastank we need it
	// get shapes and posis
	RectangleShape* getForm();
	FloatRect getPosition(); 
	// funcitons
	// move, delete instance when interacted
	// and respawn 
	void move(); 
	void deleteInst();
	void reAppear(Vector2f startPos);
};