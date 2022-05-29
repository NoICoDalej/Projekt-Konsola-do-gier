#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Gra.h"

namespace Engine
{
	class AI
	{
	public:
		AI(int graczElement, DaneGryRef dane);

		void PolozElement(int(*gridTabela)[3][3], sf::Sprite gridElementy[3][3], int *graState);

	private:
		void SprawdzSekcje(int x1, int y1, int x2, int y2, int X, int Y, int elementDoSprawdzenia, int(*gridTabela)[3][3], sf::Sprite gridElementy[3][3]);
		void SprawdzCzyElementJestPusty(int X, int Y, int(*gridTabela)[3][3], sf::Sprite gridElementy[3][3]);

		int aiElement;
		int graczElement;

		std::vector<std::array<int, 9>> sprawdzPasujacyWektor;

		DaneGryRef _dane;
	};
}