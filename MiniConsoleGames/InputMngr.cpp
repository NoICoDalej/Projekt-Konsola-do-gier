#include "InputMngr.h"

namespace Engine
{
	bool InputMngr::CzySpriteKlikniety(sf::Sprite obiekt, sf::Mouse::Button przycisk, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(przycisk))
		{
			sf::IntRect tempRect( obiekt.getPosition().x, obiekt.getPosition().y, obiekt.getGlobalBounds().width, obiekt.getGlobalBounds().height );

			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}

		return false;
	}

	sf::Vector2i InputMngr::WczytajPozMyszki(sf::RenderWindow &window)
	{
		return::sf::Mouse::getPosition( window );
	}
}