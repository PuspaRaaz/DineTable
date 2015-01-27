#ifndef _POLYGON_H
#define _POLYGON_H
#include "basicFunctions.h"

class polygon
{
public:
	int vertexCount;
	vertex* point;
	polygon(int num = 0){
		if(num < 3) num = 3;
		vertexCount = num;
		point = new vertex[num];
	}
	~polygon(){}
	void drawPolygon(SDL_Surface*);
	void transformTo2D();
	void rotatePolygonX(SDL_Surface*, float);
	void rotatePolygonY(SDL_Surface*, float);
	void rotatePolygonZ(SDL_Surface*, float);
	
};

void polygon::drawPolygon(SDL_Surface* window){
	int final = vertexCount - 1;
	for (int i = 0; i < final; i++){
		drawLineDDA(window, point[i], point[i+1]);
	}
	drawLineDDA(window, point[final], point[0]);
    SDL_Flip(window);
}
void polygon::transformTo2D(){
	double zvp = 1200, zv = 300;
	for (int i = 0; i < vertexCount; i++){
		double h = (zv - point[i].z)/(zvp - zv);
		point[i].x = point[i].x*h;
		point[i].y = point[i].y*h;
		point[i].z = point[i].z*h;
	}
}
void polygon::rotatePolygonX(SDL_Surface* window, float theta = 1){
	theta = theta*3.1415926/180;
	float s = sin(theta), c = cos(theta);
	Matrix temp(4,vertexCount);
	Matrix rotation(4,4);
	// float arr[16] = {c, z, s, z, z, o, z, z, s, z,z,z,z,z,z,o};
	// rotation.data = arr;
	rotation.data[0] = 1;rotation.data[1] = 0;
	rotation.data[2] = 0;rotation.data[3] = 0;
	rotation.data[4] = 0;rotation.data[5] = c;
	rotation.data[6] = -s;rotation.data[7] = 0;
	rotation.data[8] = 0;rotation.data[9] = s;
	rotation.data[10] = c;rotation.data[11] = 0;
	rotation.data[12] = 0;rotation.data[13] = 0;
	rotation.data[14] = 0;rotation.data[15] = 1;
	
	for(int i = 0; i < vertexCount; i++){
		temp.data[0] = point[i].x; temp.data[1] = point[i].y;
		temp.data[2] = point[i].z; temp.data[3] = 1;
		temp = rotation * temp;
		point[i].x = temp.data[0]; point[i].y = temp.data[1];
		point[i].z = temp.data[2];
	}
	drawPolygon(window);
}
void polygon::rotatePolygonY(SDL_Surface* window, float theta = 1){
	theta = theta*3.1415926/180;
	float s = sin(theta), c = cos(theta);
	Matrix temp(4,1);
	Matrix rotation(4,4);
	// float arr[16] = {c, z, s, z, z, o, z, z, s, z,z,z,z,z,z,o};
	// rotation.data = arr;
	rotation.data[0] = c;rotation.data[1] = 0;
	rotation.data[2] = s;rotation.data[3] = 0;
	rotation.data[4] = 0;rotation.data[5] = 1;
	rotation.data[6] = 0;rotation.data[7] = 0;
	rotation.data[8] = -s;rotation.data[9] = 0;
	rotation.data[10] = c;rotation.data[11] = 0;
	rotation.data[12] = 0;rotation.data[13] = 0;
	rotation.data[14] = 0;rotation.data[15] = 1;
	
	for(int i = 0; i < vertexCount; i++){
		temp.data[0] = point[i].x; temp.data[1] = point[i].y;
		temp.data[2] = point[i].z; temp.data[3] = 1;
		temp = rotation * temp;
		point[i].x = temp.data[0]; point[i].y = temp.data[1];
		point[i].z = temp.data[2];
	}
	drawPolygon(window);
}
void polygon::rotatePolygonZ(SDL_Surface* window, float theta = 1){
	theta = theta*3.1415926/180;
	float s = sin(theta), c = cos(theta);
	Matrix temp(4,1);
	Matrix rotation(4,4);
	// float arr[16] = {c, z, s, z, z, o, z, z, s, z,z,z,z,z,z,o};
	// rotation.data = arr;
	rotation.data[0] = c;rotation.data[1] = -s;
	rotation.data[2] = 0;rotation.data[3] = 0;
	rotation.data[4] = s;rotation.data[5] = c;
	rotation.data[6] = 0;rotation.data[7] = 0;
	rotation.data[8] = 0;rotation.data[9] = 0;
	rotation.data[10] = 1;rotation.data[11] = 0;
	rotation.data[12] = 0;rotation.data[13] = 0;
	rotation.data[14] = 0;rotation.data[15] = 1;
	
	for(int i = 0; i < vertexCount; i++){
		temp.data[0] = point[i].x; temp.data[1] = point[i].y;
		temp.data[2] = point[i].z; temp.data[3] = 1;
		temp = rotation * temp;
		point[i].x = temp.data[0]; point[i].y = temp.data[1];
		point[i].z = temp.data[2];
	}
	drawPolygon(window);
}

#endif