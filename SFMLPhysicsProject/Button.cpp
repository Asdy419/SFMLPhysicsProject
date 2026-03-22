#include "Button.h"

bool isFloat(const std::string& str)
{
    if (str.empty())
        return false;

    char* ptr;
    strtof(str.c_str(), &ptr);
    return (*ptr) == '\0';
}


void Button::TextReset() {
    InputText = "";
    accvar = false;
    FinishedClicking = false;
}


void Button::ButtonMaker(sf::String Textabove, int xPos, int yPos, int width, int height, int txtsize, bool isintonly,int MaxCharSize)
{

    XPos = xPos;
    YPos = yPos;
    isint = isintonly;
    CharSize = MaxCharSize;
	font.loadFromFile("Kinemechanics assets\\RobotoSlab-Medium.ttf");
    TextAbove.setFont(font);
    TextAbove.setString(Textabove);
    TextAbove.setCharacterSize(txtsize);
    TextAbove.setFillColor(sf::Color::Black);
    TextAbove.setPosition(sf::Vector2f(XPos-5, YPos-20));

    ButtonsRectangle.setSize(sf::Vector2f(width, height));
    ButtonsRectangle.setFillColor(sf::Color::White);
    ButtonsRectangle.setPosition(sf::Vector2f(XPos, YPos));
    ButtonsRectangle.setOutlineThickness(2.5f);
    ButtonsRectangle.setOutlineColor(sf::Color::Black);

    OutputText.setFont(font);
    OutputText.setCharacterSize(txtsize-2);
    OutputText.setFillColor(sf::Color::Black);
    OutputText.setPosition(sf::Vector2f(XPos, YPos));

    Error.setFont(font);
    Error.setString("Error please enter \n   number values");
    Error.setStyle(sf::Text::Bold);
    Error.setCharacterSize(100);
    Error.setFillColor(sf::Color::Red);
    Error.setPosition(1980 / 4, 1080 / 4);
    Error.setOrigin(sf::Vector2f(Error.getGlobalBounds().getSize().x/2,( Error.getGlobalBounds().getSize().y / 2)+50));

    Error2.setFont(font);
    Error2.setString("Character Limit Exceeded!");
    Error2.setStyle(sf::Text::Bold);
    Error2.setCharacterSize(80);
    Error2.setFillColor(sf::Color::Red);
    Error2.setPosition((1980 / 4) - 50, (1080 / 4)+30);
    Error2.setOrigin(sf::Vector2f(Error.getGlobalBounds().getSize().x / 2, (Error.getGlobalBounds().getSize().y / 2)));
}
void Button::ButtonEventLogic(sf::Event e, bool isinbounds)
{
    if (isinbounds && e.type == e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
    {
        FinishedClicking = true;
    }

    if ((!isinbounds && e.type == e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) || (e.type == e.KeyReleased && e.key.code == sf::Keyboard::Enter)) { FinishedClicking = false; }
    if (FinishedClicking == true) {
        if (e.type == sf::Event::TextEntered)
        {
            if (std::isprint(e.text.unicode))
            {
                InputText += e.text.unicode;
            }
        }
        else if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::BackSpace) {
                if (!InputText.isEmpty()) {
                    InputText.erase(InputText.getSize() - 1);
                }
            }
        }

    }
}
void Button::ButtonDisplayLogic()
    {
    static sf::Time text_time;
    text_time += clock.restart();
    if (text_time >= sf::seconds(2) && FinishedClicking == true)
    {
        pointerclicker = !pointerclicker;
        text_time = sf::Time::Zero;
    }
    if (!FinishedClicking) {
        pointerclicker = false;
    }
    TextAbove.setPosition(sf::Vector2f(XPos - 5, YPos - 20));
    ButtonsRectangle.setPosition(sf::Vector2f(XPos, YPos));
    OutputText.setPosition(sf::Vector2f(XPos, YPos));
    OutputText.setString(InputText + (pointerclicker ? '|' : ' '));
    Error.setFillColor(sf::Color(Error.getFillColor().r, Error.getFillColor().g, Error.getFillColor().b, opacity));
    Error2.setFillColor(sf::Color(Error.getFillColor().r, Error.getFillColor().g, Error.getFillColor().b, opacity2));
    }
void Button::DrawButton(sf::RenderWindow& window) {
    window.draw(ButtonsRectangle);
    window.draw(OutputText);
    window.draw(TextAbove);

    
}

bool Button::Check(sf::RenderWindow& window) {
    if (isint == true) {
        window.draw(Error);
    }
        window.draw(Error2);
        if (accvar || FinishedClicking == true) {
            accvar = true;
            if ((FinishedClicking == false && !isFloat(std::string(InputText)))&&isint==true)
            {
                timer = 60;
                opacity = 255;
                
                Error.setOutlineThickness(1.5f);
                TextReset();
                accvar = false;
                return false;
            }



        }
        if (FinishedClicking == true && InputText.getSize() > CharSize) {
            timer = 60;
            opacity2 = 255;
            Error2.setOutlineThickness(1.5f);
            TextReset();
            accvar = false;
            return false;
        }
        if (timer > 0) {
            timer -= 1;
        }
        if (opacity > 0 && timer == 0) {
            opacity = opacity - 4.25f;
            std::cout << opacity << std::endl;
            Error.setOutlineThickness(0);
        }
        if (opacity2 > 0 && timer == 0) {
            opacity2 = opacity2 - 4.25f;
            std::cout << opacity << std::endl;
            Error2.setOutlineThickness(0);
        }
        return true;
    }
