// #include "basicFunctions.h"
#include "matrix.h"
#include "vertex.h"
#include <iostream>

int main(){
	float arr [9] = {1,2,3,4,5,6,7,8,9};
	Matrix a(3,3), b(3,3), d(3,1);
	vertex v(1,2), u(1,2,3), w;

	w.x = w.y = w.z = 2;
	float ver[4] = {u.x,u.y,u.z}, vert[4] = {v.x,v.y,1}, verte[4] = {w.x,w.y,w.z,1};
	a.data = b.data = arr;
	d.data = ver;
	d.displayMat();
	d.data = vert;
	d.displayMat();
	d.data = verte;
	d.displayMat();
	
	Matrix c = a * b;
	
	a.displayMat();
	b.displayMat();
	c.displayMat();

	c = a * d;
	c.displayMat();
	return 0;
}
