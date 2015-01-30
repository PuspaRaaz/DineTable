#ifndef __OBJECT__
#define __OBJECT__

#include "Point.h"
#include "Matrix.h"
#include "Vector.h"
#include <iostream>

struct Edge : public Dual<unsigned>
{
	Edge(unsigned x, unsigned y) : Dual <unsigned>(x,y){}
};

struct Surface : public Threesome<unsigned>
{
	Vector normal;
	Surface(unsigned xx, unsigned yy, unsigned zz) : Threesome<unsigned>(xx, yy, zz){}
};

#endif