#include "particleSystem.hpp"
particle::particle(){
	currentTime = SDL_GetTicks();
	timeCreated = SDL_GetTicks();
}
particle::~particle(){
}
particle::particle(const Vector3D& position,const Vector3D& rotation,
	const Vector3D& color,float size,const Vector3D& speed){
	_position = position;
	_rotation = rotation;
	_color = color;
	_size = size;
	_speed = Vector3D();
	// timeCreated = SDL_GetTicks();
	isDead = false;
}

//we set it as a bool here because we want to know if it is dead by the time updating.
bool particle::update(){
	float diff = ((float)SDL_GetTicks() - currentTime)/(float)1000;
	_position = _position + diff*_speed;
	lifeTime -= diff;
	currentTime = SDL_GetTicks();
	// std::cout<<"Time is"<<timeCreated<<std::endl;
	float percentage = (float)lifeTime/timeCreated;
	_color = percentage*startingColor + (1-percentage)*endingColor;
	if(lifeTime<=0){
		isDead = true;
		return isDead;
	}
	return false;
}

void particle::show(){
	float percentage = (float)lifeTime/timeCreated;
	// std::cout<<"position is "<<_position<<std::endl;
	 glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	// std::cout<<"color is "<<_color<<std::endl;
	// std::cout<<"percentage is "<<percentage<<std::endl;
	glTexCoord2f(0,0);
	glVertex3f(_position[0],_position[1],_position[2]);
	glTexCoord2f(1,0);
	glVertex3f(_position[0],_position[1]+_size,_position[2]);
	glTexCoord2f(1,1);
	glVertex3f(_position[0]+_size,_position[1]+_size,_position[2]);
	glTexCoord2f(0,1);
	glVertex3f(_position[0]+_size,_position[1],_position[2]);
	glEnd();
	glEnable(GL_LIGHTING);
}

particleSystem::particleSystem(){
}

particleSystem::~particleSystem(){
}
particleSystem::particleSystem(const Vector3D& position,float minSize,float maxSize,
					float minSpeed,float maxSpeed,int numberOfParticles,int minLifeTime,int maxLifeTime,const Vector3D& force){
	_position = position;
	_minSize = minSize;
	_maxSize = maxSize;
	_minSpeed = minSpeed;
	_maxSpeed = maxSpeed;
	_numberOfParticles = numberOfParticles;
	_minLifeTime = minLifeTime;
	_maxLifeTime = maxLifeTime;
	_force = force;
	texture = loadTexture("fireTexture.bmp");
	for(int i=0; i<numberOfParticles;i++){
		particles.push_back(particle());
		generateParticle(particles[i]);
	}
}

void particleSystem::generateParticle(particle& p){
	// isActive =true;
	p._position = _position;
	// std::cout<<"MAX - MIN is "<<_maxSpeed - _minSpeed<<std::endl;
	p._size=(float)(rand()%((int)((_maxSize-_minSize)*1000)))/1000.0 + _minSize;

	p._speed=Vector3D(((float)(rand()%((int)((_maxSpeed-_minSpeed))*1000)/1000.0 + _minSpeed)-(_maxSpeed-_minSpeed)/2)+_force[0],
									 ((float)(rand()%((int)((_maxSpeed-_minSpeed))*1000)/1000.0 + _minSpeed)-(_maxSpeed-_minSpeed)/2)+_force[1],
									 ((float)(rand()%((int)((_maxSpeed-_minSpeed))*1000)/1000.0 + _minSpeed)-(_maxSpeed-_minSpeed)/2)+_force[2]);
	p.timeCreated=rand()%((_maxLifeTime-_minLifeTime)*1000)/1000.0 + _minLifeTime;
	p.timeCreated=p.lifeTime;
	p.startingColor=_startingColor;
	p.endingColor=_endingColor;
	p.isDead = false;
	_numberOfParticles--;
}


void particleSystem::update(){
	// std::cout<<"size is "<<particles.size()<<std::endl;
	for(int i=0;i<particles.size();i++){
		if(particles[i].update()&&_numberOfParticles>0){
		}
	}
	if(_numberOfParticles<=0){
		isActive=false;
	}
}
void particleSystem::regenerate(int number){
	_numberOfParticles = number;
	isActive = true;
	particles.resize(number);
	for(int i=0;i<particles.size();i++){
		generateParticle(particles[i]);
	}
}
void particleSystem::show(){
	float f[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,f);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			if(i!=j)
				f[i*4+j]=0;
			else
				f[i*4+j]=1;
		}
	glPushMatrix();
	glLoadMatrixf(f);
		glBindTexture(GL_TEXTURE_2D,texture);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvi(GL_TEXTURE_ENV_MODE,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	for(int i=0;i<particles.size();i++){
		particles[i].show();
	}
	glDisable(GL_TEXTURE_2D);
	// glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glPopMatrix();
}










