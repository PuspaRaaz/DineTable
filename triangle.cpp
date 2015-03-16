#include <iostream>
#include <SDL/SDL.h>
#include "Basic.h"
#include "Vertex.h"

//pixel plot with x and y supplied differently considering depth
void setPixel(SDL_Surface* screen, int xx, int yy, float depth, Color c = White){
	int *pixmem32;
    int colour, width = screen->w, height = screen->h;
    xx=ROUNDOFF(xx); yy=ROUNDOFF(yy);
    if (xx < 0 || xx >= width || yy < 0 || yy >= height)
		return;
    colour = SDL_MapRGB ( screen->format, 255*MIN(1,c.r), 255*MIN(1,c.g), 255*MIN(1,c.b));
    yy = yy*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+yy+xx;
    *pixmem32 = colour;
}

void sortVertices(Vertex3D& a, Vertex3D& b, Vertex3D& c, Vertex3D& xx, Vertex3D& yy, Vertex3D& zz){
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

int main(){
	if((SDL_Init(SDL_INIT_EVERYTHING)) == -1) return -1; //initialize SDL
	SDL_Surface* screen;
	if((screen = SDL_SetVideoMode(800, 800, 32, SDL_SWSURFACE | SDL_RESIZABLE)) == NULL) return -1;
    	//get three vertices of the surface
		Vertex3D a = {400, 200, 50};
		Vertex3D b = {400, 300, 50};
		Vertex3D c = {200, 500, 50};

		Vertex3D n = (b-a).crossProduct(c-b)*-1;
		float d = -(a.x*n.x + a.y*n.y + a.z*n.z);

    	Vertex3D start, mid, end;
    	sortVertices(start, mid, end, a, b, c);

    	std::cout << start.x << " " << mid.x << " "<< end.x << std::endl;
    	std::cout << start.y << " " << mid.y << " "<< end.y << std::endl;



    	if (start.y >= 800 || end.y < 0) return -1;
    	if (start.y == end.y) return -1;

    	float slopeSM = (mid.x-start.x) / (mid.y-start.y);	
    	float cSM = start.y;
    	if(!EQUAL(slopeSM,0))
    	 	cSM -= start.x/ slopeSM;
    	std::cout << cSM << std::endl;

    	
    	float slopeSE = (end.x-start.x) / (end.y-start.y) ;
    	if(EQUAL(slopeSE,0))
    		return -1;
    	float cSE = start.y - start.x/slopeSE;
   		std::cout << cSE << std::endl;


    	for (int y = start.y; y < mid.y; y++){
    		int xM = (y - cSM) * slopeSM;
    		int xE = (y - cSE) * slopeSE;

    		if (xM >= xE) SWAP(xM, xE);
    		std::cout << xM << " " << xE << std::endl;

    		xM = MAX(0, xM); xE = MIN(800, xE);
    		
    		while(xM <= xE){
    			float depth = -(n.x*xM + n.y*y + d) / n.z;
				setPixel(screen, xM, y, -depth, White);
    			xM++;
    		}
    	}

/*
    	slopeSM = (mid.y-end.y) / (mid.x-end.x);
    	cSM = mid.y - slopeSM*mid.x;
    	

    	for (int y = mid.y; y <= end.y; y++){
    		float xM = (y - cSM) / slopeSM;
    		float xE = (y - cSE) / slopeSE;

    		if (xM >= xE) SWAP(xM, xE);
    		xM = MAX(0, xM); xE = MIN(800, xE);
    		while(xM <= xE){
    			float depth = -(n.x*xM + n.y*y + d) / n.z;
				setPixel(screen, xM, y, -depth, White);
    			xM++;
    		}
    	}

*/
    SDL_Flip(screen);

    SDL_Delay(5000);
    SDL_Quit();
	return 0;
}