#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <cmath>
#include "Basic.h"

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
	Vertex3D normalized();
	void normalize();
	float x, y, z;
	~Vertex3D(){} //destructor
};
Vertex3D Vertex3D::normalized(){
	float m = magnitude();
	if (EQUAL(m, 0.0))
		return {0, 0, 0};
	return {x/m, y/m, z/m};
}
void Vertex3D::normalize(){
	float M = magnitude();
	if (!EQUAL(M, 0.0))
		(*this) = (*this) / M;
}
Vertex3D Vertex3D::crossProduct (const Vertex3D vec) const{
	return Vertex3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}
Vertex3D Vertex3D::operator* (const float f) const{
	return Vertex3D(x*f, y*f, z*f);
}
Vertex3D Vertex3D::operator+ (const Vertex3D vec) const{
	return Vertex3D(x+vec.x, y+vec.y, z+vec.z);
}
Vertex3D Vertex3D::operator- (const Vertex3D vec) const{
	return Vertex3D(x-vec.x, y-vec.y, z-vec.z);
}
Vertex3D Vertex3D::operator/ (const float f) const{
	return Vertex3D(x/f, y/f, z/f);
}
float Vertex3D::cosine(const Vertex3D& v) const{
	return ((*this).dotProduct(v) / ((*this).magnitude() * v.magnitude()));
}
float Vertex3D::dotProduct (const Vertex3D vec) const{
	return (x*vec.x + y*vec.y + z*vec.z);
}
float Vertex3D::magnitude() const{
	return sqrt(x*x + y*y + z*z);
}

class LightSource{
public:
	Color Intensity;
	Vertex3D pos;
	LightSource(Vertex3D v, Color c):pos(v), Intensity(c){}
	~LightSource(){}
};

class ColorVertex
{
public:
	float x, y, z;
	Color col;
	ColorVertex(){}
	ColorVertex(const ColorVertex& c):x(c.x), y(c.y), z(c.z), col(c.col){}
	ColorVertex(float a, float b, float d, Color c):x(a), y(b), z(d), col(c){}
	ColorVertex(Vertex3D v, Color c):x(v.x), y(v.y), z(v.z), col(c){}
	~ColorVertex(){}
	
};

#endif