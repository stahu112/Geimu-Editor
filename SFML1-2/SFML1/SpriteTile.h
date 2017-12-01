#pragma once

#include <SFML\Graphics.hpp>

class SpriteTile
{
public:

	int id;

	sf::Vector2f position;

	sf::Sprite shape;

	SpriteTile(float x, float y, sf::Texture tex);
	~SpriteTile();
};

