#include "main.h"
#include "myapplication.h"
static float angle=0.0;

void KeyboardDown(unsigned char key, int x, int y){
	myApplication::getInstance()->KeyboardDown(key,x,y);
}

void KeyboardUp(unsigned char key, int x, int y){
	myApplication::getInstance()->KeyboardUp(key,x,y);
}

void MouseMove(int x, int y){
	myApplication::getInstance()->MouseMove(x,y);
}

void MouseClick(int button, int state, int x, int y){
	myApplication::getInstance()->MouseClick(button, state, x, y);
}


void changeSize(int w, int h) {
	myApplication::getInstance()->changeSize(w,h);
}

void renderScene(void) {
	myApplication::getInstance()->renderScene();
}

void inputKey(int key, int x, int y) {
	myApplication::getInstance()->inputKey(key,x,y);
}

void CleanUpUponExit(void)
{
	myApplication::getInstance()->drop();
}

int main(int argc, char **argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800,600);
	glutCreateWindow("DM2231 Lab");

	glutReshapeFunc(changeSize);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutSpecialFunc(inputKey);
	
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);// for mouse click

	atexit(CleanUpUponExit);

	if (myApplication::getInstance()->Init() == true)
		glutMainLoop();
	else
	{
		printf("Error Initialising Program\n");
		return 1;
	}

	return 0;

}
