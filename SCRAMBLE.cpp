// now include everything!
#include "stdafx.h"
#include "Player.h"
#include "Landscape.h"
#include "GasTank.h"
#include "Bomb.h"
#include "EnemyRocket.h"
#include "EnemyTwo.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

// parameters
#define gameWIDTH 1100
#define gameHEIGHT 475
#define LIVES 3

using namespace sf;
using namespace std;

int main() {
	// Declare all variables

	// first, make sure you render game window, with title
	// SCRAMBLE
	RenderWindow window(VideoMode(gameWIDTH, gameHEIGHT), "SCRAMBLE");
	
	// Load in Player Picture!
	Texture playerPic;
	if (!playerPic.loadFromFile("MainCharacter.png")) {
		cout << "Couldn't load MainCharacter.png!" << endl;
		return EXIT_FAILURE;
	}
	
	// load in galaxy pic!
	Texture galaxyPic;
	if (!galaxyPic.loadFromFile("galaxy.jpg")) {
		cout << "Couldn't load galaxy.jpg!" << endl;
		return EXIT_FAILURE;
	}
	Sprite background;
	background.setTexture(galaxyPic);

	// player variables!
	int playerLives = LIVES;
	float fuel = 100;
	int score = 0;
	
	// other variables
	// for when player scores points
//	bool playerWins = false;

	// when getting gas the first and another time
	bool gastankDone = false;
	bool gastankTwiceRem = false;

	// for killing enemies a few times
	bool enemyrocketKill = false;
	bool enemyrockkillagain = false;
	bool enemytwoKill = false;
	bool enemytwokillagain = false;

	// for when the game ends
	bool gameOver = false;

	// for creating Bob-ombs!
	vector<Bomb*> bombs;

	// and critical for getting the last location
	// player was at when they were killed
	Vector2f lastPosition;  

	// and of course, 
	// all are false becayse they have yet to happen...

	// Now lets spawn the player
	// position they will first appear
	Player player(gameWIDTH / 8, gameHEIGHT / 2);

	// next the landscape
	Landscape* moonfloor = new Landscape();
	vector<RectangleShape*> landscapeBars;
	landscapeBars = moonfloor->landscape;

	// The Three types of Texts used:
	// Score, Fuel, End Message

	Text scoreText;
	Text fuelText;
	Text gameOverText;

	// Font used for this game is flatwheat
	Font font;
	font.loadFromFile("Flatwheat-Regular.ttf");

	// Fuel
	fuelText.setFont(font);
	fuelText.setCharacterSize(45);
	fuelText.setPosition(gameWIDTH / 2, 0.0f);
	fuelText.setColor(sf::Color::Green);
	fuelText.setString("FUEL");

	// Now create the fuel box
	RectangleShape fuelBox(Vector2f(355, 35));
	fuelBox.setPosition(710, 7);
	fuelBox.setFillColor(Color::Color(10, 255, 100, 100));

	// ScoreBoard
	scoreText.setFont(font);
	scoreText.setCharacterSize(45);
	scoreText.setPosition(10.0f, 0.0f);
	scoreText.setColor(sf::Color::Green);

	// Now create the little images of the player under the 
	// Scoreboard
	// Only 3 appear, respresntative of your lives
	// when you die, one disappears

	vector<RectangleShape*> lives;
	// use for method
	for (int totalLives = 0; totalLives < LIVES; totalLives++) {
		RectangleShape* playerlives = new RectangleShape(Vector2f(50.0f, 50.0f));
		// Use player image
		playerlives->setTexture(&playerPic);
		lives.push_back(playerlives);
	}

	// Game Over Message
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(75);
	gameOverText.setPosition(gameWIDTH / 85, gameHEIGHT / 3);
	gameOverText.setColor(Color::Blue);
	gameOverText.setString("GAME OVER! SPACE to Play AGAIN!");

	// Now the objects
	// create at least two for all, for now...

	GasTank gasTank(moonfloor->xPosition[5], gameHEIGHT - moonfloor->yPosition[5] - gastankHeight);
	GasTank gasTank2(moonfloor->xPosition[10], gameHEIGHT - moonfloor->yPosition[10] - gastankHeight);
	EnemyRocketOne enemyrocket(moonfloor->xPosition[7], gameHEIGHT - moonfloor->yPosition[7] - enemyHeight);
	EnemyRocketOne enemyrocket2(moonfloor->xPosition[12], gameHEIGHT - moonfloor->yPosition[12] - enemyHeight);
	EnemyTwo enemytwo(moonfloor->xPosition[15], gameHEIGHT - moonfloor->yPosition[15] - enemytwoHeight);
	EnemyTwo enemytwo2(moonfloor->xPosition[8], gameHEIGHT - moonfloor->yPosition[8] - enemytwoHeight);
	background.setScale(1.6f, 1.5f);

	// Start
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Keyboard Events
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.move_left();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.move_right();
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.move_up();
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.move_down();
		}

		// To restart the game
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (gameOver) {
				gameOver = false;
				gameOverText.setString("GAME OVER!");

				// Return to the start
				player.setPosition(Vector2f(gameWIDTH / 8, gameHEIGHT / 2));

				// Score is back to Zero
				// Player has full gas again
				// and all lives
				score = 0;
				fuel = 100;
				playerLives = LIVES;

				// Restart Landscape too
				moonfloor->zooomNo(false);
				moonfloor->reset();

				//position back objects from before
				// Necessary or else they will not respawn
				gastankDone = false;
				gastankTwiceRem = false;
				enemyrocketKill = false;
				enemyrockkillagain = false;
				enemytwoKill = false;
				enemytwokillagain = false;
				gasTank.reAppear(Vector2f(moonfloor->xPosition[9], gameHEIGHT - moonfloor->yPosition[9] - gastankHeight));
				gasTank2.reAppear(Vector2f(moonfloor->xPosition[13], gameHEIGHT - moonfloor->yPosition[13] - gastankHeight));
				enemyrocket.reAppear(Vector2f(moonfloor->xPosition[7], gameHEIGHT - moonfloor->yPosition[7] - enemyHeight));
				enemyrocket2.reAppear(Vector2f(moonfloor->xPosition[12], gameHEIGHT - moonfloor->yPosition[12] - enemyHeight));
				enemytwo.reAppear(Vector2f(moonfloor->xPosition[4], gameHEIGHT - moonfloor->yPosition[4] - enemytwoHeight));
				enemytwo2.reAppear(Vector2f(moonfloor->xPosition[10], gameHEIGHT - moonfloor->yPosition[10] - enemytwoHeight));

				// Get Lives back
				// Copied from before
				for (int totalLives = lives.size(); totalLives < LIVES; totalLives++) {
					RectangleShape* playerlives = new RectangleShape(Vector2f(50.0f, 50.0f));
					playerlives->setTexture(&playerPic);
					lives.push_back(playerlives);
				}
			}
		}
		// Action for dropping bombs
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			// counting player framerates
			// when to drop bomb
			if (player.frameTimes >= 10) {
				// get positions of whereabouts
				Vector2f dropBobomb(player.getPosition().x + (playerWidth *(0.5)), player.getPosition().y + playerHeight);
				// More moremore
				Bomb* moreBombs = new Bomb(dropBobomb);
				bombs.push_back(moreBombs);
				// reset
				player.frameTimes = 0;
			}
		}

		// When the main character wants to kill themself
		// Events to handle
		// very similar from before
		// very repeitive 

		bool hitgasTank = player.getForm()->getGlobalBounds().intersects(gasTank.getPosition());
		bool hitgasTank2 = player.getForm()->getGlobalBounds().intersects(gasTank2.getPosition());
		bool hitenemyrocket = player.getForm()->getGlobalBounds().intersects(enemyrocket.getPosition());
		bool hitenemyrocket2 = player.getForm()->getGlobalBounds().intersects(enemyrocket2.getPosition());
		bool hitenemytwo = player.getForm()->getGlobalBounds().intersects(enemytwo.getPosition());
		bool hitenemytwo2 = player.getForm()->getGlobalBounds().intersects(enemytwo2.getPosition());

		if (hitgasTank) {
			// no more gas
			// deleted
			fuel = 0;
			gasTank.deleteInst();
			gastankDone = true;
		}

		// when this happens again
		// same thing, only for 2nd obk this time
		if (hitgasTank2) {
			fuel = 0;
			gasTank2.deleteInst();
			gastankTwiceRem = true;
		}

		// now for enemyrocket
		// samething, for all of them really
		// okay you get it, im going to stop commenting 
		// just for a little biit
		if (hitenemyrocket) {
			fuel = 0;
			enemyrocket.deleteInst();
			enemyrocketKill = true;
		}

		if (hitenemyrocket2) {
			fuel = 0;
			enemyrocket2.deleteInst();
			enemyrockkillagain = true;
		}

		if (hitenemytwo) {
			fuel = 0;
			enemytwo.deleteInst();
			enemytwoKill = true;
		}

		if (hitenemytwo2) {
			fuel = 0;
			enemytwo2.deleteInst();
			enemytwokillagain = true;
		}

		// Now for when your bomb hits something
		// same deal as above
		for (int j = 0; j < bombs.size(); j++) {

			bool bombhitgastank = (*bombs[j]).bombForm.getGlobalBounds().intersects(gasTank.getPosition());
			bool bombhitgastank2 = (*bombs[j]).bombForm.getGlobalBounds().intersects(gasTank2.getPosition());
			bool bombhitenemyrocket = (*bombs[j]).bombForm.getGlobalBounds().intersects(enemyrocket.getPosition());
			bool bombhitenemyrocket2 = (*bombs[j]).bombForm.getGlobalBounds().intersects(enemyrocket2.getPosition());
			bool bombhitenemytwo = (*bombs[j]).bombForm.getGlobalBounds().intersects(enemytwo.getPosition());
			bool bombhitenemytwo2 = (*bombs[j]).bombForm.getGlobalBounds().intersects(enemytwo2.getPosition());

			// Similar to before
			// only this time, this benefits you
			// your score, and your fuel perhaps

			if (bombhitgastank) {
				// so now we have extra fuel
				// and a higher score!
				fuel += 10;
				score += 100;
				gasTank.deleteInst();

				// also got this from stack overflow
				// helped alot for 'erasing'
				delete(bombs[j]);
				bombs.erase(bombs.begin() + j);
				gastankDone = true;
			}

			if (bombhitgastank2) {
				fuel += 10;
				score += 100;
				gasTank2.deleteInst();

				delete(bombs[j]);
				bombs.erase(bombs.begin() + j);
				gastankTwiceRem = true;
			}

			if (bombhitenemyrocket) {
				score += 100;
				// now deletes rocket
				enemyrocket.deleteInst();
				delete(bombs[j]);
				bombs.erase(bombs.begin() + j);
				enemyrocketKill = true;
			}

			if (bombhitenemyrocket2) {
				score += 100;
				enemyrocket2.deleteInst();
				delete(bombs[j]);
				bombs.erase(bombs.begin() + j);
				enemyrockkillagain = true;
			}

		if (bombhitenemytwo) {
			score += 100;
			enemytwo.deleteInst();
			delete(bombs[j]); 
			bombs.erase(bombs.begin() + j); 
			enemytwoKill = true;
		}

		if (bombhitenemytwo2) {
			// means we scored 100 points again yay
			score += 100;
			enemytwo2.deleteInst();

			delete(bombs[j]); 
			bombs.erase(bombs.begin() + j); 
			enemytwokillagain = true;
		}
	}
		  
	// Now some updates
		window.clear();
		player.update();

		// update player score
		stringstream score_stream;
		score_stream << "Score     " << score;
		scoreText.setString(score_stream.str());
		window.draw(background);

		// Update lives
		for (int l = 0; l < lives.size(); l++) {
			lives[l]->setPosition(Vector2f(10 + l * 55.0f, 50.0f));
			window.draw(*lives[l]);
		}

		// Game Over
		if (gameOver) {
			if (player.getPosition().y < gameHEIGHT) {
				// player falls down...
				player.move_down(); 
			}
		} else {
			// if the game is still going on
			bool end = player.getForm()->getGlobalBounds().intersects(scoreText.getGlobalBounds());
			// if both occur, means game is done
			if (end && moonfloor->zooomYes()) {
				// you lost
				gameOver = true;
			}
			moonfloor->move();

			// objects update as well
			gasTank.move();
			gasTank2.move();
			enemyrocket.move();
			enemyrocket2.move();
			enemytwo.move();
			enemytwo2.move();

			// Fuel Bar Stuff

			// Goes down really slowly
			fuel -= 0.008f; 
			fuelBox.setScale(fuel / 100, 1); 

			// if fuel is 0
			// and player is still alive
			// too bad, they die
			if (fuel <= 0) {
				if (!player.playerKilled) {
					player.playerKilled = true;

					// gets last player pos
					lastPosition = player.getPosition();

					// loses a life
					playerLives--;

					// use pointer like last time
					RectangleShape* ptr = lives[0]; 
					delete(ptr); 
					lives.erase(lives.begin()); 
				}

				// when the player is killed, they fall down
				if (player.playerKilled) {
					player.move_down();
				}

				// fall all the way down
				if (player.getPosition().y >= gameHEIGHT - 50) {
					player.playerKilled = false;
					// if the player still has a life
					// they can continue
					// and their fuel is replenished
					if (playerLives > 0) {
						player.setPosition(lastPosition);
						fuel = 100;
					} else {
						//if the Player lost all their lives
						// they lost
						gameOver = true;
					}
				}
			}
			
			// More updates for bombs

			for (int i = 0; i<bombs.size(); i++) {
				// move them
				bombs[i]->move();
				// get the y pos and check
				if (bombs[i]->position.y > gameHEIGHT) {
					// erase the bomb
					vector<Bomb*>::iterator instance = bombs.begin();
					// similar like before
					instance += i;
					delete(bombs[i]);
					bombs.erase(instance);
				}
			}

			// And like last time, 
			// drawing comes at the end, 
			// otherwise, nothing starts in the beginning

			// re-draw objs
			if (!gastankDone) window.draw(*gasTank.getForm());
			if (!gastankTwiceRem) window.draw(*gasTank2.getForm());
			if (!enemyrocketKill) window.draw(*enemyrocket.getForm());
			if (!enemyrockkillagain) window.draw(*enemyrocket2.getForm());
			if (!enemytwoKill) window.draw(*enemytwo.getForm());
			if (!enemytwokillagain) window.draw(*enemytwo2.getForm());
			window.draw(*player.getForm());
			
			// redraw texts
			window.draw(scoreText);
			window.draw(fuelText);
			window.draw(fuelBox);

			// and landscape
			if (moonfloor->zooomYes()) {
				window.draw(scoreText); 
			}
			for (int a = 0; a < landscapeBars.size(); a++) {
				window.draw(*landscapeBars[a]);
			}

			// and for bombs
			for (int b = 0; b < bombs.size(); b++) {
				window.draw(*(bombs[b]->getShape()));
			}

			// Now for the grand finale
			// Game oVer
			if (gameOver) {
				window.draw(gameOverText);
			}
			window.display();
		}
	} 
	// Success :)
	return 0;
}