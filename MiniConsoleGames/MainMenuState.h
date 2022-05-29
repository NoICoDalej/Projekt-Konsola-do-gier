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

		sf::Sprite _snakePrzycisk;

		sf::Sprite _mahjongPrzycisk;

		sf::Sprite _kolkoikrzyzykPrzycisk;

		sf::Sprite _tytul;
	};
}