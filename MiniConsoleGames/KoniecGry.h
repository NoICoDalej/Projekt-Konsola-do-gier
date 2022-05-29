#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Gra.h"

namespace Engine
{
	class KoniecGry : public State
	{
	public:
		KoniecGry(DaneGryRef dane);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		DaneGryRef _dane;

		sf::Sprite _powtorzPrzycisk;

		sf::Sprite _homePrzycisk;
	};
}
