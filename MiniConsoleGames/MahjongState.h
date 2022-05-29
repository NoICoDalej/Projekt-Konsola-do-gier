#pragma once

#include <fstream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Gra.h"

namespace Engine
{
	class MahjongState : public State
	{
	public:
		MahjongState(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:

		bool czyOtwarte(int x, int y, int z);

		void pomieszaj();

		void zaladujMape();

		DaneGryRef _dane;

		sf::Sprite _tlo;
		sf::Sprite _klocki;
		sf::Sprite _pauzaPrzycisk;

		int w = 48, h = 66;
		int stepX = w / 2 - 2, stepY = h / 2 - 2;
		float offX = 4.6, offY = 7.1; // z

		sf::Clock _zegar;
	};
}
