#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Gra.h"

namespace Engine
{
	class SplashState : public State
	{
	public:
		SplashState(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		DaneGryRef _dane;

		sf::Clock _zegar;

		sf::Sprite _tlo;
	};
}