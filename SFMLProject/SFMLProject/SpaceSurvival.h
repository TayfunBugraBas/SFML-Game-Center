#pragma once
#include <SFML/Graphics.hpp>
#include<math.h>
#include <vector>


using namespace std;
using namespace sf;
float DegToRad = 0.017453f;

class Animasyon {
public:
	float kare, animHiz;
	Sprite sprite;

	vector<IntRect> kareler;

	Animasyon() {};

	Animasyon(Texture& t, int X, int Y, int w, int h, int sayac, float hiz) {
		kare = 0;
		animHiz = hiz;
		for (int i = 0; i < sayac; i++) {
			IntRect a(X + i * w, Y, w, h);

			kareler.push_back(a);

		}
		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(kareler[0]);
	}

	void update() {
		kare = kare + animHiz;
		if (kare >= kareler.size()) {
			kare = kare - kareler.size();
		}
		if (kareler.size() > 0) {
			sprite.setTextureRect(kareler[int(kare)]);
		}
	}
	
};

class Varlik {
public:

	float xa, ya, dxa, dya, R, aci;
	bool can;
	string isim;
	Animasyon anim;

	Varlik() {
		can = 1;
	}

	void ayarlar(Animasyon& a, int X, int Y, float angle, int radius) {
		xa = X;
		ya= Y;
		anim = a;
		R = radius;
		aci = angle;
	}

	virtual void update() {};

	void ciz(RenderWindow& ekran) {
		anim.sprite.setPosition(xa, ya);
		anim.sprite.setRotation(aci + 90);
		ekran.draw(anim.sprite);
	}



};

class Asteroid :public Varlik {
public:
	Asteroid() {
		dxa = rand() % 8 - 4;
		dya = rand() % 8 - 4;
		
		isim = "asteroid";
	}

	void update() {
		

		if (xa > 1200) {
			xa = 0;
		}
		if (xa < 0) {
			xa = 1200;
		}
		if (ya > 800) {
			ya = 0;
		}
		if (ya < 0) {
			ya = 800;
		}
	}


};

class Mermi :public Varlik {
public:
	Mermi() {
		isim = "mermi";
	}

	void update() {
		dxa = cos(aci * DegToRad) * 6;
		dya = sin(aci * DegToRad) * 6;

		xa = xa + dxa;
		ya = ya + dya;
		if (xa > 1200) {
			xa = 0;
		}
		if (xa < 0) {
			xa = 1200;
		}
		if (ya > 800) {
			ya = 0;
		}
		if (ya < 0) {
			ya = 800;
		}

	}

};




class SpaceSurvival
{
public:

	SpaceSurvival() {};

	void Ciz(RenderWindow& ekran, Sprite s ) {
		
		ekran.draw(s);
		
	}

	bool Carpisma(Varlik a, Varlik b) {

	  return(b.xa - a.xa) * (b.xa - a.xa) + (b.ya - a.ya) * (b.ya - a.ya) < (a.R+b.R) * (a.R+b.R);

	}

	


	void SpaceMain() {
		RenderWindow SurvivalSpace(VideoMode(1200, 800), "SpaceSurvival");
		SurvivalSpace.setFramerateLimit(60);

		Texture texture1, texture2, texture3,texture4,texture5;
		texture1.loadFromFile("images/spaceship.png");
		texture2.loadFromFile("images/background.jpg");
		texture3.loadFromFile("images/type_A.png");
		texture4.loadFromFile("images/tas.png");
		texture5.loadFromFile("images/fire_red.png");

		Sprite sOyuncu(texture1), sBackground(texture2), sPatlama(texture3);
		
		sOyuncu.setTextureRect(IntRect(40, 0, 40, 40));
		sOyuncu.setOrigin(20,20);

		Animasyon sTas(texture4, 0, 0, 64, 64, 16, 0.2);
		Animasyon sMermi(texture5, 0, 0, 32, 64, 16, 0.8);
		sTas.sprite.setPosition(400, 400);

		vector<Varlik> varliklar;

		for (int i = 0; i < 15; i++) {
			Asteroid a;
			a.ayarlar(sTas, rand() % 1200, rand() % 800, rand() % 360, 25);
			varliklar.push_back(a);
		}
		

		float x = 300, y = 300;
		float dx = 0, dy = 0, aci = 0;
		bool engineOnOff ;



		while (SurvivalSpace.isOpen()) {
			Event olay;

			while (SurvivalSpace.pollEvent(olay)) {
				if (olay.type == Event::Closed) {
					SurvivalSpace.close();
				}

				if (olay.type == Event::KeyPressed) {
					if (olay.key.code == Keyboard::Space) {
						Mermi mermi;
						mermi.ayarlar(sMermi, x, y, aci, 10);
						varliklar.push_back(mermi);
					}
				}


			}

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				aci += 3;
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				aci -= 3;
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				engineOnOff = true;
			}
			else {
				engineOnOff = false;
			}

			sTas.update();
			
			for (int i = 0; i < varliklar.size(); i++) {
				for (int j = 0; j < varliklar.size(); j++) {

					if (varliklar[i].isim == "asteroid" && varliklar[j].isim == "mermi") {
						if (Carpisma(varliklar[i], varliklar[j])) {

							varliklar[i].can = false;
							varliklar[j].can = false;

							for (int i = 0; i < 1; i++) {
								if (varliklar[i].R == 15) {
									continue;
								}
								Asteroid spawner;
								spawner.ayarlar(sTas, rand() % 1200, rand() % 800, rand() % 360, 25);
								varliklar.push_back(spawner);

							}

						}
					}
					

				}


			}

			
			if (engineOnOff) {
				dx = dx+cos(aci * DegToRad)*0.2 ;
				dy = dy+sin(aci * DegToRad)*0.2 ;
			}
			else {
				dx = dx* 0.99;
				dy = dy*0.99;
			}
			int maxhiz = 15;
			float hiz = sqrt(dx * dx + dy * dy);
			if (hiz > maxhiz) {
				dx *= maxhiz / hiz;
				dy *= maxhiz / hiz;
			}

			x = x+ dx;
			y = y+ dy;

			if (x > 1200) {
				x = 0;
			}
			if (x < 0) {
				x = 1200;
			}
			if (y > 800) {
				y = 0;
			}
			if (y < 0) {
				y = 800;
			}
			

			sOyuncu.setPosition(x,y);
			sOyuncu.setRotation(aci + 90);



			for (int i = 0; i<varliklar.size(); i++) {
				 
				if (varliklar[i].isim == "asteroid") {
					varliklar[i].xa = varliklar[i].xa + varliklar[i].dxa;
					varliklar[i].ya = varliklar[i].ya+ varliklar[i].dya;

					if (varliklar[i].xa > 1200) {
						varliklar[i].xa = 0;
					}
					if (varliklar[i].xa < 0) {
						varliklar[i].xa = 1200;
					}
					if (varliklar[i].ya > 800) {
						varliklar[i].ya = 0;
					}
					if (varliklar[i].ya < 0) {
						varliklar[i].ya = 800;
					}
				}
				 if (varliklar[i].isim == "mermi"){
					varliklar[i].dxa = cos(varliklar[i].aci * DegToRad) * 6;
					varliklar[i].dya = sin(varliklar[i].aci * DegToRad) * 6;

					varliklar[i].xa = varliklar[i].xa + varliklar[i].dxa;
					varliklar[i].ya = varliklar[i].ya + varliklar[i].dya;
					if (varliklar[i].xa > 1200) {
						varliklar[i].can = 0;
					}
					if (varliklar[i].xa < 0) {
						varliklar[i].can = 0;
					}
					if (varliklar[i].ya > 800) {
						varliklar[i].can = 0;
					}
					if (varliklar[i].ya < 0) {
						varliklar[i].can = 0;
					}

				}
				

				varliklar[i].anim.update();
				
				if (varliklar[i].can == false) {
					varliklar.erase(begin(varliklar) + i);
				}


			}


			Ciz(SurvivalSpace, sBackground);
			Ciz(SurvivalSpace, sOyuncu);

			for (int j = 0; j < varliklar.size(); j++) {
				varliklar[j].ciz(SurvivalSpace);
			}

			

			SurvivalSpace.display();
		}
	}

};

