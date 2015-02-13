#ifndef _TRIANGLEFILL_H_
#define _TRIANGLEFILL_H_

#include "Screen.h"
#include "Basic.h"
#include "Vertex.h"

void TriangleFill(Vertex3D v1, Vertex3D v2, Vertex3D v3){
		/* get the bounding box of the triangle */
	int maxX = MAX(v1.x, MAX(v2.x, v3.x));
	int minX = MIN(v1.x, MIN(v2.x, v3.x));
	int maxY = MAX(v1.y, MAX(v2.y, v3.y));
	int minY = MIN(v1.y, MIN(v2.y, v3.y));

	Vertex3D vs1 = Vertex3D(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	Vertex3D vs2 = Vertex3D(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
	float vs1Xvs2 = vs1.x*vs2.y - vs2.x*vs1.y;

	for (int x = minX; x <= maxX; x++){
		for (int y = minY; y <= maxY; y++){
			Vertex3D q(x - v1.x, y - v1.y, z - v1.z);
			float s = (q.x*vs2.y - q.y*vs2.x) / vs1Xvs2;
			float t = (vs1.x*q.y - q.x*vs1.y) / vs1Xvs2;

			if(s>=0 && t >=0 && (s+t) <= 1)
				drawPixel(x,y,White);
		}
	}
}

#endif