#include <sstream>
#include "MainMenuState.h"
#include "definicje.h" 
#include "SnakeState.h"
#include "PauzaState.h"
#include <iostream>
using namespace sf;

struct Wonsz
{
	int x, y;
}  s[100];

struct Owoc
{
	int x, y;
} f;

namespace Engine
{
	SnakeState::SnakeState(DaneGryRef dane) : _dane(dane)
	{

	}

	void SnakeState::Init()
	{

		this->_dane->assets.WczytajTexture("Bialy", BIALY);
		this->_dane->assets.WczytajTexture("Czerwony", CZERWONY);
		this->_dane->assets.WczytajTexture("Przycisk Pauzy", PAUZA_PRZYCISK);

		_bialy.setTexture(this->_dane->assets.WczytajTexture("Bialy"));
		_czerwony.setTexture(this->_dane->assets.WczytajTexture("Czerwony"));
		_pauzaPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Przycisk Pauzy"));

		_pauzaPrzycisk.setPosition((SCREEN_WIDTH / 2) - (this->_pauzaPrzycisk.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (this->_pauzaPrzycisk.getGlobalBounds().height * (-2.5)));

		Ustaw();

	}

	void SnakeState::HandleInput()
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
				// Zmien do Stanu Gry
				this->_dane->maszyna.DodajState(StateRef(new PauzaState(_dane)), false);
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
			if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
			if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
			if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
		}
	}

	void SnakeState::Update(float dt)
	{
		float time = _zegar.getElapsedTime().asSeconds();
		_zegar.restart();
		czasomierz += time;

		if (czasomierz > opoznienie)
		{
			czasomierz = 0;
			Tick();
		}
	}

	void SnakeState::Draw(float dt)
	{
		this->_dane->window.clear();

		this->_dane->window.draw(this->_bialy);
		this->_dane->window.draw(this->_czerwony);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				_bialy.setPosition(i * size, j * size);  this->_dane->window.draw(this->_bialy);
			}

		for (int i = 0; i < num; i++)
		{
			_czerwony.setPosition(s[i].x * size, s[i].y * size);  this->_dane->window.draw(this->_czerwony);
		}

		_czerwony.setPosition(f.x * size, f.y * size);  this->_dane->window.draw(this->_czerwony);

		this->_dane->window.draw(this->_pauzaPrzycisk);

		this->_dane->window.display();
	}

	void SnakeState::Ustaw()
	{
		f.x = 10;
		f.y = 10;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				_bialy.setPosition(i * size, j * size);
			}

		for (int i = 0; i < num; i++)
		{
			_czerwony.setPosition(s[i].x * size, s[i].y * size);
		}

		_czerwony.setPosition(f.x * size, f.y * size);
	}

	void SnakeState::Tick()
	{
		for (int i = num; i > 0; --i)
		{
			s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
		}

		if (dir == 0) s[0].y += 1;
		if (dir == 1) s[0].x -= 1;
		if (dir == 2) s[0].x += 1;
		if (dir == 3) s[0].y -= 1;

		if ((s[0].x == f.x) && (s[0].y == f.y))
		{
			num++; f.x = rand() % N; f.y = rand() % M;
		}

		if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
		if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

		for (int i = 1; i < num; i++)
			if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i;
	}

}