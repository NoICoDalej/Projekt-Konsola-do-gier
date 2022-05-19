#include "AI.h"

#include "definicje.h"

#include <iostream>

using namespace std;

namespace Engine
{
	AI::AI(int graczElement, DaneGryRef dane)
	{
		this->_dane = dane;

		this->graczElement = graczElement;

		if (O_ELEMENT == graczElement)
		{
			aiElement = X_ELEMENT;
		}
		else
		{
			aiElement = O_ELEMENT;
		}

		sprawdzPasujacyWektor.push_back({ 0, 2, 1, 2, 2, 2 });
		sprawdzPasujacyWektor.push_back({ 0, 2, 0, 1, 0, 0 });
		sprawdzPasujacyWektor.push_back({ 0, 2, 1, 1, 2, 0 });
		sprawdzPasujacyWektor.push_back({ 2, 2, 1, 2, 0, 2 });
		sprawdzPasujacyWektor.push_back({ 2, 2, 2, 1, 2, 0 });
		sprawdzPasujacyWektor.push_back({ 2, 2, 1, 1, 0, 0 });
		sprawdzPasujacyWektor.push_back({ 0, 0, 0, 1, 0, 2 });
		sprawdzPasujacyWektor.push_back({ 0, 0, 1, 0, 2, 0 });
		sprawdzPasujacyWektor.push_back({ 0, 0, 1, 1, 2, 2 });
		sprawdzPasujacyWektor.push_back({ 2, 0, 2, 1, 2, 2 });
		sprawdzPasujacyWektor.push_back({ 2, 0, 1, 0, 0, 0 });
		sprawdzPasujacyWektor.push_back({ 2, 0, 1, 1, 0, 2 });
		sprawdzPasujacyWektor.push_back({ 0, 1, 1, 1, 2, 1 });
		sprawdzPasujacyWektor.push_back({ 1, 2, 1, 1, 1, 0 });
		sprawdzPasujacyWektor.push_back({ 2, 1, 1, 1, 0, 1 });
		sprawdzPasujacyWektor.push_back({ 1, 0, 1, 1, 1, 2 });
		sprawdzPasujacyWektor.push_back({ 0, 1, 2, 1, 1, 1 });
		sprawdzPasujacyWektor.push_back({ 1, 2, 1, 0, 1, 1 });
		sprawdzPasujacyWektor.push_back({ 0, 2, 2, 0, 1, 1 });
		sprawdzPasujacyWektor.push_back({ 2, 2, 0, 0, 1, 1 });
		sprawdzPasujacyWektor.push_back({ 0, 2, 2, 2, 1, 2 });
		sprawdzPasujacyWektor.push_back({ 0, 0, 2, 0, 1, 0 });
		sprawdzPasujacyWektor.push_back({ 0, 2, 0, 0, 0, 1 });
		sprawdzPasujacyWektor.push_back({ 2, 2, 2, 0, 2, 1 });
	}

	void AI::PolozElement(int(*gridTabela)[3][3], sf::Sprite gridElementy[3][3], int *graState)
	{
		try
		{
			// sprawdz czy AI moze wygrac
			for (int i = 0; i < sprawdzPasujacyWektor.size(); i++)
			{
				SprawdzSekcje(sprawdzPasujacyWektor[i][0], sprawdzPasujacyWektor[i][1], sprawdzPasujacyWektor[i][2], sprawdzPasujacyWektor[i][3], sprawdzPasujacyWektor[i][4], sprawdzPasujacyWektor[i][5], AI_ELEMENT, gridTabela, gridElementy);
			}

			// sprawdz czy Gracz moze wygrac
			for (int i = 0; i < sprawdzPasujacyWektor.size(); i++)
			{
				SprawdzSekcje(sprawdzPasujacyWektor[i][0], sprawdzPasujacyWektor[i][1], sprawdzPasujacyWektor[i][2], sprawdzPasujacyWektor[i][3], sprawdzPasujacyWektor[i][4], sprawdzPasujacyWektor[i][5], GRACZ_ELEMENT, gridTabela, gridElementy);
			}

			//sprawdz czy srodek jest pusty
			SprawdzCzyElementJestPusty(1, 1, gridTabela, gridElementy);

			//sprawdz czy rog jest pusty
			SprawdzCzyElementJestPusty(0, 2, gridTabela, gridElementy);
			SprawdzCzyElementJestPusty(2, 2, gridTabela, gridElementy);
			SprawdzCzyElementJestPusty(0, 0, gridTabela, gridElementy);
			SprawdzCzyElementJestPusty(2, 1, gridTabela, gridElementy);

			//sprawdz czy sa jakies inne puste elementy
			SprawdzCzyElementJestPusty(1, 2, gridTabela, gridElementy);
			SprawdzCzyElementJestPusty(0, 1, gridTabela, gridElementy);
			SprawdzCzyElementJestPusty(2, 1, gridTabela, gridElementy);
			SprawdzCzyElementJestPusty(1, 0, gridTabela, gridElementy);
		}
		catch (int error)
		{
			
		}

		*graState = STATE_W_TRAKCIE_GRY;
	}

	void AI::SprawdzSekcje(int x1, int y1, int x2, int y2, int X, int Y, int elementDoSprawdzenia, int(*gridTabela)[3][3], sf::Sprite gridElementy[3][3])
	{
		//sprawdz czy 2 elementy sa pasujace
		if ((*gridTabela)[x1][y1] == elementDoSprawdzenia &&
			(*gridTabela)[x2][y2] == elementDoSprawdzenia)
		{
			if (PUSTY_ELEMENT == (*gridTabela)[X][Y])
			{
				(*gridTabela)[X][Y] = AI_ELEMENT; 
				gridElementy[X][Y].setTexture(this->_dane->assets.WczytajTexture("Element O"));

				gridElementy[X][Y].setColor(sf::Color(255, 255, 255, 255));

				throw -1;
			}
		}
	}

	void AI::SprawdzCzyElementJestPusty(int X, int Y, int(*gridTabela)[3][3], sf::Sprite gridElementy[3][3])
	{
		
		if (PUSTY_ELEMENT == (*gridTabela)[X][Y])
		{
			(*gridTabela)[X][Y] = AI_ELEMENT;
			gridElementy[X][Y].setTexture(this->_dane->assets.WczytajTexture("Element O"));

			gridElementy[X][Y].setColor(sf::Color(255, 255, 255, 255));

			throw - 2;
		}
	}
}