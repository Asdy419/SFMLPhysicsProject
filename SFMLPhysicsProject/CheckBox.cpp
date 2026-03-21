#include "CheckBox.h"

void CheckBox::CheckBoxReset() {
    isActive = -1;
}

void CheckBox::CheckBoxMaker(sf::String Textn, int xPos, int yPos,int textsize) {
    font.loadFromFile("C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\RobotoSlab-Medium.ttf");
    TextNextTo.setFont(font);
    TextNextTo.setString(Textn);
    TextNextTo.setCharacterSize(textsize);
    TextNextTo.setFillColor(sf::Color::Black);
    TextNextTo.setPosition(sf::Vector2f(xPos +32, yPos+3));

    BackBoxTexture.loadFromFile("C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\checkbox.png");
    BackBox.setTexture(BackBoxTexture);
    BackBox.setPosition(sf::Vector2f(xPos,yPos));
    BackBox.setScale(sf::Vector2f(0.5f*0.1,0.5f*0.1));

    CheckMarkTexture.loadFromFile("C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\checkmark.png");
    CheckMark.setTexture(CheckMarkTexture);
    CheckMark.setPosition(sf::Vector2f(xPos-2, yPos-4));
    CheckMark.setScale(sf::Vector2f(0.6f*0.1, 0.6f*0.1));
    CheckMark.setColor(sf::Color::Green);
    
}

void CheckBox::CheckBoxEventLogic(sf::Event e, bool isinbounds) {
    if (isinbounds) {
        if (e.type == e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
        {
            isActive = isActive*-1;
        }
    }
}

void CheckBox::CheckBoxDraw(sf::RenderWindow& window) {
    window.draw(TextNextTo);
    window.draw(BackBox);
    if (isActive == 1) {
        window.draw(CheckMark);
    }
}

int CheckBox::isCheckMarkTrue() {
    return isActive;
}

void CheckBox::SetCheckBox(int isCheck) {
    isActive = isCheck;
}

sf::Sprite CheckBox::ReturnBackBox() {
    return BackBox;
}