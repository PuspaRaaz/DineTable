// #ifndef _TRIANGLEFILL_H_
// #define _TRIANGLEFILL_H_

#include "Basic.h"
#include "Vertex.h"
#include <SDL/SDL.h>
float zBuffer[600*480];

//pixel plot with x and y supplied differently
void setPixel(SDL_Surface* screen, int xx, int yy, float depth, Color c){
	int *pixmem32;
    int colour;
    int width = screen->w;
    int height = screen->h;
    int x=ROUNDOFF(xx); int y=ROUNDOFF(yy);
    if (x < 0 || x >= width || y < 0 || y >= height)
		return;
    colour = SDL_MapRGB ( screen->format, c.r, c.g, c.b);
	if (depth > zBuffer[x * height + y])
		return;
	zBuffer[x * height + y] = depth;
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

void TriangleFill(SDL_Surface* screen, Vertex3D v1, Vertex3D v2, Vertex3D v3, Color c){
		/* get the bounding box of the triangle */
	int maxX = MAX(v1.x, MAX(v2.x, v3.x));
	int minX = MIN(v1.x, MIN(v2.x, v3.x));
	int maxY = MAX(v1.y, MAX(v2.y, v3.y));
	int minY = MIN(v1.y, MIN(v2.y, v3.y));

	Vertex2D vs1 = Vertex2D(v2.x - v1.x, v2.y - v1.y);
	Vertex2D vs2 = Vertex2D(v3.x - v1.x, v3.y - v1.y);
	float vs1Xvs2 = vs1.x*vs2.y - vs2.x*vs1.y;

	for (int x = minX; x <= maxX; x++){
		for (int y = minY; y <= maxY; y++){
			Vertex2D q(x - v1.x, y - v1.y);
			float s = (q.x*vs2.y - q.y*vs2.x) / vs1Xvs2;
			float t = (vs1.x*q.y - q.x*vs1.y) / vs1Xvs2;

			if(s>=0 && t >=0 && (s+t) <= 1)
				setPixel(screen, x, y, v1.z, c);
		}
	}
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* window = NULL;
	window = SDL_SetVideoMode(600, 480, 32, SDL_SWSURFACE);
	for (int i = 0; i < 600*480; i++)
		zBuffer[i] = 0xffffff;
	TriangleFill(window, Vertex3D(100,100,100), Vertex3D(100,250,100),Vertex3D(250,250,100), Green);
	TriangleFill(window, Vertex3D(200,150,50), Vertex3D(200,300,50),Vertex3D(350,300,50), Red);
	TriangleFill(window, Vertex3D(250,100,100), Vertex3D(250,250,100),Vertex3D(100,100,100), Blue);
	TriangleFill(window, Vertex3D(350,150,150), Vertex3D(350,300,150),Vertex3D(200,150,150), White);
	SDL_Flip(window);
	SDL_Delay(15000);
	SDL_Quit();
	return 0;
}

// #endif