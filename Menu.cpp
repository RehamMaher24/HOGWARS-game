#include "Menu.h"
#include<SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>


using namespace std;
using namespace sf;

Menu::Menu(float width, float height)
{
	font.loadFromFile("IZONERY Trial.otf");

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color::Green);
	mainmenu[0].setString("Play");
	mainmenu[0].setCharacterSize(110);
	mainmenu[0].setPosition(Vector2f(width / 4, height / (2)));


	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("Instructions");
	mainmenu[1].setCharacterSize(110);
	mainmenu[1].setPosition(Vector2f(width / 4, height / (2) + 110));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("Designers");
	mainmenu[2].setCharacterSize(110);
	mainmenu[2].setPosition(Vector2f(width / 4, height / (2) + 220));

	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(Color::White);
	mainmenu[3].setString("Exit");
	mainmenu[3].setCharacterSize(110);
	mainmenu[3].setPosition(Vector2f(width / 4, height / (2) + 330));

	selected = 0;

}


Menu::~Menu() {}


void Menu::setselected(int n) {
	selected = n;
}

void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 4; i++)
	{
		window.draw(mainmenu[i]);
	}
}

void Menu::MoveDown() {
	if (selected + 1 <= 4) //not exit
	{
		mainmenu[selected].setFillColor(Color::White);
		selected++;
		if (selected == 4)
		{
			selected = 0;
		}
		mainmenu[selected].setFillColor(Color::Green);
	}
}

void Menu::MoveUp()
{
	if (selected - 1 >= -1)  //not play
	{
		mainmenu[selected].setFillColor(Color::White);
		selected--;
		if (selected == -1)
		{
			selected = 3;
		}
		mainmenu[selected].setFillColor(Color::Green);
	}

}

void Menu::checkMouseHover(RenderWindow& window)     //Move the mouse to change the color.
{
	for (int i = 0; i < 4; i++)
	{
		if (mainmenu[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			mainmenu[selected].setFillColor(Color::White);  // Before the mouse moves
			selected = i;                                                              // Convert to new
			mainmenu[selected].setFillColor(Color::Green);  //After the mouse moves
		}
	}
}
int Menu::getHoveredIndex(RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		if (mainmenu[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			return i;
		}
	}
	return -1;
}