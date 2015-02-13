#ifndef _BASIC_H_
#define _BASIC_H_

#include <iostream>

#define PI 3.1415926 //value of pi
#define PRECISION 0.00001 //precision required
#define ABS(a) ((a < 0) ? -a : a) //absolute value
#define EQUAL(a, b) ((bool)(ABS(a - b)) <= PRECISION) //return if a and b are equal or not
#define ROUNDOFF(a) ((int)((a < 0) ? (a - 0.5) : (a + 0.5))) //gives the rounded value of float
#define RADIAN(a) (a * PI / 180) //equivalent radian value for provided degree angle
#define DEGREE(a) (a * 180 / PI) //ewuivalent angle in degree for its radian value
#define MIN(a, b) (a < b ? a : b) //minimum of two numbers
#define MAX(a, b) (a > b ? a : b) //maximum of two numbers8

template <class T>
inline void SWAP(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}
//color class 
class Color
{
public:
	int r, g, b, a;
	Color():r(255), g(255), b(255), a(255){} //default is a white
	Color(int red, int green, int blue, int alpha = 255):
		r(red), g(green), b(blue), a(alpha){}
	~Color(){}
	
};

//predifined colors with alpha -> 255
extern const Color White(255,255,255);
extern const Color Black(0, 0, 0);
extern const Color Red(255,0,0);
extern const Color Green(0,255,0);
extern const Color Blue(0,0,255);

#endif