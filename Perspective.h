#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include "Vertex.h"
#include "Basic.h"
#include "Matrix.h"

//changes 3D vertex into corresponding plotable 2D vertex
Vertex2D perspective(const Vertex3D& source, const Vertex3D& cam,
	const Vertex3D& view, float n, float f, int width, int height){
	Matrix translation(4,4), rotationY(4,4), rotationX(4,4);
	Matrix perspect(4,4), WtoV(4,4), src(4,1);

	float arrT[16] = {
		1, 0, 0, -cam.x,
		0, 1, 0, -cam.y,
		0, 0, 1, -cam.z,
		0, 0, 0, 1
	};
	translation.data = arrT;

	float theta;
	if(view.z > 0)
		theta = PI - atan(view.x/view.magnitude());
	else
		theta = atan(view.x/view.magnitude());
	float cosine = cos(theta);
	float sine = sin(theta);
	float arrRY[16] = {
	    cosine, 0,      sine,   0,
	    0,      1,      0,      0,
	    -sine,  0,      cosine, 0,
	    0,      0,      0,      1		
	};
	rotationY.data = arrRY;

	theta = -atan(view.y/sqrt(view.x*view.x + view.z*view.z));
	cosine = cos(theta);
	sine = sin(theta);
	float arrRX[16] = {
		1,      0,      0,      0,
        0,      cosine, -sine,  0,
        0,      sine,   cosine, 0,
        0,      0,      0,      1
	};
	rotationX.data = arrRX;

	theta = 95; float ratio = width/height;
	float tangent = tan(theta/2*PI/180);
	float arrP[16] = {
		1/tangent,  0,              0,              0,
        0,          ratio/tangent,  0,              0,
        0,          0,              -(n+f)/(f-n),   -(2*f*n)/(f-n),
        0,          0,              -1,              0
    };
    perspect.data = arrP;

    WtoV = (((perspect * rotationX) * rotationY) * translation);
    
    Matrix cop(4,1);
    float arrC[4] = {source.x, source.y, source.z, 1};
    cop.data = arrC;

    Matrix copy = WtoV * cop;
    copy(0) /= copy(3);
    copy(1) /= copy(3);
    copy(2) /= copy(3);
    copy(0) = copy(0)*width + width/2;
    copy(1) = height/2 - copy(1)*height;
    copy(2) = (-copy(2)*0.5 + 0.5) * 0xffffff;

    Vertex2D res;
    res.x = copy(0);
    res.y = copy(1);
    return res;
}

#endif