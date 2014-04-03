#ifndef MONSTER_HPP
#define MONSTER_HPP
#include "algebra.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "loader.hpp"
#include "primitives.hpp"
#include "SoundManager.h"
#include "player.hpp"
class Monster
{
	Vector3D _position;
	objFileLoader *loader;
	int startingTime,currentTime;
	float _speed;
	Sphere sphere;
	int PASS;
	int OUCH;
	int LAUGH;
	bool isMoving;
	unsigned int texture;
	int lastPlayingTime;
	float rotation;
	int startingLaugh;
	Vector3D tmpSpeed;
	// unsigned int callNumber;loaoao
public:
	Player *player;
	Monster();
	Monster(Vector3D position,Player *p);
	void show();
	void start();
	void update();
	float getSpeed(){
		return _speed;
	}
	~Monster();

	/* data */
};
#endif