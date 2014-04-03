#ifndef MAP_HPP
#define MAP_HPP
#include "algebra.hpp"
#include "loader.hpp"
#include "particleSystem.hpp"
#include "primitives.hpp"
class Map
{
	std::string mapName;
	objFileLoader *mapObj;
	unsigned int side;
	int startingTime;
public:
	// std::vector<Plane*> planes;
	particleSystem *fireWork;
	Map();
	Map(const char* mapName);
	~Map();
	void show();
	void testPlane();
	std::vector<Plane*> getCollisionPlane(){
		return mapObj->getCollisionPlane();
	}
	/* data */
};
#endif