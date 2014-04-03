#include "monster.hpp"
Monster::Monster(){
}
Monster::Monster(Vector3D position,Player *p){
  _position = position;
  loader = new objFileLoader();
  loader->load("monster.obj");
  loader->draw();
  _speed = 80.0;
  texture = loadTexture("marble.bmp");
  loader->setTexture(texture);
  // std::cout<<loader->getFlag()<<std::endl;
  sphere = Sphere(_position,(float)60.0);
  startingTime = SDL_GetTicks();
  player = p;
  isMoving = false;
  tmpSpeed = Vector3D(0,0,-_speed);
  int BUF_1 = SM.LoadWav("youShallNotPass.wav");
  int BUF_2 = SM.LoadWav("ouch.wav");
  int BUF_3 = SM.LoadWav("laughSound.wav");
  PASS = SM.MakeSource();
  OUCH = SM.MakeSource();
  LAUGH = SM.MakeSource();
  SM.QueueBuffer(PASS,BUF_1);
  SM.QueueBuffer(OUCH,BUF_2);
  SM.QueueBuffer(LAUGH,BUF_3);
  SM.Play(PASS);
  rotation = 0.0;
  startingTime=SDL_GetTicks();
  // SM.Play(laughSound);
}

void Monster::update(){
  float t;
  Vector3D move;
  const int TIMES =10 ;
  //AI part.
  if (sphere.getCenter()[0]>472&&sphere.getCenter()[2]>470){
          rotation = -270.0;
          tmpSpeed = Vector3D(-_speed,0.0,0.0);
  }
  if(sphere.getCenter()[0]<-470&&sphere.getCenter()[2]>470){
          rotation = -360.0;
          tmpSpeed = Vector3D(0.0,0.0,-_speed);
  }
  if (sphere.getCenter()[0]>472&&sphere.getCenter()[2]<=-470){
        rotation = -180.0;
        tmpSpeed = Vector3D(0.0,0.0,_speed);
  }
  else if(sphere.getCenter()[2]<-470){
        rotation = -90.0;
        tmpSpeed = Vector3D(_speed,0.0,0.0);  
} 
 
  for (int i=0;i<TIMES;i++){
      if(isMoving&&SDL_GetTicks()-startingTime>10){
      _position=_position+(tmpSpeed/(double)TIMES);
        startingTime = SDL_GetTicks();
      }
      if(sphereIntersectSphere(player->getSphere(),sphere,&t,&move)){
    if(SDL_GetTicks()-lastPlayingTime>900){
    SM.Play(OUCH);
    lastPlayingTime = SDL_GetTicks();
  }
    player->updatePosition(move);
    }
  }
sphere.setCenter(_position);
}
void Monster::start(){
  isMoving=!isMoving;
}
void Monster::show(){
  if(SDL_GetTicks()- startingLaugh>10000){
    // std::cout<<"fuck"<<std::endl;
    SM.Play(LAUGH);
    startingLaugh = SDL_GetTicks();
  }
  glPushMatrix();
  // glLoadIdentity();
  glEnable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
  glEnable(GL_TEXTURE_2D);
  glTranslatef(_position[0],_position[1],_position[2]);
  glRotatef(rotation,0,1,0);
  glCallList(loader->getIndex());
    glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glPopMatrix();
}