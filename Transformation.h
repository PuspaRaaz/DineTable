#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include "Basic.h"
#include "Matrix.h"
#include "Vertex.h"

//gives the translation matrix to translate from a 3D point to origin
Matrix translation(const Vertex3D v){
	Matrix translate({4,4});
	translate.init(
		1, 0, 0, v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,
		0, 0, 0, 1
		);
	return translate;
}

//gives the matrix that rotates around y-axis
Matrix rotateY(float theta){
	Matrix rotationY({4,4});
	float cosine = cos(theta);
	float sine = sin(theta);
	rotationY.init(
	    cosine, 0,      sine,   0,
	    0,      1,      0,      0,
	    -sine,  0,      cosine, 0,
	    0,      0,      0,      1
		);
	return rotationY;
}

//gives the matrix that rotates around y-axis
Matrix rotateX(float theta){
	Matrix rotationX({4,4});
	float cosine = cos(theta);
	float sine = sin(theta);
	rotationX.init(
		1,      0,      0,      0,
        0,      cosine, -sine,  0,
        0,      sine,   cosine, 0,
        0,      0,      0,      1
		);
	return rotationX;
}

//gives the matrix normalizes the viewpoint and pipelining
//theta = human eyes' viewing angle
//ratio = width/height
//n = near point/plane(XY)
//f = far point/plane(XY)
Matrix perspectiveMat(float theta, float ratio, float n, float f){
	Matrix perspect({4,4});
	float tangent = tan(theta*PI/360);
    perspect.init(
		1/tangent,  0,              0,              0,
        0,          ratio/tangent,  0,              0,
        0,          0,              -(n+f)/(f-n),   -(2*f*n)/(f-n),
        0,          0,              -1,              0
    	);
    return perspect;
}

#endif