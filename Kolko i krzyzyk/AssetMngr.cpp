#include "AssetMngr.h"

namespace Engine
{
	void AssetMngr::WczytajTexture(std::string nazwa, std::string nazwaPliku)
	{
		sf::Texture tex;

		if (tex.loadFromFile(nazwaPliku))
		{
			this->_textures[nazwa] = tex;
		}
	}

	sf::Texture &AssetMngr::WczytajTexture(std::string nazwa)
	{
		return this->_textures.at(nazwa);
	}

	void AssetMngr::WczytajFont(std::string nazwa, std::string nazwaPliku)
	{
		sf::Font font;

		if (font.loadFromFile(nazwaPliku))
		{
			this->_fonts[nazwa] = font;
		}
	}

	sf::Font &AssetMngr::WczytajFont(std::string nazwa)
	{
		return this->_fonts.at(nazwa);
	}
}