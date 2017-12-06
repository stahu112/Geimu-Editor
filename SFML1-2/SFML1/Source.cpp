#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Level.h"

void pollEvent(sf::Event e);

void addLevel(unsigned w, unsigned h, std::string id);

void makeGrid(sf::VertexArray& gridX, sf::VertexArray& gridY);

int counter = -1;

std::vector<Level*> levels;
sf::RenderWindow window(sf::VideoMode(1280, 720), "Edytor", sf::Style::Close);

sf::View levelView;

sf::RectangleShape curs;
sf::RectangleShape curs1;

int x = 0, y = 0, w, h;

float zoom = 1;

bool toggle = true;
bool back = false;

float xt = 0, yt = 0;

std::string id;
std::string spriteid;

int main()
{
	std::cout << "ID col" << std::endl;

	std::cin >> id;

	std::cout << "ID sprite" << std::endl;

	std::cin >> spriteid;

	std::cout << "X" << std::endl;
	std::cin >> w;

	std::cout << "Y" << std::endl;
	std::cin >> h;

	sf::Sprite tile;

	sf::VertexArray gridX(sf::Lines, (h + 1)* 2 );
	sf::VertexArray gridY(sf::Lines, (w + 1)* 2 );

	makeGrid(gridX, gridY);

	levelView.setSize(sf::Vector2f(w * 32 * zoom, h * 32 * zoom));

	window.setMouseCursorVisible(false);

	curs.setSize(sf::Vector2f(16, 16));
	curs.setFillColor(sf::Color(0,255,0,155));

	sf::Texture tex;
	tex.loadFromFile("tilemap.png");

	curs1.setSize(sf::Vector2f(32, 32));
	curs1.setTexture(&tex);
	curs1.setTextureRect(sf::IntRect(xt, yt, 32, 32));
	//curs1.setFillColor(sf::Color(curs1.getFillColor().r, curs1.getFillColor().g, curs1.getFillColor().b, 100));

	addLevel(w, h, id);

	float x1 = 0, y1 = 0;

	while (window.isOpen())
	{
		sf::Event e;
		pollEvent(e);

		x = sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;
		sf::Vector2f pos(window.mapPixelToCoords(sf::Vector2i(x, y)));
		
		sf::Vector2f posV(x1, y1);

		levelView.setCenter(posV);
		levelView.setSize(sf::Vector2f(w * 32 * zoom, ((h * 32) - 12) * zoom));
		window.setView(levelView);

		curs1.setTextureRect(sf::IntRect(xt, yt, 32, 32));

		curs.setPosition(pos);
		curs1.setPosition(pos);

		window.clear(sf::Color(255, 255, 255, 255));

		levels[counter]->drawTiles(&window);

		if (toggle)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) levels[counter]->addTile(pos.x, pos.y);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) levels[counter]->removeTile(pos.x, pos.y);

			window.draw(curs);
		}
		else
		{
			if (back)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) levels[counter]->addSpriteTile(pos.x, pos.y, xt, yt, true);
			}
			else
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) levels[counter]->addSpriteTile(pos.x, pos.y, xt, yt, false);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) levels[counter]->removeSpriteTile(pos.x, pos.y);

			window.draw(curs1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  x1 += 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  x1 -= 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  y1 += 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  y1 -= 10;

		levels[counter]->saveLevel();

		window.draw(gridX);
		window.draw(gridY);

		window.display();
	}


	return EXIT_SUCCESS;
}

void pollEvent(sf::Event e)
{
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::KeyReleased)
		{
			if (e.key.code == sf::Keyboard::Right && xt < 9 * 32) { xt += 32; std::cout << "Rect: " << xt / 32 << " " << yt / 32 << std::endl; }
			if (e.key.code == sf::Keyboard::Left && xt > -32) { xt -= 32; std::cout << "Rect: " << xt / 32 << " " << yt / 32 << std::endl; }

			if (e.key.code == sf::Keyboard::Up && yt < 9 * 32) { yt += 32; std::cout << "Rect: " << xt / 32 << " " << yt / 32 << std::endl; }
			if (e.key.code == sf::Keyboard::Down && yt > -32) { yt -= 32; std::cout << "Rect: " << xt / 32 << " " << yt / 32 << std::endl; }

			if (e.key.code == sf::Keyboard::LShift) { toggle = true; std::cout << "Collision mapping: On" << std::endl; }
			if (e.key.code == sf::Keyboard::LControl) { toggle = false; std::cout << "Collision mapping: Off" << std::endl; }

			if (e.key.code == sf::Keyboard::O) { back = true; std::cout << "Background mapping: On" << std::endl; }
			if (e.key.code == sf::Keyboard::P) { back = false; std::cout << "Background mapping: Off" << std::endl; }

			if (e.key.code == sf::Keyboard::C) { levels[counter]->fill(xt, yt, back); }

		}

		if (e.type == sf::Event::MouseWheelMoved)
		{
			zoom += e.mouseWheel.delta * 0.1;
		}
	}
}

void addLevel(unsigned w, unsigned h, std::string id)
{
	levels.emplace_back(new Level(w, h, id, spriteid, "tilemap.png"));
	counter++;
}

void makeGrid(sf::VertexArray& gridX, sf::VertexArray& gridY)
{
	for (int i = 0; i < gridX.getVertexCount(); i++)
	{
		gridX[i].color = sf::Color(0, 0, 0, 255);
		if (i % 2 == 0) gridX[i].position = sf::Vector2f(0, i * 16);
		else gridX[i].position = sf::Vector2f(w * 32, (i - 1) * 16);
	}

	for (int i = 0; i < gridY.getVertexCount(); i++)
	{
		gridY[i].color = sf::Color(0, 0, 0, 255);
		if (i % 2 == 0) gridY[i].position = sf::Vector2f(i * 16, 0);
		else gridY[i].position = sf::Vector2f((i - 1) * 16, h * 32);
	}
}