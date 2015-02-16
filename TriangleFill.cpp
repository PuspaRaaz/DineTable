#include "Basic.h"
#include "Vertex.h"
#include <SDL/SDL.h>
float zBuffer[600*480];

//pixel plot with x and y supplied differently
void setPixel(SDL_Surface* screen, int xx, int yy, float depth, Color c){
	int *pixmem32, colour, width = screen->w, height = screen->h;
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

//draw line from point A to B with color C using DDA line drawing algorithm
void line(SDL_Surface* screen, Vertex3D A, Vertex3D B, Color c){
	float dx, dy, xInc, yInc, dInc;
	float dStart = A.z, dEnd = B.z, dVal = dStart, dDepth = dStart - dEnd;
    int step, k = 0;
    dx = B.x - A.x; dy = B.y - A.y;
    if (ABS(dx) > ABS(dy)){        step = ABS(dx);        dInc = dDepth / dx;   }
    else {    	step = ABS(dy);    	dInc = dDepth / dy;    }
    xInc = dx/step; yInc = dy/step;
    float x = A.x, y = A.y;
    do{   setPixel(screen, ROUNDOFF(x),ROUNDOFF(y), dVal,c);  x+= xInc; y+= yInc; dVal+= dInc;    k++;    }
    while(k<=step);
}

void TriangleFill(SDL_Surface* screen, Vertex3D v1, Vertex3D v2, Vertex3D v3, Camera cam, Color c){
	Vertex3D vca = v1.toVC(cam), vcb = v2.toVC(cam), vcc = v3.toVC(cam);
	Vertex3D normal = (vcb - vca).crossProduct(vcc - vca);
	float d = -(normal.x*vca.x + normal.y*vca.y + normal.z*vca.z);

	Vertex3D pa = vca.project(cam).to2D(), pb = vcb.project(cam).to2D(), pc = vcc.project(cam).to2D();

	/* get the bounding box of the triangle */
	int maxX = MAX(pa.x, MAX(pb.x, pc.x));	int minX = MIN(pa.x, MIN(pb.x, pc.x));
	int maxY = MAX(pa.y, MAX(pb.y, pc.y));	int minY = MIN(pa.y, MIN(pb.y, pc.y));

	Vertex2D vs1 = Vertex2D(pb.x - pa.x, pb.y - pa.y);	Vertex2D vs2 = Vertex2D(pc.x - pa.x, pc.y - pa.y);
	float vs1Xvs2 = vs1.x*vs2.y - vs2.x*vs1.y;

	for (int x = minX; x <= maxX; x++){
		for (int y = minY; y <= maxY; y++){
			Vertex2D q(x - pa.x, y - pa.y);
			float s = (q.x*vs2.y - q.y*vs2.x) / vs1Xvs2; float t = (vs1.x*q.y - q.x*vs1.y) / vs1Xvs2;
			if(s>=0 && t >=0 && (s+t) <= 1){
				float depth = -(x*normal.x + y*normal.y + d)/normal.z;
				setPixel(screen, x, y, depth, c);
			}
		}
	}
}
class Cuboid
{
public:
	Vertex3D a, b, c, d, e, f, g, h;
	Cuboid(float ox, float oy, float oz, float length, float breadth, float height){
		a = Vertex3D(ox, oy, oz);
	    b = Vertex3D(ox + length, oy, oz);
	    c = Vertex3D(ox + length, oy + breadth, oz);
	    d = Vertex3D(ox, oy + breadth, oz);
	    e = Vertex3D(ox, oy, oz + height);
	    f = Vertex3D(ox + length, oy, oz + height);
	    g = Vertex3D(ox + length, oy + breadth, oz + height);
	    h = Vertex3D(ox, oy + breadth, oz + height);
	}
	void draw(SDL_Surface* screen, Camera cam){
		TriangleFill(screen, a, b, c, cam, Green);
		TriangleFill(screen, a, d, c, cam, Green);

		TriangleFill(screen, e, f, g, cam, Red);
		TriangleFill(screen, e, h, g, cam, Red);

		TriangleFill(screen, a, d, e, cam, White);
		TriangleFill(screen, h, d, e, cam, White);

		TriangleFill(screen, b, f, g, cam, Blue);
		TriangleFill(screen, c, b, g, cam, Blue);

		TriangleFill(screen, a, e, b, cam, Black);
		TriangleFill(screen, b, e, f, cam, Black);
	}
	~Cuboid(){}
	
};

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* window = NULL;
	window = SDL_SetVideoMode(600, 480, 32, SDL_SWSURFACE);
	Camera camera;
	Cuboid cube(50,50,0,200,200,200);
	SDL_Event e;
	bool quit = false;
	while(!quit){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT) quit = true;
		}
		Uint8* keys = SDL_GetKeyState(0);
	    if (keys[SDLK_a]) camera.phi += 0.1;
	    if (keys[SDLK_d]) camera.phi -= 0.1;
	    
	    if (keys[SDLK_q]) camera.theta += 0.1;
	    if (keys[SDLK_e]) camera.theta -= 0.1;
	    const int delta = 2;
	    if (keys[SDLK_z]) camera.ze += delta, camera.zv += delta; //zoom in
	    if (keys[SDLK_x]) camera.ze -= delta, camera.zv -= delta; //zoom out
	    SDL_FillRect(window, &window->clip_rect, 0xbada55);
		for (int i = 0; i < 600*480; i++)	zBuffer[i] = 0xffffff;   
		cube.draw(window, camera);
		// TriangleFill(window, Vertex3D(100,100,0), Vertex3D(100,250,100),Vertex3D(250,250,200), White);
		// TriangleFill(window, Vertex3D(200,150,25), Vertex3D(200,300,125),Vertex3D(350,300,225), Red);
		// TriangleFill(window, Vertex3D(250,100,50), Vertex3D(250,250,150),Vertex3D(100,100,250), Blue);
		// TriangleFill(window, Vertex3D(350,150,75), Vertex3D(350,300,175),Vertex3D(200,150,275), Green);
		SDL_Flip(window);
	}
	SDL_Quit();
	return 0;
}