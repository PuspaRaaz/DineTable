#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Basic.h"
#include "Graphics.h"
#include "Vertex.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Vertex
{
	Ve
};

class Object3D
{
private:
	std::vector<Vertex3D> vertexBuffer;
	std::vector<Vertex3D> surfaceBuffer;
	bool texture;
public:
	Object3D():texture(false){}
	void addVertex(Vertex3D&);
	void addVertex(unsigned int, Vertex3D);
	void addSurface(Vertex3D&);
	void addnormal(Vertex3D&);
	void addTexture(Vertex3D&);
	void draw(Vertex3D&, Vertex3D&);
	void loadObject(string);
	~Object3D();	
};

#endif