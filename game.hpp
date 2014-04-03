#ifndef GAME_HPP
#define GAME_HPP
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "fpsCamera.hpp"
#include "algebra.hpp"
#include "loader.hpp"
#include "player.hpp"
#include "map.hpp"
#include "monster.hpp"
#include "particleSystem.hpp"
// #include "scoreboard.hpp"
class Game{
	// fpsCamera camera;
	void update();
	void show();
	void display();
	int loadImage(char* filename);
		bool forward;
	bool backward;
	bool left;
	bool right;
	bool shouldFire;
	bool showScore;
	int FIRE;
	int startingPlayingSound;
	// objFileLoader* loader;
	Map* gameMap;
	Player* player;
	ScoreBoard* score;
	Monster* boss;
	particleSystem* fireWork;

public:
	Game();
	~Game();
	void start();//actually start the game.

// unsigned int loadTexture(const char* name);
};
#endif