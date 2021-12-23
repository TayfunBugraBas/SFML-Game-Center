#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;
class Tus
{
private:
	RectangleShape tus;
	Text yazi;

	

public:
	Tus(string _yazi, Vector2f boyut, Color yaziRengi,Color tusRengi);
	

	void ArkaRenk(Color arkarenk);

	void YaziRengi(Color yaziRengi);

	void TusPoz(Vector2f pozisyon);

	void EkranaCiz(RenderWindow& ekran);

	bool FareHover(RenderWindow& ekran);

	void sFont(Font& font);

	void FontSize(int size);

};

