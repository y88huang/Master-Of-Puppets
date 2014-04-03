#include "player.hpp"
#include "SoundManager.h"
Player::Player(const char* playerName,float speed,float lookat,Sphere playerSphere,Gun* gun){
	name = playerName;
	_playerSphere = playerSphere;
	_physicalParameter = Vector3D(0.0,-0.3,0.0);//originally no x speed.
	camera.setPosition(_playerSphere.getCenter());
	startingTime = SDL_GetTicks();
	hasGun = true;
	isJumping = false;
	gravity = 0.0005;
	initialYvalue = _playerSphere.getCenter()[1];
	initialJumpingSpeed = 0.3;
	_gun=gun;
	int BUF_1 = SM.LoadWav("booyah.wav");
	 HIT = SM.MakeSource();
	SM.QueueBuffer(HIT,BUF_1);
	gunFire = new particleSystem(Vector3D(14,-30,-20),
						0.01,0.1,0,250,6000,2,10.0,Vector3D(0,0,-50));
	gunFire->regenerate(0);
}


Player::~Player(){
}

void Player::update(std::vector<Plane*> planes){
	Vector3D move =  camera.getMovement();
	Vector3D newPosition=camera.getPosition();
	const int CHECK_DEPTH = 20;
for(int j=0;j<CHECK_DEPTH;j++){
		// std::cout<<"move is "<<move<<std::endl;
		newPosition=newPosition+(move/(float)CHECK_DEPTH);
	for (int i=0;i<planes.size();i++){
		if(planeIntersectSphere((*planes[i]),_playerSphere,&newPosition)&&SDL_GetTicks()-startingTime>500){
			SM.Play(HIT);
			startingTime = SDL_GetTicks();//UPDATE the tics.
			//play sound.
		}	
	}
	
}
    double yPos;
	if(isJumping){
		double currentT = (SDL_GetTicks() - startingJumpingTime);
		yPos = initialYvalue + initialJumpingSpeed*currentT - 0.5 * gravity * currentT*currentT;
		// std::cout<<" Y pos "<<yPos<<std::endl;
		// std::cout<<"currentT is "<<currentT<<std::endl;
		// std::cout<<"gravity is "<<gravity*currentT*currentT<<std::endl;
		// std::cout<<"inital jumping is "<<initialJumpingSpeed*currentT<<std::endl;
		if (yPos<initialYvalue){
			newPosition[1] = initialYvalue;
			isJumping = false;
			SM.Play(HIT);
		}
		else{
			newPosition[1]=yPos;
		}
	}
updatePosition(newPosition);
// _gun->update();
gunFire->update();
camera.doneMoving();	
}


void Player::jump(){
	startingJumpingTime = SDL_GetTicks();
	isJumping = true;
}
void Player::updatePosition(Vector3D newPosition){
	_playerSphere.setCenter(newPosition);
	camera.setPosition(newPosition);
}
void Player::show(){//actually player has nothing to show except a Gun.
	glPushMatrix();
	glLoadIdentity();
		_gun->show();
	glPopMatrix();
}