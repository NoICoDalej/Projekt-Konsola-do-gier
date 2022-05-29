#include "MainMenuState.h"
#include "definicje.h" 
#include "MahjongState.h"
#include "PauzaState.h"
using namespace sf;

int field[50][50][50] = { 0 };

int& f(int x, int y, int z) 
{ return field[y + 2][x + 2][z]; }

int& f(Vector3i v) 
{ return f(v.x, v.y, v.z); }

Vector3i v1, v2;
std::vector<Vector3i> moves;

namespace Engine
{
	MahjongState::MahjongState(DaneGryRef dane) : _dane(dane)
	{
	}

	void MahjongState::Init()
	{

		this->_dane->assets.WczytajTexture("Tlo", MAHJONG_TLO_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Klocki", MAHJON_KLOCKI_SCIEZKAPLIK);
		this->_dane->assets.WczytajTexture("Przycisk Pauzy", PAUZA_PRZYCISK);

		_tlo.setTexture(this->_dane->assets.WczytajTexture("Tlo"));
		_klocki.setTexture(this->_dane->assets.WczytajTexture("Klocki"));
		_pauzaPrzycisk.setTexture(this->_dane->assets.WczytajTexture("Przycisk Pauzy"));

		_pauzaPrzycisk.setPosition((SCREEN_WIDTH / 2) - (this->_pauzaPrzycisk.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 3) - (this->_pauzaPrzycisk.getGlobalBounds().height * (-2.5)));


		zaladujMape();
		pomieszaj();

	}

	void MahjongState::HandleInput()
	{
		sf::Event event;

		while (this->_dane->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_dane->window.close();
			}

			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == Mouse::Right)
				{
					int n = moves.size();
					if (n == 0) continue;
					f(moves[n - 1]) *= -1;
					moves.pop_back();
					f(moves[n - 2]) *= -1;
					moves.pop_back();
				}
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					for (int z = 0; z < 10; z++)
					{
						Vector2i pos = Mouse::getPosition(this->_dane->window) - Vector2i(30, 0);
						int x = (pos.x - z * offX) / stepX;
						int y = (pos.y + z * offY) / stepY;

						for (int i = 0; i < 2; i++)
							for (int j = 0; j < 2; j++)
								if (f(x - i, y - j, z) > 0 && czyOtwarte(x - i, y - j, z))
									v1 = Vector3i(x - i, y - j, z);

						if (v1 == v2) continue;

						int a = f(v1), b = f(v2);
						if (a == b || (a > 34 && a < 39 && b>34 && b < 39) || (a >= 39 && b >= 39))
						{
							f(v1) *= -1; moves.push_back(v1);
							f(v2) *= -1; moves.push_back(v2);
						}
						v2 = v1;
					}
				}

			}

			if (this->_dane->wczytywanie.CzySpriteKlikniety(this->_pauzaPrzycisk, sf::Mouse::Left, this->_dane->window))
			{
				// Zmien do Stanu Gry
				this->_dane->maszyna.DodajState(StateRef(new PauzaState(_dane)), false);
			}

			
		}
	}

	void MahjongState::Update(float dt)
	{
		
	}

	void MahjongState::Draw(float dt)
	{
		this->_dane->window.clear();

		this->_dane->window.draw(this->_tlo);
		

		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z) - 1;
					if (k < 0) continue;
					_klocki.setTextureRect(IntRect(k * w, 0, w, h));
					if (czyOtwarte(x, y, z)) _klocki.setTextureRect(IntRect(k * w, h, w, h));
					_klocki.setPosition(x * stepX + z * offX, y * stepY - z * offY);
					_klocki.move(30, 0); 
					this->_dane->window.draw(_klocki);
				}

		this->_dane->window.draw(this->_pauzaPrzycisk);

		this->_dane->window.display();
	}

	bool MahjongState::czyOtwarte(int x, int y, int z)
	{
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if (f(x + 2, y + i, z) > 0 && f(x - 2, y + j, z) > 0) return 0;

		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if (f(x + i, y + j, z + 1) > 0) return 0;

		return 1;
	}

	void MahjongState::pomieszaj()
	{
		srand(time(0));

		for (int k = 1;; k++)
		{
			std::vector<Vector3i> opens;
			for (int z = 0; z < 10; z++)
				for (int y = 0; y < 18; y++)
					for (int x = 0; x < 30; x++)
						if (f(x, y, z) > 0 && czyOtwarte(x, y, z)) opens.push_back(Vector3i(x, y, z));

			int n = opens.size();
			if (n < 2) break;
			int a = 0, b = 0;
			while (a == b) { a = rand() % n; b = rand() % n; }
			f(opens[a]) = -k;  if (k > 34) k++;
			f(opens[b]) = -k;
			k %= 42;
		}

		for (int z = 0; z < 10; z++)
			for (int y = 0; y < 18; y++)
				for (int x = 0; x < 30; x++) f(x, y, z) *= -1;
	}

	void MahjongState::zaladujMape()
	{
		std::fstream plik(MAHJON_MAPA_SCIEZKAPLIK);
		for (int y = 0; y < 18; y++)
			for (int x = 0; x < 30; x++)
			{
				char a;  plik >> a;
				int n = a - '0';
				for (int z = 0; z < n; z++)
					if (f(x - 1, y - 1, z)) f(x - 1, y, z) = f(x, y - 1, z) = 0;
					else f(x, y, z) = 1;
			}
	}
}