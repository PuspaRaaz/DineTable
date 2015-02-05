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
	std::vector<Vertex3D> vertexMatrix;
	std::vector<Vertex3D> vertexNormal;
	std::vector<Vertex3D> vertexTexture;
	std::vector<Vertex3D> surfaceVertex;
	std::vector<Vertex3D> surfaceNormal;
	std::vector<Vertex3D> surfaceTexture;
public:
	// Object3D(){}
	Object3D(const string&);
	void addVertex(Vertex3D&);
	void addVertex(unsigned int, Vertex3D);
	void addSurface(Vertex3D&, Vertex3D&, Vertex3D&);
	void addnormal(Vertex3D&);
	void addTexture(Vertex3D&);
	void draw(Vertex3D&, Vertex3D&);
	Matrix vMatrix();
	Matrix vtMatrix();
	Matrix vnMatrix();
	Matrix fMatrix();
	~Object3D(){}
};

void Object3D::addVertex(Vertex3D& ver){
	vertexMatrix.push_back(Vertex3D());
	unsigned int index = vertexMatrix.size() - 1;
	vertexMatrix[index] = ver;
}
void Object3D::addTexture(Vertex3D& ver){
}
void Object3D::addSurface(Vertex3D& ver, Vertex3D& tex, Vertex3D& nor){
	surfaceVertex.push_back(Vertex3D());
	unsigned int index = surfaceVertex.size() - 1;
	surfaceVertex[index] = ver;
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
	unsigned int count = 1, vN = 0, vtN = 0, fN = 0, els = 0;
	while(getline(objFile, line)){
		while(line.compare(0,1," ") == 0)
			line.erase(line.begin());
		while(line.size() > 0 && line.compare(line.size()-1,1," ") == 0)
			line.erase(line.end()-1);

		istringstream linestream(line);
		linestream >> keyword;
		if(line.length() == 0) keyword = "";
		if(keyword == "v"){
			Vertex3D tempV;
			unsigned int t;
			linestream >> tempV.x;
			linestream >> tempV.y;
			linestream >> tempV.z;
			if(!(linestream >> t))
				t = 1.0f;
			if(t > 0 && t < 1)
				tempV = tempV / t;
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
			Vertex3D ver, text;
			lstream >> ver.x;
			lstream >> text.x;
			lstream >> text.x;
			lstream >> ver.y;
			lstream >> text.y;
			lstream >> text.y;
			lstream >> ver.z;
			lstream >> text.z;
			lstream >> text.z;
			fN++;
			addSurface(ver,ver,ver);
		}
	}
	cout<<"Vertices: "<<vN<<", Surfaces: "<<fN<<endl;
}

void Object3D::draw(Vertex3D& cam, Vertex3D& viewPlane){
	int width = 960, height = 720;
    SDL_WM_SetCaption("DineTable", NULL);
    Screen DineTable(width, height);
    float plane = 1000;
    unsigned int len = vertexMatrix.size();
    Vertex2D v2[len];
    for(int i = 0; i < len; i++){
        v2[i] = perspective(vertexMatrix[i], cam, viewPlane, 5, 10000, width, height);
    }
    unsigned int t1, t2, count;
    for(unsigned int i = 0; i < len; i++){
    	count = i;
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

#endif
