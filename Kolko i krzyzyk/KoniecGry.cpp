#include <sstream>
#include "KoniecGry.h"
#include "definicje.h" 
#include "StateGry.h"
#include "MainMenuState.h"
#include <iostream>


namespace Engine
{
	KoniecGry::KoniecGry(DaneGryRef dane) : _dane(dane)
	{

	}

	void KoniecGry::Init()
	{
		this->_dane->assets.WczytajTexture("Powtorz Przycisk", POWTORZ_PRZYCISK);
		this->_dane->assets.WczytajTexture("Home Przycisk", HOME_PRZYCISK);

		this->_powtorzPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Powtorz Przycisk"));
		this->_homePrzycisk.setTexture(this->_dane->assets.WczytajTexture("Home Przycisk"));

		this->_powtorzPrzycisk.setPosition((this->_dane->window.getSize().x / 2) - (this->_powtorzPrzycisk.getLocalBounds().width / 2),
			(this->_dane->window.getSize().y / 3) - (this->_powtorzPrzycisk.getLocalBounds().height / 2)); 
		this->_homePrzycisk.setPosition((this->_dane->window.getSize().x / 2) - (this->_homePrzycisk.getLocalBounds().width / 2),
			(this->_dane->window.getSize().y / 3 * 2) - (this->_homePrzycisk.getLocalBounds().height / 2)); 
	}

	void KoniecGry::HandleInput()
	{
		sf::Event event;

		while (this->_dane->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_dane->window.close();
			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_powtorzPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				// Zmien do Main Menu zamieniajac stan konca gry
				this->_dane->maszyna.DodajState(StateRef(new StateGry(_dane)), true);
			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_homePrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				// Zmien do Main Menu zamieniajac stan konca gry
				this->_dane->maszyna.DodajState(StateRef(new MainMenuState(_dane)), true);
			}
		}
	}

	void KoniecGry::Update(float dt)
	{

	}

	void KoniecGry::Draw(float dt)
	{
		this->_dane->window.clear(sf::Color::Red);

		this->_dane->window.draw(this->_powtorzPrzycisk);
		this->_dane->window.draw(this->_homePrzycisk);

		this->_dane->window.display();

	}

}

//specyfikacja stanu konca gry i ustawienie przycisków