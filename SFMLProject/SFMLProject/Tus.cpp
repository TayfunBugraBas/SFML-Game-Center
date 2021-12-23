#include "Tus.h"

Tus::Tus(string _yazi, Vector2f boyut, Color yaziRengi, Color tusRengi)
{
	yazi.setString(_yazi);
	yazi.setFillColor(yaziRengi); 



	tus.setSize(boyut);
	tus.setFillColor(tusRengi);
}



void Tus::ArkaRenk(Color arkarenk)
{
	tus.setFillColor(arkarenk);
}

void Tus::YaziRengi(Color yaziRengi)
{
	yazi.setFillColor(yaziRengi);
}

void Tus::TusPoz(Vector2f pozisyon)
{
	tus.setPosition(pozisyon);

	float pozisyonX = (pozisyon.x + tus.getLocalBounds().width/2)-(yazi.getLocalBounds().width/2) - 60;
	float pozisyonY = (pozisyon.y + tus.getLocalBounds().height / 2) - (yazi.getLocalBounds().height / 2) -15;
	yazi.setPosition(pozisyonX, pozisyonY);
}

void Tus::EkranaCiz(RenderWindow& ekran)
{
	ekran.draw(tus);
	ekran.draw(yazi);
}

bool Tus::FareHover(RenderWindow& ekran)
{
	float fareX = Mouse::getPosition(ekran).x;
	float fareY = Mouse::getPosition(ekran).y;

	float tusPozX = tus.getPosition().x;
	float tusPozY = tus.getPosition().y;

	float tusPozCalcGen = tus.getLocalBounds().width + tus.getPosition().x;
	float tusPozCalcYuk = tus.getLocalBounds().height + tus.getPosition().y;

	if (fareX < tusPozCalcGen && fareX > tusPozX && fareY < tusPozCalcYuk && fareY > tusPozY) {
		return true;
	}
	else {
		return false;
	}

}

void Tus::sFont(Font& font)
{
	yazi.setFont(font);
}

void Tus::FontSize(int size)
{
	yazi.setCharacterSize(size);
}

