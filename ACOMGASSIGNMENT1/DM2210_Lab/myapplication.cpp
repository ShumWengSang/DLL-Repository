#pragma once
#include "myapplication.h"
#include <mmsystem.h>
#include "Camera.h"
#include <string>
#include <cstdlib>
#include <iostream>
#define PI 3.141

GLfloat whiteSpecularLight[] = { 0, 0, 0 };

GLfloat blackAmbientLight[] = { 0.2, 0.2, 0.2 };

GLfloat whiteDiffuseLight[] = { 0.8, 0.8, 0.8 };

myApplication * myApplication::s_pInstance = NULL;

// you can use constructor to initialise variables
myApplication::myApplication()
: counter(0), theCamera(NULL)
{
	px = -1.2;
	count = 0;
	incr = 0.008;
	index = 0;
	nospriteframe = 0;
	deltasprite = 0;
	TIEy = 0;
	TIEz = 0;
	TIEx = 0;
	TIErotate = 0;
	moveTIE = false;
	TIEreturn = false;
	turbulencenum = 256;
	LightPosition[0] = 0;
	LightPosition[1] = 110;
	LightPosition[2] = 54;
	LightPosition[3] = 1;
}

myApplication::~myApplication()
{
	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}
}

myApplication* myApplication::getInstance()
{
	if(s_pInstance == NULL)
	{
		s_pInstance = new myApplication();
	}

	return s_pInstance;
}

void myApplication::drop()
{
	if(s_pInstance != NULL)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

void myApplication::Draw3DEnvironment()
{

	/*glPushMatrix();
	glTranslatef(0,500,0);
		glRotatef(skyangle,0,1,0);
		GeneratePlane(128,300,2000,1,1);
	glPopMatrix();*/
	


	//renderTerrain();


	//glPushMatrix();
	//glTranslatef(258, 113, 0);
	//drawside(false);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-258, 113, 0);
	//glRotatef(180,0,1,0);
	//drawside(true);
	//glPopMatrix();

	//glPushMatrix();
	//glColor3f(0,0,1);
	//glTranslatef(0,113,-261);
	//glRotatef(180,0,1,0);
	//drawback(true);
	//glPopMatrix();

	//glDisable(GL_LIGHTING);
	//glPushMatrix();
	//glEnable(GL_BLEND);
	//glColor4f((float)30 / 255, (float)144 / 255, 1, 0.7);
	////glScalef(520, 185, 0);
	//glTranslatef(-280, 200, 261);
	//glRotatef(90, 1, 0, 0);
	//glScalef(8.5, 1, 3);
	
	drawbluedoor();
	rendertable();
	
	//glDisable(GL_BLEND);
	//glPopMatrix();
	//glEnable(GL_LIGHTING);

	//drawroof();

	//glDisable(GL_LIGHTING);
	//glPushMatrix();
	//rendernoise();
	//glPopMatrix();
//	glEnable(GL_LIGHTING);

	//drawTIE();

	/*glPushMatrix();
		glTranslatef(0, 50, 0);
		billboardBegin();
		renderstormanimation();
		billboardEnd();
	glPopMatrix();*/
	//glDisable(GL_DEPTH_TEST);

	//glAccum(GL_MULT, 0.3f); // multiple renders blurring, degree specified
	//glAccum(GL_ACCUM, 0.9f); //blurs certain degree & add to presentcontent
	//glAccum(GL_RETURN, 1.0f); // transfer exactly to color buffer to be swap

}

void myApplication::drawbluedoor()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glPushMatrix();
	double t = timeGetTime() / 40.0;
	//glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < noiseHeight - 1; ++i)
	{
		glPushMatrix();
		glBegin(GL_TRIANGLE_STRIP);					//BEGIN DRAWING OF THE NOISE POOL.
		for (int k = 0; k < noiseWidth; ++k)
		{
			float nextBlue;
			double nextB;
			double inter = turbulence(k, i, t, turbulencenum);

			nextB = turbulence(k, i + 1, t, turbulencenum);

			blue =   (inter / 2);

			Rh = 23, Gs = 5, Bl = 100 - blue;	//SET HSL COLORS. USING HSL BECAUSE IT IS EASIER TO MOVE THE COLORS AROUND FROM BLUE TO WHITE
			HSLtoRGB(Rh, Gs, Bl);	//CONVERT FROM HSL TO RGB
			glColor4f(Rh, Gs, Bl,0.5);
			glVertex3f(k, 0, i);
			glVertex3f(k, 0, (i + 1));
		}
		glEnd();
		glPopMatrix();
	}



	//drawcube(520, 185, false);

	glColor3f(1, 1, 1);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void myApplication::generatenoise()
{
	for (int x = 0; x < noiseWidth; ++x)
	{
		for (int y = 0; y < noiseHeight; ++y)
		{
			for (int z = 0; z < noiseDepth; ++z)
			{
				noise[x][y][z] = (rand() % 32768) / 32768.0;	//GEN BETWEEN  0 AND 1
			}
		}
	}
}

void myApplication::billboardBegin() {

	float modelview[16];
	int i, j;

	// save the current modelview matrix
	glPushMatrix();

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

	for (i = 0; i<3; i += 2)
	for (j = 0; j<3; j++) {
		if (i == j)
			modelview[i * 4 + j] = 1.0;
		else
			modelview[i * 4 + j] = 0.0;
	}

	// set the modelview matrix
	glLoadMatrixf(modelview);
}



void myApplication::billboardEnd() {

	// restore the previously 
	// stored modelview matrix
	glPopMatrix();
}

void myApplication::rendernoise()
{
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground.texID);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, moss.texID);
	//glScalef(0.5, 0.5, 0.5);

	glRotatef(180, 0, 1, 0);
	glTranslatef(0 - noiseWidth/2, 0 , 70);
	
	
	double t  = timeGetTime() / 400.0;
	//glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < noiseHeight -1; ++i)
	{
		glPushMatrix();
		glBegin(GL_TRIANGLE_STRIP);					//BEGIN DRAWING OF THE NOISE POOL.
		for (int k = 0; k < noiseWidth; ++k)
		{
			float nextBlue;
			double nextB;
			double inter = turbulence(k , i , t, turbulencenum);

			nextB = turbulence(k , i + 1, t, turbulencenum);

			blue = 10 + (inter / 4);
			
			Rh = 194, Gs = 100, Bl = blue;	//SET HSL COLORS. USING HSL BECAUSE IT IS EASIER TO MOVE THE COLORS AROUND FROM BLUE TO WHITE
			HSLtoRGB(Rh, Gs, Bl);	//CONVERT FROM HSL TO RGB

			//glColor3f(Rh, Gs, Bl); 
			glColor4f(1, 1, 1, 0.8);

			glVertex3f(k , inter, i );
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, (GLfloat)k / noiseWidth * 8, (GLfloat)i / noiseHeight * 8);//tile it with texture coords
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, (GLfloat)k / noiseWidth * 8, (GLfloat)i / noiseHeight * 8);//tile it with texture coords
			glVertex3f(k, nextB  , (i + 1) );
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, (GLfloat)k / noiseWidth * 8, (GLfloat)(i+1) / noiseHeight * 8);//tile it with texture coords
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, (GLfloat)k / noiseWidth * 8, (GLfloat)(i+1) / noiseHeight * 8);//tile it with texture coords
			//glVertex3f(k, 0, i);
			//glVertex3f(k, 0, i + 1);
		}
		glEnd();
		glPopMatrix();
	}
	//glEnd();
	glDisable(GL_BLEND);
	glActiveTextureARB(GL_TEXTURE1_ARB);//disable texture 2
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);//disable texture 2
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glColor3f(1, 1, 1);
}

void myApplication::rendertable()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
	glEnable(GL_BLEND);
	glPushMatrix();
	//glEnable(GL_TEXTURE_2D);
	glTranslatef(0, 50, 0);
	double t = timeGetTime() / 100.0;
	for (int i = 0; i < noiseHeight - 1; ++i)
	{
		for (int k = 0; k < noiseWidth; ++k)
		{
			double inter = turbulence(i, k, t, turbulencenum);
			blue = 20 + (inter / 4);

			Rh = 239, Gs = 100, Bl = blue;	//SET HSL COLORS. USING HSL BECAUSE IT IS EASIER TO MOVE THE COLORS AROUND FROM BLUE TO WHITE
			HSLtoRGB(Rh, Gs, Bl);	//CONVERT FROM HSL TO RGB

			
			//glColor4f(Rh , Gs , Bl, 0.4f );
			glColor3f(Rh, Gs, Bl);
			Bl *= 30;
			//glBindTexture(GL_TEXTURE_2D, greycube.texID);
			glPushMatrix();
			glTranslatef(i, 0, k);
			glPushMatrix();
			glTranslatef(0, Bl / 2, 0);
			glScalef(1, Bl, 1);
			glutSolidCube(1);
			glPopMatrix();
			glPopMatrix();
		}
		//glTranslatef(0, 0, 1);
	}
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable(GL_BLEND);
	glColor3f(1, 1, 1);
}



bool myApplication::LoadHeightMap(char*filename)
{
	FILE *pFile=fopen(filename,"rb");
	if(!pFile) cout<<"Error : Loading heightmap !"<<endl;
	fread( heightmap,TERRAIN_SIZE*TERRAIN_SIZE,1,pFile);
	fclose(pFile);
	return true;
}

void myApplication::Update(void)
{
	if (myKeys['w'] == true)
		moveMeForward(true, 1.0f);
	if (myKeys['a'] == true)
		moveMeSideway(true, 1.0f);
	if (myKeys['s'] == true)
		moveMeForward(false, 1.0f);
	if (myKeys['d'] == true)
		moveMeSideway(false, 1.0f);
	if (myKeys[27] == true)
		exit(0);
	if (myKeys['1'] == true){
		if (moveTIE)
			moveTIE = false;
		else
			moveTIE = true;
	}
	if (myKeys['+'] == true)
	{
		if (turbulencenum < 256)	//CLAMPING THE VALUE
			turbulencenum += turbulencenum;
		cout << turbulencenum<< endl;
	}
	if (myKeys['-'] == true)
	{
		if (turbulencenum > 1)		//CLAMPING THE VALUE
			turbulencenum /= 2;
	}
	skyangle += 20 * dt;

	if(skyangle >= 360)
		skyangle = 0;
}



void myApplication::renderScene(void) {

	/*static int frame = 0;
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	++frame; 
	int time = glutGet(GLUT_ELAPSED_TIME);
	dt = (time - lastTime) / 1000.f ;
	lastTime = time;*/

	// Clear the buffer
	glDisable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); 

	//glLoadIdentity();

	theCamera->Update();

	calculateFPS();
	if ((timeGetTime()-timelastcall)>1000/frequency)
	{
		// Calculate the framerate
		timelastcall=timeGetTime();
		Update();
	}
	//glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.09);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0010);
	Draw3DEnvironment();

	/*glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	f_moveTIE();
	glEnable(GL_LIGHTING);*/
	// Enable 2D text display and HUD
	theCamera->SetHUD( true );

	glDisable(GL_DEPTH_TEST);

	// Display framerate
	drawFPS();
	

	theCamera->SetHUD( false ); 

	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}



void myApplication::changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);

	glClearAccum(0.0f, 0.0f, 0.0f, 1.0f); // clear to black
	glClear(GL_ACCUM_BUFFER_BIT); //clear screen with accumulation buffer
}

void myApplication::moveMeFlat(Vector3D deltaMove) 
{
	theCameraPosition.x += deltaMove.x;
	theCameraPosition.y += deltaMove.y;
	theCameraPosition.z += deltaMove.z;

}

void myApplication::orientMe(float ang) 
{
	theCameraDirection.x += sin(ang);
	theCameraDirection.z += -cos(ang);
}


void myApplication::inputKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : 
			moveMeFlat(Vector3D(1,0,0));break;
		case GLUT_KEY_RIGHT : 
			moveMeFlat(Vector3D(-1,0,0));break;
		case GLUT_KEY_UP : 
			moveMeFlat(Vector3D(0,0,1));break;
		case GLUT_KEY_DOWN : 
			moveMeFlat(Vector3D(0,0,-1));break;
	}

	counter++;
	if (counter>9)
		counter=0;
}


bool myApplication::Init(void)
{

	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 0.0, 80.0, 130.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 ); 

					// Enable Texture Mapping ( NEW )
	if (!LoadTGA(&skyTexture[0],"space.tga"))				// Load The grass Texture
		return false;										// If Loading Failed, Return False

	if(!LoadHeightMap("heightmap.raw"))
		return false;

	if (!LoadTGA(&storm, "stormmove.tga"))
		return false;

	if (!LoadTGA(&blueline, "blue.tga"))
		return false;

	if (!LoadTGA(&door, "doordone.tga"))
		return false;

	if(!LoadTGA(&lines,"cubeline.tga"))
		return false;

	if (!LoadTGA(&panels, "template.tga"))
		return false;

	if (!LoadTGA(&top, "toptexture.tga"))
		return false;

	if (!LoadTGA(&particles, "particle1.tga"))
		return false;

	if (!LoadTGA(&TIEtex, "tietexture.tga"))
		return false;

	if (!LoadTGA(&greycube, "cubeline.tga"))
		return false;

	if (!LoadTGA(&moss, "moss1.tga"))
		return false;

	if (!LoadTGA(&ground, "ground.tga"))
		return false;

	TIE = LoadObj("TIE.obj");


	// Load hardware supported extensions
	char *extension = (char*)glGetString(GL_EXTENSIONS);

	// Check multitexture support 
	if(strstr(extension, "GL_ARB_multitexture") == 0)
		cout << "Error : Multi texture not supported !" << endl;
	
	// Load multitexture function
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	
	if(!glActiveTextureARB || !glMultiTexCoord2fARB)  // check functions are loaded
		cout << "Error : Loading multi texture functions !"<< endl;

	
	angle = 0.0f;
	mouseInfo.lastX = 800 >> 1;
	mouseInfo.lastY = 600 >> 1;

	//  The number of frames
	frameCount = 0;
	//  Number of frames per second
	fps = 0;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	currentTime = 0, previousTime = 0;
	//  Pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	// realtime loop control
	timelastcall=timeGetTime();
	frequency = 30.0f;
	generatenoise();
	skyangle = 0;

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		float negx = rand() % 2;
		float negz = rand() % 2;
		float x = (((float)rand() / RAND_MAX) - 0.5f) / 15;
		float y = ((float)rand() / RAND_MAX) / 2;
		float z = ((float)rand() / RAND_MAX) / 2;
		if(negx == 0)
		{
			x = -x;
		}
		if(negz == 0)
		{
			z = -z;
		}
		ps[i].vel = Vector3D(x, y + 0.2, z) * 3; // Direction

		x = (((float)rand() / RAND_MAX) - 0.5f) / 2;
		y = (((float)rand() / RAND_MAX) - 0.5f) / 2;
		z = (((float)rand() / RAND_MAX) - 0.5f) / 2;
		ps[i].pos = Vector3D(x, y, z); // Position

		float a = ((float)rand() / RAND_MAX);//LIFE
		ps[i].life = a;
	}

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	

	//glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2000.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

	glShadeModel(GL_SMOOTH); //set the shader to smooth shader

	return true;
}

void myApplication::moveMeForward(bool mode, float timeDiff) 
{
	if (mode)
	{
		theCamera->Walk( 5.0f );
	}
	else
	{
		theCamera->Walk( -5.0f );
	}
}

void myApplication::moveMeSideway(bool mode, float timeDiff)
{
	if (mode)
	{
		theCamera->Strafe( -5.0f );
	}
	else
	{
		theCamera->Strafe( 5.0f );
	}
}

//void myApplication::orientMe(float ang) 
//{
//	theCamera->Yaw( ang );
//}

void myApplication::KeyboardDown(unsigned char key, int x, int y){

	myKeys[key]= true;
}

void myApplication::KeyboardUp(unsigned char key, int x, int y){

	myKeys[key]= false;
}

void myApplication::MouseMove (int x, int y) {
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;

	//Update on y axis
	theCamera->Pitch( diffY * 3.142f / 180.0f );

	//Update on x and z axis
	angle += (float) diffX * 3.142f / 180.0f;
	if (angle > 6.284f)
		angle -= 6.284f;
	else if (angle < -6.284f)
		angle += 6.284f;

	theCamera->Yaw( -angle );

	mouseInfo.lastX = x;
	mouseInfo.lastY = y;

	//Checking mouse boundary. //	 800 is the window width. You may need to change this to suit your program.
	if  (mouseInfo.lastX > 800-20 || mouseInfo.lastX < 20)
	{
		mouseInfo.lastX = (800 >> 1);
		glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	}
	//	 600 is the window height. You may need to change this to suit your program.
	if (mouseInfo.lastY > 600-20 || mouseInfo.lastY < 20)
	{
		mouseInfo.lastY = (600 >> 1);
		glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	}
}

void myApplication::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			mouseInfo.mLButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;
			
			if (mouseInfo.mLButtonUp) {
				//	Add codes to manage the bullets shot out and the remaining bullets
			}
			
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}


void myApplication::renderMulti()
{
	//set frist texture
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,grassTexture[5].texID);

	//set second texture

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,grassTexture[7].texID);

	glPushMatrix();
		glBegin(GL_QUADS);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0.0f,0.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
			glVertex3f(-1.0f,-1.0f,1.0f);	//bottom left

			
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1.0f,0.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,1.0f,0.0f);
			glVertex3f(1.0f,-1.0f,1.0f);	//bottom right

			
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1.0f,1.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,1.0f,1.0f);
			glVertex3f(1.0f,1.0f,1.0f);	//top right

			
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0.0f,1.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,1.0f);
			glVertex3f(-1.0f,1.0f,1.0f);	//top left
		glEnd();
	glPopMatrix();

	glActiveTextureARB(GL_TEXTURE1_ARB);//disable texture 2
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);//disable texture 1
	glDisable(GL_TEXTURE_2D);
}


bool myApplication::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}


void myApplication::GeneratePlane(int slices, float radius, float height, float hTile, float vTile)
{ 
	(slices < 1) ? (slices = 1) : (slices > 256) ? (slices = 256) : (slices);	
	numVertices = ( slices + 1 ) * ( slices + 1 );
	numIndices = slices * slices * 2 * 3;
	vertices = new Vertex[numVertices];
	indices = new unsigned short[numIndices];
	float planeSize = 2.0f * sqrtf((height*height) - (radius*radius));
	float delta = planeSize / (float)slices;
	float texDelta = 2.0f / (float)slices;
	for ( int z = 0; z <= slices; ++z )
	{
		for ( int x = 0; x <= slices; ++x )
		{
			float xDist = (-0.5f * planeSize) + ( (float)x * delta );
			float zDist = (-0.5f * planeSize) + ( (float)z * delta );
			float xHeight = ( xDist * xDist ) / height;
			float zHeight = ( zDist * zDist ) / height;
			float height = xHeight + zHeight;
			Vertex vertex;
			vertex.x = xDist;
			vertex.y = -height;
			vertex.z = zDist;

			// Calculate the texture coordinates
			vertex.u = hTile * ((float)x * texDelta * 0.5f);
			vertex.v = vTile * (1.0f - (float)z * texDelta * 0.5f);
			vertices[z * (slices+1) + x] = vertex;
		}
	}
	int index = 0;	// Indices	
	for (int i=0; i < slices; ++i)
	{
		for (int j=0; j < slices; ++j)
		{
			int startvert = (i * (slices+1) + j);		    
			indices[index++] = startvert;// tri 1
			indices[index++] = startvert + 1;
			indices[index++] = startvert + slices + 1;
			indices[index++] = startvert + 1; 	// tri 2
			indices[index++] = startvert + slices + 2;
			indices[index++] = startvert + slices + 1;
		}
	}
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glScalef(0.25f,0.25f,0.25f);//makes the plane smaller;
		glBindTexture(GL_TEXTURE_2D,skyTexture[0].texID);
		glBegin(GL_TRIANGLES);
			for(int i=0;i<numIndices;++i)
			{
				glColor3f(1.0f,1.0f,1.0f);
				unsigned short index=indices[i];
				glTexCoord2f(vertices[index].u,vertices[index].v);
				glVertex3f(vertices[index].x,vertices[index].y,vertices[index].z);
			}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	delete vertices;
	delete indices;
}

void myApplication::renderparticles()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, particles.texID);
	glEnable(GL_BLEND);
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		static const Vector3D inipos = ps[i].pos;

		ps[i].vel.y -= 0.05;
		ps[i].pos = ps[i].pos + ps[i].vel;
		ps[i].life -= 0.01f;
		if (ps[i].life < 0.005f)
		{
			ps[i].life = rand() % 5;
			ps[i].pos = inipos;
			ps[i].vel.y = ((float)rand() / RAND_MAX) / 2+1;
		}
		if (ps[i].life > 0.0f)
		{
			glPushMatrix();
			glTranslatef(ps[i].pos.x, ps[i].pos.y + 50, ps[i].pos.z - 80.f);
			glColor4f(ps[i].life, ps[i].life, 0, ps[i].life);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
			glEnd();
			glPopMatrix();
		}
		if (ps[i].pos.y <= -50)
		{
			
			ps[i].vel.y = -ps[i].vel.y;
			ps[i].vel.y -= 1;
		}
	}
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void myApplication::renderGround(void) {
	glPushMatrix();
	glTranslatef( -10.0f, 0.0f, 0.0f );
	glColor3f(1.0,1.0,1.0);

	glRotatef(90,1,0,0);

		//set frist texture
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,lines.texID);

	//set second texture

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground.texID);

	glBegin(GL_QUADS);
	double w = 64;
	double h = 64;

	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0.0f,0.0f);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
	glVertex3f(-w,-h,1.0f);	//bottom left


	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1.0f,0.0f);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,8.0f,0.0f);
	glVertex3f(w,-h,1.0f);	//bottom right


	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1.0f,1.0f);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,8.0f,8.0f);
	glVertex3f(w,h,1.0f);	//top right


	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0.0f,1.0f);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,8.0f);
	glVertex3f(-w,h,1.0f);	//top left
	glEnd();

	glPopMatrix();

	glActiveTextureARB(GL_TEXTURE1_ARB);//disable texture 2
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);//disable texture 1
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_DEPTH_TEST);
}

void myApplication::renderSky(void) {

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
		glBindTexture(GL_TEXTURE_2D, skyTexture[0].texID);

			glBegin(GL_QUADS);
			glTexCoord2f(1,0);			glVertex3f(-10,4,-10);
			glTexCoord2f(1,1);			glVertex3f(10,4,-10);
			glTexCoord2f(0,1);			glVertex3f(10,4,10);
			glTexCoord2f(0,0);			glVertex3f(-10,4,10);
			glEnd();
	glPopMatrix();
}

void myApplication::renderQuad()
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D,brickTex[0].texID);
		glColor3f(1.0f,1.0f,1.0f);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-1.0f,-1.0f,-6.0f);
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(1.0f,-1.0f,-6.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(1.0f,1.0f,-6.0f);
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(-1.0f,1.0f,-6.0f);
		}
		glEnd();
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glAlphaFunc(GL_ALWAYS, 0.99f);
	glEnable(GL_ALPHA_TEST);
	glColor4f(1.0f,0.0f,0.0f,0.9f);

		glPushMatrix();
		glTranslatef(-0.5f,0.0f,0.0f);
		glColor3f(1.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-1.0f,-1.0f,-6.0f);
			glVertex3f(1.0f,-1.0f,-6.0f);
			glVertex3f(1.0f,1.0f,-6.0f);
			glVertex3f(-1.0f,1.0f,-6.0f);
			glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);


	glPopMatrix();
}

void myApplication::renderTerrain(void)
{
	const float MAX_HEIGHT = 35.0f;
	const float SCALE_FACTOR = 256.0f/MAX_HEIGHT;
	glPushMatrix();

	//Draw terrain

	//set frist texture
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,lines.texID);

	

	//glColor4f (1.0, 1.0, 1.0, 0.6);
	glScalef(2, 2, 2);
	for(int z=0;z< TERRAIN_SIZE-1;++z)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(int x=0;x<  TERRAIN_SIZE;++x)
		{
			float scaledHeight=heightmap[z*TERRAIN_SIZE+x]/SCALE_FACTOR;
			
			float nextScaledHeight=heightmap[(z+1)*TERRAIN_SIZE+x]/SCALE_FACTOR;
			float color=0.5f+0.5f*scaledHeight/MAX_HEIGHT;//Brighter color shade
			float nextColor=0.5f+0.5f*nextScaledHeight/MAX_HEIGHT;

			glColor3f(color,color,color);//scale of height
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,(GLfloat)x/TERRAIN_SIZE*8,(GLfloat)z/TERRAIN_SIZE*8);//tile it with texture coords
			
			glVertex3f(static_cast<GLfloat>(x-TERRAIN_SIZE/2),scaledHeight,static_cast<GLfloat>(z-TERRAIN_SIZE/2));
			//glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE / 2), scaledHeight, static_cast<GLfloat>(0 - TERRAIN_SIZE / 2));
			glColor3f(nextColor,nextColor,nextColor);
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,(GLfloat)x/TERRAIN_SIZE*8,(GLfloat)(z+1)/TERRAIN_SIZE*8);//tile it with texture coords
			
			glVertex3f(static_cast<GLfloat>(x-TERRAIN_SIZE/2),nextScaledHeight,static_cast<GLfloat>(z+1-TERRAIN_SIZE/2));

			
			//glVertex3f(static_cast<GLfloat>(x - TERRAIN_SIZE / 2), nextScaledHeight, static_cast<GLfloat>(0 + 1 - TERRAIN_SIZE / 2));

			
		}
		glEnd();
	}
	
	glActiveTextureARB(GL_TEXTURE1_ARB);//disable texture 2
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);//disable texture 1
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

void myApplication::HSLtoRGB(float &Rh, float &Gs, float &Bl)
{
	float min, max;
	Gs /= 100;
	Bl /= 100;
	float R, G, B;
	//IF NO SATURATION, ITS GREY.
	if (Gs == 0)
	{
		R = Bl * 255;
		G = Bl * 255;
		B = Bl * 255;
	}
	else
	{
		float temp1;
		float temp2;
		//USE RIGHT FORMULA TO FIND RGB
		if (Bl < 0.5)
		{
			temp1 = Bl * (1.0 + Gs);
		}
		else if (Bl >= 0.5)
		{
			temp1 = Bl + Gs - Bl * Gs;
		}
		temp2 = 2 * Bl - temp1;
		
		Rh /= 360;

		R = Rh + 0.333;
		G = Rh;
		B = Rh - 0.333;

		//SET ALL VALUES TO BETWEEN 0 AND 1
		if (R > 1)
			R - 1;
		else if (R < 1)
			R + 1;
		if (G > 1)
			G - 1;
		else if (G < 1)
			G + 1;
		if (B > 1)
			B - 1;
		else if (B < 1)
			B + 1;
		//NOW START TO FIND THE NUMBERS FOR RGB WITH THESE TESTS. 3 TESTS TO DETERMINE WHAT FORMULA TO USE
		//RED SEARCH
		if (6 * R < 1)
		{
			R = temp2 + (temp1 - temp2) * 6 * R;
		}
		else if (2 * R < 1)
		{
			R = temp1;
		}
		else if (3 * R < 2)
		{
			R = temp2 + (temp1 - temp2) * (0.6666 - R) * 6;
		}
		else
		{
			R = temp2;
		}
		//NOW DO BLUE
		if (6 * B < 1)
		{
			B = temp2 + (temp1 - temp2) * 6 * B;
		}
		else if (2 * B < 1)
		{
			B = temp1;
		}
		else if (3 * B < 2)
		{
			B = temp2 + (temp1 - temp2) * (0.6666 - B) * 6;
		}
		else
		{
			B = temp2;
		}
		//NOW DO GREEN
		if (6 * G < 1)
		{
			G = temp2 + (temp1 - temp2) * 6 * G;
		}
		else if (2 * G < 1)
		{
			G = temp1;
		}
		else if (3 * G < 2)
		{
			G = temp2 + (temp1 - temp2) * (0.6666 - G) * 6;
		}
		else
		{
			G = temp2;
		}
		//NOW RGB IS REALLY RGB IN DECIMAL FORM. 
		Rh = R; Gs = G; Bl = B;
	}
}

//-------------------------------------------------------------------------
// Calculates the frames per second
//-------------------------------------------------------------------------
void myApplication::calculateFPS()
{
    //  Increase frame count
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    frameCount++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	dt = (time - lastTime) / 1000.f;
	lastTime = time;

    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);

        //  Set time
        previousTime = currentTime;

        //  Reset frame count
        frameCount = 0;
    }
}

double myApplication::turbulence(double x, double y, double z, double size)
{

	double value = 0.0, initialSize = size;

	while (size >= 1)		//ADD TOGETHER ALL THE ZOOMS TO MAKE TURBULANCE
	{
		value += interpolation(x / size, y / size, z / size) * size;
		size /= 2.0;
	}

	return((128.0 * value / initialSize));

}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void myApplication::drawFPS()
{
    //  Load the identity matrix so that FPS string being drawn
    //  won't get animates
	glLoadIdentity ();

	//  Print the FPS to the window
	//printw (-0.9, -0.9, 0, "FPS: %4.2f", fps);
	printw (25.0, 25.0, 0, "FPS: %4.2f", fps);
	printw(25.0, 100.0, 0, "CAM: %.2f %.2f %.2f", theCamera->GetPosition().x, theCamera->GetPosition().y, theCamera->GetPosition().z);
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void myApplication::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
    for (i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

void myApplication::renderstormanimation(void)
{
	
	px += incr;
	nospriteframe = 4;
	deltasprite = 1 / nospriteframe;
	if (px > 3 )
	{
		px = -1;
	}
	count++;

	if (count > nospriteframe)
	{
		count = 0;
		index++;
		if (index > nospriteframe)
		{
			index = 0;
		}
	
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, storm.texID);
//	glTranslatef(0, -0.4, 1.1);
	
	glPushMatrix();
	glScalef(50, 50, 50);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	float w = 1;
	float h = 1;
	glTexCoord2f((index)*deltasprite, 1);			glVertex3f(-w / 2, h / 2, px * 5);
	glTexCoord2f(index * deltasprite, 0);			glVertex3f(-w / 2, -h / 2, px * 5);
	glTexCoord2f((index + 1)*deltasprite, 0);			glVertex3f(w / 2, -h / 2, px * 5);
	glTexCoord2f((index + 1)* deltasprite, 1);			glVertex3f(w / 2, h / 2, px * 5);

	//glTexCoord2f(index * deltasprite, 0);			glVertex3f(-1 / 2, -1 / 2, px);
	//glTexCoord2f((index + 1)*deltasprite, 0);			glVertex3f(-1 / 2, 1 / 2, px);
	//glTexCoord2f((index + 1)* deltasprite, 1.0);			glVertex3f(1 / 2, 1 / 2, px);
	//glTexCoord2f(index* deltasprite, 1.0);			glVertex3f(1 / 2, -1 / 2, px);
	glEnd();

	glPopMatrix();

	//glEnable(GL_CULL_FACE);
	

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
	
}


double myApplication::interpolation(double x, double y, double z)
{
	//get fractional part of x and y
	double fractX = x - int(x);
	double fractY = y - int(y);
	double fractZ = z - int(z);

	//wrap around
	int x1 = (int(x) + noiseWidth) % noiseWidth;
	int y1 = (int(y) + noiseHeight) % noiseHeight;
	int z1 = (int(z) + noiseDepth) % noiseDepth;

	//neighbor values
	int x2 = (x1 + noiseWidth - 1) % noiseWidth;
	int y2 = (y1 + noiseHeight - 1) % noiseHeight;
	int z2 = (z1 + noiseDepth - 1) % noiseDepth;

	//smooth the noise with bilinear interpolation
	double value = 0.0;
	value += fractX       * fractY       * fractZ       * noise[x1][y1][z1];
	value += fractX       * (1 - fractY) * fractZ       * noise[x1][y2][z1];
	value += (1 - fractX) * fractY       * fractZ       * noise[x2][y1][z1];
	value += (1 - fractX) * (1 - fractY) * fractZ       * noise[x2][y2][z1];

	value += fractX       * fractY       * (1 - fractZ) * noise[x1][y1][z2];
	value += fractX       * (1 - fractY) * (1 - fractZ) * noise[x1][y2][z2];
	value += (1 - fractX) * fractY       * (1 - fractZ) * noise[x2][y1][z2];
	value += (1 - fractX) * (1 - fractY) * (1 - fractZ) * noise[x2][y2][z2];

	return value;
}

Mesh * myApplication::LoadObj(char *filename) {
	int vc = 0, nc = 0, tc = 0, fc = 0;
	char buf[256]; FILE * fp = fopen(filename, "r");
	Mesh * pMesh = (Mesh *)malloc(sizeof (Mesh));
	// initialise values in (*p) 
	// Count elements 
	pMesh->noNormals = pMesh->noTexCoords = pMesh->noVertices = pMesh->noFaces = 0;
	while (!feof(fp)) {
		if (!fgets(buf, 256, fp)) break; // read one line 
		if (!strncmp("vn ", buf, 3)) pMesh->noNormals++;
		else if (!strncmp("vt ", buf, 3)) pMesh->noTexCoords++;
		else if (!strncmp("v ", buf, 2)) pMesh->noVertices++;
		else if (!strncmp("f ", buf, 2)) pMesh->noFaces++;
	}
	pMesh->vertices = (Vertex *)malloc(pMesh->noVertices * sizeof (Vertex)); // You have do the same for normals, texture coords, faces
	pMesh->normals = (Vertex *)malloc(pMesh->noNormals * sizeof (Vertex));
	pMesh->texCoords = (Vertex *)malloc(pMesh->noTexCoords * sizeof (Vertex)); // You have do the same for normals, texture coords, faces
	pMesh->faces = (Face *)malloc(pMesh->noFaces * sizeof (Face)); // You have do the same for normals, texture coords, faces
	fseek(fp, 0, SEEK_SET); // reset file ptr to beginning 
	while (!feof(fp)) {
		fgets(buf, 256, fp);
		if (!strncmp("vn ", buf, 3))
		{
			sscanf((buf + 2), "%f%f%f",
				&pMesh->normals[nc].x,
				&pMesh->normals[nc].y,
				&pMesh->normals[nc].z);
			nc++;// process vn 
		}
		else if (!strncmp("vt ", buf, 3))
		{
			sscanf((buf + 2), "%f%f",
				&pMesh->texCoords[tc].u,
				&pMesh->texCoords[tc].v);
			tc++;
		}// process vt 
		else if (!strncmp("v ", buf, 2))
		{
			sscanf((buf + 2), "%f%f%f",
				&pMesh->vertices[vc].x,
				&pMesh->vertices[vc].y,
				&pMesh->vertices[vc].z);
			vc++;
		}// process v 
		else if (!strncmp("f ", buf, 2))
		{
			char * pSp = NULL; int ii = 0;
			Face * pf = &pMesh->faces[fc];
			for (int i = 0; i < strlen(buf); i++)
			if (buf[i] == '/') ii++; // no of '/' 
			pf->vCount = ii / 2; // no of vertices 
			pf->vIndices = (int *)malloc(pf->vCount * sizeof (int));
			pf->nIndices = (int *)malloc(pf->vCount * sizeof (int));
			pf->tcIndices = (int *)malloc(pf->vCount * sizeof (int));
			pSp = strtok((buf + 2), " \t\n");
			for (int i = 0; pSp; pSp = strtok(NULL, " \t\n"), i++)
			{
				sscanf(pSp, "%d/%d/%d", &pf->vIndices[i], &pf->tcIndices[i], &pf->nIndices[i]);
				pf->vIndices[i] --;
				pf->tcIndices[i] --;
				pf->nIndices[i] --;
			}
			fc++;
		}// process f 
	} fclose(fp); // close file
	return pMesh;
}



void myApplication::RenderMesh(Mesh *cur) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, TIEtex.texID);
	//Mesh * cur = cur;
	for (int i = 0; i < cur->noFaces; i++) {
		Face * pf = &cur->faces[i];
		glBegin(GL_POLYGON);
		for (int j = 0; j < pf->vCount; j++) {
			glTexCoord2f(cur->texCoords[pf->tcIndices[j]].u,
				cur->texCoords[pf->tcIndices[j]].v);
			glNormal3f(cur->normals[pf->nIndices[j]].x,
				cur->normals[pf->nIndices[j]].y,
				cur->normals[pf->nIndices[j]].z);
			glVertex3f(cur->vertices[pf->vIndices[j]].x,
				cur->vertices[pf->vIndices[j]].y,
				cur->vertices[pf->vIndices[j]].z);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void myApplication::drawcube(int w, int h, bool mode)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	if (mode)
		glNormal3f(0, 0, 1);
	else
		glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);			glVertex3f(-w/2, h/2, 0);
	glTexCoord2f(1, 0);			glVertex3f(-w / 2, -h / 2, 0);
	glTexCoord2f(0, 0);			glVertex3f(w / 2, -h / 2, 0);
	glTexCoord2f(0, 1);			glVertex3f(w / 2, h / 2, 0);
	glEnd();
	glPopMatrix();
}

void myApplication::drawsidecube(int w, int h, bool mode)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	if (mode)
		glNormal3f(0, 0, 1);
	else
		glNormal3f(0, 0, -1);
	glTexCoord2f(8, 8);			glVertex3f(-w / 2, h / 2, 0);
	glTexCoord2f(8, 0);			glVertex3f(-w / 2, -h / 2, 0);
	glTexCoord2f(0, 0);			glVertex3f(w / 2, -h / 2, 0);
	glTexCoord2f(0, 8);			glVertex3f(w / 2, h / 2, 0);
	glEnd();
	glPopMatrix();
}

void myApplication::drawtopcube(int w, int h, bool mode)
{
	glColor3f(1,1,1);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,top.texID);


	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,blueline.texID);

	glPushMatrix();
	glBegin(GL_QUADS);
	if (mode)
		glNormal3f(0, -1, 0);
	else
		glNormal3f(0, 1, 0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,8,8);	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,8,8);				glVertex3f(-w / 2, h / 2, 0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,8,0);	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,8,0);				glVertex3f(-w / 2, -h / 2, 0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0,0);	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0,0);				glVertex3f(w / 2, -h / 2, 0);
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0,8);	glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0,8);				glVertex3f(w / 2, h / 2, 0);
	glEnd();
	glPopMatrix();

	glActiveTextureARB(GL_TEXTURE1_ARB);//disable texture 2
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);//disable texture 1
	glDisable(GL_TEXTURE_2D);
}

void myApplication::drawroof()
{
	
	glPushMatrix();
	glTranslatef(0, 200, 0);
	glRotatef(90, 1, 0, 0);
	drawtopcube(520, 520,true);
	glPopMatrix();
	glColor3f(1, 1, 1);
	
}

void myApplication::drawside(bool mode)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, panels.texID);
	//glNormal3f(1, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawsidecube(520, 185, mode);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void myApplication::drawback(bool mode)
{
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, door.texID);
	
	drawcube(520, 185, mode);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void myApplication::drawTIE()
{
	
	glPushMatrix();
	
	glTranslatef(0 + TIEx,100 + TIEy,TIEz);

	glPushMatrix();
	glScalef(23,25,23);
	glRotatef(270 + TIErotate,0,1,0);
	RenderMesh(TIE);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(30,-50,80);
	glEnable(GL_LIGHTING);
	renderparticles();
	glPopMatrix();
	glPopMatrix();

}


void myApplication::f_moveTIE()
{
	if (moveTIE)
	{
		if (TIEz == 0 && TIEreturn == false)//LIFTOFF
		{
			TIEy += 5 * dt;
		}
		if (TIEy >= 45 || TIEreturn == true)
		{
			if (TIEz >= 220)		//FLY OUTSIDE
			{
				if (TIEz >= 800)	//IF MAX DIS HAS BEEN REACHED
				{
					TIErotate = 180;
					TIEreturn = true;
				}
				if (TIEreturn == false)	//CONTINUE FORWARD
				{
					TIEz += 300 * dt;
					TIEy += 200 * dt;
					TIEx += 300 * dt;
				}
				if (TIEreturn == true)	//COME BACK
				{
					if (TIEz >= 0)
						TIEz -= 300 * dt;
					if (TIEy >= 45)
						TIEy -= 200 * dt;
					if (TIEx >= 0)
						TIEx -= 300 * dt;
				}
			}
			else if (TIEz <= 219 && TIEreturn == true)	//COMING BACK IN
			{
				if (TIEz > 0)
					TIEz -= 20 * dt;
				if (TIEz < 0)
					TIEz = 0;

				if (TIEz == 0)
				{
					if (TIErotate > 0)
						TIErotate -= 30 * dt;
					if (TIErotate < 0)
						TIErotate = 0;
					if (TIEy > 0)
						TIEy -= 5 * dt;
					if (TIEy < 0)
					{
						TIEy = 0;
						TIEreturn = false;
					}
				}

			}
			else
			{
				TIEz += 20 * dt;		//SLOWGLIDE
			}
		}
		
	}
}