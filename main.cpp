#include "Basic.h"
#include "Screen.h"
#include "Vertex.h"
#include "WorldToView.h"
#include <SDL/SDL.h>

int main(){
    int width = 800, height = 640;
	Screen S(width,height);
    SDL_WM_SetCaption("DineTable", NULL);
    Color C(255,255,255);
    Vertex3D cam(25,25,25), viewPlane(0,0,0);
// v 1.185411 0.974581 0.457572
// v 1.201808 0.907400 0.464548
// v 1.300536 0.907400 -0.035470
// v 1.282763 0.974581 -0.035470
    Vertex3D a(1.185411, 0.974581, 0.457572), b(1.201808, 0.907400, 0.464548), c(1.300536, 0.907400, -0.035470), d(1.282763, 0.974581, -0.035470);
    Vertex3D v3[4] = {a, b, c, d};
    Vertex2D v2[4];
    for(int i = 0; i < 4; i++){
        v2[i] = worldToView(v3[i],cam,viewPlane,0.15,0.15,width,height);
        std::cout<<v2[i].x<<" "<<v2[i].y<<"\n";
    }
    unsigned int t1 = 0;
    unsigned int t2 = 1;
    unsigned int t3 = 2;
    unsigned int t4 = 3;
    S.line(v2[t1],v2[t2],Red);
    S.line(v2[t2],v2[t3],Green);
    S.line(v2[t3],v2[t4],Blue);
    S.line(v2[t1],v2[t4],White);
    // S.line(v2[t2],v2[t4],White);
    // S.line(v2[t3],v2[t4],White);
    S.refresh();
    SDL_Delay(5000);
    SDL_Quit();

	return 0;
};