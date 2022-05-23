#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Gra.h"

namespace Engine
{
	class SnakeState : public State
	{
	public:
		SnakeState(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:

		void Tick();

		void Ustaw();

		DaneGryRef _dane;

		sf::Sprite _tlo;

		sf::Sprite _pauzaPrzycisk;

		sf::Sprite _bialy;

		sf::Sprite _czerwony;

		int N = 40, M = 40;
		int size = 16;
		int w = size * N;
		int h = size * M;

		int dir, num = 4;

		float czasomierz = 0, opoznienie = 0.1;

		int graSnakeState;

		sf::Clock _zegar;
	};
}