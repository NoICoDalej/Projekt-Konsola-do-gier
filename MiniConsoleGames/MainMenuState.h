#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Gra.h"

namespace Engine
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		DaneGryRef _dane;

		sf::Sprite _tlo;

		sf::Sprite _playPrzycisk;

		sf::Sprite _playPrzyciskZew;

		sf::Sprite _drugiPrzycisk;

		sf::Sprite _tytul;
	};
}