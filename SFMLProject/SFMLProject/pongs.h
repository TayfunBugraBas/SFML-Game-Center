#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "platesx.h"
#include "Ball.h"

using namespace sf;
using namespace std;




class pongs
{
public:
	
	

	void CollisionDetector(Ball &ball, Platesx &left, Platesx &Right, float width, float height) {

		if ((ball.pos.y < left.pos.y + 40) && (ball.pos.y > left.pos.y - 40) &&( ball.pos.x < 10)) {

			ball.dir.x *= -1;

		}
		if ((ball.pos.y < Right.pos.y + 40) && (ball.pos.y > Right.pos.y - 40) && (ball.pos.x > 570)) {

			ball.dir.x *= -1;

		}
		if (ball.pos.x < 0) {
			ball.pos = { width / 2,height / 2 };
		}
		if (ball.pos.x > 580) {
			ball.pos = { width / 2,height / 2 };
		}

	}


	void mainPong() {

		 float width = 600;
		 float height = width / 16 * 9;


		Platesx left(1,width,height);
		Platesx right(0,width, height);
		Ball ball(width,height);

		RenderWindow pongsw(VideoMode(width, height), "Poing");
		pongsw.setFramerateLimit(250);


		while (pongsw.isOpen()) {

			Event olay;


			while (pongsw.pollEvent(olay)) {

				if (olay.type == Event::Closed) {
					pongsw.close();
				}

			}
			pongsw.clear();

			left.hareket(1);
			left.ciz(pongsw);
			right.hareket(0);
			right.ciz(pongsw);

			ball.hareket();
			CollisionDetector(ball, left, right, width,height);
			ball.ciz(pongsw);

			pongsw.display();
		}



		
		

	}

	

};

