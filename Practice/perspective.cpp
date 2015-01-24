#include <iostream>
#include "transformation.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

vertex transformTo2D(vertex threeD)
{
	vertex vanishing(0,0,1200), view(0,0,300);
	vertex res;
	float h = (view.z - threeD.z)/(vanishing.z - threeD.z);
	res.x = threeD.x*h;
	res.y = threeD.y*h;
	res.z = threeD.z;
	return res;
}

vertex rotation3D(vertex v, float theta = 1)
{
	vertex res;theta = theta*3.1415926/180;
	res.x = v.x*cos(theta) + v.z*sin(theta);
	res.y = v.y;
	res.z = v.z*cos(theta) - v.x*sin(theta);
	return res;
}

vertex translate3D(vertex v, vertex translation){
	vertex res;
	res.x = v.x + translation.x;
	res.y = v.y + translation.y;
	res.z = v.z + translation.z;
	return res;
}

vertex scaling3D(vertex v, float scaleFactor = 1){
	vertex res;
	res.x = roundOff(v.x*scaleFactor);
	res.y = roundOff(v.y*scaleFactor);
	res.z = roundOff(v.z*scaleFactor);
	return res;
}
vertex scaling3D(vertex init, vertex pivot, float scalingFactor){
	vertex res;
	res.x = roundOff(init.x * scalingFactor + pivot.x * (1 - scalingFactor));
	res.y = roundOff(init.y * scalingFactor + pivot.y * (1 - scalingFactor));
	res.z = roundOff(init.z * scalingFactor + pivot.z * (1 - scalingFactor));
	return res;
}

int main(int argc, char const *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Perspective", NULL);
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_RESIZABLE);
	vertex aT(10,500,0), bT(-500,500,50), cT(500,500,100), dT(10,-150,50);
	float theta, scaleFactor;
	aT = transformTo2D(aT); bT = transformTo2D(bT);
	cT = transformTo2D(cT); dT = transformTo2D(dT);
    SDL_Event event;
    bool quit = false; bool pause = false;
    while (!quit)
    {
		SDL_Surface* screen = NULL;
		scaleFactor = 1.0f;
		vertex pivot((aT.x+bT.x+cT.x+dT.x)/4,(aT.y+bT.y+cT.y+dT.y)/4,(aT.z+bT.z+cT.z+dT.z)/4);
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
		        	switch (event.key.keysym.sym)
		        	{
		        		case SDLK_UP:
							aT = scaling3D(aT, pivot, 1.1); bT = scaling3D(bT, pivot, 1.1);
							cT = scaling3D(cT, pivot, 1.1); dT = scaling3D(dT, pivot, 1.1);
		        			break;
		        		case SDLK_DOWN:
							aT = scaling3D(aT, pivot, 0.9); bT = scaling3D(bT, pivot, 0.9);
							cT = scaling3D(cT, pivot, 0.9); dT = scaling3D(dT, pivot, 0.9);
		        			break;
		        		case SDLK_LEFT:
							aT = translate3D(aT, vertex(-5,0,0)); bT = translate3D(bT, vertex(-5,0,0));
							cT = translate3D(cT, vertex(-5,0,0)); dT = translate3D(dT, vertex(-5,0,0));
							break;
						case SDLK_RIGHT:
							aT = translate3D(aT, vertex(5,0,0)); bT = translate3D(bT, vertex(5,0,0));
							cT = translate3D(cT, vertex(5,0,0)); dT = translate3D(dT, vertex(5,0,0));
							break;
		        		case SDLK_SPACE:
		        			pause = (pause)?false:true;
		        			while(pause){
		        				SDL_Event eventPaused;
		        				while(SDL_PollEvent(&eventPaused)){
		        					switch(eventPaused.type){
						                case SDL_KEYDOWN:
								        	switch (event.key.keysym.sym)
								        	{
								        		case SDLK_SPACE:
								        			pause = (pause)?false:true;
								        			break;
								        	}
								        	break;
		        					}
		        				}
		        			}
		        			break;
		        	}
	                break;
	            case SDL_MOUSEBUTTONUP:
	            	switch(event.button.button){
	            		case SDL_BUTTON_LEFT:
							aT = scaling3D(aT, pivot, 1.01); bT = scaling3D(bT, pivot, 1.01);
							cT = scaling3D(cT, pivot, 1.01); dT = scaling3D(dT, pivot, 1.01);
		        			break;
		        		case SDL_BUTTON_RIGHT:
							aT = scaling3D(aT, pivot, 0.9); bT = scaling3D(bT, pivot, 0.9);
							cT = scaling3D(cT, pivot, 0.9); dT = scaling3D(dT, pivot, 0.9);
		        			break;	            			
	            	}
	            	break;
            }
        }
        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState( NULL );
        //If cancel x or 'q' is pressed 
        if( keystates[SDL_QUIT] || keystates[SDLK_q]) {
        	quit = true;
        }
		aT = rotation3D(aT, 0.2); bT = rotation3D(bT, 0.2);
		cT = rotation3D(cT, 0.2); dT = rotation3D(dT, 0.2);
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_RESIZABLE);
	    drawLineDDA(screen,aT,bT);
	    drawLineDDA(screen,bT,cT);
	    drawLineDDA(screen,cT,aT);
	    drawLineDDA(screen,aT,dT,255,0,0);
	    drawLineDDA(screen,bT,dT,0,255,0);
	    drawLineDDA(screen,cT,dT,0,0,255);
	    SDL_Flip(screen);
		SDL_FreeSurface(screen);
    }
    SDL_Quit();
    return 0;
}
