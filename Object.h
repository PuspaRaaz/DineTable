#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Screen.h"
#include "Vertex.h"
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
	void addnormal(Vertex3D&); //adds a new vertex normal to the vertexNormal
	void addTexture(Vertex3D&); //adds a new vertex texture to the vertexTexture
	void draw(Vertex3D&, Vertex3D&); //draw wireframe of the object loaded considering camera and lookAt position
	void rotate(float, float, float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	~Object3D(){}
};

void Object3D::addVertex(Vertex3D& ver){
	vertexMatrix.push_back(Vertex3D());
	unsigned int index = vertexMatrix.size() - 1;
	vertexMatrix[index] = ver;
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
Object3D::Object3D(const string& filename){
	vertexMatrix.clear();
	ifstream objFile(filename.c_str());
	if(!objFile.is_open()) {
		std::cout<<"Can't open the file.\n";
		throw "Can't open";
	}
	std::vector<Vertex3D> temp;
	string line, keyword;
	unsigned int vN = 0, vtN = 0, fN = 0;
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
	cout<<"Vertices: "<<vN<<", Surfaces: "<<fN<<"\n"<<endl;
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

void Object3D::rotate(float alpha, float beta, float gamma){
	float cx = cos(alpha), sx = sin(alpha);
	float cy = cos(beta), sy = sin(beta);
	float cz = cos(gamma), sz = sin(gamma);
	for(int i = 0; i < vertexMatrix.size(); i++){
		vertexMatrix[i].x = vertexMatrix[i].x*(cz*cy) + vertexMatrix[i].y*(cz*sy*sx-sz*cx) + vertexMatrix[i].z*(sz*sx+cz*sy*cx);
		vertexMatrix[i].y = vertexMatrix[i].x*(sz*cy) + vertexMatrix[i].y*(cz*cx+sz*sy*sx) + vertexMatrix[i].z*(sz*sy*cx-cz*sx);
		vertexMatrix[i].z = vertexMatrix[i].x*(-sy) + vertexMatrix[i].y*(cy*sx) + vertexMatrix[i].z*(cy*cx);
	}
	for(int i = 0; i < vertexNormal.size(); i++){
		vertexNormal[i].x = vertexNormal[i].x*(cz*cy) + vertexNormal[i].y*(cz*sy*sx-sz*cx) + vertexNormal[i].z*(sz*sx+cz*sy*cx);
		vertexNormal[i].y = vertexNormal[i].x*(sz*cy) + vertexNormal[i].y*(cz*cx+sz*sy*sx) + vertexNormal[i].z*(sz*sy*cx-cz*sx);
		vertexNormal[i].z = vertexNormal[i].x*(-sy) + vertexNormal[i].y*(cy*sx) + vertexNormal[i].z*(cy*cx);
	}
}

void Object3D::rotateZ(float theta){
	for (int i = 0; i < vertexMatrix.size(); i++){
		vertexMatrix[i].x = vertexMatrix[i].x*cos(theta) - vertexMatrix[i].y*sin(theta);
		vertexMatrix[i].y = vertexMatrix[i].y*cos(theta) + vertexMatrix[i].x*sin(theta);
		vertexMatrix[i].z = vertexMatrix[i].z;
	}
	for (int i = 0; i < vertexNormal.size(); i++){
		vertexNormal[i].x = vertexNormal[i].x*cos(theta) - vertexNormal[i].y*sin(theta);
		vertexNormal[i].y = vertexNormal[i].y*cos(theta) + vertexNormal[i].x*sin(theta);
		vertexNormal[i].z = vertexNormal[i].z;
	}
}

void Object3D::rotateY(float theta){
	for (int i = 0; i < vertexMatrix.size(); i++){
		vertexMatrix[i].x = vertexMatrix[i].x*cos(theta) + vertexMatrix[i].z*sin(theta);
		vertexMatrix[i].y = vertexMatrix[i].y;
		vertexMatrix[i].z = vertexMatrix[i].z*cos(theta) - vertexMatrix[i].x*sin(theta);
	}
	for (int i = 0; i < vertexNormal.size(); i++){
		vertexNormal[i].x = vertexNormal[i].x*cos(theta) + vertexNormal[i].z*sin(theta);
		vertexNormal[i].y = vertexNormal[i].y;
		vertexNormal[i].z = vertexNormal[i].z*cos(theta) - vertexNormal[i].x*sin(theta);
	}
}

void Object3D::rotateX(float theta){
	for (int i = 0; i < vertexMatrix.size(); i++){
		vertexMatrix[i].x = vertexMatrix[i].x;
		vertexMatrix[i].y = vertexMatrix[i].y*cos(theta) - vertexMatrix[i].z*sin(theta);
		vertexMatrix[i].z = vertexMatrix[i].z*cos(theta) + vertexMatrix[i].y*sin(theta);
	}
	for (int i = 0; i < vertexNormal.size(); i++){
		vertexNormal[i].x = vertexNormal[i].x;
		vertexNormal[i].y = vertexNormal[i].y*cos(theta) - vertexNormal[i].z*sin(theta);
		vertexNormal[i].z = vertexNormal[i].z*cos(theta) + vertexNormal[i].y*sin(theta);
	}
}

#endif
