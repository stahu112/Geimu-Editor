#include "SpriteTile.h"



SpriteTile::SpriteTile(float x, float y, sf::Texture tex1)
{
	shape = sf::RectangleShape(sf::Vector2f(32, 32));

	shape.setPosition(x * 32, y * 32);

	tex = tex1;
	shape.setTexture(&tex);
}


SpriteTile::~SpriteTile()
{
}
