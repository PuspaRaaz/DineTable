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
	void scalePolygon(SDL_Surface*, vertex, float);
	void translatePolygon(SDL_Surface*, int, int, int);
	Matrix polygonToMatrix();
	void matrixToPolygon(Matrix);
	
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
Matrix polygon::polygonToMatrix(){
	Matrix temp(4,vertexCount);
	for(int i = 0; i < vertexCount; i++){
		temp.data[i+0*vertexCount] = point[i].x;
		temp.data[i+1*vertexCount] = point[i].y;
		temp.data[i+2*vertexCount] = point[i].z;
		temp.data[i+3*vertexCount] = 1;
	}
	return temp;
}
void polygon::matrixToPolygon(Matrix temp){
	for(int i = 0; i < vertexCount; i++){
		point[i].x = temp.data[i+0*vertexCount];
		point[i].y = temp.data[i+1*vertexCount];
		point[i].z = temp.data[i+2*vertexCount];
	}
}
void polygon::rotatePolygonY(SDL_Surface* window, float theta = 1){
	theta = theta*3.1415926/180;
	float s = sin(theta), c = cos(theta);
	Matrix rotation(4,4);
	float arr[] = {c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1};
	rotation.data = arr;	
	Matrix temp(this->polygonToMatrix());
	temp = rotation * temp;
	this->matrixToPolygon(temp);	
	drawPolygon(window);
}
void polygon::translatePolygon(SDL_Surface* window, int tx, int ty, int tz){
	Matrix translate(4,4);
	float arr[] = {1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1};
	translate.data = arr;
	Matrix temp(this->polygonToMatrix());
	temp = translate * temp;
	this->matrixToPolygon(temp);
	drawPolygon(window);
}
void polygon::scalePolygon(SDL_Surface* window, vertex pivot, float s){
	Matrix scale(4,4);
	float arr[] = {s, 0, 0, pivot.x*(1 - s), 0, s, 0, pivot.y*(1 - s), 0, 0, s, pivot.z*(1 - s), 0, 0, 0, 1};
	scale.data = arr;
	Matrix temp(this->polygonToMatrix());
	temp = scale * temp;
	this->matrixToPolygon(temp);
	drawPolygon(window);
}

#endif