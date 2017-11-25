#include "Level.h"

#include <fstream>

void Level::addTile(float x, float y)
{
	x = floor(x / 32);
	y = floor(y / 32);

	if (tiles[x][y])
	{
		tiles[x][y]->id = 1;

		list[y][x] = 1;
	}
}

void Level::removeTile(float x, float y)
{
	x = floor(x / 32);
	y = floor(y / 32);

	tiles[x][y]->id = 0;

	list[y][x] = 0;
}

void Level::drawTiles(sf::RenderWindow * window)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j]->id) window->draw(tiles[i][j]->shape);
		}
	}
}

Level::Level(unsigned width, unsigned height, std::string id)
{
	levid = id;

	size.x = width;
	size.y = height;
	numOfTiles = size.x * size.y;

	list.resize(size.y);

	for (int i = 0; i < list.size(); i++)
	{
		list[i].resize(size.x);
	}

	for (int i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < list[i].size(); j++)
		{
			list[i][j] = 0;
		}
	}

	tiles.resize(size.x);

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(size.y);
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j] = new Tile(i, j);
			tiles[i][j]->id = 0;
		}
	}
}

void Level::saveLevel()
{
	std::fstream file;

	file.open(levid + ".txt", std::ios::out);

	if (file.good())
	{
		for (int i = 0; i < list.size(); i++)
		{
			for (int j = 0; j < list[i].size(); j++)
			{
				if(j+1 != list[i].size() ) file << list[i][j] << " ";
				else file << list[i][j];
			}
			file << "\n";
		}
	}

	file.close();
}

Level::~Level()
{
}
