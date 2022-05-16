#include "Gra.h"
#include "SplashState.h"

namespace Engine
{
	Gra::Gra(int width, int height, std::string tytul)
	{
		_dane->window.create(sf::VideoMode(width, height), tytul, sf::Style::Close | sf::Style::Titlebar);
		_dane->maszyna.DodajState(StateRef(new SplashState(this->_dane)));

		this->Run( );
	}

	void Gra::Run()
	{
		float nowyCzas, czasKlatki, interpolacja;

		float aktualnyCzas = this->_zegar.getElapsedTime().asSeconds();

		float akumulator = 0.0f;

		while (this->_dane->window.isOpen())
		{
			this->_dane->maszyna.PrzetworzZmianyState();

			nowyCzas = this->_zegar.getElapsedTime().asSeconds();

			czasKlatki = nowyCzas - aktualnyCzas;

			if (czasKlatki > 0.25f)
			{
				czasKlatki = 0.25f;
			}

			aktualnyCzas = nowyCzas;
			akumulator += czasKlatki;

			while (akumulator >= dt)
			{
				this->_dane->maszyna.AktywnyState()->HandleInput();
				this->_dane->maszyna.AktywnyState()->Update(dt);

				akumulator -= dt;
			}

			interpolacja = akumulator / dt;
			this->_dane->maszyna.AktywnyState()->Draw(interpolacja);
		}
	}
}

//zintegrowanie poprzednich manadzerow i state