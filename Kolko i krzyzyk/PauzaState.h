#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Gra.h"

namespace Engine
{
	class PauzaState : public State
	{
	public:
		PauzaState(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		DaneGryRef _dane;

		sf::Sprite _tlo;

		sf::Sprite _homePrzycisk;
		sf::Sprite _wznowPrzycisk;
	};
}
