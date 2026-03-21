#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class Button
{
public:

	Button() {}
	~Button() {}
	sf::Text TextAbove;
	sf::RectangleShape ButtonsRectangle;
	sf::String InputText;
	sf::Text OutputText;
	sf::Text Error;
	sf::Text Error2;


	float opacity = 0;
	float opacity2 = 0;
	int timer = 0;

	sf::Clock clock;

	sf::Font font;
	bool accvar = false;
	bool pointerclicker;
	bool FinishedClicking;
	bool isint;
	int CharSize;
	int XPos;
	int YPos;
	//void ButtonConstructor(sf::Text txtabov,sf::RectangleShape rctngl, sf::String InputTxt)

	void ButtonMaker(sf::String Textabove, int xPos, int yPos, int width, int height, int txtsize,bool isintonly,int MaxCharSize);
	void TextReset();
	void ButtonEventLogic(sf::Event e, bool isinbounds);
	void ButtonDisplayLogic();
	bool Check(sf::RenderWindow& window);
	void DrawButton(sf::RenderWindow& window);
};

