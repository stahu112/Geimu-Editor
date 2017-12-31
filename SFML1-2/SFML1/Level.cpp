#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>
std::fstream file2;
std::fstream file1;

void Level::addTile(float x, float y)
{
	x = floor(x / 32);
	y = floor(y / 32);

	if (x >= 0 && x < size.x && y >= 0 && y < size.y)
	{
		tiles[x][y]->id = 1;

		list[y][x] = 1;
	}
}

void Level::removeTile(float x, float y)
{
	x = floor(x / 32);
	y = floor(y / 32);

	if (x >= 0 && x < size.x && y >= 0 && y < size.y)
	{
		tiles[x][y]->id = 0;

		list[y][x] = 0;
	}
}

void Level::fill(float xt, float yt, bool back)
{
	for (int i = 0; i < spriteTiles.size(); i++)
	{
		for (int j = 0; j < spriteTiles[i].size(); j++)
		{
			spriteTiles[i][j]->shape.setTextureRect(sf::IntRect(xt, yt, 32, 32));
			if( back ) spriteTiles[i][j]->id = 2;
			else spriteTiles[i][j]->id = 1;
		}
	}
}

void Level::addSpriteTile(float x, float y, int xt, int yt, bool back)
{
	x = floor(x / 32);
	y = floor(y / 32);

	if (x >= 0 && x < size.x && y >= 0 && y < size.y)
	{
		spriteTiles[x][y]->shape.setTextureRect(sf::IntRect(xt, yt, 32, 32));

		if (back)
		{
			spriteTiles[x][y]->id = 2;
		}
		else
		{
			spriteTiles[x][y]->id = 1;
		}

		if(back) spriteList[y][x] = std::to_string(xt/32) + "#" + std::to_string(yt/32);
		else spriteList[y][x] = std::to_string(xt/32) + "," + std::to_string(yt/32);
	}

}

void Level::removeSpriteTile(float x, float y)
{
	x = floor(x / 32);
	y = floor(y / 32);

	if (x >= 0 && x < size.x && y >= 0 && y < size.y)
	{
		spriteTiles[x][y]->id = 0;

		spriteList[y][x] = "x,x";
	}
}

void Level::drawTiles(sf::RenderWindow * window)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (spriteTiles[i][j]->id)
			{
				if(spriteTiles[i][j]->id > 1) spriteTiles[i][j]->shape.setFillColor(sf::Color(spriteTiles[i][j]->shape.getFillColor().r, spriteTiles[i][j]->shape.getFillColor().g, spriteTiles[i][j]->shape.getFillColor().b, 100));
				else spriteTiles[i][j]->shape.setFillColor(sf::Color(spriteTiles[i][j]->shape.getFillColor().r, spriteTiles[i][j]->shape.getFillColor().g, spriteTiles[i][j]->shape.getFillColor().b, 255));
				
				window->draw(spriteTiles[i][j]->shape);
			}

			if (tiles[i][j]->id)
			{
				window->draw(tiles[i][j]->shape);
			}
		}
	}
}

Level::Level(unsigned width, unsigned height, std::string id, std::string levelid, std::string path)
{
	levid = id;
	spriteid = levelid;

	sf::Texture tex;

	tex.loadFromFile(path);

	tile.setTexture(tex);

	size.x = width;
	size.y = height;
	numOfTiles = size.x * size.y;

	////////////////////////////////////////

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

	//////////////////////////////////

	spriteList.resize(size.y);

	for (int i = 0; i < spriteList.size(); i++)
	{
		spriteList[i].resize(size.x);
	}

	for (int i = 0; i < spriteList.size(); i++)
	{
		for (int j = 0; j < spriteList[i].size(); j++)
		{
			spriteList[i][j] = "x,x";
		}
	}

	spriteTiles.resize(size.x);

	for (int i = 0; i < spriteTiles.size(); i++)
	{
		spriteTiles[i].resize(size.y);
	}

	for (int i = 0; i < spriteTiles.size(); i++)
	{
		for (int j = 0; j < spriteTiles[i].size(); j++)
		{
			spriteTiles[i][j] = new SpriteTile(i, j, tex);
			spriteTiles[i][j]->id = 0;
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

	std::fstream fileS;

	fileS.open(spriteid + ".txt", std::ios::out);

	if (fileS.good())
	{
		for (int i = 0; i < spriteList.size(); i++)
		{
			for (int j = 0; j < spriteList[i].size(); j++)
			{
				if (j + 1 != spriteList[i].size()) fileS << spriteList[i][j] << " ";
				else fileS << spriteList[i][j];
			}
			fileS << "\n";
		}
	}

	fileS.close();
}

Level::~Level()
{
}
