#ifndef _WORLDTOVIEW_H_
#define _WORLDTOVIEW_H_

#include "Matrix.h"
#include "Vertex.h"

//changes 3D vertex into corresponding plotable 2D vertex
Vertex2D worldToView(const Vertex3D& source, const Vertex3D& camera,
	const Vertex3D& viewPlane, float planeWidht, float planeHeight,
	int winWidth, int winHeight)
{
	Matrix WtoV(4,4);
	Vertex3D N, U, V(0, 1, 0);

	N = camera - viewPlane;
	N = N / N.magnitude();

	U = V.crossProduct(N);
	U = U / U.magnitude();

	V = N.crossProduct(U);

	Matrix translate(4,4);
	float arr[16] = {
		1, 0, 0, -camera.x,
		0, 1, 0, -camera.y,
		0, 0, 1, -camera.z,
		0, 0, 0, 1
	};
	translate.data = arr;

	Matrix rotate(4,4);
	float arr2[16] = {
		U.x, U.y, U.z, 0,
		V.x, V.y, V.z, 0,
		N.x, N.y, N.z, 0,
		0, 0, 0, 1
	};
	rotate.data = arr2;

	WtoV = rotate * translate;

	Matrix src(4,1);
	float arr3[4] = {source.x, source.y, source.z, 1};
	src.data = arr3;

	src = WtoV * src;

	Vertex2D res;
	res.x = src(0) / -src(2);
	res.y = src(1) / -src(2);

	res.x = (res.x + planeWidht*0.5) / planeWidht;
	res.y = (res.y + planeHeight*0.5) / planeHeight;

	res.x = (int)(res.x * winWidth);
	res.y = (int)(res.y * winHeight);

	return res;
}

#endif