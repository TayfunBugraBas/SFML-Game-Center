#pragma once
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Tetriss
{
public:

	bool end=0;
	bool hemenYerlestir = 0;
	bool cevir = 0;

	unsigned lag = 0;

	unsigned temizlenenSatirlar = 0;



	void TetMain();


};

