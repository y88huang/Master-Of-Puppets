#include "fpsCamera.hpp"
#include "cmath"
#include "SoundManager.h"
// void cameraMove();
// 	void cameraMoveUp();
	void control();
void fpsCamera::update(){
	glTranslatef(-position[0],-position[1],-position[2]);
	// std::cout<<" y pos is "<<position[1]<<std::endl;
	// glTranslatef(0.5,0.5,0.5);
}	

//helper function keep camera in the window.
void fpsCamera::keepInWindow(){
	if(vertical>90.0)vertical=90.0;
	if(vertical<-90.0)vertical=-90;
	if(horizontal>360.0)horizontal-=360.0;
	if(horizontal<0.0)horizontal+=360.0;// Questionable.
}


fpsCamera::fpsCamera():speed(10.0),mouseDiff(1.2){
	horizontal = 0.0;
	vertical = 0.0;
	int BUF_1 = SM.LoadWav("footStep.wav");
	FOOT = SM.MakeSource();
	SM.QueueBuffer(FOOT,BUF_1);
	 int BUFF_2 = SM.LoadWav("gunFire.wav");
	 FIRE = SM.MakeSource();
	 SM.QueueBuffer(FIRE,BUFF_2);
}
fpsCamera::fpsCamera(Vector3D p):speed(10.0),position(p),mouseDiff(1.2){
	horizontal = 0.0;
	vertical = 0.0;
	int BUF_1 = SM.LoadWav("footStep.wav");
	FOOT = SM.MakeSource();
	SM.QueueBuffer(FOOT,BUF_1);
	 int BUFF_2 = SM.LoadWav("gunFire.wav");
	 FIRE = SM.MakeSource();
	 SM.QueueBuffer(FIRE,BUFF_2);
}
fpsCamera::~fpsCamera(){

}
void fpsCamera::control(){
	// Vector3D position;
		// std::cout<<"LLLL"<<std::endl;
		int MidX=320;
		int MidY=240;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);
		// std::cout<<"mouse state "<<tmpx<<" "<<tmpy<<std::endl;
		horizontal+=mouseDiff*(float)(MidX-tmpx);
		vertical+=mouseDiff*(MidY-tmpy);
		// std::cout<<"[DEBUG HORIZONTAL]"<<MidX<<" "<<tmpx<<tmpy<<std::endl;
		// std::cout<<"[DEBUG] "<<horizontal<<" "<<vertical<<std::endl;
		keepInWindow();
		SDL_WarpMouse(MidX,MidY);
		// std::cout<<"warping mouse"<<std::endl;
		Uint8* state=SDL_GetKeyState(NULL);
		isMoving=false;
		// SM.Play(FOOT);
		if(state[SDLK_w])
		{
			isMoving=true;
			// SM.Play(FOOT);
			if(vertical!=90 && vertical!=-90)
				cameraMove(0.0);
		//	cameraMoveUp(0.0);
		}else if(state[SDLK_s])
		{
			isMoving=true;
			// SM.Play(FOOT);
			if(vertical!=90 && vertical!=-90)
				cameraMove(180.0);
		//	moveCameraUp(180.0);
		}		
		else if(state[SDLK_a])
		{
			isMoving=true;
			// SM.Play(FOOT);
			cameraMove(90.0);
		}
		else if(state[SDLK_d])
		{
			isMoving=true;
			// SM.Play(FOOT);
			cameraMove(270);	
		}
		if(SDL_GetMouseState(NULL,NULL)&&SDL_BUTTON(1)){
			if(SDL_GetTicks()-startingGunPlayingTime>800){
				SM.Play(FIRE);
				startingGunPlayingTime=SDL_GetTicks();
			}
		}
		if(isMoving){
			if(SDL_GetTicks()-startingPlayingTime>800){
				SM.Play(FOOT);
				startingPlayingTime = SDL_GetTicks();
			}
	}
	// std::cout<<"rotating "<<vertical<<horizontal<<std::endl;
	glRotatef(-vertical,1.0,0.0,0.0);
	glRotatef(-horizontal,0.0,1.0,0.0);
	// std::cout<<" pos x y "<<position[0]<<position[1]<<std::endl;
	// return position;
}

void fpsCamera::cameraMove(float value){
	float radiance = (horizontal+value)*M_PI/180.0;
	float radianceY = (vertical+value)*M_PI/180.0;
	//since we only move X and Z here.
	// std::cout<<"changed "<<(*v)[0]<<std::endl;
	// position[2]-=cos(radiance)*speed;
	// movement[1]+=sin(radianceY)*speed;
	// position[0]-=sin(radiance)*speed;
	movement[2]=-cos(radiance)*speed;
	movement[0]= -sin(radiance)*speed;
}

void fpsCamera::reverseUpdate(){
	glTranslatef(position[0],position[1],position[2]);
	glRotatef(horizontal,0,1,0);
	glRotatef(vertical,1,0,0);
}
void fpsCamera::doneMoving(){
	movement = Vector3D();
}
void fpsCamera::mouseIn(){
	isIn=true;
}
void fpsCamera::mouseOut(){
	isIn=false;
}