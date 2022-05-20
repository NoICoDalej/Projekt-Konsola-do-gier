#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Gra.h"

#include "AI.h"

namespace Engine
{
	class StateGry : public State
	{
	public:
		StateGry(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		void WczytyajElementyGrid();

		void SprawdzIPolozElement();

		void SprawdzCzyGraczWygral(int turn);
		void SprawdzCzy3ElementyPasuja(int x1, int y1, int x2, int y2, int x3, int y3, int elementDoSprawdzenia);

		DaneGryRef _dane;

		sf::Sprite _tlo;

		sf::Sprite _pauzaPrzycisk;

		sf::Sprite _gridSprite;

		sf::Sprite _gridElementy[3][3];
		int gridTablica[3][3];

		int turn;
		int graState;

		AI* ai;

		sf::Clock _zegar;
	};
}