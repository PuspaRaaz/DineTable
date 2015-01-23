//#ifndef pixelPlot;
//#define pixelPlot;
#include <iostream>
#include <cmath>
void setpixel(SDL_Surface* screen, int x,int y,int r, int g,int b)
{
    int *pixmem32;
    int colour;
    colour = SDL_MapRGB ( screen->format,r,g,b);
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

void drawLineDDA(SDL_Surface* screen, int x1, int y1, int x2, int y2, int r, int g, int b)
{
    float dx, dy, xInc, yInc;
    int step, k = 0;
    dx = x2 - x1; dy = y2 - y1;
    if (abs(dx) > abs(dy)){
        step = abs(dx);}
    else {step = (dy);}

    xInc = dx/step; yInc = dy/step;

    float x = x1, y = y1;

    do
    {
        setpixel(screen,roundOff(x),roundOff(y),r,g,b);//SDL_Flip(screen);
        x+= xInc; y+= yInc;
        k++;
    }
    while(k<=step);
    SDL_Flip(screen);
}

void drawLineBresenham(SDL_Surface* screen, vertex A, vertex B, int r, int g, int b)
{
    float x, y, dx, dy, xInc, yInc, p;
    int k = 0;
    dx = abs(B.x - A.x); dy = abs(B.y - A.y);
    xInc = (B.x - A.x)/dx; yInc = (B.y - A.y)/dy;
    x = A.x; y = A.y;

    setpixel(screen,x,y,r,g,b);

    if(dx < dy){
        p = 2*dx-dy;
        for (int k = 0; k < dy; k++){
            if(p < 0){
                y+=yInc; p+=2*dx;
            }else{
                x+=xInc; y+=yInc; p+=(2*dx-2*dy);
            }
            setpixel(screen,x,y,r,g,b);SDL_Flip(screen);
        }
    }else{
        2*dy-dx;
        for (int k = 0; k < dx; k++){
            if(p < 0){
                x+=xInc; p+=2*dy;
            }else{
                y+=yInc; x+=xInc; p+=(2*dy-2*dx);
            }
            setpixel(screen,x,y,r,g,b);SDL_Flip(screen);
        }
    }
    SDL_Flip(screen);
}

void circleDrawing(SDL_Surface* screen, int h, int k, int radius, int r, int g, int b)
{
    int p = 1 - radius, y = radius, x = 0;
    do
    {
        setpixel(screen,h+x,k+y,r,g,b);
        setpixel(screen,h+x,k-y,r,g,b);
        setpixel(screen,h-x,k+y,r,g,b);
        setpixel(screen,h-x,k-y,r,g,b);
        setpixel(screen,h+y,k+x,r,g,b);
        setpixel(screen,h+y,k-x,r,g,b);
        setpixel(screen,h-y,k+x,r,g,b);
        setpixel(screen,h-y,k-x,r,g,b);

        if(p < 0){
            x++; p+=(2*x+1);
        }else{
            x++; y--; p+=(-2*y+2*x+1);
        }
    }while(x<=y);
    SDL_Flip(screen);
}


void ellipseDrawing(SDL_Surface* screen, int h, int k, int rx, int ry, int r, int g, int b)
{
    int rySQ = ry*ry, rxSQ = rx*rx;
    float p;
    int y, x;
    	y = ry; x = 0;
	    p = rySQ - rxSQ*ry + rxSQ/4;
		do
		{
		    setpixel(screen,h+x,k+y,r,g,b);
		    setpixel(screen,h+x,k-y,r,g,b);
		    setpixel(screen,h-x,k+y,r,g,b);
		    setpixel(screen,h-x,k-y,r,g,b);

		    if(p < 0){
		        x++; p+=(2*rySQ*x+rySQ);
		    }else{
		        x++; y--; p+=(2*rySQ*x+rySQ-2*rxSQ*y);
		    }
		}while(rxSQ*y>rySQ*x);

		p = rySQ*(x+0.5)*(x+0.5) + rxSQ*(y-1)*(y-1) - rxSQ*rySQ;
		do
		{
		    setpixel(screen,h+x,k+y,r,g,b);
		    setpixel(screen,h+x,k-y,r,g,b);
		    setpixel(screen,h-x,k+y,r,g,b);
		    setpixel(screen,h-x,k-y,r,g,b);
		    
		    if(p > 0){
		        y--; p+=(rxSQ - 2*rxSQ*y);
		    }else{
		        x++; y--; p+=(2*rySQ*x+rxSQ-2*rxSQ*y);
		    }
		}while(y>=0);	
    SDL_Flip(screen);
}
