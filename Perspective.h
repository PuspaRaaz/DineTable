#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include "Vertex.h"
#include "Basic.h"
#include "Transformation.h"
#include "Matrix.h"

//changes 3D vertex into corresponding plotable 2D vertex
Vertex3D perspective(const Vertex3D& source, const Vertex3D& cam,
	const Vertex3D& view, float n, float f, int width, int height){
	float theta, ratio = width/height;
    Matrix copy({4,1});
    copy.init(source.x, source.y, source.z, 1);//matrix of the source vertex

	Matrix translate = translation(cam*-1);//translates camera position to the origin

    //U, V and N method for rotation
    Vertex3D u, v(0,1,0), N;
    N = cam - view;           N = N/N.magnitude();
    u = v.crossProduct(N);    u = u/u.magnitude();
    v = N.crossProduct(u);    v = v/v.magnitude();

    Matrix rotation({4,4});
    rotation.init(
        u.x, u.y, u.z, 0,
        v.x, v.y, v.z, 0,
        N.x, N.y, N.z, 0,
        0, 0, 0, 1
        );
    //U, V and N method ends

    //general rotation method for rotation
	if(view.z > 0)
		theta = PI - atan(view.x/view.magnitude());
	else
		theta = atan(view.x/view.magnitude());
	Matrix rotationY = rotateY(theta); //rotates about y axis, the camera position

	theta = -atan(view.y/sqrt(view.x*view.x + view.z*view.z));
	Matrix rotationX = rotateX(theta); //rotates about x axis, the camera position
    //making x and y axis of camera position symmetric with the coordinate axes makes
    //the z axis symmetric automatically
    //general rotation method for rotation ends

    Matrix perspect = perspectiveMat(95, ratio, n, f);//gives the perspective view of the object

    //implementing general rotation method for rotation of camera coordinate axes to match with original geometric coordinate axes
    Matrix WtoVGR = (((perspect * rotationX) * rotationY) * translate);//gives the CTM for all above
    // copy %= WtoVGR;

    //implementing U, V and N method for rotation of camera coordinate axes to match with original geometric coordinate axes
    Matrix WtoVUVN = ((perspect * rotation) * translate);//gives the CTM for all above
    copy %= WtoVUVN;

    copy(0) /= copy(3);
    copy(1) /= copy(3);
    copy(2) /= copy(3);
    copy(0) = copy(0)*width + width/2;
    copy(1) = height/2 - copy(1)*height;
    copy(2) = (-copy(2)*0.5 + 0.5) * 0xffffff; //normalizing and fitting the view to screen size

    Vertex3D res;
    res.x = copy(0);
    res.y = copy(1);
    res.z = copy(2);

    return res;//return 2D equivalent vertex of the 3D source vertex
}

#endif