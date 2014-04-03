#ifndef LOADER_HPP
#define LOADER_HPP
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "algebra.hpp"
#include "primitives.hpp"

class face{
public:
	int vertex1;
	int vertex2;
	int vertex3;
	int vertex4;
	int normal;

	face(int vertexIndex1,int vertexIndex2,int vertexIndex3,
		int normalIndex):vertex1(vertexIndex1),vertex2(vertexIndex2),vertex3(vertexIndex3),normal(normalIndex){
	}
	face(int vertexIndex1,int vertexIndex2,int vertexIndex3,int vertexIndex4,
		int normalIndex):vertex1(vertexIndex1),vertex2(vertexIndex2),vertex3(vertexIndex3),vertex4(vertexIndex4),normal(normalIndex){
	}
	~face(){};
};
class objFileLoader{
	std::vector<std::string*> lines;
	std::vector<Vector3D*> vertices;
	std::vector<Vector3D*> normals;
	std::vector<face*> faces;
	std::vector<Plane*> collplane;
	int flag;
	int callerIndex;
	unsigned int texture;
	unsigned int extraTexture;
	unsigned int roof;
public:
	objFileLoader():flag(-1){};
	~objFileLoader(){};
	int load(std::string filename);
	std::vector<Plane*>  getCollisionPlane(){
		return collplane;
	}
	void drawQuads();
	void draw();
	int getFlag(){
		return flag;
	}
	int getIndex(){
		return callerIndex;
	}
	void setTexture(unsigned int t){
		texture = t;
	}
	void setExtra(unsigned int t){
		extraTexture = t;
	}
	void setRoof(unsigned int t){
		roof = t;
	}
};

unsigned int loadTexture(const char* name);



#endif