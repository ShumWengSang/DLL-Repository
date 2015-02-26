
#pragma once
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "vector3D.h"
#include <iostream>
#include "Camera.h"
#include "LoadObj.h"
#include <stdlib.h>

#define noiseWidth 64
#define noiseHeight 64
#define noiseDepth 64

using namespace std;

// For Particles
// Particle
const int MAX_PARTICLE = 30;
typedef struct
{
	float r, g, b;
	float life;
	Vector3D pos, vel;
}Particle;

typedef struct {
	float x, y, z, u, v;
	unsigned int color;
} Vertex;

typedef struct {
	int * vIndices, *nIndices, *tcIndices; int vCount;
} Face;

typedef struct _Mesh
{
	Vertex * vertices;
	Vertex * normals;
	Vertex * texCoords;
	Face * faces;
	int noVertices, noNormals, noTexCoords, noFaces;
} Mesh;




typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name

//Mouse Info
typedef struct {
	bool mLButtonUp;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
} theMouseInfo;

const int TERRAIN_SIZE=260;

class myApplication 
{
public:

	Particle ps[MAX_PARTICLE];
	// this is a constructor, it is implemented in myapplication.cpp
	myApplication();
	// this is a destructor, it is implemented in myapplication.cpp
	~myApplication();

	bool Init();
	void renderScene(void);
	void changeSize(int w, int h);
	void inputKey(int key, int x, int y);

	
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);

	static myApplication* getInstance();
	void drop();
	

	//STORM animation varaibles.
	double incr;
	float px;
	int count;
	int index;
	float  nospriteframe;
	float deltasprite;
	
	float dt;
	double noise[noiseWidth][noiseHeight][noiseDepth];

private:
	//function for rendering cat
	void renderstormanimation(void);
	//NOISE GENERATION
	double turbulence(double x, double y, double z, double size);
	void generatenoise();
	void rendernoise();
	double interpolation(double x, double y,double z);
	void HSLtoRGB(float &Rh, float &Bs, float &Gl);
	float Rh, Gs, Bl;
	float blue;
	void rendertable();
	int turbulencenum;

	//BILLBOARDING
	void billboardBegin();
	void billboardEnd();

	//PARTICLES
	void renderparticles();


	static myApplication *s_pInstance;
	// Texture mapping
//	GLuint	texture[16];			// Storage For Grass Texture
	TextureImage grassTexture[8];
	TextureImage skyTexture[1];
	TextureImage  brickTex[1];
	TextureImage cat;
	TextureImage lines;
	TextureImage storm;
	TextureImage door;
	TextureImage panels;
	TextureImage top;
	TextureImage blueline;
	TextureImage TIEtex;
	TextureImage particles;
	TextureImage greycube;
	TextureImage moss;
	TextureImage ground;

	float skyangle;

	//plane generation stuff
	int numVertices;
	int numIndices;
	Vertex* vertices;
	unsigned short* indices;

	void GeneratePlane(int slices, float radius, float height, float hTile, float vTile);

	//storage for terrain height map

	GLubyte heightmap[TERRAIN_SIZE*TERRAIN_SIZE];
	
	PFNGLACTIVETEXTUREARBPROC glActiveTextureARB; // ARB = Architecture Review Board
	PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB ;

	// Camera
	Vector3D theCameraPosition;
	Vector3D theCameraDirection;

	int counter;
	
	bool LoadHeightMap(char*filename);
	void renderMulti(void);
	void Draw3DEnvironment();
	void Update(void);
	bool LoadTGA(TextureImage *texture, char *filename);			// Loads A TGA File Into Memory

	void moveMeFlat(Vector3D deltaMove);

	void orientMe(float ang); 

	void renderGround(void);
	void renderSky(void);
	void renderQuad(void);
	void renderTerrain(void);

	float deltatime();

	void drawroof();
	void drawside(bool mode);
	void drawback(bool mode);
	void drawTIE();

	void drawcube(int w, int h, bool mode);
	void drawsidecube(int w, int h, bool mode);
	void drawtopcube(int w, int h, bool mode);
	void drawsquare();
	void drawbluedoor();

	//mouse stuff

	void moveMeForward(bool mode, float timeDiff);
	void moveMeSideway(bool mode, float timeDiff);

	float angle;

	bool myKeys[255];
	theMouseInfo mouseInfo;

	// The camera
	Camera* theCamera;

	//  The number of frames
	int frameCount;
	//  Number of frames per second
	float fps;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	int currentTime, previousTime;
	//  Pointer to a font style..

	//GLvoid *font_style;
	void *font_style;
	// Calculate the FPS
	void calculateFPS();
	// Display FPS
	void drawFPS();
	//  Draws a string at the specified coordinates.
	void printw (float x, float y, float z, char* format, ...);

	// realtime loop control
	long timelastcall;
	// realtime loop control - frequency
	float frequency;

	Mesh *LoadObj(char *filename);
	Mesh* TIE;

	void RenderMesh(Mesh *pMesh);


	GLfloat LightPosition[4];

	//TIE MOVMENT
	float TIEz, TIEy, TIEx, TIErotate;
	bool moveTIE;
	bool TIEreturn;
	void f_moveTIE();
};