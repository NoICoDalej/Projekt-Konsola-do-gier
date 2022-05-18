#include <sstream>
#include "StateGry.h"
#include "definicje.h" 

#include <iostream>

namespace Engine
{
	StateGry::StateGry(DaneGryRef dane) : _dane(dane)
	{
		
	}

	void StateGry::Init()
	{
		graState = STATE_W_TRAKCIE_GRY;
		turn = GRACZ_ELEMENT;

		this->_dane->assets.WczytajTexture("Przycisk Pauzy", PAUZA_PRZYCISK);

		_tlo.setTexture(this->_dane->assets.WczytajTexture("Tlo"));
		_pauzaPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Przycisk Pauzy"));
		_pauzaPrzycisk.setPosition(this->_dane->window.getSize().x - _pauzaPrzycisk.getLocalBounds().width, _pauzaPrzycisk.getPosition().y);
	}

	void StateGry::HandleInput()
	{
		sf::Event event;

		while (this->_dane->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_dane->window.close();
			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_pauzaPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				std::cout << "Zapauzuj Grê" << std::endl;
			}
		}
	}

	void StateGry::Update(float dt)
	{

	}

	void StateGry::Draw(float dt)
	{
		this->_dane->window.clear();

		this->_dane->window.draw(this->_tlo);
		this->_dane->window.draw(this->_pauzaPrzycisk);

		this->_dane->window.display();

	}

}

//specyfikacja i ustawienie elementów w menu Gry