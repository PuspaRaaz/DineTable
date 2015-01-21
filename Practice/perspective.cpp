#include <iostream>
#include "transformation.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

vertex transformTo2D(vertex threeD)
{
	vertex vanishing(0,0,300), view(0,0,100);
	vertex res;
	float h = (view.z - threeD.z)/(vanishing.z - threeD.z);
	res.x = threeD.x*h;
	res.y = threeD.y*h;
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

int main(int argc, char const *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Perspective", NULL);
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_RESIZABLE);

	vertex a(600,600,10), b(600,700,10), c(700,700,10), d(700,600,10);
	vertex e(600,600,30), f(600,700,30), g(700,700,30), h(700,600,30);
	vertex aT(150,150,150), bT(250,150,150), cT(150,150,0), dT(150,50,75);
	
	a = transformTo2D(a); b = transformTo2D(b);
	c = transformTo2D(c); d = transformTo2D(d);
	e = transformTo2D(e); f = transformTo2D(f);
	g = transformTo2D(g); h = transformTo2D(h);
	
	aT = transformTo2D(aT); bT = transformTo2D(bT);
	cT = transformTo2D(cT); dT = transformTo2D(dT);

	drawLineDDA(screen,aT,bT,255,255,255);
    drawLineDDA(screen,bT,cT,255,255,255);
    drawLineDDA(screen,cT,aT,255,255,255);
    drawLineDDA(screen,dT,aT,255,255,255);
	drawLineDDA(screen,dT,bT,255,255,255);
    drawLineDDA(screen,dT,cT,255,255,255);

	drawLineDDA(screen,a,b,255,0,0);
    drawLineDDA(screen,b,c,0,255,0);
    drawLineDDA(screen,c,d,0,0,255);
    drawLineDDA(screen,d,a,255,255,255);
	drawLineDDA(screen,e,f,255,0,0);
    drawLineDDA(screen,f,g,0,255,0);
    drawLineDDA(screen,g,h,0,0,255);
    drawLineDDA(screen,h,e,255,255,255);
    drawLineDDA(screen,a,e,255,0,0);
    drawLineDDA(screen,b,f,0,255,0);
    drawLineDDA(screen,c,g,0,0,255);
    drawLineDDA(screen,d,h,255,255,255);
	int count = 0;/*
	while(count<360){
		SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_RESIZABLE);
		
		a = rotation3D(a); b = rotation3D(b);
		c = rotation3D(c); d = rotation3D(d);
		e = rotation3D(e); f = rotation3D(f);
		g = rotation3D(g); h = rotation3D(h);

		drawLineDDA(screen,a,b,255,0,0);
	    drawLineDDA(screen,b,c,0,255,0);
	    drawLineDDA(screen,c,d,0,0,255);
	    drawLineDDA(screen,d,a,255,255,255);
		drawLineDDA(screen,e,f,255,0,0);
	    drawLineDDA(screen,f,g,0,255,0);
	    drawLineDDA(screen,g,h,0,0,255);
	    drawLineDDA(screen,h,e,255,255,255);
	    drawLineDDA(screen,a,e,255,0,0);
	    drawLineDDA(screen,b,f,0,255,0);
	    drawLineDDA(screen,c,g,0,0,255);
	    drawLineDDA(screen,d,h,255,255,255);
		
		count++;
		SDL_FreeSurface(screen);
	}*/
	
    SDL_Event event;
    bool keypress = false;    
    while (!keypress)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                //If the cross on the top is pressed it is triggered
                case SDL_QUIT:
                    keypress = true;
                break;
                //Triggered for keydown
                case SDL_KEYDOWN:
                    keypress = true;
                break;
            }
        }
    }
    SDL_Quit();
    return 0;
}
