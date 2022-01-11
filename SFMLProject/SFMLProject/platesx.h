#pragma once
#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;


class Platesx {
public:

	Vector2f pos;
	RectangleShape plate;
	bool left;

	Platesx(bool left,float x,float y) {
		plate.setSize({ 10, 80 });
		plate.setFillColor(Color::White);
		plate.setOrigin(5, 40);
		if (left) {
			pos = { 10,y/2 };
		}
		else {
			pos = { x - 20,y / 2 };
		}
	}

	void ciz(RenderWindow& ekran) {

		plate.setPosition(pos);
		ekran.draw(plate);

	}

	void hareket(bool left) {
		if (left) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				pos.y--;
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				pos.y++ ;
			}
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				pos.y--;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				pos.y++;
			}
		}

		if (pos.y <= 40) {
			pos.y++;
		}
		if (pos.y >= 290) {
			pos.y--;
		}


	}

};


