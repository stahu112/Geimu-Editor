#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:

	int id;

	sf::Vector2i position;

	sf::RectangleShape shape;

	Tile(float x, float y);
	~Tile();
};

