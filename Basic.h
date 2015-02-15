#ifndef _BASIC_H_
#define _BASIC_H_

#include <iostream>

#define ABS(a) ((a < 0) ? -a : a) //absolute value
#define DEGREE(a) (a * 180 / PI) //equivalent angle in degree for its radian value
#define DELETE "\033[A\033[2K" //character to delete one line from output
#define EQUAL(a, b) ((bool)(ABS(a - b)) <= PRECISION) //return if a and b are equal or not
#define MAX(a, b) (a > b ? a : b) //maximum of two numbers
#define MIN(a, b) (a < b ? a : b) //minimum of two numbers
#define PI 3.1415926 //value of pi
#define PRECISION 0.00001 //precision required
#define RADIAN(a) (a * PI / 180) //equivalent radian value for provided degree angle
#define ROUNDOFF(a) ((int)((a < 0) ? (a - 0.5) : (a + 0.5))) //gives the nearest integer value of float

//template function to swap two numbers
template <class T>
inline  void SWAP(T& a, T& b){
	T temp = a;	a = b;	b = temp;
}

//color class 
class Color
{
public:
	int r, g, b, a; //variables to hold red, blue, green and alpha component of the color
	Color():r(255), g(255), b(255), a(255){} //default is a white
	Color(int red, int green, int blue, int alpha = 255):
		r(red), g(green), b(blue), a(alpha){}
	~Color(){}
	
};

//predifined colors with alpha -> 255
extern const Color Black(0, 0, 0, 0xff);
extern const Color Blue(0, 0, 0xff, 0xff);
extern const Color Green(0, 0xff, 0, 0xff);
extern const Color Red(0xff, 0, 0, 0xff);
extern const Color White(0xff, 0xff, 0xff, 0xff);

#endif