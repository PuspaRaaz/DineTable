#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <cmath>

//2D vertex consisting only x and y
class Vertex2D{
public:
	float x, y;
	Vertex2D():x(0), y(0){}
	Vertex2D(int xx, int yy):x(xx), y(yy){}
	Vertex2D(const Vertex2D& v):x(v.x),y(v.y){}
	~Vertex2D(){};
};

//3D vertex with z coordinate included
class Vertex3D
{
public:
	float x, y, z;
	Vertex3D(){}
	Vertex3D(float xx, float yy, float zz):x(xx), y(yy), z(zz){}
	Vertex3D operator+ (const Vertex3D) const; //a + b
	Vertex3D operator- (const Vertex3D) const; //a - b
	Vertex3D operator* (const float) const; //a * f
	Vertex3D operator/ (const float) const; //a / f
	// void operator*= (const Matrix&); //mat * vertex3D
	Vertex3D crossProduct (const Vertex3D) const; //a x b
	float dotProduct (const Vertex3D) const; //a . b
	float magnitude() const; //|a|
	~Vertex3D(){} //destructor
};
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
// void Vertex3D::operator*= (const Matrix& mat){
// 	Matrix point({mat.col(),1});
// 	point.init(x, y, z, 1);
// 	point %= mat;
// 	return (Vertex3D(point(0),point(1),point(2)));
// }
Vertex3D Vertex3D::crossProduct (const Vertex3D vec) const{
	return Vertex3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}
float Vertex3D::dotProduct (const Vertex3D vec) const{
	return (x*vec.x + y*vec.y + z*vec.z);
}
float Vertex3D::magnitude() const{
	return sqrt(x*x + y*y + z*z);
}

#endif