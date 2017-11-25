#include "Tile.h"

Tile::Tile(float x, float y)
{
	shape = sf::RectangleShape(sf::Vector2f(32, 32));
	shape.setPosition(x*32, y*32);

	shape.setFillColor(sf::Color(255, 0, 0, 255));
}

Tile::~Tile()
{
}
