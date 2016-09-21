#include "stdafx.h"
#include "Landscape.h"

using namespace sf;

Landscape::Landscape() {
	// as always, load image
	if (!moonPic.loadFromFile("landscape.jpg")) {
		cout << "Couldn't load landscape.jpg!" << endl;
	}

	// set size and position it will start from bottom to top
	Vector2f sizeVect(160, 510);
	Vector2f spawnPosition(0, gameHEIGHT); 
	switX = 0;

	// for basically all the 30 blocks going by
	for (int i = 0; i < MOUNTAINS; i++) {
		// create the shape and fill in with moon image
		RectangleShape* shape = new RectangleShape(sizeVect);
		shape->setTexture(&moonPic);

		// make sure positions are correct to where you want
		// mountains to form for your player char
		// to avoid them easily
		shape->setPosition(Vector2f(spawnPosition.x, spawnPosition.y - yPosition[i]));
		xPosition.push_back(spawnPosition.x + ((0.5)*sizeVect.x));

		// add the positions as long as they are scrolling
		spawnPosition.x += sizeVect.x;
		landscape.push_back(shape);
	}
}

void Landscape::move() {
	// this func now 'moves' the blocks
	// make sure the landscape is within range
	if (landscape[landscape.size() - 1]->getPosition().x > gameWIDTH - 150) {
		for (int i = 0; i < landscape.size(); i++) {
			// moves in direction using the set speed for scrolling
			Vector2f dir(-1 * SCROLLSPEED, 0);
			// use pointers
			// discovered this on stackoverflow
			// bless stackoverflow
			// so tired..
			landscape[i]->move(dir);
		}
		// speedin on with x positions
		switX += SCROLLSPEED;
	} else {
		// if this isnt happeneing
		// then that means we r done
		// we dont need to scroll anymore
		// zoooooom!
		zooOm = true;
	}
}

// resets are battlefield
void Landscape::reset() {
	// change new coords
	Vector2f* chg = new Vector2f(switX, 0);
	// for out entire landscape
	for (int i = 0; i < landscape.size(); i++) {
		// change coords using pointers
		landscape[i]->move(*chg);
	}
	// back to zero
	switX = 0;
}

// zooomed we have
bool Landscape::zooomYes() {
	return zooOm;
}

// zoomed we have not
void Landscape::zooomNo(bool val) {
	// return value
	zooOm = val;
}