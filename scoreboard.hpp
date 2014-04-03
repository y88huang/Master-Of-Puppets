#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "algebra.hpp"
class ScoreBoard
{
	float _percentage;
	float _width;
	float _height;
	Vector3D _position;
	Vector3D _rotation;
public:
	ScoreBoard(float percentage,Vector3D position,Vector3D rotation);
	~ScoreBoard();
	float getPercentage(){
		return _percentage;
	}
	void update();
	void show();
	// void test(bool t);
	/* data */
};
#endif