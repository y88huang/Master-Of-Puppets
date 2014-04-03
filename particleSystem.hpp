#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "algebra.hpp"
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>    
#include "loader.hpp"
class particle //just a small particle.
{
public:
	Vector3D _position;
	Vector3D _rotation;
	Vector3D _particleSpeed;
	Vector3D _color;
	Vector3D startingColor;
	Vector3D endingColor;
	Vector3D _speed;
	bool isDead;
	int currentTime;
	int lifeTime;
	int timeCreated;
	int timeDead;

	float _size; //size of the particle.
	particle();
	particle(const Vector3D& position,const Vector3D& rotation,
	const Vector3D& color,float size,const Vector3D& speed);
	~particle();
	void show();
	bool update();
	/* data */
};

//A collection of particle system.
class particleSystem{
	std::vector<particle> particles;
	int _numberOfParticles;
	Vector3D _position;
	bool isActive;//is the system active.
	Vector3D _startingColor;
	Vector3D _endingColor;
	float _maxSize,_minSize;
	float _maxSpeed,_minSpeed;
	int _minLifeTime,_maxLifeTime;
	Vector3D _force;
	unsigned int texture;
public:
	particleSystem();
	particleSystem(const Vector3D& position,float minSize,float maxSize,
					float minSpeed,float maxSpeed,int numberOfParticles,int minLifeTime,int maxLifeTime,const Vector3D& force);
	~particleSystem();
	void generateParticle(particle& p);
	Vector3D getPosition(){
		return _position;
	}
	void setNumberOfParticles(int number);
	void update();
	void show();
	bool isSystemActive(){
		return isActive;
	}
	void regenerate(int number);
	void decreaseParticles(){
		_numberOfParticles--;
	}
};
#endif