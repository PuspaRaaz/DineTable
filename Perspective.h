/*#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include "Basic.h"
#include "Matrix.h"
#include "Transformation.h"
#include "Vertex.h"

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

    //general rotation method
	if(view.z > 0)
		theta = PI - atan(view.x/view.magnitude());
	else
		theta = atan(view.x/view.magnitude());
	Matrix rotationY = rotateY(theta); //rotates about y axis, the camera position

	theta = -atan(view.y/sqrt(view.x*view.x + view.z*view.z));
	Matrix rotationX = rotateX(theta); //rotates about x axis, the camera position
    //making x and y axis of camera position symmetric with the coordinate axes makes the z axis symmetric automatically
    //general rotation method for rotation ends

    Matrix perspect = perspectiveMat(95, ratio, n, f);//gives the perspective view of the object

    //implementing general rotation method for rotation of camera coordinate axes to match with original geometric coordinate axes
    Matrix WtoVGR = (((perspect * rotationX) * rotationY) * translate);//gives the CTM for all above
    copy %= WtoVGR;

    //implementing U, V and N method for rotation of camera coordinate axes to match with original geometric coordinate axes
    Matrix WtoVUVN = ((perspect * rotation) * translate);//gives the CTM for all above
    // copy %= WtoVUVN;

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

#endif*/


#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include "Basic.h"
#include "Matrix.h"
#include "Transformation.h"
#include "Vertex.h"

//changes 3D vertex into corresponding plotable 2D vertex
Vertex3D perspective(const Vertex3D& source, const Vertex3D& cam,
    const Vertex3D& view, float n, float f, int width, int height){

    // For perspective transformation
    float ang = 120; // some view angle
    float ratio = (float)width/height; // ratio of the screen
    float maxDepth = 0x5000;
    float tangent = std::tan( RADIAN(ang/2) );
    Matrix perspective({4,4});
    perspective.init(
            1/tangent,  0,              0,              0,
            0,          ratio/tangent,  0,              0,
            0,          0,              -(n+f)/(f-n),   -(2*f*n)/(f-n),
            0,          0,              -1,              0
            );
    // Note f and n are positive values



    // For device co-ordinate
    Matrix todevice({4,4});
    todevice.init(
            width,      0,          0,              width/2,
            0,          -height,    0,              height/2,
            0,          0,          -0.5*maxDepth,  0.5 * maxDepth,
            0,          0,          0,              1.0
            );
    // here, maxDepth is the maximum value for depth,
    // if not mulitplied then we have a normalized Z value



    // For lookAt matrix


    // I have assumed that "cam" is the camera position
    // and "view" the the point where camera must look
    Vertex3D vrp = cam;
    Vertex3D vup = {0,1,0};
    Vertex3D vpn = cam - view;

    Vertex3D forward = vpn.normalized();
    Vertex3D side = (forward.crossProduct(vup)).normalized();
    Vertex3D up = (side.crossProduct(forward)).normalized();

    // UVN system is left handed so forward is negative
    // Translate + Rotate
    Matrix lookAt({4,4});
    lookAt.init(
            side.x,     side.y,     side.z,     side.dotProduct((vrp*-1)),
            up.x,       up.y,       up.z,       up.dotProduct((vrp*-1)),
            forward.x, forward.y, forward.z, forward.dotProduct((vrp*-1)),
            0,          0,          0,          1
            );


    Matrix transformer = todevice * perspective * lookAt;

    Matrix copy({4, 1});
    copy.init(source.x, source.y, source.z, 1);

    copy = transformer*copy;

    Vertex3D res;
    res.x = copy(0) / copy(3);
    res.y = copy(1) / copy(3);
    res.z = copy(2) / copy(3);

    return res;//return 2D equivalent vertex of the 3D source vertex
}

#endif
