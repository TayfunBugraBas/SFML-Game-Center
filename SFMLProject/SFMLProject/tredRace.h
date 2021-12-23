#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<math.h>

using namespace sf;
using namespace std;

int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;
float camD = 0.84;

class Line {
public:
	float x, y, z;
	float X, Y, W;
	float olcek,viraj;
	Line() {
		viraj=x = y = z = 0;
	}

	void project(int camX, int camY, int camZ) {
		olcek = camD / (z - camZ);
		X = (1 + olcek * (x - camX)) * width / 2;
		Y = (1 - olcek * (y - camY))* height / 2;
		W = olcek * roadW * width / 2;
	}

};

class tredRace
{
public:
	tredRace() {};
	

	void DrawShape(RenderWindow & w, Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
		ConvexShape sekil(4);
		sekil.setFillColor(c);
		sekil.setPoint(0, Vector2f(x1 - w1, y1));
		sekil.setPoint(1, Vector2f(x2 - w2, y2));
		sekil.setPoint(2, Vector2f(x2 + w2, y2));
		sekil.setPoint(3, Vector2f(x1 + w1, y1));
		w.draw(sekil);
	}

	void drawRoad(int pos,int startpos,RenderWindow& Psedo,vector<Line>& lines,int Xpos, float x, float dx,int camH,int maxy){
	
		for (int n = startpos; n < startpos + 300; n++) {
			Line& l = lines[n % lines.size()];
			l.project(Xpos-x, camH, pos-(n >=lines.size()?lines.size()*segL:0));
			x += dx;
			dx += l.viraj;

			if (l.Y >= maxy) continue;
			maxy = l.Y;

			Color cimen = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
			Color yol = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);
			Color kaldirim = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);

			Line& p = lines[(n - 1) % lines.size()];

			DrawShape(Psedo, cimen, 0, p.Y, width, 0, l.Y, width);
			DrawShape(Psedo, kaldirim, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
			DrawShape(Psedo, yol, p.X, p.Y, p.W, l.X, l.Y, l.W);

		}
	
	}

	void PsedoMain() {
		RenderWindow Psedo(VideoMode(width, height), "Psedo Race!!");
		Psedo.setFramerateLimit(60);

		vector<Line> lines;

		for (int i= 0; i < 1600; i++) {
			Line line;
			line.z = i * segL;

			if (i > 300 && i < 700) {
				line.viraj = 0.5;
			}

			if (i > 750) {
				float a = i / 30.0;
				line.y = sin(a)*1500;
			}
			if (i > 1100) {
				line.viraj = -0.5;
			}
			lines.push_back(line);
		}

		int pozisyon = 0;
		int PozX = 0;
		while (Psedo.isOpen()) {
			Event e;

			while (Psedo.pollEvent(e)) {
				if (e.type == Event::Closed) {
					Psedo.close();
				}

			}
			

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				PozX += 200;
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				PozX -= 200;
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				pozisyon += 200;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				pozisyon -= 200;
			}
			while (pozisyon >= lines.size() * segL) pozisyon -= lines.size() * segL;
			while (pozisyon < 0) pozisyon += lines.size() * segL;
			

			Psedo.clear();
		
			
			
			int startPozisyon = pozisyon / segL;
			float x = 0, directionX = 0;
			int camH = 1500+lines[startPozisyon].y;
			int maxy = height;

			drawRoad(pozisyon, startPozisyon, Psedo, lines,PozX,x,directionX,camH,maxy);
			
			Psedo.display();
		}


	}


};

