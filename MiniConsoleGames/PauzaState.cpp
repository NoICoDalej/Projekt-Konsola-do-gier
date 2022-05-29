#include <sstream>
#include "PauzaState.h"
#include "definicje.h" 
#include "StateGry.h"
#include "MainMenuState.h"
#include <iostream>


namespace Engine
{
	PauzaState::PauzaState(DaneGryRef dane) : _dane(dane)
	{
	
	}

	void PauzaState::Init()
	{
		this->_dane->assets.WczytajTexture("Pauza Tlo", PAUZA_TLO_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Wznow Przycisk", WZNOW_PRZYCISK);
		this->_dane->assets.WczytajTexture("Home Przycisk", HOME_PRZYCISK);

		this->_tlo.setTexture(this->_dane->assets.WczytajTexture("Pauza Tlo") );
		this->_wznowPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Wznow Przycisk"));
		this->_homePrzycisk.setTexture(this->_dane->assets.WczytajTexture("Home Przycisk"));

		this->_wznowPrzycisk.setPosition((this->_dane->window.getSize().x / 2) - (this->_wznowPrzycisk.getLocalBounds().width / 2), 
			(this->_dane->window.getSize().y / 3) - (this->_wznowPrzycisk.getLocalBounds().height / 2)); //gdy wiecej przyciskow, dzielimy "y" przez n+1 (n - ilosc przyciskow)
		this->_homePrzycisk.setPosition((this->_dane->window.getSize().x / 2) - (this->_homePrzycisk.getLocalBounds().width / 2),
			(this->_dane->window.getSize().y / 3 * 2) - (this->_homePrzycisk.getLocalBounds().height / 2)); //mnozmy tez +1
	}

	void PauzaState::HandleInput()
	{
		sf::Event event;

		while (this->_dane->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_dane->window.close();
			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_wznowPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				// Wznow gre usuwajac Stan Pauzy
				this->_dane->maszyna.UsunState();
			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_homePrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				// Usun Stan Pauzy ze stosu
				this->_dane->maszyna.UsunState();

				// Zmien do Main Menu zamieniajac stan gry
				this->_dane->maszyna.DodajState(StateRef(new MainMenuState(_dane)), true);
			}
		}
	}

	void PauzaState::Update(float dt)
	{

	}

	void PauzaState::Draw(float dt)
	{
		this->_dane->window.clear();

		this->_dane->window.draw(this->_tlo);
		this->_dane->window.draw(this->_wznowPrzycisk);
		this->_dane->window.draw(this->_homePrzycisk);

		this->_dane->window.display();

	}

}

//specyfikacja stanu pauzy i ustawienie przycisków