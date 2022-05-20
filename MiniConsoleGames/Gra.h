#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateGlowny.h"
#include "AssetMngr.h"
#include "InputMngr.h"

namespace Engine
{
	struct DaneGry
	{
		StateGlowny maszyna;
		sf::RenderWindow window;
		AssetMngr assets;
		InputMngr wczytywanie;
	};

	typedef std::shared_ptr<DaneGry> DaneGryRef;

	class Gra
	{
	public:
		Gra( int width, int height, std::string tytul);
	private:
		const float dt = 1.0f / 60.0f; //framerate
		sf::Clock _zegar;

		DaneGryRef _dane = std::make_shared<DaneGry>();

		void Run();
	};



}

//zintegrowanie poprzednich manadzerow i state