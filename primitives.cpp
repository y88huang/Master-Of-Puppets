#include "primitives.hpp"
#include "polyroots.hpp"
#define EPSLON 0.0000001
Plane::Plane(Vector3D A,Vector3D B,Vector3D C,Vector3D D,Vector3D normal){
	_A=A;
	_B=B;
	_C=C;
	_D=D;
	_normal=normal;
}

float triangleArea(Vector3D A,Vector3D B,Vector3D C){
	float t1 = (B-A).length();
	float t2 = (C-B).length();
	float t3 = (C-A).length();
	float S = (t1+t2+t3)/2;
	float result = sqrt(S*((S-t1)*(S-t2)*(S-t3)));
	return result;
}
bool sphereIntersectRay(Sphere sphere,Ray r,float* tValue,Vector3D* intersectionPoint){
		Vector3D center = sphere.getCenter();
		float radius = sphere.getRadius();
		Vector3D ray = r.getStart();
		Vector3D direction = r.getDirection();
		float A = direction.dot(direction);
		Vector3D tmp = ray - center;
		float B = 2*(tmp.dot(direction));
		float C = tmp.dot(tmp) - radius*radius;
		double roots[2];
		int numberOfRoots = quadraticRoots(A,B,C,roots);
		float t = 0; //para t.
		if (numberOfRoots>0){
			if (numberOfRoots == 2){
				t = roots[0]<roots[1]?roots[0]:roots[1];
				if (t>EPSLON){
					(*tValue) = t;
					(*intersectionPoint)= ray+t*direction;
					return true;
				}
				else return false;
			}
			else if (numberOfRoots==1){ //tangent.
				t=roots[0];
				if(t>EPSLON){
					(*tValue) = t;
					(*intersectionPoint)= ray+t*direction;
					return true;
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
}
//Dynamic collision detection, transport sphere2 backward.
bool sphereIntersectSphere(Sphere sphere1,Sphere sphere2,float* t,Vector3D* intersectionPoint){
	float distance = (sphere1.getCenter() - sphere2.getCenter()).length();
	if(distance>sphere1.getRadius()+sphere2.getRadius()){
		(*t) = distance;
		return false;
	}
	else{
		Vector3D direction = sphere2.getCenter()- sphere1.getCenter();
		direction.normalize();
		(*intersectionPoint) = sphere2.getCenter() - (sphere1.getRadius()+sphere2.getRadius())*direction;
		return true;
	}
}
bool rayIntersectPlane(Ray ray,Plane plane,float* t,Vector3D* intersectionPoint){
	Vector3D A,B,C,D;
	A = plane.getA();
	B = plane.getB();
	C = plane.getC();
	D = plane.getD();
	Vector3D normal = plane.getNormal();
	Vector3D startingPoint = ray.getStart();
	Vector3D rayDirection = ray.getDirection();
	float dotProduct = rayDirection.dot(normal);
	float dist=0;
	if (dotProduct==0){//ray is parallel to the plane.
		return false;
	}
	float tmp = normal.dot(A - startingPoint);
	dist = tmp/dotProduct;//PARAMETRIC t VALUE
	// std::cout<<"the dist is "<<dist<<std::endl;
	if(dist<0){
		return false;
	}
	// Vector3D intersection = Vector3D(rayDir[0]+dist*direction[0],rayDir[1]+dist*direction[1],rayDir[2]+dist*direction[2]);
	Vector3D intersection = startingPoint + dist*rayDirection;
	//Now we ensure the rayDir actually pentrate the plane. so the rest is to ensure it is on the plane.
	float area1 = abs(triangleArea(A,C,D)-triangleArea(A,D,intersection)
					-triangleArea(A,C,intersection)-triangleArea(C,D,intersection));
	float area2 = abs(triangleArea(A,B,C)-triangleArea(A,B,intersection)
					-triangleArea(A,C,intersection)-triangleArea(B,C,intersection));
	// std::cout<<"dis is "<<dist<<std::endl;
	if(area1<EPSLON||area2<EPSLON){
		if(t!=NULL){
			(*t)=dist;
			(*intersectionPoint) = startingPoint + dist*rayDirection;
		}
		return true;
	}
	return false;
}

// bool Collision::sphereIntersectSphere(Vector3D center1,Vector3D radius1,Vector3D center2,Vector3D radius2){
// 	float t = (center1 - center2).length();
// 	if (t<radius1+radius2){
// 		return true;
// 	}
// 	else return false;
// }
bool planeIntersectSphere(Plane plane,Sphere sphere,Vector3D* intersectionPoint){
	float t0=0.0;
	float t1=0.0;
	float radius = sphere.getRadius();
	Vector3D v0,v1;
	Plane negatePlane = plane;
	Vector3D tmpNormal = plane.getNormal();
	Vector3D sphereCenter = sphere.getCenter();
	Ray ray0 = Ray(sphereCenter,-tmpNormal);
	Ray ray1 = Ray(sphereCenter,tmpNormal);

	// std::cout<<"The normal is "<<tmpNormal<<std::endl;
	// std::cout<<"The plane is "<<plane.getA()<<" "<<plane.getB()<<" "<<plane.getC()<<" "<<plane.getD()<<std::endl;
	// std::cout<<"The sphere is"<<sphere.getCenter()<<" and the radius is "<<sphere.getRadius()<<std::endl;
	if(rayIntersectPlane(ray0,plane,&t0,&v0)||rayIntersectPlane(ray1,plane,&t1,&v1)){
		// std::cout<<"Hey ray intersect plane!"<<std::endl;
		if(t0>=radius||t1>=radius) return false;
		if(t0==10.0){
			// std::cout<<"warning !!!!!"<<std::endl;
		}
		// Vector3D vector;
		else if (t0>EPSLON){//now it means t<=radius
			// std::cout<<"t0 "<<t0<<"  t1 "<<t1<<std::endl;
			(*intersectionPoint)=sphereCenter + (radius - t0)*plane.getNormal();
		}
		else if (t1>EPSLON){
			// std::cout<<"t0 "<<t0<<"  t1 "<<t1<<std::endl;
			(*intersectionPoint)=sphereCenter - (radius - t1)*plane.getNormal();
		}
		return true;
	}
	return false;
}

