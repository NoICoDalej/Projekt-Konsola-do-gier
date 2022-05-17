#include <sstream>
#include "MainMenuState.h"
#include "definicje.h" 

#include <iostream>

namespace Engine
{
	MainMenuState::MainMenuState(DaneGryRef dane) : _dane(dane)
	{

	}

	void MainMenuState::Init()
	{
		this->_dane->assets.WczytajTexture("Tlo", MAIN_MENU_TLO_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Przycisk Play", MAIN_MENU_PLAY_PRZYCISK);
		this->_dane->assets.WczytajTexture("Przycisk Play Zewnetrzny", MAIN_MENU_PLAY_PRZYCISK_ZEW);
		this->_dane->assets.WczytajTexture("Tytul Gry", MAIN_MENU_TYTUL_SCIEZKAPLIK);

		this->_tlo.setTexture(this->_dane->assets.WczytajTexture("Tlo"));
		this->_playPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Przycisk Play"));
		this->_playPrzyciskZew.setTexture(this->_dane->assets.WczytajTexture("Przycisk Play Zewnetrzny"));
		this->_tytul.setTexture(this->_dane->assets.WczytajTexture("Tytul Gry"));

		this->_playPrzycisk.setPosition((SCREEN_WIDTH / 2) - (this->_playPrzycisk.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_playPrzycisk.getGlobalBounds().height / 2));
		this->_playPrzyciskZew.setPosition((SCREEN_WIDTH / 2) - (this->_playPrzyciskZew.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_playPrzyciskZew.getGlobalBounds().height / 2));
		this->_tytul.setPosition((SCREEN_WIDTH / 2) - (this->_tytul.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_tytul.getGlobalBounds().height * 1.8));

	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_dane->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_dane->window.close();
			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_playPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				std::cout << "Idz do ekranu Gry" << std::endl;
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		this->_dane->window.clear();
		this->_dane->window.draw( this->_tlo);
		this->_dane->window.draw( this->_playPrzycisk);
		this->_dane->window.draw( this->_playPrzyciskZew);
		this->_dane->window.draw( this->_tytul);

		this->_dane->window.display();

	}

}

//specyfikacja main menu i ustawienie przycisków