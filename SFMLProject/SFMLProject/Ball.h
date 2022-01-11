#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
public:
	Ball(float x, float y){
		ball.setRadius(5);
		ball.setFillColor(Color::White);
		pos = {x / 2,y / 2 };
		dir = {1,1};
	}

	Vector2f pos;
	CircleShape ball;
	Vector2f dir;

 void ciz(RenderWindow& ekran) {
	 ball.setPosition(pos);
	 ekran.draw(ball);

   }

 void hareket() {
	 pos.x += dir.x;
	 pos.y += dir.y;
	 if (pos.y < 5) {
		 dir.y *= -1;
	 }
	 if (pos.y > 295) {
		 dir.y *= -1;
	 }


 }


};

