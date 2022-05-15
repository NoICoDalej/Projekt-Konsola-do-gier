#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
	class InputMngr
	{
	public:
		InputMngr( ) { }
		~InputMngr( ) { }

		bool CzySpriteKlikniety( sf::Sprite obiekt, sf::Mouse::Button przycisk, sf::RenderWindow &window);
		
		sf::Vector2i WczytajPozMyszki(sf::RenderWindow& window);
	};
}