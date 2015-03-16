#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Basic.h"
#include "Matrix.h"
#include "Perspective.h"
#include "Screen.h"
#include "Transformation.h"
#include "Vertex.h"
#include <SDL/SDL.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
	std::vector<Vertex3D> surfaceNormal; //stores the array of vertex normals of a face
	std::vector<Vertex3D> surfaceTexture; //stores the arrayo of vertex texture of a face
	std::vector<Vertex3D> surfaceVertex; //stores the array of vertices of a face
	std::vector<Vertex3D> vertexMatrix; //stores the array of vertices
	std::vector<Vertex3D> vertexNormal; //stores the array of vertex normals
	std::vector<Vertex3D> vertexTexture; //stores the array of vertex textures
public:
	Object3D(const string&); //constructor, loads .obj file
	void draw(Vertex3D&, Vertex3D&); //draw wireframe of the object loaded considering camera and lookAt position
	void rotate(float, float, float); //rotates the object about origin in three direction, alpha -> X, beta -> Y & gamma -> Z axis
	void scale(float); //scale the object about origin by the factor supplied
	void sortVertices(Vertex3D&, Vertex3D&, Vertex3D&, Vertex3D&, Vertex3D&, Vertex3D&); //sort last three vertices in ascending order according to their y value and returns through the first three arguments
	void translate(const Vertex3D&); //translate the object by the given 3D vertex
	void triangleFill(int, int, Vertex3D&, Vertex3D&);
	void drawHLine(float, float, float, Vertex3D&, float, Color);
	~Object3D(){}
};

void Object3D::sortVertices(Vertex3D& a, Vertex3D& b, Vertex3D& c, Vertex3D& xx, Vertex3D& yy, Vertex3D& zz){
	if(xx.y <= yy.y && xx.y <= zz.y){
		a = xx;
		if(yy.y <= zz.y){	b = yy; c = zz;		}
		else{	b = zz; c = yy;		}
	}
	else if(yy.y <= xx.y && yy.y <= zz.y){
		a = yy;
		if(xx.y <= zz.y){	b = xx; c = zz;		}
		else{	b = zz; c = xx;		}
	}
	else{
		a = zz;
		if(xx.y <= yy.y){	b = xx; c = yy;		}
		else{	b = yy; c = xx;		}
	}
}

void Object3D::draw(Vertex3D& cam, Vertex3D& viewPlane){
	int width = 960, height = 720;
    SDL_WM_SetCaption("DineTable", NULL);
    Screen DineTable(width, height);
    unsigned int len = vertexMatrix.size();
    Vertex3D v3[len];
    for(int i = 0; i < len; i++){
        v3[i] = perspective(vertexMatrix[i], cam, viewPlane, 5, 10000, width, height); //conversion to device coordinate
    }
    len = surfaceVertex.size();
    for(unsigned int i = 0; i < len; i++){
		unsigned int xxx = (unsigned int) surfaceVertex[i].x - 1;
		unsigned int yyy = (unsigned int) surfaceVertex[i].y - 1;
		unsigned int zzz = (unsigned int) surfaceVertex[i].z - 1;
    	DineTable.line(v3[xxx], v3[yyy], White);
    	DineTable.line(v3[yyy], v3[zzz], White);
    	DineTable.line(v3[zzz], v3[xxx], White);
    }
    DineTable.refresh();
    DineTable.clear();    
}

void Object3D::triangleFill(int width, int height, Vertex3D& cam, Vertex3D& viewPlane){

    SDL_WM_SetCaption("DineTable", NULL);
    Screen DineTable(width, height);

    Color ia(0.1,0.1,0.1), ks(0.1, 0.1, 0.1), kd(0.5, 0.5, 0.5), ka(0.5, 0.5, 0.5);

    Color ColorIntensity[surfaceVertex.size()];
    for(unsigned int i = 0; i < surfaceVertex.size(); i++){
    	//get three vertices of the surface
		Vertex3D a = vertexMatrix[ (unsigned int) surfaceVertex[i].x - 1 ];
		Vertex3D b = vertexMatrix[ (unsigned int) surfaceVertex[i].y - 1 ];
		Vertex3D c = vertexMatrix[ (unsigned int) surfaceVertex[i].z - 1 ];	

		std::vector<LightSource> light;
		LightSource redLight({{0, -200, 0},{1, 0, 0}}), greenLight({{300,0,0},{0, 1,0}}), blueLight({{-500, 0, 0},{0,0,1}});
		light.push_back(redLight); light.push_back(blueLight); light.push_back(greenLight);
		
		Vertex3D n = (b-a).crossProduct(c-b)*-1;
		Vertex3D centroid((a.x+b.x+c.x)/3, (a.y+b.y+c.y)/3, (a.z+b.z+c.z)/3);
		
		// if (n.z <= 0) continue;
		
		float intensityR = ia.r*ka.r, intensityG = ia.g*ka.g, intensityB = ia.b*ka.b;
		for(int i = 0; i < light.size(); i++){

			float costheta = (light[i].pos).cosine(n);
			if(costheta > 0){
				intensityR += light[i].Intensity.r*kd.r*costheta;
				intensityG += light[i].Intensity.g*kd.g*costheta;
				intensityB += light[i].Intensity.b*kd.b*costheta;
			}

			Vertex3D R = n*(n.dotProduct(light[i].pos - centroid))*2/(n.magnitude() * (light[i].pos - centroid).magnitude()) - light[i].pos;
			costheta = R.cosine(cam);
			if(costheta > 0){
				intensityR += light[i].Intensity.r*ks.r*pow(costheta, 2);
				intensityG += light[i].Intensity.g*ks.g*pow(costheta, 2);
				intensityB += light[i].Intensity.b*ks.b*pow(costheta, 2);
			}
		}
		ColorIntensity[i] = Color(intensityR, intensityG, intensityB);
	}

    float near = 5, far = 0xffffff;
    Vertex3D v3[vertexMatrix.size()];
    for(int i = 0; i < vertexMatrix.size(); i++){
        v3[i] = perspective(vertexMatrix[i], cam, viewPlane, near, far, width, height); //conversion to device coordinate
    }

/*



    for (int i = 0; i < surfaceVertex.size(); i++){
    	//get three vertices of the surface
		Vertex3D a = v3[ (unsigned int) surfaceVertex[i].x - 1 ];
		Vertex3D b = v3[ (unsigned int) surfaceVertex[i].y - 1 ];
		Vertex3D c = v3[ (unsigned int) surfaceVertex[i].z - 1 ];

		Vertex3D n = (b-a).crossProduct(c-b)*-1;
		float d = -(a.x*n.x + a.y*n.y + a.z*n.z);

    	Vertex3D start, mid, end;
    	sortVertices(start, mid, end, a, b, c);

    	if (start.y >= height || end.y < 0) continue;
    	if ( start.y >= end.y ) continue;


		if( EQUAL(mid.y,start.y) )
			continue;
    	float slopeSM = (mid.x-start.x) / (mid.y-start.y);
    	float cSM = start.y;
    	if(!EQUAL(slopeSM,0))
    		 cSM -= slopeSM*start.x/slopeSM;


		if( EQUAL(end.y,start.y) )
			continue;
    	float slopeSE = (end.x-start.x) / (end.y-start.y);
    	float cSE = start.y;
    	if(!EQUAL(slopeSM,0))
    		 cSE -= slopeSE*start.x/slopeSE;

    	for (int y = start.y; y <= mid.y; y++){
    		int xM = (y - cSM) * slopeSM;
    		int xE = (y - cSE) * slopeSE;


    		if (xM >= xE) SWAP(xM, xE);
    		//std::cout << xM << " " << xE << std::endl;	

    		xM = MAX(0, xM); xE = MIN(width, xE);
    		
    		while(xM <= xE){
    			float depth = -(n.x*xM + n.y*y + d) / n.z;
				DineTable.setPixel(xM, y, -depth, ColorIntensity[i]);
    			xM++;
    		}
    	}


		if( EQUAL(mid.y,end.y) )
			continue;
		if( EQUAL(mid.x,end.x) )
			continue;
    	slopeSM = (mid.y-end.y) / (mid.x-end.x);
    	cSM = mid.y - slopeSM*mid.x;

    	for (int y = mid.y; y <= end.y; y++){
    		int xM = (y - cSM) / slopeSM;
    		int xE = (y - cSE) * slopeSE;

    		if (xM > xE) SWAP(xM, xE);
    		
    		//std::cout << xM << " " << xE << std::endl;	
    		xM = MAX(0, xM); xE = MIN(width, xE);
    		
    		while(xM <= xE){
    			float depth = -(n.x*xM + n.y*y + d) / n.z;
				DineTable.setPixel(xM, y, -depth, ColorIntensity[i]);
    			xM++;
    		}
    	}
    }

*/


    for (int i = 0; i < surfaceVertex.size(); i++){
        //get three vertices of the surface
        Vertex3D a = v3[ (unsigned int) surfaceVertex[i].x - 1 ];
        Vertex3D b = v3[ (unsigned int) surfaceVertex[i].y - 1 ];
        Vertex3D c = v3[ (unsigned int) surfaceVertex[i].z - 1 ];


        Vertex3D n = (b-a).crossProduct(c-b)*-1;
        float d = -(a.x*n.x + a.y*n.y + a.z*n.z);

        Vertex3D start, mid, end;
        sortVertices(start, mid, end, a, b, c);

        if (start.y >= height || end.y < 0) continue;
        if (start.y == end.y) continue;

        float islopeSM = (mid.x-start.x) / (mid.y-start.y);
        float islopeSE = (end.x-start.x) / (end.y-start.y) ;

        float xM = start.x;
        float xE = start.x;
        for(int y = start.y; y < mid.y; y++){

            int xxM = xM;
            int xxE = xE;
            if( xxM > xxE ) SWAP(xxM, xxE);
            while (xxM <= xxE){
                float depth = -(n.x*xxM + n.y*y + d) / n.z;
                DineTable.setPixel( xxM, y, -depth, ColorIntensity[i]);
                xxM++;
            }

            xM += islopeSM;
            xE += islopeSE;
        }

        islopeSM = (mid.x-end.x) / (mid.y-end.y);

        for(int y = mid.y; y <= end.y; y++){
            int xxM = xM;
            int xxE = xE;
            if( xxM > xxE ) SWAP(xxM, xxE);
            while (xxM <= xxE){
                float depth = -(n.x*xxM + n.y*y + d) / n.z;
                DineTable.setPixel( xxM, y, -depth, ColorIntensity[i]);
                xxM++;
            }
            xM += islopeSM;
            xE += islopeSE;
        }

    }






/*
    for(unsigned int i = 0; i < surfaceVertex.size(); i++){
    	//get three vertices of the surface
		Vertex3D a = v3[ (unsigned int) surfaceVertex[i].x - 1 ];
		Vertex3D b = v3[ (unsigned int) surfaceVertex[i].y - 1 ];
		Vertex3D c = v3[ (unsigned int) surfaceVertex[i].z - 1 ];	

		//get the smallest possible rectangle that bound the given triangle
		int maxX = MAX(a.x, MAX(b.x, c.x));
		int minX = MIN(a.x, MIN(b.x, c.x));
		int maxY = MAX(a.y, MAX(b.y, c.y));
		int minY = MIN(a.y, MIN(b.y, c.y));

		Vertex3D n = (b-a).crossProduct(c-b)*-1;
		float d = -(a.x*n.x + a.y*n.y + a.z*n.z);
		//normalize the surface
		Vertex2D vs1(b.x - a.x, b.y - a.y), vs2(c.x - a.x, c.y - a.y);
		float vs1Xvs2 = vs1.x*vs2.y - vs2.x*vs1.y; //gives the normal through cross product of AB and CA

		for (int x = minX; x < maxX; x++){
			for (int y = minY; y < maxY; y++){
				Vertex2D q(x - a.x, y - a.y); //q = {point} - a
				float s = (q.x*vs2.y - q.y*vs2.x) / vs1Xvs2; //q x vs2 / AB x CA
				float t = (vs1.x*q.y - q.x*vs1.y) / vs1Xvs2; //vs1 x q / AB x CA

				if((s)>=0 && (t) >=0 && (s+t) <= 1){ //check if the pixel is inside the triangle or not
					float depth = -(n.x*x + n.y*y + d) / n.z;
					DineTable.setPixel(x, y, -depth, ColorIntensity[i]); //if inside, plot the pixel
				}
			}
		}
	}
*/

    DineTable.refresh();
    DineTable.clear();
}

void Object3D::drawHLine(float xend, float xstart, float y, Vertex3D& normal, float d, Color colour){
}

void Object3D::translate(const Vertex3D& v){
	Matrix temp = translation(v);
	for (int i = 0; i < vertexMatrix.size(); i++)
		vertexMatrix[i] = temp * vertexMatrix[i];
	for (int i = 0; i < vertexNormal.size(); i++)
		vertexNormal[i] = temp * vertexNormal[i];
}

void Object3D::scale(float s){
	Matrix temp = scaling(s);
	for (int i = 0; i < vertexMatrix.size(); i++)
		vertexMatrix[i] = temp * vertexMatrix[i];
	for (int i = 0; i < vertexNormal.size(); i++)
		vertexNormal[i] = temp * vertexNormal[i];
}

void Object3D::rotate(float alpha, float beta, float gamma){
	Matrix RinX = rotateX(alpha);
	Matrix RinY = rotateY(beta);
	Matrix RinZ = rotateZ(gamma);
	Matrix temp = RinZ * RinY * RinX;
	for (int i = 0; i < vertexMatrix.size(); i++)
		vertexMatrix[i] = temp * vertexMatrix[i];
	for (int i = 0; i < vertexNormal.size(); i++)
		vertexNormal[i] = temp * vertexNormal[i];
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
		istringstream linestream(line);
		if(line.length() == 0) continue; //if line is empty, reset the keyword
		//this is to be done as the keyword remains same of the latest line and causes errors
		if(line.length() > 0)
			line = line.substr(1, line.length()-1);
		while(line.compare(0,1," ")==0)
			line.erase(line.begin()); //removes leading spaces
		while(line.size() > 0 && line.compare(line.size()-1,1," ")==0)
			line.erase(line.end()-1); //removes trailing spaces
		linestream >> keyword; //get the details keyword
		if(keyword == "v"){
			Vertex3D tempV;
			linestream >> tempV.x;	linestream >> tempV.y;	linestream >> tempV.z;
			vertexMatrix.push_back(tempV); //add new vertex to its vector
			vN++;
		}
		else if(keyword == "vn"){
			Vertex3D tempV;
			linestream >> tempV.x;	linestream >> tempV.y;	linestream >> tempV.z;
			vertexNormal.push_back(tempV); //add new vertex normal to its vector
			vnN++;
		}
		else if(keyword == "vt"){
			Vertex3D tempV;
			linestream >> tempV.x;	linestream >> tempV.y;	linestream >> tempV.z;
			vertexTexture.push_back(tempV); //add new vertex texture to its vector
			vtN++;
		}
		else if(keyword == "f"){
			replaceAll(line,"/"," "); //replaces '/' with <space>
			istringstream lstream(line);
			Vertex3D ver, tex, nor;
			lstream >> ver.x;	lstream >> tex.x;	lstream >> nor.x;
			lstream >> ver.y;	lstream >> tex.y;	lstream >> nor.y;
			lstream >> ver.z;	lstream >> tex.z;	lstream >> nor.z;
			surfaceVertex.push_back(ver); surfaceTexture.push_back(tex); surfaceNormal.push_back(nor);//add new surface to the surface vector
			fN++;
		}
	}
	// cout<<"Vertices: "<<vN<<", Normals: "<<vnN<<", Surfaces: "<<fN<<"\n"<<endl;
}

#endif
