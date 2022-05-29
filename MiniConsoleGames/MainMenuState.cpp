#include <sstream>
#include "MainMenuState.h"
#include "definicje.h" 
#include "StateGry.h"
#include "SnakeState.h"
#include "MahjongState.h"
#include <iostream>


namespace Engine
{
	MainMenuState::MainMenuState(DaneGryRef dane) : _dane(dane)
	{

	}

	void MainMenuState::Init()
	{
		this->_dane->assets.WczytajTexture("Tlo", MAIN_MENU_TLO_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Przycisk Play", KOLKO_I_KRZYZYK_PLAY);
		this->_dane->assets.WczytajTexture("Tytul Gry", MAIN_MENU_TYTUL_SCIEZKAPLIK);
		
		this->_dane->assets.WczytajTexture("snake", SNAKE_PLAY);  //snake

		this->_dane->assets.WczytajTexture("mahjong", MAHJONG_PLAY);  //mahjong

		this->_tlo.setTexture(this->_dane->assets.WczytajTexture("Tlo"));
		this->_kolkoikrzyzykPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Przycisk Play"));
		this->_tytul.setTexture(this->_dane->assets.WczytajTexture("Tytul Gry"));

		this->_snakePrzycisk.setTexture(this->_dane->assets.WczytajTexture("snake")); //snake

		this->_mahjongPrzycisk.setTexture(this->_dane->assets.WczytajTexture("mahjong")); //mahjong

		this->_kolkoikrzyzykPrzycisk.setPosition((SCREEN_WIDTH / 2) - (this->_kolkoikrzyzykPrzycisk.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (this->_kolkoikrzyzykPrzycisk.getGlobalBounds().height * (-0.5) ));
		this->_tytul.setPosition((SCREEN_WIDTH / 2) - (this->_tytul.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_tytul.getGlobalBounds().height * 1.8));

		this->_snakePrzycisk.setPosition((SCREEN_WIDTH / 2) - (this->_snakePrzycisk.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (this->_snakePrzycisk.getGlobalBounds().height * (-5))); //snake

		this->_mahjongPrzycisk.setPosition((SCREEN_WIDTH / 2) - (this->_mahjongPrzycisk.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (this->_mahjongPrzycisk.getGlobalBounds().height * (-3))); //mahjong

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

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_kolkoikrzyzykPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				this->_dane->maszyna.DodajState(StateRef(new StateGry(_dane)), true);
			}

			else if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_snakePrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				this->_dane->maszyna.DodajState(StateRef(new SnakeState(_dane)), true);
			}

			else if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_mahjongPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				this->_dane->maszyna.DodajState(StateRef(new MahjongState(_dane)), true);
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
		this->_dane->window.draw( this->_kolkoikrzyzykPrzycisk);
		this->_dane->window.draw(this->_snakePrzycisk);
		this->_dane->window.draw(this->_mahjongPrzycisk);
		this->_dane->window.draw( this->_tytul);

		this->_dane->window.display();

	}

}

//specyfikacja main menu i ustawienie przycisków