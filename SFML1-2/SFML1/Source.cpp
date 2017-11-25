#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Level.h"

void pollEvent(sf::Event e);

void addLevel(unsigned w, unsigned h, std::string id);

int counter = -1;

std::vector<Level*> levels;
sf::RenderWindow window(sf::VideoMode(1280, 720), "Edytor", sf::Style::Close);

sf::View view;

sf::RectangleShape curs;

int x = 0, y = 0, w, h;

std::string id;

int main()
{
	std::cout << "ID" << std::endl;

	std::cin >> id;

	std::cout << "X" << std::endl;
	std::cin >> w;

	std::cout << "Y" << std::endl;
	std::cin >> h;

	window.setMouseCursorVisible(false);

	curs.setSize(sf::Vector2f(16, 16));
	curs.setFillColor(sf::Color(0,255,0,255));

	addLevel(w, h, id);

	while (window.isOpen())
	{
		sf::Event e;
		pollEvent(e);
		
		view.reset(sf::FloatRect(0, 0, levels[counter]->size.x * 32, levels[counter]->size.y * 32));
		

		window.setView(view);

		x = sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;
		sf::Vector2f pos(window.mapPixelToCoords(sf::Vector2i(x, y)));
		
		curs.setPosition(pos);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) levels[counter]->addTile(pos.x, pos.y);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) levels[counter]->removeTile(pos.x, pos.y);

		levels[counter]->saveLevel();

		window.clear(sf::Color(255, 255, 255, 255));
		levels[counter]->drawTiles(&window);
		window.draw(curs);
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
	}
}

void addLevel(unsigned w, unsigned h, std::string id)
{
	levels.emplace_back(new Level(w, h, id));
	counter++;
}
