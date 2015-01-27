#ifndef _POLYGON_H
#define _POLYGON_H

#include "transformation.h"

class Polygon
{
public:
	vertex* ver;
	int vertexCount;
	Polygon(int num = 0){
		if(num < 3) num = 3;
		vertexCount = num;
		ver = new vertex[vertexCount];
	}
	~Polygon(){}
	void Draw(SDL_Surface* screen){
		int initial = 0, final = this->vertexCount - 1;
		for(int i = 0; i < final; i++){
			drawLineDDA(screen, ver[i], ver[i+1]);
		}
		drawLineDDA(screen, ver[final], ver[initial]);
	}
	
};

#endif