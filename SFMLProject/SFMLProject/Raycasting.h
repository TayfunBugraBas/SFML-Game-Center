#pragma once
#include<GL/glut.h>
#include<GL/GLU.h>
#include<iostream>
#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2





using namespace sf;
using namespace std;
class Map {

public:

	int mapX = 8, mapY = 8, mapS = 64;

	Map() {

	}

	int map[64] = {/*Sonra Büyüyecek*/
		   1,1,1,1,1,1,1,1,
		   1,0,0,0,0,0,0,1,
		   1,0,1,0,1,0,1,1,
		   1,0,0,0,0,0,0,1,
		   1,0,0,1,0,1,0,1,
		   1,0,0,0,1,0,0,1,
		   1,0,1,0,0,0,0,1,
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
				glVertex2i(xo + 1, yo + 1);
				glVertex2i(xo + 1, yo + mapS - 1);
				glVertex2i(xo + mapS - 1, yo + mapS - 1);
				glVertex2i(xo - 1 + mapS, yo + 1);
				glEnd();
			}
		}
	}


};

float degToRad(int a) {

	return a * PI / 180.0; /* Bilgisayarlar neden Radyanla çalýþýyor :d */

}
int AciDuzelt(int a) {
	if (a > 359) {
		a -= 360;

	}
	if (a < 0) {
		a += 360;
	}
	return a;
}


class Oyuncu {
public:
	Map avr;

	float px , py ;
	float 	pdx,pdy,pa;


	void drawPlayer() {
		glColor3f(1, 1, 0);   glPointSize(8);    glLineWidth(4);
		glBegin(GL_POINTS); glVertex2i(px, py); glEnd();
		glBegin(GL_LINES);  glVertex2i(px, py); glVertex2i(px + pdx * 20, py + pdy * 20); glEnd();

	}

	float mesafe(float ax, float ay, float bx, float by,  float ang) {
		return cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay);
	}




	void drawRays() {
		glColor3f(0, 1, 1); glBegin(GL_QUADS); glVertex2i(526, 0); glVertex2i(1006, 0); glVertex2i(1006, 160); glVertex2i(526, 160); glEnd();
		glColor3f(0, 0, 1); glBegin(GL_QUADS); glVertex2i(526, 160); glVertex2i(1006, 160); glVertex2i(1006, 320); glVertex2i(526, 320); glEnd();

		int r, mx, my, mp, dof, side; float vx, vy, rx, ry, ra, xo, yo, disV, disH;

		ra = AciDuzelt(pa + 30);                                                            

		for (r = 0; r < 60; r++)
		{
			
			dof = 0; side = 0; disV = 100000;/*Ellemeyiniz sonra Dünyayý tersten görüyoruz*/
			float Tan = tan(degToRad(ra));
			if (cos(degToRad(ra)) > 0.001) { 
				rx = (((int)px >> 6) << 6) + 64;   
			ry = (px - rx) * Tan + py; xo = 64; yo = -xo * Tan;
			
			}
			else if (cos(degToRad(ra)) < -0.001) { rx = (((int)px >> 6) << 6) - 0.0001; ry = (px - rx) * Tan + py; xo = -64; yo = -xo * Tan; }
			else { rx = px; ry = py; dof = 8; }                                                 
			while (dof < 8)
			{
				mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * avr.mapX + mx;
				if (mp > 0 && mp < avr.mapX * avr.mapY && avr.map[mp] == 1) { dof = 8; disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); }
				else { rx += xo; ry += yo; dof += 1; }                                               
			}
			vx = rx; vy = ry;

			
			dof = 0; disH = 100000;/*Ellemeyiniz sonra Dünyayý tersten görüyoruz*/
			Tan = 1.0 / Tan;
			if (sin(degToRad(ra)) > 0.001) { ry = (((int)py >> 6) << 6) - 0.0001; rx = (py - ry) * Tan + px; yo = -64; xo = -yo * Tan; }
			else if (sin(degToRad(ra)) < -0.001) { ry = (((int)py >> 6) << 6) + 64;      rx = (py - ry) * Tan + px; yo = 64; xo = -yo * Tan; }
			else { rx = px; ry = py; dof = 8; }                                                  

			while (dof < 8)
			{
				mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * avr.mapX + mx;
				if (mp > 0 && mp < avr.mapX * avr.mapY && avr.map[mp] == 1) { dof = 8; disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py); }
				else { rx += xo; ry += yo; dof += 1; }                                             
			}

			glColor3f(0, 0.8, 0);
			if (disV < disH) { rx = vx; ry = vy; disH = disV; glColor3f(0, 0.6, 0); }                  
			glLineWidth(2); glBegin(GL_LINES); glVertex2i(px, py); glVertex2i(rx, ry); glEnd();

			int ca =AciDuzelt(pa - ra); disH = disH * cos(degToRad(ca));                          
			int lineH = (avr.mapS * 320) / (disH); if (lineH > 320) { lineH = 320; }                    
			int lineOff = 160 - (lineH >> 1);                                               

			glLineWidth(8); glBegin(GL_LINES); glVertex2i(r * 8 + 530, lineOff); glVertex2i(r * 8 + 530, lineOff + lineH); glEnd(); 

			ra = AciDuzelt(ra - 1);                                                              

		}

		}




	};






	Oyuncu o;
	Map m;
	void display() {
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m.loadLevelMap();
		o.drawRays();
		o.drawPlayer();
		glutSwapBuffers();
		

	}

	void tuslar(unsigned char key, int x, int y) {

		if (key == 'a') { o.pa += 5; o.pa = AciDuzelt(o.pa); o.pdx = cos(degToRad(o.pa)); o.pdy = -sin(degToRad(o.pa)); }
		if (key == 'd') { o.pa -= 5; o.pa = AciDuzelt(o.pa); o.pdx = cos(degToRad(o.pa)); o.pdy = -sin(degToRad(o.pa)); }
		if (key == 'w') { o.px += o.pdx * 5; o.py += o.pdy * 5; }
		if (key == 's') { o.px -= o.pdx * 5; o.py -= o.pdy * 5; }
		glutPostRedisplay();

	}



class Raycasting
{
public:
	Oyuncu o;

	

	

	void init() {Oyuncu o;

		glClearColor(0.3, 0.3, 0.3, 0);
		gluOrtho2D(0, 1024, 512, 0);
		o.px = 150;
		o.py = 400;
		o.pa = 90;
		o.pdx = cos(degToRad(o.pa)); o.pdy = -sin(degToRad(o.pa));
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

