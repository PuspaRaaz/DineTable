#ifndef _VERTEX_H
#define _VERTEX_H

#include <iostream>

class vertex
{
private:
public:
	int x, y, z;
	vertex(){}
	vertex(int X, int Y, int Z = 0):x(X), y(Y), z(Z){}
	~vertex(){};
	bool operator==(const vertex & point)
	{
		return ((x == point.x) && (y == point.y) && (z == point.z));
	}
	vertex operator+(const vertex & point)
	{
		return vertex(x + point.x, y + point.y, z + point.z);
	}
	vertex operator-(const vertex & point)
	{
		return vertex(x - point.x, y - point.y, z - point.z);
	}
	vertex operator/ (float k){
		return vertex(x/k, y/k, z/k);
	}
	vertex operator* (float k){
		return vertex(x*k, y*k, z*k);
	}
};
class fourPointVertex
{
private:
public:
	int x, y, z, w;
	fourPointVertex(){}
	fourPointVertex(int x, int y, int z, int w = 1):x(x), y(y), z(z), w(w){}
	fourPointVertex(vertex v, int w = 1):x(v.x), y(v.y), z(v.z), w(w){}
	~fourPointVertex();
	bool operator == (const fourPointVertex& point){
		return((x == point.x) && (y == point.y) && (z  == point.z) && (w == point.w));
	}
	fourPointVertex operator+ (const fourPointVertex& point){
		return fourPointVertex(x + point.x, y + point.y, z + point.z, w + point.w);
	}
	fourPointVertex operator- (const fourPointVertex& point){
		return fourPointVertex(x - point.x, y - point.y, z - point.z, w - point.w);
	}
	fourPointVertex operator/ (float k){
		return fourPointVertex(x/k, y/k, z/k, w/k);
	}
	fourPointVertex operator* (float k){
		return fourPointVertex(x*k, y*k, z*k, w*k);
	}
};

#endif