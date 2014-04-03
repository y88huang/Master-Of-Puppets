#include "gun.hpp"

Gun::Gun(Vector3D position,Vector3D rotation,float speed){
	currentGunPosition = position;
	currentGunRotation = rotation;
	movingSpeed = speed;
	obj = new objFileLoader();
	obj->load("ak47.obj");
	obj->draw();
}
void Gun::update(){ //Gun position updating.
}
void Gun::show(){//show position.
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	 	glTranslatef(currentGunPosition[0],currentGunPosition[1],currentGunPosition[2]);
		glRotatef(currentGunRotation[0],1,0,0);
		glRotatef(currentGunRotation[1],0,1,0);
		glRotatef(currentGunRotation[2],0,0,1);
	// std::cout<<obj->getFlag()<<std::endl;
	glCallList(obj->getIndex());
	glPopMatrix();
}








