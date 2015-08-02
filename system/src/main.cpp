#include "iostream"
#include <string>
#include "stdio.h"
#include<Windows.h>

#include"../glut/glut.h"
#include"../Headers/map.h"
#include"../Headers/vector.h"

using namespace std;

int SCENE_W = 1024;
int SCENE_H = 768;

Map* map1 = NULL;

DWORD dt;
DWORD olddt;
DWORD drowdt;
int FPS;
Vector pos_map = Vector(-7,-7);
bool stop = true;
bool Dragflag = false;
int oldx=0;
int oldy=0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
	GLfloat light_ambient[] = {0,0,0,1.0};
	GLfloat light_position[] = {0.0,0.0,1.0,0};
	glLightfv(GL_LIGHT0,GL_POSITION, light_position);
	glLightModelfv(GL_DIFFUSE,light_diffuse);
	glLightModelfv(GL_AMBIENT,light_ambient); // настройки света

	GLfloat red[] = {1.0,0.0,0.0};
	glNormal3f(0.0, 0.0, -1.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,red);

	/*glTranslated(pos_map.GetX(),pos_map.GetY(),0);
	glutSolidCube(1);*/
	
	glPopMatrix();
		//glScaled(1.5,1.5,1);
		map1->drawMap(pos_map);
	glPopMatrix();
	/*if(!stop)
	{
		
	}*/
	
	FPS++;
	glDisable(GL_LIGHT0);
	glFlush();
	glutSwapBuffers();
}
void idle()
{
	DWORD dt=GetTickCount();
	if(dt - olddt > 1000)
	{
		cout << "FPS. " << FPS << endl;
		FPS = 0;
		olddt = dt;
	}
	if(dt - drowdt > 15)
	{
		drowdt = dt;
		glutPostRedisplay();
	}
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'd':
			pos_map.SetX(pos_map.GetX() +1);
			break;
		case 'a':
			pos_map.SetX(pos_map.GetX() -1);
			break;
		case 'w':
			pos_map.SetY(pos_map.GetY() +1);
			break;
		case 's':
			pos_map.SetY(pos_map.GetY() -1);
			break;
		case 'p':
			stop = !stop;
			break;
		case 'r':
			map1->genMap(50,4,0.5, "test.txt");
			break;
	}
	glutPostRedisplay();
}
void mouseClick(int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Dragflag = true;
		oldx= x;
		oldy= y;
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		Dragflag = false;
	}
}
void mouseMotion(int x, int y)
{
	if(Dragflag)
	{
		pos_map.SetX(pos_map.GetX() - (x - oldx)*0.25);
		pos_map.SetY(pos_map.GetY() + (y - oldy)*0.25);
		oldx = x;
		oldy = y;
	}
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-20,20,-20,20);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(25,25,1,25,25,0,0,1,0);
	SCENE_W = width;
	SCENE_H = height;
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL,"RUS");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCENE_W, SCENE_H);
	glutCreateWindow("OpenGL экосистема");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glClearColor(0.95, 0.95, 0.95, 1.0);

	map1 = new Map;
	string mapf;
	cout << "Hellow! \n";
	/*cin  >> mapf;
	cout << mapf << endl;*/
	map1->genMap(50,4,0.5, "test.txt"); // "test.txt"->mapf
	//map1->readMap("test.txt");
	glutMainLoop();
	
	delete map1;
	return 0;
}