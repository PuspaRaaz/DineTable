#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <cmath>
#include "Basic.h"

//2D vertex consisting only x and y
class Vertex2D{
public:
	Vertex2D():x(0), y(0){}
	Vertex2D(const Vertex2D& v):x(v.x),y(v.y){}
	Vertex2D(int xx, int yy):x(xx), y(yy){}
	float x, y;
	~Vertex2D(){};
};

//3D vertex with z coordinate included
class Vertex3D
{
public:
	Vertex3D crossProduct (const Vertex3D) const; //a x b
	Vertex3D operator* (const float) const; //a * f
	Vertex3D operator+ (const Vertex3D) const; //a + b
	Vertex3D operator- (const Vertex3D) const; //a - b
	Vertex3D operator/ (const float) const; //a / f
	Vertex3D():x(0), y(0), z(0){}
	Vertex3D(float xx, float yy, float zz):x(xx), y(yy), z(zz){}
	float cosine(const Vertex3D&) const; //costheta between two vectors
	float dotProduct (const Vertex3D) const; //a . b
	float magnitude() const; //|a|
	float x, y, z;
	~Vertex3D(){} //destructor
};
float Vertex3D::cosine(const Vertex3D& v) const{
	return ((*this).dotProduct(v) / ((*this).magnitude() * v.magnitude()));
}
Vertex3D Vertex3D::operator+ (const Vertex3D vec) const{
	return Vertex3D(x+vec.x, y+vec.y, z+vec.z);
}
Vertex3D Vertex3D::operator- (const Vertex3D vec) const{
	return Vertex3D(x-vec.x, y-vec.y, z-vec.z);
}
Vertex3D Vertex3D::operator* (const float f) const{
	return Vertex3D(x*f, y*f, z*f);
}
Vertex3D Vertex3D::operator/ (const float f) const{
	return Vertex3D(x/f, y/f, z/f);
}
Vertex3D Vertex3D::crossProduct (const Vertex3D vec) const{
	return Vertex3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}
float Vertex3D::dotProduct (const Vertex3D vec) const{
	return (x*vec.x + y*vec.y + z*vec.z);
}
float Vertex3D::magnitude() const{
	return sqrt(x*x + y*y + z*z);
}

class LightSource{
public:
	Vertex3D pos;
	Color Intensity;
	LightSource(Vertex3D v, Color c):pos(v), Intensity(c){}
	~LightSource(){}
};

#endif