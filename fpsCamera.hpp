#ifndef FPS_CAMERA_HPP
#define FPS_CAMERA_HPP
#include "algebra.hpp"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
class fpsCamera{
	Vector3D position;
	Vector3D movement;
	float cameraSpeed;
	float cameraSensity;
	float cameraError;
	float movingDiff;
	float mouseDiff;
	float speed;
	float vertical;
	float horizontal;
	bool isIn;
	bool isMoving;
	int FOOT;
	int FIRE;
	int startingPlayingTime;
	int startingGunPlayingTime;
public:
	fpsCamera();
	fpsCamera(Vector3D position);
	fpsCamera(Vector3D position,float sensity,float cameraError);
	~fpsCamera();
	void cameraMove(float value);
	void cameraMoveUp(float value);
	void control();
	void update();
	void reverseUpdate();//only for score board.
	void mouseIn();
	void mouseOut();
	void keepInWindow();
	bool hasMoved(){
		return isMoving;
	}
	Vector3D getPosition(){
		return position;
	}
	void setPosition(Vector3D v){
		position=v;
	}
	void cameraLookAt();
	void setSpeed(float sp){
		speed = sp;
	}
	Vector3D getMovement(){
		return movement;
	}
	void doneMoving();
	
	float getVertical(){
		return vertical; 
	}
	float getHorizontal(){
		return horizontal;
	}

};


#endif

