#include "SpriteTile.h"



SpriteTile::SpriteTile(float x, float y, sf::Texture tex)
{
	shape.setPosition(x * 32, y * 32);

	shape.setTexture(tex);
}


SpriteTile::~SpriteTile()
{
}
