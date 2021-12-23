#pragma once
#include<GL/glut.h>
#include<GL/GLU.h>
#include<iostream>
#include <math.h>
#define PI 3.1415926535




using namespace sf;
using namespace std;

class Oyuncu {
public:

	float px = 300, py = 300;
	float 	pdx,pdy,pa;


	void drawPlayer() {

		glColor3f(1, 1, 0);
		glPointSize(8);
		glBegin(GL_POINTS);
		glVertex2i(px, py);
		glEnd();

		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2i(px, py);
		glVertex2i(px + pdx * 5, py + pdy * 5);
		glEnd();

	}

	void drawRays() {

	}


};

class Map {

public:

	int mapX = 8, mapY = 8, mapS = 64;

	Map() {

	}

 int map[64]= {
		1,1,1,1,1,1,1,1,
		1,0,0,1,0,0,0,1,
		1,0,0,1,0,0,0,1,
		1,0,0,0,0,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,0,1,1,0,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1

	};

	void loadLevelMap() {
		int xa, ya, xo, yo;
		for (ya = 0; ya < mapY; ya++) {
			for (xa = 0; xa < mapX; xa++) {
				if (map[ya * mapX + xa] == 1) {
					glColor3f(1, 1, 1);
				}
				else {
					glColor3f(0, 0, 0);
				}
				xo = xa * mapS; yo = ya * mapS;
				glBegin(GL_QUADS);
				glVertex2i(xo+1, yo+1);
				glVertex2i(xo+1, yo+mapS-1);
				glVertex2i(xo+ mapS-1,yo+mapS-1);
				glVertex2i(xo-1 + mapS,yo+1);
				glEnd();
			}
		}
	}

	
};

	Oyuncu o;
	Map m;
	void display() {
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m.loadLevelMap();
		o.drawPlayer();
		glutSwapBuffers();

	}

	void tuslar(unsigned char key, int x, int y) {

		if (key == 'A' || key == 'a') {
			o.pa = o.pa - 0.1;
			if (o.pa < 0) {
				o.pa = o.pa + 2 * PI;
			}
			o.pdx = cos(o.pa) * 5;
			o.pdy = sin(o.pa) * 5;
		}
		if (key == 'D' || key == 'd') {
			o.pa = o.pa + 0.1;
			if (o.pa > 2*PI) {
				o.pa = o.pa - 2 * PI;
			}
			o.pdx = cos(o.pa) * 5;
			o.pdy = sin(o.pa) * 5;
		}
		if (key == 'W' || key == 'w') {
			o.px = o.px + o.pdx;
			o.py = o.py + o.pdy;
		}
		if (key == 'S' || key == 's') {
			o.px = o.px - o.pdx;
			o.py = o.py - o.pdy;
		}
		glutPostRedisplay();

	}



class Raycasting
{
public:
	Oyuncu o;

	

	

	void init() {Oyuncu o;

		glClearColor(0.3, 0.3, 0.3, 0);
		gluOrtho2D(0, 1024, 512, 0);
		o.px = 300;
		o.py = 300;
		o.pdx = cos(o.pa) * 5;
		o.pdy = sin(o.pa) * 5;
	}

	void RayMain(int argc, char* argv[]) {
		
		glutInit( &argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(1024, 512);
		glutCreateWindow("");
		init();
		glutDisplayFunc(display);
		glutKeyboardFunc(tuslar);
		glutMainLoop();
		
		}




};

