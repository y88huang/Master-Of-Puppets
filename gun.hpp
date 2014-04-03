#ifndef GUN_HPP
#define GUN_HPP
#include "algebra.hpp"
#include "loader.hpp"
#include "particleSystem.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
class Gun
{
	objFileLoader* obj;
	Vector3D currentGunPosition;
	Vector3D currentGunRotation;
	float movingSpeed;
	float _horizontal;
	float _vertical;
public:
	Gun();
	Gun(Vector3D position,Vector3D rotation,float speed);
	~Gun();
	void update();
	void show();
	void showFire();
	/* data */
};
#endif




// void Gun::test(bool istest)
// {
	// if(istest)
	// {
	// 	Uint8* keys=SDL_GetKeyState(NULL);
	// 	if(keys[SDLK_j]){
	// 		endingGunPosition[0]=endingGunPosition[0]-0.02;
	// 	}
	// 	if(keys[SDLK_l]){
	// 		endingGunPosition[0]=endingGunPosition[0]+0.02;
	// 	}
	// 	if(keys[SDLK_k]){
	// 		endingGunPosition[2]=endingGunPosition[2]-0.02;
	// 	}
	// 	if(keys[SDLK_i]){
	// 		endingGunPosition[2]=endingGunPosition[2]+0.02;
	// 	}
	// 	if(keys[SDLK_z]){
	// 		endingGunPosition[1]=endingGunPosition[1]-0.02;
	// 	}
	// 	if(keys[SDLK_t]){
	// 		endingGunPosition[1]=endingGunPosition[1]+0.02;
	// 	}
	// 	if(keys[SDLK_u]){
	// 		endingGunRotation[1]=endingGunRotation[1]-0.4;
	// 	}
	// 	if(keys[SDLK_o]){
	// 		endingGunRotation[1]=endingGunRotation[1]+0.4;
	// 	}
	// 	std::cout << "weapon: " << endingGunPosition << currentGunRotation << std::endl;
	// }
// }

	// Vector3D tmpPosition = endingGunPosition - currentGunPosition;
	// tmpPosition.normalize();
	// currentGunPosition=currentGunPosition+movingSpeed*tmpPosition;
	// Vector3D errorCheck = endingGunPosition-currentGunPosition;
	// if(abs(errorCheck[0]<0.3&&abs(errorCheck[1]<0.3&&abs(errorCheck[2]<0.3)))){
	// 	currentGunPosition = endingGunPosition;
	// }
	// Vector3D tmpRotation = endingGunRotation - currentGunRotation;
	// tmpRotation.normalize();
	// currentGunRotation=currentGunRotation+movingSpeed*tmpRotation;
	// Vector3D errorCheckRoation = endingGunRotation-currentGunRotation;

	// if(abs(errorCheckRoation[0]<0.3&&abs(errorCheckRoation[1]<0.3&&abs(errorCheckRoation[2]<0.3)))){
	// 	currentGunRotation = endingGunRotation;
	// }
	// _horizontal = horizontal;
	// _vertical = vertical;
	// _gunPosition = position;
	// gunParticleSystem->update();

