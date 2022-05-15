#pragma once

#include <map>

#include <SFML/Graphics.hpp>

namespace Engine
{
	class AssetMngr
	{
	public:
		AssetMngr() {}
		~AssetMngr() {}

		void WczytajTexture(std::string nazwa, std::string nazwaPliku);
		sf::Texture &WczytajTexture(std::string nazwa);

		void WczytajFont(std::string nazwa, std::string nazwaPliku);
		sf::Font &WczytajFont(std::string nazwa);

	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
	};


}