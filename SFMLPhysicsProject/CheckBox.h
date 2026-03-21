#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
class CheckBox
{
	sf::Text TextNextTo;
	int isActive = -1;
	sf::Texture BackBoxTexture;
	sf::Sprite BackBox;

	sf::Texture CheckMarkTexture;
	sf::Sprite CheckMark;

	sf::Font font;

public:
	CheckBox() {}
	~CheckBox() {}
	void CheckBoxReset();
	void CheckBoxMaker(sf::String Textn, int xPos, int yPos, int textsize);
	void CheckBoxEventLogic(sf::Event e, bool isinbounds);
	void CheckBoxDraw(sf::RenderWindow &window);
	int isCheckMarkTrue();
	void SetCheckBox(int isCheck);
	sf::Sprite ReturnBackBox();

};

