#include <sstream>
#include "MainMenuState.h"
#include "StateGry.h"
#include "definicje.h" 
#include "PauzaState.h"
#include "KoniecGry.h"

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

		this->ai = new AI(turn, this->_dane);

		this->_dane->assets.WczytajTexture("Przycisk Pauzy", PAUZA_PRZYCISK);
		this->_dane->assets.WczytajTexture("Grid Sprite", GRID_SPRITE_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Element X", X_ELEMENT_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Element O", O_ELEMENT_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Element X Wygrany", X_WYGRANY_ELEMENT_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Element O Wygrany", O_WYGRANY_ELEMENT_SCIEZKAPLIK);

		_tlo.setTexture(this->_dane->assets.WczytajTexture("Tlo"));

		_pauzaPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Przycisk Pauzy"));
		_gridSprite.setTexture(this->_dane->assets.WczytajTexture("Grid Sprite"));

		_pauzaPrzycisk.setPosition(this->_dane->window.getSize().x - _pauzaPrzycisk.getLocalBounds().width, _pauzaPrzycisk.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH/2)-(_gridSprite.getGlobalBounds().width/2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

		WczytyajElementyGrid();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridTablica[x][y] = PUSTY_ELEMENT;
			}
		}
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
				// Zmien do Stanu Gry
				this->_dane->maszyna.DodajState(StateRef(new PauzaState( _dane )), false);
			}

			else if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_gridSprite, sf::Mouse::Left, this->_dane->window))
			{
				if (STATE_W_TRAKCIE_GRY == graState)
				{
					this->SprawdzIPolozElement();
				}
			}
		}
	}

	void StateGry::Update(float dt)
	{
		if (STATE_REMIS == graState || STATE_PRZEGRAL == graState || STATE_WYGRAL == graState)
		{
			if (this->_zegar.getElapsedTime().asSeconds() > CZAS_PRZED_POKAZANIEM_KONIEC_GRY)
			{
				this->_dane->maszyna.DodajState(StateRef(new KoniecGry(_dane)), true);
			}
		}
	}

	void StateGry::Draw(float dt)
	{
		this->_dane->window.clear(sf::Color::Red);

		this->_dane->window.draw(this->_tlo);
		this->_dane->window.draw(this->_pauzaPrzycisk);
		this->_dane->window.draw(this->_gridSprite);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_dane->window.draw(this->_gridElementy[x][y]);
			}
		}

		this->_dane->window.display();
	}

	void StateGry::WczytyajElementyGrid()
	{
		sf::Vector2u tempSpriteRozm = this->_dane->assets.WczytajTexture("Element X").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridElementy[x][y].setTexture(this->_dane->assets.WczytajTexture("Element X"));
				_gridElementy[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteRozm.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteRozm.y * y) - 7);
				_gridElementy[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void StateGry::SprawdzIPolozElement()
	{
		sf::Vector2i klikPoz = this->_dane->wczytywanie.WczytajPozMyszki(this->_dane->window);
		sf::FloatRect gridRozm = _gridSprite.getGlobalBounds();
		sf::Vector2f dziuraNaZewnatrzGrid = sf::Vector2f((SCREEN_WIDTH - gridRozm.width) / 2, (SCREEN_HEIGHT - gridRozm.height) / 2);

		sf::Vector2f gridLokalnaKlikPoz = sf::Vector2f(klikPoz.x - dziuraNaZewnatrzGrid.x, klikPoz.y - dziuraNaZewnatrzGrid.y);

		//std::cout << gridLokalnaKlikPoz.x << ", " << gridLokalnaKlikPoz.y << std::endl;

		sf::Vector2f gridSectionSize = sf::Vector2f(gridRozm.width / 3, gridRozm.height / 3);

		int kolumna, wiersz;

		// Sprawdzenie, ktora kolumne kliknal uzytkownik
		if (gridLokalnaKlikPoz.x < gridSectionSize.x) // Pierwsza Kolumna
		{
			kolumna = 1;
		}
		else if (gridLokalnaKlikPoz.x < gridSectionSize.x * 2) // Druga Kolumna
		{
			kolumna = 2;
		}
		else if (gridLokalnaKlikPoz.x < gridRozm.width) // Trzecia Kolumna
		{
			kolumna = 3;
		}

		// Sprawdzenie, ktora kolumne kliknal uzytkownik
		if (gridLokalnaKlikPoz.y < gridSectionSize.y) // Pierwszy Wiersz
		{
			wiersz = 1;
		}
		else if (gridLokalnaKlikPoz.y < gridSectionSize.y * 2) // Drugi Wiersz
		{
			wiersz = 2;
		}
		else if (gridLokalnaKlikPoz.y < gridRozm.height) // Trzeci Wiersz
		{
			wiersz = 3;
		}

		if (gridTablica[kolumna - 1][wiersz - 1] == PUSTY_ELEMENT)
		{
			gridTablica[kolumna - 1][wiersz - 1] = turn;

			if (GRACZ_ELEMENT == turn)
			{
				_gridElementy[kolumna - 1][wiersz - 1].setTexture(this->_dane->assets.WczytajTexture("Element X"));

				this->SprawdzCzyGraczWygral(turn);
			}
			

			_gridElementy[kolumna - 1][wiersz - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void StateGry::SprawdzCzyGraczWygral(int gracz)
	{
		SprawdzCzy3ElementyPasuja(0, 0, 1, 0, 2, 0, gracz);
		SprawdzCzy3ElementyPasuja(0, 1, 1, 1, 2, 1, gracz);
		SprawdzCzy3ElementyPasuja(0, 2, 1, 2, 2, 2, gracz);
		SprawdzCzy3ElementyPasuja(0, 0, 0, 1, 0, 2, gracz);
		SprawdzCzy3ElementyPasuja(1, 0, 1, 1, 1, 2, gracz);
		SprawdzCzy3ElementyPasuja(2, 0, 2, 1, 2, 2, gracz);
		SprawdzCzy3ElementyPasuja(0, 0, 1, 1, 2, 2, gracz);
		SprawdzCzy3ElementyPasuja(0, 2, 1, 1, 2, 0, gracz);

		if (STATE_WYGRAL != graState)
		{
			graState = STATE_AI_W_TRAKCIE_GRY;

			ai->PolozElement(&gridTablica, _gridElementy, &graState);

			SprawdzCzy3ElementyPasuja(0, 0, 1, 0, 2, 0, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(0, 1, 1, 1, 2, 1, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(0, 2, 1, 2, 2, 2, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(0, 0, 0, 1, 0, 2, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(1, 0, 1, 1, 1, 2, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(2, 0, 2, 1, 2, 2, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(0, 0, 1, 1, 2, 2, AI_ELEMENT);
			SprawdzCzy3ElementyPasuja(0, 2, 1, 1, 2, 0, AI_ELEMENT);
		}

		int pustyNum = 9;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (PUSTY_ELEMENT != gridTablica[x][y])
				{
					pustyNum--;
				}
			}
		}

		//sprawdz czy wynik gry to remis
		if (0 == pustyNum && (STATE_WYGRAL != graState) && (STATE_PRZEGRAL != graState))
		{
			graState = STATE_REMIS;
		}

		//sprawdz czy to koniec gry
		if (STATE_REMIS == graState || STATE_PRZEGRAL == graState || STATE_WYGRAL == graState)
		{
			this->_zegar.restart();
		}

		std::cout << graState << std::endl;
	}

	void StateGry::SprawdzCzy3ElementyPasuja(int x1, int y1, int x2, int y2, int x3, int y3, int elementDoSprawdzenia)
	{
		if (elementDoSprawdzenia == gridTablica[x1][y1] && elementDoSprawdzenia == gridTablica[x2][y2] && elementDoSprawdzenia == gridTablica[x3][y3])
		{
			std::string wygranyElementStr;

			if (O_ELEMENT == elementDoSprawdzenia)
			{
				wygranyElementStr = "Element O Wygrany";
			}

			else
			{
				wygranyElementStr = "Element X Wygrany";
			}

			_gridElementy[x1][y1].setTexture(this->_dane->assets.WczytajTexture(wygranyElementStr));
			_gridElementy[x2][y2].setTexture(this->_dane->assets.WczytajTexture(wygranyElementStr));
			_gridElementy[x3][y3].setTexture(this->_dane->assets.WczytajTexture(wygranyElementStr));

			if (GRACZ_ELEMENT == elementDoSprawdzenia)
			{
				graState = STATE_WYGRAL;
			}

			else
			{
				graState = STATE_PRZEGRAL;
			}
		}
	}

}

//specyfikacja i ustawienie elementów w menu Gry, ustawienie siatki gry, ustawienie elementów X i O