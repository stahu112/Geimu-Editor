#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#include "Tile.h"
#include "SpriteTile.h"

class Level
{


public:
	sf::Sprite tile;
	std::string levid;
	std::string spriteid;

	std::vector<std::vector<Tile*>> tiles;

	std::vector<std::vector<SpriteTile*>> spriteTiles;

	sf::Vector2i size;

	unsigned numOfTiles;

	std::vector<std::vector<int>> list;
	std::vector<std::vector<std::string>> spriteList;

	void addTile(float x, float y);
	void removeTile(float x, float y);

	void addSpriteTile(float x, float y, int xt, int yt, bool back);
	void removeSpriteTile(float x, float y);

	void drawTiles(sf::RenderWindow * window);

	Level(unsigned width, unsigned height, std::string id, std::string levelid, std::string path);

	void saveLevel();
	~Level();
};

