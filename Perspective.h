#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include "Vertex.h"
#include "Basic.h"
#include "Transformation.h"
#include "Matrix.h"

//changes 3D vertex into corresponding plotable 2D vertex
Vertex2D perspective(const Vertex3D& source, const Vertex3D& cam,
	const Vertex3D& view, float n, float f, int width, int height){
	float theta;

	Matrix translate = translation(cam*-1);//translates camera position to the origin

	if(view.z > 0)
		theta = PI - atan(view.x/view.magnitude());
	else
		theta = atan(view.x/view.magnitude());
	Matrix rotationY = rotateY(theta); //rotates about y axis, the camera position

	theta = -atan(view.y/sqrt(view.x*view.x + view.z*view.z));
	Matrix rotationX = rotateX(theta); //rotates about x axis, the camera position
    //making x and y axis of camera position symmetric with the coordinate axes makes
    //the z axis symmetric automatically

	float ratio = width/height;
	Matrix perspect = perspectiveMat(95, ratio, n, f);//gives the perspective view of the object

    Matrix WtoV = (((perspect * rotationX) * rotationY) * translate);//gives the CTM for all above
    
    Matrix copy({4,1});
    copy.init(source.x, source.y, source.z, 1);//matrix of the source vertex

    copy %= WtoV;
    copy(0) /= copy(3);
    copy(1) /= copy(3);
    copy(2) /= copy(3);
    copy(0) = copy(0)*width + width/2;
    copy(1) = height/2 - copy(1)*height;
    copy(2) = (-copy(2)*0.5 + 0.5) * 0xffffff; //normalizing and fitting the view to screen size

    Vertex2D res;
    res.x = copy(0);
    res.y = copy(1);//matrix to 2D vertex

    return res;//return 2D equivalent vertex of the 3D source vertex
}

#endif