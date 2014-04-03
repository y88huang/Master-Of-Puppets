#include "game.hpp"
#include "SoundManager.h"
Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	glClearColor(0.5,0.5,0.5,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,2000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
		glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	showScore = false;
	gameMap = new Map("awesomeMap.obj");
	 player = new Player("MF",20.0,0.5,Sphere(Vector3D(550,70,50),20.0),
	 	new Gun(Vector3D(7.4,-5.98,-18.07),Vector3D(0,93.2,0),0.5));
	 score = new ScoreBoard(0.1,Vector3D(),Vector3D(0,-180,0));
	 	boss = new Monster(Vector3D(-504,76.7801,123.543),player);
	 fireWork = new particleSystem(Vector3D(500,10,0),0.01,20.0,0,10,0,0.1,10,Vector3D(10,10,10));
	fireWork->regenerate(12000);
	 int BUFF_1 = SM.LoadWav("gunFire.wav");
	 FIRE = SM.MakeSource();
	 SM.QueueBuffer(FIRE,BUFF_1);
}

Game::~Game(){
}


void Game::start(){
	SDL_Event event;//sdl event.
	Vector3D direction;
	bool moving = true;
	bool pressingButton;
	Uint32 start;
	while(moving){
		start=SDL_GetTicks();
		// std::cout<<"moving"<<std::endl;
		while(SDL_PollEvent(&event)){
		
			switch(event.type){
				case SDL_QUIT: moving=false;
					 break;
				case SDL_KEYDOWN:{
					 if(event.key.keysym.sym==SDLK_ESCAPE){
					 	moving=false;
					 	break;
					 }
					 if (event.key.keysym.sym==SDLK_TAB){
					 	showScore = true;
					 }
					 if(event.key.keysym.sym == SDLK_r){
					 	// std::cout<<"k"<<std::endl;
					 	boss->start();
					 }
					 if (event.key.keysym.sym ==SDLK_SPACE){
					 	player->jump();
					 }
					
					}
				break;
				case SDL_KEYUP:{
					switch(event.key.keysym.sym){
					 	case SDLK_TAB:
					 		showScore=false;
					 		break;
					}
				}
				case SDL_MOUSEBUTTONDOWN:
					 shouldFire = true;
					break;
				case SDL_MOUSEBUTTONUP:
					shouldFire = false;
					player->stopFire();
					break;
				break;
			}
		 }
		 		show();
			SDL_GL_SwapBuffers();
			if(1000/30>(SDL_GetTicks()-start)){
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
		}

	}
}



void Game::show()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	player->update(gameMap->getCollisionPlane());
	player->show();
	player->camera.control();
	player->camera.update();//static after this point
	// fireWork->show();
	gameMap->show();
	boss->update();
	boss->show();
	player->camera.reverseUpdate();//dynamic after reverse.
	if(showScore){
	score->show();
}

	if(shouldFire&&!player->isFiring()){
		player->doingFire();
	player->gunFire->regenerate(15000);
	}
	player->gunFire->show();
	glPopMatrix();
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
}



