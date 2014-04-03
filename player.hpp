#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gun.hpp"
#include "primitives.hpp"
#include "fpsCamera.hpp"
#include "scoreboard.hpp"
#include "particleSystem.hpp"
// #include "OpenAL/SoundManager.h"
// #include 
class Player
{
	int hp;
	Gun* _gun;
	// ScoreBoard* _score;
	bool hasGun;
	objFileLoader* objectFile;
	int startingTime;
	Sphere _playerSphere;
	std::string name;
	Vector3D _physicalParameter;
	Vector3D _direction;
	bool isFire;
	bool isJumping;
	// SoundManager *sound;

	int HIT;//sound source

	double gravity; //mini gravity's.
	double startingJumpingTime;
	double initialJumpingSpeed;
	double initialYvalue;
	
public:
	fpsCamera camera;
	particleSystem *gunFire;
	Player(const char* playerName,float speed,float lookat,Sphere playerSphere,Gun* gun);
	~Player();
	/* data */
	int getHp(){
		return hp;
	}
	void update(std::vector<Plane*> planes);// updating player's location according to current map.
	void show();
	void updatePosition(Vector3D newPosition);
	void changeWeapon(){
	}
	void jump();
	bool isFiring(){
		return isFire;
	}
	void doingFire(){
		isFire = true;
	}
	void stopFire(){
		isFire = false;
	}
	Vector3D getPosition(){
		return _playerSphere.getCenter();
	}
	Sphere getSphere(){
		return _playerSphere;
	}
};
#endif