#ifndef __VECTOR__
#define __VECTOR__

#include "Basic.h"
#include "Container.h"
#include "Exception.h"

class Vector: public Foursome<float>{
public:
	Vector();
	Vector(float, float, float, float);
	Vector(const Vector&);
	float magnitude();
	Vector normalized();
	void normalize();
	void operator *= (float);
	void operator /= (float);
	Vector operator * (float);
	Vector operator / (float);
	void operator += (const Vector&);
	void operator -= (const Vector&);
	void operator *= (/*const*/ Vector&);//this*that
	void operator /= (/*const*/ Vector&);//that*this
	Vector operator + (const Vector&);
	Vector operator - (const Vector&);
	Vector operator * (/*const*/ Vector&);//cross product
	float operator % (/*const*/ Vector&);//dot product
	float cosine(/*const*/ Vector&, /*const*/ Vector&);//cos(theta) between 1 and 2
	float sine(/*const*/ Vector&, /*const*/ Vector&);//sin(theta) between 1 and 2
	void display() const;
};

//constructors
inline Vector::Vector():Foursome<float>(0,0,0,0){}
inline Vector::Vector(float XXX, float YYY, float ZZZ, float WWW):
	Foursome<float>(XXX, YYY, ZZZ, WWW){}
inline Vector::Vector(const Vector& vec):
	Foursome<float>(vec.x, vec.y, vec.z, vec.w){}

//vector operation functions
inline float Vector::magnitude(){
	return std::sqrt(x*x + y*y + z*z);
}
inline Vector Vector::normalized(){
	float mag = magnitude();
	if(Basic::EQUAL(mag, 0.0))
		return Vector(0, 0, 0, 0);
	return Vector(x/mag, y/mag, z/mag, w);
}
inline void Vector::normalize(){
	float mag = magnitude();
	if(!Basic::EQUAL(mag, 0.0))
		(*this) /= mag;
}

//vector arithmetic functions
inline void Vector::operator *= (float a){
	x *= a; y *= a; z *= a;
}
inline void Vector::operator /= (float a){
	x /= a; y /= a; z /= a;
}
inline Vector Vector::operator * (float a){
	Vector temp = (*this);
	temp *= a;
	return temp;
}
inline Vector Vector::operator / (float a){
	Vector temp = (*this);
	temp /= a;
	return temp;
}
inline void Vector::operator += (const Vector& v){
	x += v.x; y += v.y; z += v.z;
}
inline void Vector::operator -= (const Vector& v){
	x -= v.x; y -= v.y; z -= v.z;
}
inline void Vector::operator *= (/*const*/ Vector& v){
	(*this) = (*this) * v;
}
inline void Vector::operator /= (/*const*/ Vector& v){
	(*this) = v * (*this);
}
inline Vector Vector::operator + (const Vector& v){
	Vector temp = (*this);
	temp += v;
	return temp;
}
inline Vector Vector::operator - (const Vector& v){
	Vector temp = (*this);
	temp -= v;
	return temp;
}
inline Vector Vector::operator * (/*const*/ Vector& v){
	Vector temp;
	temp.x = y*v.z - z*v.y;
	temp.y = z*v.x - x*v.z;
	temp.z = x*v.y - y*v.x;
	return temp;
}
inline float Vector::operator % (/*const*/ Vector& v){
	return x*v.x + y*v.y + z*v.z;
}
inline float Vector::cosine(/*const*/ Vector& a, /*const*/ Vector& b){
	return (a % b)/(a.magnitude() * b.magnitude());
}
inline float Vector::sine(/*const*/ Vector& a, /*const*/ Vector& b){
	return ((a * b).magnitude())/(a.magnitude() * b.magnitude());
}
inline void Vector::display() const{
	std::cout<<"(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}

#endif