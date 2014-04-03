#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP
#include "algebra.hpp"
// #include "loader.hpp"
//Classes to construct our map and checking the constructor.
class Plane{
	Vector3D _A,_B,_C,_D;
	Vector3D _normal;
public:
	Plane(){};
	Plane(Vector3D A,Vector3D B,Vector3D C,Vector3D D,Vector3D normal);//since obj loader will provide normals here,so we don't calculate.
	~Plane(){};
	Vector3D getA(){
		return _A;
	}
	Vector3D getB(){
		return _B;
	}
	Vector3D getC(){
		return _C;
	}
	Vector3D getD(){
		return _D;
	}
	Vector3D getNormal(){
		return _normal;
	}
};


class Sphere
{
	Vector3D _center;
	float _radius;
public:
	Sphere(){};
	Sphere(Vector3D center,float radius){
		_center = center;
		_radius = radius;
	}
	~Sphere(){

	};
	float getRadius(){
		return _radius;
	}
	Vector3D getCenter(){
		return _center;
	}
	void setCenter(Vector3D center){
		_center = center;
	}
	/* data */
};

class Ray
{
	Vector3D _direction;
	Vector3D _startingPoint;
public:
	Ray(Vector3D start,Vector3D direction){
		_direction = direction;
		_startingPoint = start;
	}
	~Ray(){};
	Vector3D getDirection(){
		return _direction;
	}
	Vector3D getStart(){
		return _startingPoint;
	}
	/* data */
};

bool sphereIntersectRay(Sphere sphere,Vector3D ray,Vector3D direction,float* tValue,Vector3D* intersectionPoint);
bool planeIntersectSphere(Plane plane,Sphere sphere,Vector3D* intersectionPoint);
bool sphereIntersectSphere(Sphere sphere1,Sphere sphere2,float* t,Vector3D* intersectionPoint);
#endif