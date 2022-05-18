#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Gra.h"

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
		DaneGryRef _dane;

		sf::Sprite _tlo;

		sf::Sprite _pauzaPrzycisk;

		int turn;
		int graState;
	};
}