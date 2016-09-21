#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

#define gameWIDTH 1100
#define gameHEIGHT 500
// mountains are our blocks of landscape
// the ones that look like bar graphs
// i made 30 of them
// so the game will keep going on longer
// also set the speed on how fast the blocks
// will 'move' 
#define MOUNTAINS 30
#define SCROLLSPEED 0.6f


using namespace sf;
using namespace std;

class Landscape {

private:
	// zoomed in picture of the moon
	Texture moonPic;
	// zooOm sounded kind of fun to put in here
	// anyways note: zooOm is basically meaning
	// that all the blocks are done and stopped
	// so the game is done
	// soo... ZOOOOM!
	// im really tired. 
	bool zooOm = false;

public:
	// constructor
	Landscape(); 

	// basically what gives the landscape its form
	// long rectangles
	vector<RectangleShape*> landscape;

	// lets not forget x coordinates
	// for positions and changes to update
	vector<float> xPosition;
	float switX;

	// functions that move landscape at set speed
	// also resets when game is over and continued
	void move(); 
	void reset(); 

	// Means game is not scrolling anymore
	void zooomNo(bool value); 
	// Means game IS scrolling and returns True
	bool zooomYes(); 

	// Here are the mountain coordinates
	// meaning how high will they go?
	// starts at 0, ends at 29
	// because you know we dont ever start at 1..
	float yPosition[MOUNTAINS] = {
		100,  
		75,  
		100, 
		50,  
		100, 
		150, 
		200, 
		250,  
		140,   
		100, 
		200, 
		350, 
		100, 
		90,  
		75,  
		20,   
		100,  
		200, 
		250,
		250,  
		200, 
		100,
		50,
		100,
		275,
		400,
		300,
		225,
		200,
		100
	};
};