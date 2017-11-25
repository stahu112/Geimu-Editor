#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#include "Tile.h"

class Level
{
public:
	std::string levid;

	std::vector<std::vector<Tile*>> tiles;

	sf::Vector2i size;

	unsigned numOfTiles;

	std::vector<std::vector<int>> list;

	void addTile(float x, float y);
	void removeTile(float x, float y);

	void drawTiles(sf::RenderWindow * window);

	Level(unsigned width, unsigned height, std::string id);

	void saveLevel();
	~Level();
};

