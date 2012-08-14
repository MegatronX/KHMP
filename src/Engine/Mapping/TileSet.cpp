#include "TileSet.h"

namespace Mapping
{
	TileSet::TileSet(void)
	{
	}

	TileSet::TileSet(std::string &name, int firstGID)
	{
		this->name = name;
		this->firstGID = firstGID;
	}
	TileSet::TileSet(std::string &name, int firstGID, int tileWidth, int tileHeight, boost::shared_ptr<sf::Texture> refImage)
	{
		this->firstGID = firstGID;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		//this->referenceImage = sourceImage;
		this->BaseTexture = refImage;
		this->name = name;
		BaseTexture->setSmooth(false);
		auto size = BaseTexture->getSize();
		int XTiles = (int)size.x / tileWidth;
		int YTiles = (int)size.y / tileHeight;
		for (int y = 0; y < YTiles; ++y)
		{
			for (int x = 0; x < XTiles; ++x)
			{
				sf::Sprite sprite(*BaseTexture);
				sprite.setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
				tilesprites.push_back(sprite);
			}
		}
		Animated = false;
	}
	TileSet::TileSet(std::string &name, int firstGID, int tileWidth, int tileHeight, sf::Texture &sourceImage)
	{
		this->firstGID = firstGID;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->referenceTexture = sourceImage;
		this->name = name;
		//referenceImage.SetSmooth(false);
		auto size = referenceTexture.getSize(); 
		int XTiles = (int)size.x / tileWidth;
		int YTiles = (int)size.y / tileHeight;
		for (int y = 0; y < YTiles; ++y)
		{
			for (int x = 0; x < XTiles; ++x)
			{
				sf::Sprite sprite(referenceTexture);
				sprite.setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
				tilesprites.push_back(sprite);
			}
		}
		Animated = false;
	}

	int TileSet::GetFirstGID()
	{
		return firstGID;
	}
	int TileSet::GetEndGID()
	{
		return firstGID + tilesprites.size() - 1;
	}
	sf::Sprite& TileSet::GetTile(int index)
	{
		return tilesprites[index];
	}
	std::string TileSet::GetName()
	{
		return name;
	}

	const sf::Texture& TileSet::GetTexture()
	{
		return referenceTexture;
	}
	void TileSet::SetTexture(sf::Texture& image)
	{
		referenceTexture = image;
	}
	void TileSet::SetTexture(boost::shared_ptr<sf::Texture>& tex)
	{
		this->BaseTexture = tex;
		for (auto tspr = tilesprites.begin(); tspr != tilesprites.end(); ++tspr)
		{
			tspr->setTexture(*tex);
		}
	}
	void TileSet::Add(sf::Sprite &sprite)
	{
		tilesprites.push_back(sprite);
	}

	bool TileSet::IsAnimated() const
	{
		return Animated;
	}

	TileSet::~TileSet(void)
	{

	}

}