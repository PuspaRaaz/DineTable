#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Screen.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Transformation.h"
#include "Perspective.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <SDL/SDL.h>

using namespace std;

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


class Object3D
{
private:
	std::vector<Vertex3D> vertexMatrix; //stores the array of vertices
	std::vector<Vertex3D> vertexNormal; //stores the array of vertex normals
	std::vector<Vertex3D> vertexTexture; //stores the array of vertex textures
	std::vector<Vertex3D> surfaceVertex; //stores the array of vertices of a face
	std::vector<Vertex3D> surfaceNormal; //stores the array of vertex normals of a face
	std::vector<Vertex3D> surfaceTexture; //stores the arrayo of vertex texture of a face
public:
	// Object3D(){}
	Object3D(const string&); //constructor, loads .obj file
	void addVertex(Vertex3D&); //adds a new vertex to the vertexMatrix
	void addSurface(Vertex3D&, Vertex3D&, Vertex3D&); //adds a new surface to the surfaceMatrix along with surface normals and surface textures
	void addNormal(Vertex3D&); //adds a new vertex normal to the vertexNormal
	void addTexture(Vertex3D&); //adds a new vertex texture to the vertexTexture
	void draw(Vertex3D&, Vertex3D&); //draw wireframe of the object loaded considering camera and lookAt position
	void rotate(float, float, float); //rotates the object about origin in three direction, alpha -> X, beta -> Y & gamma -> Z axis
	void scale(float); //scale the object about origin by the factor supplied
	void translate(const Vertex3D&); //translate the object by the given 3D vertex
	~Object3D(){}
};

void Object3D::translate(const Vertex3D& v){
	Matrix temp = translation(v);
	for (int i = 0; i < vertexMatrix.size(); i++)
		vertexMatrix[i] = temp * vertexMatrix[i];
	for (int i = 0; i < vertexNormal.size(); i++)
		vertexNormal[i] = temp * vertexNormal[i];
}

void Object3D::scale(float s){
	Matrix temp = scaling(s);
	for (int i = 0; i < vertexMatrix.size(); i++){
		vertexMatrix[i] = temp * vertexMatrix[i];/*
	for (int i = 0; i < vertexNormal.size(); i++)
		vertexNormal[i] = temp * vertexNormal[i];*/
}

void Object3D::rotate(float alpha, float beta, float gamma){
	Matrix RinX = rotateX(alpha);
	Matrix RinY = rotateY(beta);
	Matrix RinZ = rotateZ(gamma);
	Matrix temp = (RinZ * RinY) * RinX;
	for (int i = 0; i < vertexMatrix.size(); i++)
		vertexMatrix[i] = temp * vertexMatrix[i];
	for (int i = 0; i < vertexNormal.size(); i++)
		vertexNormal[i] = temp * vertexNormal[i];
}

void Object3D::addVertex(Vertex3D& ver){
	vertexMatrix.push_back(Vertex3D());
	unsigned int index = vertexMatrix.size() - 1;
	vertexMatrix[index] = ver;
}

void Object3D::addNormal(Vertex3D& tex){
	vertexNormal.push_back(Vertex3D());
	unsigned int index = vertexNormal.size() - 1;
	vertexNormal[index] = tex;
}

void Object3D::addTexture(Vertex3D& tex){
	vertexTexture.push_back(Vertex3D());
	unsigned int index = vertexTexture.size() - 1;
	vertexTexture[index] = tex;
}

void Object3D::addSurface(Vertex3D& ver, Vertex3D& tex, Vertex3D& nor){
	surfaceVertex.push_back(Vertex3D());
	unsigned int index = surfaceVertex.size() - 1;
	surfaceVertex[index] = ver;

	surfaceTexture.push_back(Vertex3D());
	index = surfaceTexture.size() - 1;
	surfaceTexture[index] = tex;

	surfaceNormal.push_back(Vertex3D());
	index = surfaceNormal.size() - 1;
	surfaceNormal[index] = nor;
}

void Object3D::draw(Vertex3D& cam, Vertex3D& viewPlane){
	int width = 960, height = 720;
    SDL_WM_SetCaption("DineTable", NULL);
    Screen DineTable(width, height);
    float plane = 1000;
    unsigned int len = vertexMatrix.size();
    Vertex2D v2[len];
    for(int i = 0; i < len; i++){
        v2[i] = perspective(vertexMatrix[i], cam, viewPlane, 5, 10000, width, height); //pipelining
    }
    unsigned int t1, t2;
    len = surfaceVertex.size();
    for(unsigned int i = 0; i < len; i++){
    	t1 = surfaceVertex[i].x-1;
    	t2 = surfaceVertex[i].y-1;
    	DineTable.line(v2[t1], v2[t2], White);

    	t1 = surfaceVertex[i].y-1;
    	t2 = surfaceVertex[i].z-1;
    	DineTable.line(v2[t1], v2[t2], White);

    	t1 = surfaceVertex[i].z-1;
    	t2 = surfaceVertex[i].x-1;
    	DineTable.line(v2[t1], v2[t2], White);
    }
    DineTable.refresh();
    DineTable.clear();    
}

Object3D::Object3D(const string& filename){
	vertexMatrix.clear();
	ifstream objFile(filename.c_str());
	if(!objFile.is_open()) {
		std::cout<<"Can't open the file.\n";
		throw "Can't open";
	}
	std::vector<Vertex3D> temp;
	string line, keyword;
	unsigned int vN = 0, vtN = 0, fN = 0, vnN = 0;
	while(getline(objFile, line)){
		while(line.compare(0,1," ") == 0)
			line.erase(line.begin()); //erases all leading spaces
		while(line.size() > 0 && line.compare(line.size()-1,1," ") == 0)
			line.erase(line.end()-1); //erases all following spaces

		istringstream linestream(line);
		linestream >> keyword;
		if(line.length() == 0) keyword = ""; //if line is empty, reset the keyword
		//this is to be done as the keyword remains same of the latest line and causes errors
		if(keyword == "v"){
			Vertex3D tempV;
			unsigned int t;
			linestream >> tempV.x;
			linestream >> tempV.y;
			linestream >> tempV.z;
			if(!(linestream >> t))
				t = 1.0f;
			if(t > 0 && t < 1)
				tempV = tempV / t; //normalize the vertex
			addVertex(tempV);
			vN++;
		}
		else if(keyword == "vn"){
			Vertex3D tempV;
			linestream >> tempV.x;
			linestream >> tempV.y;
			linestream >> tempV.z;
			addNormal(tempV);
			vnN++;
		}
		else if(keyword == "vt"){
			Vertex3D tempV;
			linestream >> tempV.x;
			linestream >> tempV.y;
			linestream >> tempV.z;
			addTexture(tempV);
			vtN++;
		}
		else if(keyword == "f"){
			if(line.length() > 0)
				line = line.substr(1, line.length()-1);
			while(line.compare(0,1," ")==0)
				line.erase(line.begin());
			while(line.size() > 0 && line.compare(line.size()-1,1," ")==0)
				line.erase(line.end()-1);
			replaceAll(line,"/"," ");
			istringstream lstream(line);
			Vertex3D ver, tex, nor;
			lstream >> ver.x;
			lstream >> tex.x;
			lstream >> nor.x;
			lstream >> ver.y;
			lstream >> tex.y;
			lstream >> nor.y;
			lstream >> ver.z;
			lstream >> tex.z;
			lstream >> nor.z;
			fN++;
			addSurface(ver,tex,nor);
		}
	}
	cout<<"Vertices: "<<vN<<", Normals: "<<vnN<<", Surfaces: "<<fN<<"\n"<<endl;
}

#endif
