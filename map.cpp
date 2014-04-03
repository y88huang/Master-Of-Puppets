#include "map.hpp"

Map::Map(){
}
Map::Map(const char* mapName){
	mapObj = new objFileLoader();
	mapObj->load(mapName);
	mapObj->draw();
	side = loadTexture("sideWall.bmp");
	unsigned int ground = loadTexture("groundTexture.bmp");
	// std::cout <<"ground is "<<ground<<std::endl;
	unsigned int roof = loadTexture("roofTop.bmp");
	// std::cout<<"side is "<<side<<std::endl;
	mapObj->setTexture(side);
	mapObj->setExtra(ground);
	mapObj->setRoof(roof);
	startingTime = SDL_GetTicks();
}
void Map::show(){
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	// glBindTexture(GL_TEXTURE_2D,side);	//use the texture we want
	glColor3f(1.0,1.0,1.0);
	// glCallList(mapObj->getIndex());
	mapObj->drawQuads();
		glDisable(GL_TEXTURE_2D);

}

void Map::testPlane(){
	// std::cout<<"Tesing Collision Plane!"<<std::endl;
	std::vector<Plane*> planes = mapObj->getCollisionPlane();
	for (int i=0;i<planes.size();i++){
		std::cout<<planes[i]->getA()<<" "<<planes[i]->getB()<<" "<<planes[i]->getC()<<" "<<planes[i]->getD()<<" "<<std::endl;
	}
}
Map::~Map(){
}