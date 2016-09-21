#include "stdafx.h"
#include "GasTank.h"

using namespace sf;

GasTank::GasTank(float startX, float startY) {
	// load image
	if (!gastankPic.loadFromFile("gas-tank.png")) {
		cout << "Couldn't load gas-tank.png!" << endl;
	}

	// position, reference
	position = new Vector2f(startX, startY);

// similar to both enemy rocket and two
	gastankForm.setTexture(&gastankPic);
	gastankForm.setSize(Vector2f(gastankWidth, gastankHeight));
	gastankForm.setPosition(*position);
}

// get shape
RectangleShape* GasTank::getForm() {
	RectangleShape* pointer = &gastankForm;
	return pointer;
}

// get pisition
FloatRect GasTank::getPosition() {
	return gastankForm.getGlobalBounds();
}

// moves along with landscape
// so it doesnt look stuck onscreen
void GasTank::move() {
	Vector2f dir(-1 * SCROLLSPEED, 0);
	gastankForm.move(dir);
}

// Function makes the gas tank disappear after impact
// Initially had troubles with deleting
// But I then found something off of Stack Overflow about this problem
// One way to 'delete' it is to push it off the screen entirely
// was running out of time so I did it this way
void GasTank::deleteInst() {
	position->y = -2000;
	// And as always, update the position
	gastankForm.setPosition(*position);
}

void GasTank::reAppear(Vector2f startPosition) {
	// respawns back onscreen
	*position = startPosition;
	gastankForm.setPosition(*position);
}
