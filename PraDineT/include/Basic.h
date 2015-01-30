#ifndef __BASIC__
#define __BASIC__

#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include "Exception.h"

namespace Basic{
	const float PI = 3.1415926;
	const float PRECISION = 0.00001;

	inline int ROUNDOFF(float a){
		return (a >= 0) ? (a + 0.5) : (a - 0.5);
	}

	inline bool EQUAL(float a, float b){
		return std::fabs(a - b) <= PRECISION;
	}

	template <class T>
	inline T ABS(T a){
		return (a < 0) ? -a : a;
	}

	template <class T>
	inline T MAX(T a, T b){
		return (a > b) ? a : b;
	}

	template <class T>
	inline T MIN(T a, T b){
		return (a < b) ? a : b;
	}

	inline float DEGREE(float radian){
		return (radian * 180 / PI);
	}

	inline float RADIAN(float degree){
		return (degree * PI / 180);
	}

	template <class T>
	inline void SWAP(T& a, T& b){
		T temp = a;
		a = b;
		b = temp;
	}
}

#endif