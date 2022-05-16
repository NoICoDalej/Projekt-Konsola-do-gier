#include <sstream>
#include "SplashState.h"
#include "definicje.h"
#include <iostream>

namespace Engine
{
	SplashState::SplashState(DaneGryRef dane) : _dane(dane)
	{

	}

	void SplashState::Init()
	{
		this->_dane->assets.WczytajTexture("Splash State Background", SPLASH_SCENA_TLO_SCIEZKAPLIK);

		_tlo.setTexture(this->_dane->assets.WczytajTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		
		while (this->_dane->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_dane->window.close();
			}
		}
	}
	
	void SplashState::Update(float dt)
	{
		if (this->_zegar.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// przejscie do main menu
			std::cout << "Idz do Main Menu" << std::endl;
		}

	}

	void SplashState::Draw(float dt)
	{
		this->_dane->window.clear(sf::Color::Green);

		this->_dane->window.draw(this->_tlo);

		this->_dane->window.display();
	}
}