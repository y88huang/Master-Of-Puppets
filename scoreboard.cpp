#include "scoreboard.hpp"
ScoreBoard::ScoreBoard(float percentage,Vector3D position,Vector3D rotation){
	_percentage = percentage;
	_width = 320*_percentage;
	_height = 240*_percentage;
	_position = position;
	_rotation = rotation;
}
void ScoreBoard::show(){
	glPushMatrix();

	glTranslatef(_position[0],_position[1],_position[2]);
	glRotatef(_rotation[0],1,0,0);
	glRotatef(_rotation[1],0,1,0);
	glRotatef(_rotation[2],0,0,1);
	// glNormal3f(0,0,1);
	// glColor3f(0.0,0.0,0.0);
	// glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glColor4f(0.0f,0.8f,0.0f,0.1f);
	// glNormal3f(0,0,-1);
	glVertex3f(-_width/(float)2,_height/(float)2,40);
	glVertex3f(_width/(float)2,_height/(float)2,40);
	glVertex3f(_width/(float)2,-_height/(float)2,40);
	glVertex3f(-_width/(float)2,-_height/(float)2,40);
	glEnd();
	glPopMatrix();
}