#include "Basic.h"
#include "Screen.h"
#include "Vertex.h"
#include <SDL/SDL.h>

int main(){
	Screen S(800,640);
    SDL_WM_SetCaption("DineTable", NULL);
    Color C(255,255,255);
    Vertex2D a(0,0), b(0,500), c(500,250), d(500,0);
    Vertex2D v[4] = {a, b, c, d};
    unsigned int t1 = 0;
    unsigned int t2 = 1;
    unsigned int t3 = 2;
    unsigned int t4 = 3;
    S.line(v[t1],v[t2],Red);
    S.line(v[t2],v[t3],Green);
    S.line(v[t3],v[t1],Blue);
    S.refresh();
    SDL_Delay(5000);
    SDL_Quit();
	return 0;
};