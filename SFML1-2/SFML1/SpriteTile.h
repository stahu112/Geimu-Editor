#pragma once

#include <SFML\Graphics.hpp>

class SpriteTile
{
public:

	int id;

	sf::Vector2f position;

	sf::Texture tex;

	sf::RectangleShape shape;

	SpriteTile(float x, float y, sf::Texture tex);
	~SpriteTile();
};

