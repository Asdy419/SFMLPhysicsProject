#include "StatesManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
#include "Button.h"
#include "CheckBox.h"
#include<string>
#include<iomanip>
#include<fstream>
#include <limits>
#include <sstream>
#include<cctype>
#include <regex>
#include<cmath>

bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp)
{
    if (sprite.contains(mp)) {
        return true;
    }
    return false;
}

int checkSign(int num) {
    if (num < 0)
        return -1;
    else if (num > 0)
        return 1;
    else
        return 0;
}

std::string States::getLineFromFile(const std::string& filename, int lineNumber) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        int currentLine = 0;

        while (getline(file, line)) {
            currentLine++;
            if (currentLine == lineNumber) {
                file.close();
                return line;
            }
        }

        file.close();
        // Return an empty string if the specified line number is out of range
        return "";
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        // Return an empty string if the file couldn't be opened
        return "";
    }
}

float States::extractFloatFromString(const std::string& inputString) {
    // Regular expression to match floating-point numbers
    std::regex floatRegex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");

    // Search for the first match in the input string
    std::smatch match;
    if (std::regex_search(inputString, match, floatRegex)) {
        // Convert the matched substring to a float
        float result = std::stof(match.str());
        return result;
    }
    else {
        // Return some default value or handle the case where no float is found
        std::cerr << "No float found in the input string." << std::endl;
        return 0.0f;
    }
} 

int States::QuestionType() {
    int horizontalCounter = 0;
    int verticalCounter = 0;
    if ((horizontalCounter<2&&verticalCounter<2&&Time.InputText.isEmpty()&&Time.FinishedClicking==false)||(horizontalCounter<1&&verticalCounter<3)) {
        if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false) {
            verticalCounter += 1;
        }
        if (!InitialVelocity.InputText.isEmpty() && InitialVelocity.FinishedClicking == false) {
            verticalCounter += 1;
        }
        if (!FinalVelocity.InputText.isEmpty() && FinalVelocity.FinishedClicking == false) {
            verticalCounter += 1;
        }
        if (!Acceleration.InputText.isEmpty() && Acceleration.FinishedClicking == false) {
            verticalCounter += 1;
        }
        if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false) {
            horizontalCounter += 1;
        }
        if (!HVelocity.InputText.isEmpty() && HVelocity.FinishedClicking == false) {
            horizontalCounter += 1;
        }
        if (!Time.InputText.isEmpty() && Time.FinishedClicking == false && horizontalCounter <2 && verticalCounter < 3) {
            verticalCounter += 1;
        }
    }
    if (horizontalCounter>= 2&&verticalCounter>=2) {
        return 2;
    }
    
    if (verticalCounter >= 3) {
        return 1;
    }
    else {
        return 0;
    }
}


void States::textmaker(sf::Text &object,const sf::Font &font,const sf::String InputString, int size, sf::Vector2f position, sf::Color color, sf::Uint32 style) {
    object.setFont(font);
    object.setString(InputString);
    object.setCharacterSize(size);
    object.setPosition(position);
    object.setFillColor(color);
    object.setStyle(style);
}
void States::buttonmaker(sf::Sprite& object,std::string textureloc,sf::Texture& texture, sf::Vector2f position, sf::Vector2f size, sf::Color color){
    texture.loadFromFile(textureloc);
    object.setTexture(texture);
    object.setPosition(position);
    object.setScale(size);
    object.setColor(color);
    object.setTexture(texture, true);

}


void States::start(int x, int y)
{
    //Window Constructor
    xWinSize = x;
    yWinSize = y;
    window.create(sf::VideoMode(xWinSize,yWinSize),"Kinemechanics");
    window.setFramerateLimit(60);
    Icon.loadFromFile("C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Logo.png");
    font.loadFromFile("C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\RobotoSlab-Medium.ttf");
    window.setIcon(256, 256, Icon.getPixelsPtr());
    cursor.loadFromSystem(sf::Cursor::Arrow);
    CurrentState = 1;
    
}

bool States::menustate(){

    if (MenuRanOnce == false) {
        //Menu Title
        buttonmaker(Title, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Menu\\Title.png", TitleTexture, sf::Vector2f(xWinSize * 0.5, yWinSize * 0.15), sf::Vector2f(0.65f, 0.65f), sf::Color::White);
        sf::Vector2u Titlesize = TitleTexture.getSize();
        Title.setOrigin(Titlesize.x / 2, Titlesize.y / 2);

        //Projectile Motion Button
        buttonmaker(PMB, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Menu\\ProjectileMotion.png", PMBTexture, sf::Vector2f(xWinSize * 0.28, yWinSize * 0.68), sf::Vector2f(0.65f, 0.65f), sf::Color::White);
        sf::Vector2u PMBsize = PMBTexture.getSize();
        PMB.setOrigin(PMBsize.x / 2, PMBsize.y / 2);

        //Collision Button
        buttonmaker(CB, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Menu\\collisions.png", CBTexture, sf::Vector2f(xWinSize - PMB.getPosition().x,PMB.getPosition().y), sf::Vector2f(0.65f, 0.65f), sf::Color::White);
        sf::Vector2u CBsize = CBTexture.getSize();
        CB.setOrigin(CBsize.x / 2, CBsize.y / 2);

        //cursor reset
        cursor.loadFromSystem(sf::Cursor::Arrow);

        MenuRanOnce = true;
    }


        
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))window.close();

            

            if (isSpriteHover(CB.getGlobalBounds(), worldPos)) {
                CB.setScale(sf::Vector2f(0.8f, 0.8f));
                if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    CurrentState = 3;
                    CollisionRanOnce = false;
            }
            else {
                CB.setScale(sf::Vector2f(0.65f, 0.65f));

            }

            if (isSpriteHover(PMB.getGlobalBounds(), worldPos)) {
                PMB.setScale(sf::Vector2f(0.8f, 0.8f));
                if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    CurrentState = 2;
                    ProjectileMotionRanOnce = false;
            }
            else {
                PMB.setScale(sf::Vector2f(0.65f, 0.65f));
            }
        }



        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        worldPos = window.mapPixelToCoords(pixelPos);


        if (isSpriteHover(CB.getGlobalBounds(), worldPos)||isSpriteHover(PMB.getGlobalBounds(),worldPos)) {
            cursor.loadFromSystem(sf::Cursor::Hand);
        }
        else {
            cursor.loadFromSystem(sf::Cursor::Arrow);
        }
        
        window.clear();
        window.draw(PMB);
        window.draw(Title);
        window.draw(CB);
        window.display();


    


    return true;


}

bool States::projectilemotionstate() {
    if (ProjectileMotionRanOnce == false) {
        eqranonce = false;
        showsaved = false;
        ShowDownloadUI = -1;
        ShowImportUI = -1;
        showhelp = -1;
        run = false;
        setValues1 = false;
        setValues2 = false;
        horizontalVelocity = 0;
        verticalInitialVelocity = 0;
        //Object
        ObjectInMotion.setRadius(10);
        ObjectInMotion.setFillColor(sf::Color::Black);
        ObjectInMotion.setPosition(sf::Vector2f(16, 520));
        ObjectInMotion.setOrigin(ObjectInMotion.getRadius()+5, ObjectInMotion.getRadius());
        lineSegments.clear();


        //Back Button
        buttonmaker(BackButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Back Button.png", BackButtonTexture, sf::Vector2f(0, 0), sf::Vector2f(0.1f, 0.1f), sf::Color::White);
        buttonmaker(Background, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\background.png", BackgroundTexture, sf::Vector2f(0, -5), sf::Vector2f(0.53f, 0.53f), sf::Color::White);



        textmaker(Verticaltxt, font, "Vertical Components", 12, sf::Vector2f(105, 10), sf::Color::Black, sf::Text::Bold);
        textmaker(Horizontaltxt, font, "Horizontal Components", 8, sf::Vector2f(1, 43), sf::Color::Black, sf::Text::Bold);

        //Run Button
        buttonmaker(RunButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Run Button.png", RunButtonTexture, sf::Vector2f(170, 230), sf::Vector2f(0.07f, 0.07f), sf::Color::White);

        //Import Button
        buttonmaker(ImportButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Import Button.png", ImportButtonTexture, sf::Vector2f(90, 230), sf::Vector2f(0.07f, 0.07f), sf::Color::White);

        //reset button
        buttonmaker(ResetButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\resetbutton.png", ResetButtonTexture, sf::Vector2f(80, 200), sf::Vector2f(0.045f, 0.045f), sf::Color::White);

        //help button
        buttonmaker(Help, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\Explination.png", HelpTexture, sf::Vector2f(45, 200), sf::Vector2f(0.045f, 0.045f), sf::Color::White);

        //Download Button
        buttonmaker(DownloadButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\DownloadButton.png", DownloadButtonTexture, sf::Vector2f(10, 200), sf::Vector2f(0.044f, 0.044f), sf::Color::White);

        //Close Button Download
        buttonmaker(CloseButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Close Button.png", CloseButtonTexture, sf::Vector2f(650, 216), sf::Vector2f(0.044f, 0.044f), sf::Color::White);

        //Close Button Import
        buttonmaker(ImportCloseButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Close Button.png", ImportCloseButtonTexture, sf::Vector2f(650, 216), sf::Vector2f(0.044f, 0.044f), sf::Color::White);

        //Close Button Import
        buttonmaker(CloseButtonHelp, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Close Button.png", CloseButtonHelpTexture, sf::Vector2f(677, 166), sf::Vector2f(0.044f, 0.044f), sf::Color::White);


        //Save Button
        buttonmaker(SaveButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Save Button.png", SaveButtonTexture, sf::Vector2f(465, 289), sf::Vector2f(0.075f, 0.075f), sf::Color::White);


        //Clean / Reset button
        buttonmaker(ResetSim, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\resetprojectile.png", ResetSimTexture, sf::Vector2f(0, 0), sf::Vector2f(0.075f, 0.075f), sf::Color::White);

        //outputs a confirmation text on save
        textmaker(successsave, font, "", 50, sf::Vector2f(160, 150), sf::Color::Green, sf::Text::Bold);
        successsave.setOutlineColor(sf::Color::Black);
        successsave.setOutlineThickness(3);

        //outputs an error if the program hasnt been run first
        textmaker(NotRunError, font, "You need to run\n the program first\n before saving a text file", 50, sf::Vector2f(180, 150), sf::Color::Red, sf::Text::Bold);
        NotRunError.setOutlineColor(sf::Color::Black);
        NotRunError.setOutlineThickness(3);

        //outputs an error if a text file isnt found
        textmaker(TxtNotFound, font, "Text File not found\n (Do not include .txt)", 50, sf::Vector2f(200, 200), sf::Color::Red, sf::Text::Bold);
        TxtNotFound.setOutlineColor(sf::Color::Black);
        TxtNotFound.setOutlineThickness(3);

        //outputs a success message if the file is found
        textmaker(SuccessImport, font, "The file\n'" + filenameholder + ".txt'" + "\nhas been succesfully imported", 50, sf::Vector2f(200, 200), sf::Color::Green, sf::Text::Bold);
        SuccessImport.setOutlineColor(sf::Color::Black);
        SuccessImport.setOutlineThickness(3);


        //Advanced Button
        buttonmaker(Advanced, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\advanced.png", AdvancedTexture, sf::Vector2f(10, 230), sf::Vector2f(0.07f, 0.07f), sf::Color::White);

        //confirm for importing
        buttonmaker(Confirm, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Confirm Button.png", ConfirmTexture, sf::Vector2f(465, 289), sf::Vector2f(0.075f, 0.075f), sf::Color::White);


        //Acceleration arrow
        buttonmaker(AccelerationArrow, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\accelerationarrows.png",AccelerationArrowTexture,sf::Vector2f(0,0),sf::Vector2f(0.1f,0.1f),sf::Color::White);
        AccelerationArrow.setOrigin(sf::Vector2f(AccelerationArrow.getLocalBounds().width/2,AccelerationArrow.getLocalBounds().height/2));
        
        //Force arrow
        buttonmaker(ForceArrow, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\forcearrow.png", ForceArrowTexture, sf::Vector2f(0, 0), sf::Vector2f(0.1f, 0.1f), sf::Color::White);
        ForceArrow.setOrigin(sf::Vector2f(ForceArrow.getLocalBounds().width / 2, ForceArrow.getLocalBounds().height / 2));
        textmaker(ForceArrowText,font,"",15,sf::Vector2f(0,0),sf::Color::Black,sf::Text::Regular);
        ForceArrowText.setRotation(90);
        
        //Close Button for advanced ui
        buttonmaker(AdvancedClose, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Close Button.png", advancedclosetexture, sf::Vector2f(378, 0), sf::Vector2f(0.044f, 0.044f), sf::Color::White);

        buttonmaker(HorizontalRightArrow, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\arrowright.png", RightArrowTexture, sf::Vector2f(0, 0), sf::Vector2f(0.06f, 0.06f), sf::Color(0, 0, 0, 180));
        buttonmaker(HorizontalLeftArrow, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\arrowleft.png", LeftArrowTexture, sf::Vector2f(50, 0), sf::Vector2f(0.06f, 0.06f), sf::Color(0, 0, 0, 180));
        textmaker(HorizontalDisplayText, font, "", 20, sf::Vector2f(0, 0), sf::Color::Black, sf::Text::Bold);

        buttonmaker(VerticalRightArrow, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\arrowright.png", RightArrowTexture, sf::Vector2f(200, 200), sf::Vector2f(0.06f, 0.06f), sf::Color(0, 0, 0, 180));
        buttonmaker(VerticalLeftArrow, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\arrowleft.png", LeftArrowTexture, sf::Vector2f(250, 200), sf::Vector2f(0.06f, 0.06f), sf::Color(0, 0, 0, 180));
        textmaker(VerticalDisplayText, font, "", 20, sf::Vector2f(200, 200), sf::Color::Black, sf::Text::Bold);
        VerticalDisplayText.setRotation(90);
        VerticalLeftArrow.setRotation(-90);
        VerticalRightArrow.setRotation(-90);

        textmaker(AccelerationText,font,"",15,sf::Vector2f(0,0),sf::Color::White,sf::Text::Regular);
        AccelerationText.setOutlineThickness(3);
        AccelerationText.setRotation(90);

        buttonmaker(horizTrig,"C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\traignle.png",Trig,sf::Vector2f(0,0),sf::Vector2f(0.045f,0.045f),sf::Color::Red);
        buttonmaker(vertTrig,"C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\traignle.png",Trig, sf::Vector2f(0, 0), sf::Vector2f(0.045f, 0.045f), sf::Color::Red);
        buttonmaker(resTrig,"C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\traignle.png",Trig, sf::Vector2f(0, 0), sf::Vector2f(0.045f, 0.045f), sf::Color(125, 0, 0));

        horizTrig.setOrigin(sf::Vector2f(horizTrig.getLocalBounds().width/2,horizTrig.getLocalBounds().height/2));
        vertTrig.setOrigin(sf::Vector2f(vertTrig.getLocalBounds().width / 2, vertTrig.getLocalBounds().height / 2));
        resTrig.setOrigin(sf::Vector2f(resTrig.getLocalBounds().width / 2, resTrig.getLocalBounds().height / 2));


        resTrig.setScale(sf::Vector2f(resTrig.getScale().x,resTrig.getScale().y));

        textmaker(MassofObject,font,"(The object weighs 22.5kg)",11,sf::Vector2f(460,50),sf::Color::Black,sf::Text::Regular);

        textmaker(FullScreenOnly, font, "Please put the program on fullscreen", 11, sf::Vector2f(300, 180), sf::Color::Black, sf::Text::Bold);

        textmaker(showDirection, font, "^ Upwards direction represents positive numbers\nv Downwards direction represents negative numbers", 15, sf::Vector2f(450, 10), sf::Color::Black, sf::Text::Regular);

        Displacement.TextReset();
        InitialVelocity.TextReset();
        FinalVelocity.TextReset();
        Acceleration.TextReset();
        Time.TextReset();

        DownloadInput.TextReset();
        ImportInput.TextReset();

        HDisplacement.TextReset();
        HVelocity.TextReset();

        Displacement.ButtonMaker("Displacement (s)", 125, 18 + 30, 105, 15, 14, true, 15);
        InitialVelocity.ButtonMaker("Initial Velocity (u)", 125, 58 + 30, 105, 15, 14, true, 15);
        FinalVelocity.ButtonMaker("Final Velocity (v)", 125, 98 + 30, 105, 15, 14, true, 15);
        Acceleration.ButtonMaker("Acceleration (a)", 125, 138 + 30, 105, 15, 14, true, 15);
        Time.ButtonMaker("Time (t)", 125, 178 + 30, 105, 15, 14, true, 15);

        HDisplacement.ButtonMaker("Displacement (s)", 5, 55 + 30 - 10, 105, 15, 14, true, 15);
        HVelocity.ButtonMaker("Velocity (v)", 5, 95 + 30 - 10, 105, 15, 14, true, 15);

        DownloadInput.ButtonMaker("Please input a suitable name for the text file", (1980 / 4) - 143, (1080 / 4) - 4, 285, 20, 14, false, 41);
        ImportInput.ButtonMaker("Please enter the name of the text file to import", (1980 / 4) - 150, (1080 / 4) - 4, 300, 20, 14, false, 41);



        TraceMotion.CheckBoxMaker("Trace Motion", 255, 20, 12);
        VelocityVector.CheckBoxMaker("Velocity Vector", 255, 60, 12);
        AccelerationVector.CheckBoxMaker("Acceleration Vector", 255, 100, 12);
        ForceVector.CheckBoxMaker("Force Vector", 255, 140, 12);

        BackBorder.setSize(sf::Vector2f(250, 220 * 1.2));
        BackBorder.setFillColor(sf::Color(128, 128, 128));
        BackBorder.setPosition(sf::Vector2f(0, 0));

        BackBorderforborder.setSize(sf::Vector2f(250, 235 * 1.2));
        BackBorderforborder.setFillColor(sf::Color(0, 0, 0));
        BackBorderforborder.setPosition(sf::Vector2f(0, 0));

        advancedBack.setSize(sf::Vector2f(150, 200));
        advancedBack.setFillColor(sf::Color(150, 150, 150));
        advancedBack.setPosition(sf::Vector2f(250, 0));

        backforadvancedback.setSize(sf::Vector2f(150 * 1.015f, 200 * 1.015f));
        backforadvancedback.setFillColor(sf::Color(90, 90, 90));
        backforadvancedback.setPosition(sf::Vector2f(250, 0));

        HorizontalArrowBox.setSize(sf::Vector2f(0, 15));
        HorizontalArrowBox.setFillColor(sf::Color(0, 0, 0, 180));
        HorizontalArrowBox.setPosition(sf::Vector2f(29, 520));
        HorizontalArrowBox.setOrigin(HorizontalArrowBox.getLocalBounds().left,HorizontalArrowBox.getLocalBounds().height/2);

        VerticalArrowBox.setSize(sf::Vector2f(15, 0));
        VerticalArrowBox.setFillColor(sf::Color(0, 0, 0, 180));
        VerticalArrowBox.setPosition(sf::Vector2f(0, 520));


        //BackBorder for the textfile downloader
        BackBoxDownload.setSize(sf::Vector2f(350, 100));
        BackBoxDownload.setFillColor(sf::Color(128, 128, 128));
        BackBoxDownload.setOrigin(sf::Vector2f(BackBoxDownload.getSize().x / 2, BackBoxDownload.getSize().y / 2));
        BackBoxDownload.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        BackBorderDownload.setSize(sf::Vector2f(350 * 1.025, 100 * 1.1));
        BackBorderDownload.setFillColor(sf::Color(54, 69, 79));
        BackBorderDownload.setOrigin(sf::Vector2f(BackBorderDownload.getSize().x / 2, BackBorderDownload.getSize().y / 2));
        BackBorderDownload.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        //BackBorder for the textfile importer
        BackBoxImport.setSize(sf::Vector2f(350, 100));
        BackBoxImport.setFillColor(sf::Color(128, 128, 128));
        BackBoxImport.setOrigin(sf::Vector2f(BackBoxImport.getSize().x / 2, BackBoxDownload.getSize().y / 2));
        BackBoxImport.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        BackBorderImport.setSize(sf::Vector2f(350 * 1.025, 100 * 1.1));
        BackBorderImport.setFillColor(sf::Color(54, 69, 79));
        BackBorderImport.setOrigin(sf::Vector2f(BackBorderImport.getSize().x / 2, BackBorderDownload.getSize().y / 2));
        BackBorderImport.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        HelpBack.setSize(sf::Vector2f(400, 200));
        HelpBack.setFillColor(sf::Color::White);
        HelpBack.setOrigin(sf::Vector2f(HelpBack.getSize().x / 2, HelpBack.getSize().y / 2));
        HelpBack.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));


        HelpBorder.setSize(sf::Vector2f(400 * 1.025f, 200 * 1.05f));
        HelpBorder.setFillColor(sf::Color::Black);
        HelpBorder.setOrigin(sf::Vector2f(HelpBorder.getSize().x / 2, HelpBorder.getSize().y / 2));
        HelpBorder.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        EndLocation.setFillColor(sf::Color::Yellow);
        EndLocation.setRadius(10);
        EndLocation.setOrigin(EndLocation.getRadius(), EndLocation.getRadius());

        HorizontalVelocityArrow.setOrigin(HorizontalVelocityArrow.getLocalBounds().left, HorizontalVelocityArrow.getLocalBounds().top/2);
        VerticalVelocityArrow.setOrigin(VerticalVelocityArrow.getLocalBounds().left+4, VerticalVelocityArrow.getLocalBounds().top / 2);
        ResultantVelocityArrow.setOrigin(ResultantVelocityArrow.getLocalBounds().left, 4);
        VerticalVelocityArrow.setSize(sf::Vector2f(8, 0));
        HorizontalVelocityArrow.setSize(sf::Vector2f(0, 8));



        originalPosition = ObjectInMotion.getPosition();

        //cursor reset
        cursor.loadFromSystem(sf::Cursor::Arrow);

        //Text reset
        ProjectileMotionRanOnce = true;
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))window.close();


        if (isSpriteHover(BackButton.getGlobalBounds(), worldPos)&&run==false) {
            BackButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                CurrentState = 1;
                MenuRanOnce = false;
            }
        }
        else {
            BackButton.setColor(sf::Color::White);
        }

        if (isSpriteHover(ResetSim.getGlobalBounds(), worldPos) && run == true) {
            ResetSim.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ProjectileMotionRanOnce = false;
            }
        }
        else {
            ResetSim.setColor(sf::Color::White);
        }


        if (isSpriteHover(AdvancedClose.getGlobalBounds(), worldPos) && showadvancedmenu == 1&&run==false) {
            AdvancedClose.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                showadvancedmenu = -1;
            }
        }
        else {
            AdvancedClose.setColor(sf::Color::White);
        }

        if (isSpriteHover(RunButton.getGlobalBounds(), worldPos)&&run==false) {
            RunButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left&&eqranonce==true&&!Time.InputText.isEmpty()&&Time.FinishedClicking==false&&std::stof(std::string(Time.InputText))>0) {
                run = true;
            }
        }
        else {
            RunButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(CloseButtonHelp.getGlobalBounds(), worldPos)&&run==false) {
            CloseButtonHelp.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                showhelp = -1;
            }
        }
        else {
            CloseButtonHelp.setColor(sf::Color::White);
        }

        if (isSpriteHover(SaveButton.getGlobalBounds(), worldPos)&&run==false) {
            SaveButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !DownloadInput.InputText.isEmpty() && eqranonce == true) {
                showsaved = true;
                timer = 100;
                ShowDownloadUI = -1;
                std::string tostrdi = (DownloadInput.InputText + ".txt");
                filehandler.open(tostrdi, std::ios::out);
                if (!filehandler) {
                    std::cout << "File not created!";
                }
                else {
                    std::cout << "File created successfully!";
                    filehandler << "Vertical Displacement (s): " + std::string(Displacement.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Vertical Initial Velocity (u): " + std::string(InitialVelocity.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Vertical Final Velocity (v): " + std::string(FinalVelocity.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Vertical Acceleration (a): " + std::string(Acceleration.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Time in motion (t): " + std::string(Time.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << std::endl << std::endl;
                    filehandler << "Horizontal Displacement (s): " + std::string(HDisplacement.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Horizontal Velocity (v): " + std::string(HVelocity.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << std::endl << std::endl;
                    filehandler << "Is Trace motion Enabled?: " + std::to_string(TraceMotion.isCheckMarkTrue());
                    filehandler << std::endl << std::endl;
                    filehandler << "Is Velocity Vectors Enabled?: " + std::to_string(VelocityVector.isCheckMarkTrue());
                    filehandler << std::endl << std::endl;
                    filehandler << "Is Acceleration Vectors Enabled?: " + std::to_string(AccelerationVector.isCheckMarkTrue());
                    filehandler << std::endl << std::endl;
                    filehandler << "Is Force Vectors Enabled?: " + std::to_string(ForceVector.isCheckMarkTrue());


                }
                filehandler.close();
                eqranonce = true;
                successsave.setString("The file\n'" + DownloadInput.InputText + "'\nhas been saved");
            }
            if (eqranonce != true && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !DownloadInput.InputText.isEmpty()) {
                showrunerror = true;
                timer2 = 100;
                ShowDownloadUI = -1;
            }
        }
        else {
            SaveButton.setColor(sf::Color::White);
        }

        if (isSpriteHover(ImportButton.getGlobalBounds(), worldPos)&&run==false) {
            ImportButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowImportUI = ShowImportUI * -1;
                if (ShowImportUI == 1) {
                    ShowDownloadUI = -1;
                }
            }
        }
        else {
            ImportButton.setColor(sf::Color::White);
        }

        if (isSpriteHover(CloseButton.getGlobalBounds(), worldPos) && ShowDownloadUI == 1&&run==false) {
            CloseButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowDownloadUI = -1;
            }
        }
        else {
            CloseButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(ImportCloseButton.getGlobalBounds(), worldPos) && ShowImportUI == 1&&run==false) {
            ImportCloseButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowImportUI = -1;
            }
        }
        else {
            ImportCloseButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(Confirm.getGlobalBounds(), worldPos) && ShowImportUI == 1&&run==false) {
            Confirm.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !ImportInput.InputText.isEmpty()) {
                filehandler.open(std::string(ImportInput.InputText) + ".txt", std::ios::in);
                if (!filehandler) {
                    std::cout << "Doesnt exit";
                    timer4 = 100;
                    showimporterror = true;
                }
                else {
                    timer5 = 100;
                    showsuccess = true;
                    ProjectileMotionRanOnce = false;
                    std::cout << "all working";
                    filenameholder = ImportInput.InputText;
                    SuccessImport.setString("The file\n'" + filenameholder + ".txt'" + "\nhas been succesfully imported");
                }
                filehandler.close();
                ShowImportUI = -1;
            }
        }
        else {
            Confirm.setColor(sf::Color::White);
        }
        if (isSpriteHover(Advanced.getGlobalBounds(), worldPos)&&run==false) {
            Advanced.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                showadvancedmenu = showadvancedmenu * -1;
            }
        }

        else {
            Advanced.setColor(sf::Color::White);
        }


        if (isSpriteHover(Help.getGlobalBounds(), worldPos)&&run==false) {
            Help.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && eqranonce == true) {
                showhelp = showhelp * -1;
            }
        }

        else {
            Help.setColor(sf::Color::White);
        }


        if (isSpriteHover(ResetButton.getGlobalBounds(), worldPos)&&run==false) {
            ResetButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ProjectileMotionRanOnce = false;
            }
        }

        else {
            ResetButton.setColor(sf::Color::White);
        }


        if (isSpriteHover(DownloadButton.getGlobalBounds(), worldPos)&&run==false) {
            DownloadButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowDownloadUI = ShowDownloadUI * -1;
                if (ShowDownloadUI == 1) {
                    ShowImportUI = -1;
                }
            }
        }

        else {
            DownloadButton.setColor(sf::Color::White);
        }

        if (run == false) {
            Displacement.ButtonEventLogic(event, isSpriteHover(Displacement.ButtonsRectangle.getGlobalBounds(), worldPos));
            InitialVelocity.ButtonEventLogic(event, isSpriteHover(InitialVelocity.ButtonsRectangle.getGlobalBounds(), worldPos));
            FinalVelocity.ButtonEventLogic(event, isSpriteHover(FinalVelocity.ButtonsRectangle.getGlobalBounds(), worldPos));
            Acceleration.ButtonEventLogic(event, isSpriteHover(Acceleration.ButtonsRectangle.getGlobalBounds(), worldPos));
            Time.ButtonEventLogic(event, isSpriteHover(Time.ButtonsRectangle.getGlobalBounds(), worldPos));
        }

        HDisplacement.ButtonEventLogic(event, isSpriteHover(HDisplacement.ButtonsRectangle.getGlobalBounds(), worldPos));
        HVelocity.ButtonEventLogic(event, isSpriteHover(HVelocity.ButtonsRectangle.getGlobalBounds(), worldPos));
        if (showadvancedmenu == 1) {
            TraceMotion.CheckBoxEventLogic(event, isSpriteHover(TraceMotion.ReturnBackBox().getGlobalBounds(), worldPos));
            VelocityVector.CheckBoxEventLogic(event, isSpriteHover(VelocityVector.ReturnBackBox().getGlobalBounds(), worldPos));
            AccelerationVector.CheckBoxEventLogic(event, isSpriteHover(AccelerationVector.ReturnBackBox().getGlobalBounds(), worldPos));
            ForceVector.CheckBoxEventLogic(event, isSpriteHover(ForceVector.ReturnBackBox().getGlobalBounds(), worldPos));
        }
        if (ShowDownloadUI == 1) {
            DownloadInput.ButtonEventLogic(event, isSpriteHover(DownloadInput.ButtonsRectangle.getGlobalBounds(), worldPos));
        }
        if (ShowImportUI == 1) {
            ImportInput.ButtonEventLogic(event, isSpriteHover(ImportInput.ButtonsRectangle.getGlobalBounds(), worldPos));
        }
        if (ShowDownloadUI == -1) {
            DownloadInput.TextReset();
        }
        if (ShowImportUI == -1) {
            ImportInput.TextReset();
        }

    }

    if (!Displacement.InputText.isEmpty()&&Displacement.FinishedClicking==false&&Displacement.Check(window) && run == false && std::stof(std::string(Displacement.InputText)) >= 0) {
        verticalDisplacement = originalPosition.y - (std::stof(std::string(Displacement.InputText)) * 4.8);
        ObjectInMotion.setPosition(sf::Vector2f(originalPosition.x, originalPosition.y));

    }
    else if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false &&Displacement.Check(window) && run == false && std::stof(std::string(Displacement.InputText)) < 0)
    {
        ObjectInMotion.setPosition(sf::Vector2f(originalPosition.x,originalPosition.y+(std::stof(std::string(Displacement.InputText))*4.8)));
        verticalDisplacement = originalPosition.y;
    }


    if (!HDisplacement.InputText.isEmpty()&&HDisplacement.FinishedClicking == false &&run == false&&HDisplacement.Check(window)) {
        horizontalDisplacement = originalPosition.x + (std::stof(std::string(HDisplacement.InputText)) * 4.8);
    }

    if (!InitialVelocity.InputText.isEmpty() && InitialVelocity.FinishedClicking == false && run == false && InitialVelocity.Check(window)) {
        verticalInitialVelocity = std::stof(std::string(InitialVelocity.InputText)) * 4.8;
    }
    if (!HVelocity.InputText.isEmpty() && HVelocity.FinishedClicking == false && run == false && HVelocity.Check(window)) {
        horizontalVelocity = std::stof(std::string(HVelocity.InputText)) * 4.8;
    }


    if (!Acceleration.InputText.isEmpty() && Acceleration.FinishedClicking == false && run == false&&Acceleration.Check(window)) {
        verticalAcceleration = std::stof(std::string(Acceleration.InputText)) * 4.8;
    }
    
    if ((ObjectInMotion.getPosition().x >= horizontalDisplacement && ObjectInMotion.getPosition().y <= verticalDisplacement)&& verticalDisplacement<originalPosition.y) {
        horizontalVelocity = 0;
        verticalAcceleration = 0;
        verticalInitialVelocity = 0;
        setValues1 = true;
        setValues2 = true;
    }
    else if (ObjectInMotion.getPosition().y>= verticalDisplacement && ObjectInMotion.getPosition().x >= horizontalDisplacement && verticalDisplacement>=originalPosition.y) {
        horizontalVelocity = 0;
        verticalAcceleration = 0;
        verticalInitialVelocity = 0;
        setValues1 = true;
        setValues2 = true;
    }


    if (run == true) {
        
        sf::Vector2f previousPos = ObjectInMotion.getPosition();

        ObjectInMotion.setPosition(sf::Vector2f(ObjectInMotion.getPosition().x + horizontalVelocity/60, ObjectInMotion.getPosition().y - verticalInitialVelocity/60));
        verticalInitialVelocity = verticalInitialVelocity+ verticalAcceleration/60;

        sf::Vertex newSegment[2];
        newSegment[0].position = previousPos;
        newSegment[1].position = ObjectInMotion.getPosition();
        newSegment[0].color = sf::Color::Black;
        newSegment[1].color = sf::Color::Black;
        lineSegments.push_back(newSegment[0]);
        lineSegments.push_back(newSegment[1]);
    }


    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    worldPos = window.mapPixelToCoords(pixelPos);
    if (run == false) {
        Displacement.ButtonDisplayLogic();
        InitialVelocity.ButtonDisplayLogic();
        FinalVelocity.ButtonDisplayLogic();
        Acceleration.ButtonDisplayLogic();
        Time.ButtonDisplayLogic();
    }
    if (ShowImportUI == 1) {
        ImportInput.ButtonDisplayLogic();
    }
    if (ShowDownloadUI == 1) {
        DownloadInput.ButtonDisplayLogic();
    }

    if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false && std::stof(std::string(HDisplacement.InputText)) < 0) {
        HDisplacement.InputText = std::to_string(std::stof(std::string(HDisplacement.InputText)) * -1);
    }
    if (!HVelocity.InputText.isEmpty() && HVelocity.FinishedClicking == false && std::stof(std::string(HVelocity.InputText)) < 0) {
        HVelocity.InputText = std::to_string(std::stof(std::string(HVelocity.InputText)) * -1);
    }

    if (run == false) {
        HDisplacement.ButtonDisplayLogic();
        HVelocity.ButtonDisplayLogic();
    }

    if (run==false&&(isSpriteHover(Displacement.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(InitialVelocity.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(FinalVelocity.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(Acceleration.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(Time.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(HDisplacement.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(HVelocity.ButtonsRectangle.getGlobalBounds(), worldPos) || (isSpriteHover(DownloadInput.ButtonsRectangle.getGlobalBounds(), worldPos) && ShowDownloadUI == 1) || (isSpriteHover(ImportInput.ButtonsRectangle.getGlobalBounds(), worldPos) && ShowImportUI == 1))) {
        cursor.loadFromSystem(sf::Cursor::Text);
    }
    else if (run==false&&(isSpriteHover(BackButton.getGlobalBounds(), worldPos) || isSpriteHover(Help.getGlobalBounds(), worldPos) || isSpriteHover(ResetButton.getGlobalBounds(), worldPos) || isSpriteHover(DownloadButton.getGlobalBounds(), worldPos) || isSpriteHover(RunButton.getGlobalBounds(), worldPos) || isSpriteHover(Advanced.getGlobalBounds(), worldPos) || isSpriteHover(ImportButton.getGlobalBounds(), worldPos) || ((isSpriteHover(AdvancedClose.getGlobalBounds(), worldPos) || isSpriteHover(TraceMotion.ReturnBackBox().getGlobalBounds(), worldPos) || isSpriteHover(VelocityVector.ReturnBackBox().getGlobalBounds(), worldPos) || isSpriteHover(AccelerationVector.ReturnBackBox().getGlobalBounds(), worldPos) || isSpriteHover(ForceVector.ReturnBackBox().getGlobalBounds(), worldPos)) && showadvancedmenu == 1) || (isSpriteHover(CloseButton.getGlobalBounds(), worldPos) && ShowDownloadUI == 1) || (isSpriteHover(SaveButton.getGlobalBounds(), worldPos) && ShowDownloadUI == 1) || (isSpriteHover(ImportCloseButton.getGlobalBounds(), worldPos) && ShowImportUI == 1) || (isSpriteHover(Confirm.getGlobalBounds(), worldPos) && ShowImportUI == 1) || (isSpriteHover(CloseButtonHelp.getGlobalBounds(), worldPos) && showhelp == 1))) {
        cursor.loadFromSystem(sf::Cursor::Hand);
    }
    else if (run == true && (isSpriteHover(ResetSim.getGlobalBounds(), worldPos))) {
        cursor.loadFromSystem(sf::Cursor::Hand);
    }

    else {
        cursor.loadFromSystem(sf::Cursor::Arrow);
    }


    if (timer > 0) {
        timer -= 1;
    }
    else {
        showsaved = false;
    }
    if (timer2 > 0) {
        timer2 -= 1;
    }
    else {
        showrunerror = false;
    }
    if (timer4 > 0) {
        timer4 -= 1;
    }
    else {
        showimporterror = false;
    }
    if (timer5 > 0) {
        timer5 -= 1;
    }
    else {
        showsuccess = false;
    }
    if (timer5 == 20) {
        Displacement.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 1)));
        InitialVelocity.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 3)));
        FinalVelocity.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 5)));
        Acceleration.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 7)));
        Time.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 9)));
        HDisplacement.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 13)));
        HVelocity.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 15)));
        TraceMotion.SetCheckBox(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 19)));
        VelocityVector.SetCheckBox(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 21)));
        AccelerationVector.SetCheckBox(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 23)));
        ForceVector.SetCheckBox(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 25)));

    }






    window.clear(sf::Color(0, 255, 0));
    window.draw(Background);
    if (run == false) {
        if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && (std::stof(std::string(Displacement.InputText)) > 0) && !HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false) {
            window.draw(VerticalArrowBox);
            window.draw(VerticalLeftArrow);
            window.draw(VerticalRightArrow);
        }
        else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && (std::stof(std::string(Displacement.InputText)) < 0)) {
            window.draw(VerticalArrowBox);
            window.draw(VerticalLeftArrow);
            window.draw(VerticalRightArrow);
            window.draw(VerticalDisplayText);
        }
        if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && (std::stof(std::string(Displacement.InputText)) > 0) && !HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false) {
            window.draw(VerticalDisplayText);
        }
        window.draw(BackBorderforborder);
        window.draw(BackBorder);
        if (showadvancedmenu == 1) {
            window.draw(backforadvancedback);
            window.draw(advancedBack);
            window.draw(AdvancedClose);
            TraceMotion.CheckBoxDraw(window);
            VelocityVector.CheckBoxDraw(window);
            AccelerationVector.CheckBoxDraw(window);
            ForceVector.CheckBoxDraw(window);

        }
        Displacement.DrawButton(window);
        InitialVelocity.DrawButton(window);
        FinalVelocity.DrawButton(window);
        Acceleration.DrawButton(window);
        Time.DrawButton(window);



        HDisplacement.DrawButton(window);
        HVelocity.DrawButton(window);

        window.draw(BackButton);

        window.draw(Verticaltxt);
        window.draw(Horizontaltxt);

        window.draw(RunButton);
        window.draw(ImportButton);
        window.draw(Advanced);

        window.draw(ResetButton);
        window.draw(Help);
        window.draw(DownloadButton);
        window.draw(showDirection);


        if (ShowDownloadUI == 1) {
            window.draw(BackBorderDownload);
            window.draw(BackBoxDownload);
            DownloadInput.DrawButton(window);
            DownloadInput.Check(window);
            window.draw(CloseButton);
            window.draw(SaveButton);
        }
        if (ShowImportUI == 1) {
            window.draw(BackBorderImport);
            window.draw(BackBoxImport);
            ImportInput.DrawButton(window);
            ImportInput.Check(window);
            window.draw(ImportCloseButton);
            window.draw(Confirm);
        }
        if (showhelp == 1) {
            window.draw(HelpBorder);
            window.draw(HelpBack);
            window.draw(CloseButtonHelp);
            window.draw(FullScreenOnly);
            if (eqranonce == true) {
                window.draw(eqtext);
                window.draw(rearrange2);
                window.draw(rearrange1);
                window.draw(eq2);
                window.draw(eq1);

            }
        }

        Displacement.Check(window);
        InitialVelocity.Check(window);
        FinalVelocity.Check(window);
        Acceleration.Check(window);
        Time.Check(window);
        HDisplacement.Check(window);
        HVelocity.Check(window);



        if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false && (std::stof(std::string(HDisplacement.InputText)) > 0)) {
            window.draw(HorizontalArrowBox);
            window.draw(HorizontalLeftArrow);
            window.draw(HorizontalRightArrow);
        }
        if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false &&  (std::stof(std::string(HDisplacement.InputText)) > 0)) {
            window.draw(HorizontalDisplayText);
        }

        if (showsaved == true) {
            window.draw(successsave);
        }
        if (showrunerror == true) {
            window.draw(NotRunError);
        }
        if (showmasserror == true) {
            window.draw(MassError);
        }
        if (showimporterror == true) {
            window.draw(TxtNotFound);
        }
        if (showsuccess == true) {
            window.draw(SuccessImport);
        }
        window.draw(MassofObject);
    }

    if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false && std::stof(std::string(HDisplacement.InputText)) >= 190) {
        HDisplacement.InputText = "190";
    }
    if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false && std::stof(std::string(Displacement.InputText)) >= 100) {
        Displacement.InputText = "100";


    }
    else if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false && std::stof(std::string(Displacement.InputText)) <= -45) {
        Displacement.InputText = "-45";


    }


    if (QuestionType() == 1 && eqranonce == false) {
        if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Time.InputText.isEmpty()) {
            Time.InputText = std::to_string(std::stof(std::string(Displacement.InputText)) / ((std::stof(std::string(FinalVelocity.InputText)) + std::stof(std::string(InitialVelocity.InputText))) / 2));
            Acceleration.InputText = std::to_string((std::stof(std::string(FinalVelocity.InputText)) - std::stof(std::string(InitialVelocity.InputText))) / std::stof(std::string(Time.InputText)));

            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2t.png", eq1texture, sf::Vector2f(490, 200), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(550, 295), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearranget.png", rearrange1texture, sf::Vector2f(360, 235), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(365, 325), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            textmaker(eqtext, font, "To find time, rearrange this\n\ninto this\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);


        }
        else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && FinalVelocity.InputText.isEmpty()) {
            FinalVelocity.InputText = std::to_string(std::sqrt((std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(InitialVelocity.InputText))) + (2 * (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Displacement.InputText))))));
            Time.InputText = std::to_string(std::stof(std::string(Displacement.InputText)) / ((std::stof(std::string(FinalVelocity.InputText)) + std::stof(std::string(InitialVelocity.InputText))) / 2));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2as.png", eq1texture, sf::Vector2f(540, 208), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(520, 275), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearranget.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
            textmaker(eqtext, font, "To find Final Velocity, use this this\n\n\n\nTo find time rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);

        }

        else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && Time.FinishedClicking == false && !Time.InputText.isEmpty() && FinalVelocity.InputText.isEmpty()) {
            Acceleration.InputText = std::to_string((2 * (std::stof(std::string(Displacement.InputText)) - (std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(Time.InputText))))) / (std::stof(std::string(Time.InputText)) * std::stof(std::string(Time.InputText))));
            FinalVelocity.InputText = std::to_string(std::stof(std::string(InitialVelocity.InputText)) + (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq1texture, sf::Vector2f(550, 200), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(510, 290), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc.png", rearrange1texture, sf::Vector2f(360, 235), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc.png", rearrange2texture, sf::Vector2f(550, 260), sf::Vector2f(0.7f, 0.7f), sf::Color(255, 255, 255, 0));
            textmaker(eqtext, font, "To find acceleration, rearrange this\n\ninto this\n\n\nTo find Final Velocity use this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Time.FinishedClicking == false && !Time.InputText.isEmpty() && InitialVelocity.InputText.isEmpty()) {
            InitialVelocity.InputText = std::to_string((2 * (std::stof(std::string(Displacement.InputText)) / std::stof(std::string(Time.InputText)))) - std::stof(std::string(FinalVelocity.InputText)));
            Acceleration.InputText = std::to_string((std::stof(std::string(FinalVelocity.InputText)) - std::stof(std::string(InitialVelocity.InputText))) / std::stof(std::string(Time.InputText)));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2t.png", eq1texture, sf::Vector2f(550, 200), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(550, 295), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinit.png", rearrange1texture, sf::Vector2f(360, 225), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(365, 325), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            textmaker(eqtext, font, "To find initial velocity, rearrange this\n\ninto this\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && !Acceleration.InputText.isEmpty() && Acceleration.FinishedClicking == false && InitialVelocity.InputText.isEmpty()) {
            InitialVelocity.InputText = std::to_string(std::sqrt((std::stof(std::string(FinalVelocity.InputText)) * std::stof(std::string(FinalVelocity.InputText))) - (2 * std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Displacement.InputText)))));
            Time.InputText = std::to_string(std::stof(std::string(Displacement.InputText)) / ((std::stof(std::string(FinalVelocity.InputText)) + std::stof(std::string(InitialVelocity.InputText))) / 2));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2as.png", eq1texture, sf::Vector2f(555, 205), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2t.png", eq2texture, sf::Vector2f(550, 275), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitsqr.png", rearrange1texture, sf::Vector2f(360, 225), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearranget.png", rearrange2texture, sf::Vector2f(365, 325), sf::Vector2f(0.5f, 0.5f), sf::Color::White);
            textmaker(eqtext, font, "To find initial velocity, rearrange this\n\ninto this\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && Time.FinishedClicking == false && !Time.InputText.isEmpty() && FinalVelocity.InputText.isEmpty()) {
            FinalVelocity.InputText = std::to_string((std::stof(std::string(Displacement.InputText)) + (0.5 * std::stof(std::string(Acceleration.InputText)) * (std::stof(std::string(Time.InputText)) * std::stof(std::string(std::string(Time.InputText)))))) / std::stof(std::string(Time.InputText)));
            InitialVelocity.InputText = std::to_string(std::stof(std::string(FinalVelocity.InputText)) - (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vtsqr.png", eq1texture, sf::Vector2f(555, 195), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(560, 290), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangewv.png", rearrange1texture, sf::Vector2f(365, 230), sf::Vector2f(0.4f, 0.4f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitn.png", rearrange2texture, sf::Vector2f(375, 330), sf::Vector2f(0.5f, 0.5f), sf::Color::White);
            textmaker(eqtext, font, "To find final velocity, rearrange this\n\ninto this\n\n\nTo find initial velocity rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        else if (InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && Time.FinishedClicking == false && Displacement.InputText.isEmpty()) {
            Displacement.InputText = std::to_string(((std::stof(std::string(FinalVelocity.InputText)) * std::stof(std::string(FinalVelocity.InputText))) - (std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(InitialVelocity.InputText)))) / (2 * std::stof(std::string(Acceleration.InputText))));
            Time.InputText = std::to_string(std::stof(std::string(Displacement.InputText)) / ((std::stof(std::string(FinalVelocity.InputText)) + std::stof(std::string(InitialVelocity.InputText))) / 2));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2as.png", eq1texture, sf::Vector2f(560, 205), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2t.png", eq2texture, sf::Vector2f(505, 285), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangessqr.png", rearrange1texture, sf::Vector2f(355, 225), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearranget.png", rearrange2texture, sf::Vector2f(365, 330), sf::Vector2f(0.5f, 0.5f), sf::Color::White);
            textmaker(eqtext, font, "To find displacement, rearrange this\n\ninto this\n\n\nTo find time rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        else if (InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Time.FinishedClicking == false && !Time.InputText.isEmpty() && Acceleration.InputText.isEmpty()) {
            Displacement.InputText = std::to_string(((std::stof(std::string(InitialVelocity.InputText)) + std::stof(std::string(FinalVelocity.InputText))) / 2) * std::stof(std::string(Time.InputText)));
            Acceleration.InputText = std::to_string((std::stof(std::string(FinalVelocity.InputText)) - std::stof(std::string(InitialVelocity.InputText))) / std::stof(std::string(Time.InputText)));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq1texture, sf::Vector2f(540, 198), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(540, 275), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
            textmaker(eqtext, font, "To find Displacement, use this this\n\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);

        }
        else if (FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && Time.FinishedClicking == false && !Time.InputText.isEmpty() && Displacement.InputText.isEmpty()) {
            InitialVelocity.InputText = std::to_string(std::stof(std::string(FinalVelocity.InputText)) - (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
            Displacement.InputText = std::to_string((std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(Time.InputText))) + (0.5 * std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText)) * std::stof(std::string(Time.InputText))));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq1texture, sf::Vector2f(540, 198), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(540, 275), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitn.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
            textmaker(eqtext, font, "To find Displacement, use this this\n\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        else if (InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && Time.FinishedClicking == false && !Time.InputText.isEmpty() && FinalVelocity.InputText.isEmpty()) {
            FinalVelocity.InputText = std::to_string(std::stof(std::string(InitialVelocity.InputText)) + (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
            Displacement.InputText = std::to_string((std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(Time.InputText))) + (0.5 * std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText)) * std::stof(std::string(Time.InputText))));
            buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq1texture, sf::Vector2f(540, 198), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq2texture, sf::Vector2f(540, 275), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
            buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitn.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
            buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
            textmaker(eqtext, font, "To find Final Velocity, use this this\n\n\n\nTo find Displacement use this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
        }
        if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false) {
            HVelocity.InputText = std::to_string(std::stof(std::string(HDisplacement.InputText)) / std::stof(std::string(Time.InputText)));
        }
        else if (!HVelocity.InputText.isEmpty() && HVelocity.FinishedClicking == false) {
            HDisplacement.InputText = std::to_string(std::stof(std::string(HVelocity.InputText)) * std::stof(std::string(Time.InputText)));
        }
        if (!HVelocity.InputText.isEmpty() && HVelocity.FinishedClicking == false && !HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false) {
            eqranonce = true;
        }
    }


    else if (!HVelocity.InputText.isEmpty() && HVelocity.FinishedClicking == false && HDisplacement.FinishedClicking == false && !HDisplacement.InputText.isEmpty() && eqranonce == false) {
        Time.InputText = std::to_string(std::stof(std::string(HDisplacement.InputText)) / std::stof(std::string(HVelocity.InputText)));
        if (QuestionType() == 2) {
            if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && Acceleration.InputText.isEmpty()) {
                Acceleration.InputText = std::to_string((2 * (std::stof(std::string(Displacement.InputText)) - (std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(Time.InputText))))) / (std::stof(std::string(Time.InputText)) * std::stof(std::string(Time.InputText))));
                FinalVelocity.InputText = std::to_string(std::stof(std::string(InitialVelocity.InputText)) + (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
                buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq1texture, sf::Vector2f(550, 200), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(510, 290), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
                buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc.png", rearrange1texture, sf::Vector2f(360, 235), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
                buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc.png", rearrange2texture, sf::Vector2f(550, 260), sf::Vector2f(0.7f, 0.7f), sf::Color(255, 255, 255, 0));
                textmaker(eqtext, font, "To find acceleration, rearrange this\n\ninto this\n\n\nTo find Final Velocity use this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
            }

            else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && InitialVelocity.InputText.isEmpty()) {
                InitialVelocity.InputText = std::to_string((2 * (std::stof(std::string(Displacement.InputText)) / std::stof(std::string(Time.InputText)))) - std::stof(std::string(FinalVelocity.InputText)));
                Acceleration.InputText = std::to_string((std::stof(std::string(FinalVelocity.InputText)) - std::stof(std::string(InitialVelocity.InputText))) / std::stof(std::string(Time.InputText)));
                buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vu2t.png", eq1texture, sf::Vector2f(550, 200), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(550, 295), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
                buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinit.png", rearrange1texture, sf::Vector2f(360, 225), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
                buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(365, 325), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
                textmaker(eqtext, font, "To find initial velocity, rearrange this\n\ninto this\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
            }
            else if (Displacement.FinishedClicking == false && !Displacement.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && FinalVelocity.InputText.isEmpty()) {
                FinalVelocity.InputText = std::to_string((std::stof(std::string(Displacement.InputText)) + (0.5 * std::stof(std::string(Acceleration.InputText)) * (std::stof(std::string(Time.InputText)) * std::stof(std::string(std::string(Time.InputText)))))) / std::stof(std::string(Time.InputText)));
                InitialVelocity.InputText = std::to_string(std::stof(std::string(FinalVelocity.InputText)) - (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
                buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vtsqr.png", eq1texture, sf::Vector2f(555, 195), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(560, 290), sf::Vector2f(0.75f, 0.75f), sf::Color::White);
                buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangewv.png", rearrange1texture, sf::Vector2f(365, 230), sf::Vector2f(0.4f, 0.4f), sf::Color::White);
                buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitn.png", rearrange2texture, sf::Vector2f(375, 330), sf::Vector2f(0.5f, 0.5f), sf::Color::White);
                textmaker(eqtext, font, "To find final velocity, rearrange this\n\ninto this\n\n\nTo find initial velocity rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
            }
            else if (InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Displacement.InputText.isEmpty()) {
                Displacement.InputText = std::to_string(((std::stof(std::string(InitialVelocity.InputText)) + std::stof(std::string(FinalVelocity.InputText))) / 2) * std::stof(std::string(Time.InputText)));
                Acceleration.InputText = std::to_string((std::stof(std::string(FinalVelocity.InputText)) - std::stof(std::string(InitialVelocity.InputText))) / std::stof(std::string(Time.InputText)));
                buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq1texture, sf::Vector2f(540, 198), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(540, 275), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
                buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
                textmaker(eqtext, font, "To find Displacement, use this this\n\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
            }
            else if (InitialVelocity.FinishedClicking == false && !InitialVelocity.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && FinalVelocity.InputText.isEmpty()) {
                FinalVelocity.InputText = std::to_string(std::stof(std::string(InitialVelocity.InputText)) + (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
                Displacement.InputText = std::to_string((std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(Time.InputText))) + (0.5 * std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText)) * std::stof(std::string(Time.InputText))));
                buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq1texture, sf::Vector2f(540, 198), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq2texture, sf::Vector2f(540, 275), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitn.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
                buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
                textmaker(eqtext, font, "To find Final Velocity, use this this\n\n\n\nTo find Displacement use this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
            }
            else if (FinalVelocity.FinishedClicking == false && !FinalVelocity.InputText.isEmpty() && Acceleration.FinishedClicking == false && !Acceleration.InputText.isEmpty() && Displacement.InputText.isEmpty()) {
                InitialVelocity.InputText = std::to_string(std::stof(std::string(FinalVelocity.InputText)) - (std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText))));
                Displacement.InputText = std::to_string((std::stof(std::string(InitialVelocity.InputText)) * std::stof(std::string(Time.InputText))) + (0.5 * std::stof(std::string(Acceleration.InputText)) * std::stof(std::string(Time.InputText)) * std::stof(std::string(Time.InputText))));
                buttonmaker(eq1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\ut12at.png", eq1texture, sf::Vector2f(540, 198), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(eq2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\vuat.png", eq2texture, sf::Vector2f(540, 275), sf::Vector2f(0.6f, 0.6f), sf::Color::White);
                buttonmaker(rearrange1, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeinitn.png", rearrange1texture, sf::Vector2f(360, 310), sf::Vector2f(0.7f, 0.7f), sf::Color::White);
                buttonmaker(rearrange2, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Projectile motion\\rearrangeacc2.png", rearrange2texture, sf::Vector2f(340, 280), sf::Vector2f(0.7f, 0.7f), sf::Color(0, 0, 0, 0));
                textmaker(eqtext, font, "To find Displacement, use this this\n\n\n\nTo find acceleration rearrange this\n\ninto this", 14, sf::Vector2f(300, 210), sf::Color::Black, sf::Text::Regular);
            }


            eqranonce = true;
        }
    }

    if (eqranonce == true) {
        Displacement.FinishedClicking = false;
        InitialVelocity.FinishedClicking = false;
        FinalVelocity.FinishedClicking = false;
        Acceleration.FinishedClicking = false;
        Time.FinishedClicking = false;
        HDisplacement.FinishedClicking = false;
        HVelocity.FinishedClicking = false;


    }

    HorizontalRightArrow.setPosition(sf::Vector2f(HorizontalArrowBox.getGlobalBounds().left+HorizontalArrowBox.getLocalBounds().width-6, HorizontalArrowBox.getPosition().y - 15));
    HorizontalLeftArrow.setPosition(sf::Vector2f(HorizontalArrowBox.getGlobalBounds().left - 28.2f, HorizontalArrowBox.getPosition().y - 15));

    VerticalRightArrow.setPosition(sf::Vector2f(VerticalArrowBox.getGlobalBounds().getPosition().x-8, VerticalArrowBox.getGlobalBounds().top + 6));
    VerticalLeftArrow.setPosition(sf::Vector2f(VerticalArrowBox.getGlobalBounds().getPosition().x-8, VerticalArrowBox.getGlobalBounds().top - VerticalArrowBox.getSize().y+28));





    
        EndLocation.setPosition(sf::Vector2f(horizontalDisplacement, verticalDisplacement));
        //window.draw(EndLocation);

    


    if (!HDisplacement.InputText.isEmpty() && HDisplacement.FinishedClicking == false) {
        HorizontalArrowBox.setSize(sf::Vector2f(horizontalDisplacement-originalPosition.x-41, HorizontalArrowBox.getSize().y));
        HorizontalDisplayText.setString(HDisplacement.InputText + "m");
    }


    HorizontalDisplayText.setPosition(sf::Vector2f((HorizontalArrowBox.getSize().x / 2)+15, HorizontalArrowBox.getPosition().y - 28));



    if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false&&std::stof(std::string(Displacement.InputText))>=0) {
        VerticalArrowBox.setSize(sf::Vector2f(VerticalArrowBox.getSize().x,(-(540 - verticalDisplacement-40))));
        VerticalDisplayText.setString(Displacement.InputText + "m");
    }

    else if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false && std::stof(std::string(Displacement.InputText ))<=0) {
        VerticalArrowBox.setSize(sf::Vector2f(VerticalArrowBox.getSize().x, -(originalPosition.y-ObjectInMotion.getPosition().y-20)));
        VerticalDisplayText.setString(Displacement.InputText + "m");
    }




    if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false && (std::stof(std::string(Displacement.InputText)) >= 0)) {
        VerticalArrowBox.setPosition(horizontalDisplacement, VerticalArrowBox.getPosition().y);
    }
    else if (!Displacement.InputText.isEmpty() && Displacement.FinishedClicking == false && (std::stof(std::string(Displacement.InputText)) <0)) {
        VerticalArrowBox.setPosition(3.5f, VerticalArrowBox.getPosition().y);
    }

    VerticalDisplayText.setPosition(sf::Vector2f(VerticalArrowBox.getPosition().x+40, 540-(-VerticalArrowBox.getSize().y/2)-50));
   if (horizontalVelocity>0&&VelocityVector.isCheckMarkTrue() == true) {
        window.draw(HorizontalVelocityArrow);
        window.draw(VerticalVelocityArrow);
        window.draw(ResultantVelocityArrow);
        window.draw(horizTrig);
        window.draw(vertTrig);
        window.draw(resTrig);
   }
    window.draw(ObjectInMotion);
    if (run == true) {
        window.draw(ResetSim);
    }


    if (TraceMotion.isCheckMarkTrue()==true) {
        window.draw(lineSegments.data(), lineSegments.size(), sf::Lines);
    }
    if (!Acceleration.InputText.isEmpty()&&Acceleration.FinishedClicking==false && std::stof(std::string(Acceleration.InputText)) != 0&&AccelerationVector.isCheckMarkTrue()==true) {
        AccelerationText.setPosition(sf::Vector2f(AccelerationArrow.getPosition().x+30,AccelerationArrow.getPosition().y-30));
        AccelerationText.setString(Acceleration.InputText+" ms^-2");
        AccelerationArrow.setPosition(sf::Vector2f(ObjectInMotion.getPosition().x+90,ObjectInMotion.getPosition().y-60));
        if (verticalAcceleration > 0) {
            AccelerationArrow.setColor(sf::Color(34,139,34));
            AccelerationText.setFillColor(sf::Color(34, 139, 34));
            AccelerationArrow.setRotation(-180);
            
        }
        else if (verticalAcceleration < 0) {
            AccelerationArrow.setRotation(0);
            AccelerationArrow.setColor(sf::Color::Red);
            AccelerationText.setFillColor(sf::Color::Red);

        }
        if (run==true&&horizontalVelocity > 0) {
            window.draw(AccelerationArrow);
            window.draw(AccelerationText);
        }
    }
    if (!Acceleration.InputText.isEmpty() && Acceleration.FinishedClicking == false && std::stof(std::string(Acceleration.InputText)) != 0 && ForceVector.isCheckMarkTrue() == true) {
        ForceArrowText.setString(std::to_string(std::stof(std::string(Acceleration.InputText))*22.5f)+"N");
        ForceArrowText.setPosition(sf::Vector2f(ForceArrow.getPosition().x+30,ForceArrow.getPosition().y-35));
        ForceArrow.setPosition(sf::Vector2f(ObjectInMotion.getPosition().x+140,ObjectInMotion.getPosition().y-60));
        if (verticalAcceleration > 0) {
            ForceArrowText.setFillColor(sf::Color(34, 139, 34));
            ForceArrow.setRotation(0);

        }
        else if (verticalAcceleration < 0) {
            ForceArrow.setRotation(-180);
            ForceArrowText.setFillColor(sf::Color::Red);

        }
        if (run==true&&horizontalVelocity>0) {
            window.draw(ForceArrow);
            window.draw(ForceArrowText);
        }
    }
    HorizontalVelocityArrow.setFillColor(sf::Color::Red);
    VerticalVelocityArrow.setFillColor(sf::Color::Red);
    ResultantVelocityArrow.setFillColor(sf::Color(125,0,0));

        
    if (run == false) {
        verticalVelocitybefore = verticalInitialVelocity;
    }

        scaleVariable = 1 / (std::abs((verticalVelocitybefore/4.8)) + (horizontalVelocity / 4.8));

        VerticalVelocityArrow.setPosition(sf::Vector2f(ObjectInMotion.getPosition().x - 4, ObjectInMotion.getPosition().y));
        VerticalVelocityArrow.setSize(sf::Vector2f(8, -((verticalInitialVelocity/4.8)*scaleVariable) * 150));
    

        HorizontalVelocityArrow.setPosition(sf::Vector2f(ObjectInMotion.getPosition().x-4, ObjectInMotion.getPosition().y - 4));
        HorizontalVelocityArrow.setSize(sf::Vector2f(((horizontalVelocity/4.8)*scaleVariable) * 150, 8));
    
    



    ResultantVelocityArrow.setPosition(sf::Vector2f(ObjectInMotion.getPosition().x-4, ObjectInMotion.getPosition().y));
    ResultantVelocityArrow.setSize(sf::Vector2f(sqrt(((VerticalVelocityArrow.getSize().y)* (VerticalVelocityArrow.getSize().y))+(HorizontalVelocityArrow.getSize().x*HorizontalVelocityArrow.getSize().x )), 8));
    ResultantVelocityArrow.setRotation(-atan(-1*VerticalVelocityArrow.getSize().y/HorizontalVelocityArrow.getSize().x)*(180/(acos(-1))));
    
    if (checkSign(VerticalVelocityArrow.getSize().y)==-1) {
        vertTrig.setRotation(0);
    }
    else if(checkSign(VerticalVelocityArrow.getSize().y)==1) {
        vertTrig.setRotation(180);
    }

    horizTrig.setRotation(90);
    horizTrig.setPosition(HorizontalVelocityArrow.getPosition().x+HorizontalVelocityArrow.getSize().x,HorizontalVelocityArrow.getPosition().y+4);
    vertTrig.setPosition(VerticalVelocityArrow.getPosition().x,VerticalVelocityArrow.getPosition().y+VerticalVelocityArrow.getSize().y);
    resTrig.setRotation(ResultantVelocityArrow.getRotation()+90);
    resTrig.setPosition(HorizontalVelocityArrow.getLocalBounds().getSize().x + ResultantVelocityArrow.getPosition().x, ResultantVelocityArrow.getPosition().y + (VerticalVelocityArrow.getSize().y));

    std::cout << ResultantVelocityArrow.getPosition().y << std::endl;

    window.display();
    return false;
}




bool States::collisionstate() {
    if (CollisionRanOnce == false) {

        //Resets all condition based variables
        mousepressslider = false;
        run = false;
        singlecollision = true;
        showsaved = false;

        velocity1 = 0;
        velocity2 = 0;

        ShowDownloadUI = -1;
        ShowImportUI = -1;

        

        //Velocity1 txt
        textmaker(Velocity1Out, font, "Red Objects Velocity: ", 30, sf::Vector2f(50, 450), sf::Color::Black, sf::Text::Bold);



        //Velocity2 txt
        textmaker(Velocity2Out, font, "Blue Objects Velocity: ", 30, sf::Vector2f(50, 500), sf::Color::Black, sf::Text::Bold);


        //Direction arrows txt
        textmaker(Direction, font, "-> Right direction represents positive numbers\n<- Left direction represents negative numbers", 15, sf::Vector2f(110, 0), sf::Color::Black, sf::Text::Regular);

        //elasticity
        textmaker(elasticitytxt, font, "Elasticity", 32, sf::Vector2f(822.5f, 280), sf::Color::Black, sf::Text::Regular);
        textmaker(elasticitydisplay, font, "Elasticity: ", 12, sf::Vector2f(815, 350), sf::Color::Black, sf::Text::Regular);


        //outputs an error if the program hasnt been run first
        textmaker(NotRunError, font, "You need to run\n the program first\n before saving a text file",50,sf::Vector2f(180,150),sf::Color::Red,sf::Text::Bold);
        NotRunError.setOutlineColor(sf::Color::Black);
        NotRunError.setOutlineThickness(3);

        //outputs an error if a text file isnt found
        textmaker(TxtNotFound, font, "Text File not found\n (Do not include .txt)", 50, sf::Vector2f(200, 200), sf::Color::Red, sf::Text::Bold);
        TxtNotFound.setOutlineColor(sf::Color::Black);
        TxtNotFound.setOutlineThickness(3);

        //outputs a success message if the file is found
        textmaker(SuccessImport, font, "The file\n'"+filenameholder + ".txt'" + "\nhas been succesfully imported", 50, sf::Vector2f(200, 200), sf::Color::Green, sf::Text::Bold);
        SuccessImport.setOutlineColor(sf::Color::Black);
        SuccessImport.setOutlineThickness(3);

        //outputs an error if a negative mass or 0 has been input
        textmaker(MassError, font, "Please enter a mass\n greater than 0", 50, sf::Vector2f(180, 150), sf::Color::Red, sf::Text::Bold);
        MassError.setOutlineColor(sf::Color::Black);
        MassError.setOutlineThickness(3);

        //reset button
        buttonmaker(ResetButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\resetbutton.png", ResetButtonTexture, sf::Vector2f(950, 345), sf::Vector2f(0.045f, 0.045f), sf::Color::White);

        //Run Button
        buttonmaker(RunButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Run Button.png", RunButtonTexture, sf::Vector2f(805, 410), sf::Vector2f(0.085f, 0.085f), sf::Color::White);

        //Import Button
        buttonmaker(ImportButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Import Button.png", ImportButtonTexture, sf::Vector2f(900, 410), sf::Vector2f(0.085f, 0.085f), sf::Color::White);
        
        //Close Button Import
        buttonmaker(ImportCloseButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Close Button.png", ImportCloseButtonTexture,sf::Vector2f(650, 216),sf::Vector2f(0.044f,0.044f),sf::Color::White);

        //Download Button
        buttonmaker(DownloadButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\DownloadButton.png", DownloadButtonTexture, sf::Vector2f(920, 345), sf::Vector2f(0.044f, 0.044f), sf::Color::White);
        
        //Close Button Download
        buttonmaker(CloseButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Close Button.png", CloseButtonTexture, sf::Vector2f(650, 216), sf::Vector2f(0.044f, 0.044f), sf::Color::White);

        //Save Button
        buttonmaker(SaveButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Save Button.png",SaveButtonTexture,sf::Vector2f(465,289),sf::Vector2f(0.075f,0.075f),sf::Color::White);

        //BackBorder Shape
        sliderbackborder.setSize(sf::Vector2f(160, 15));
        sliderbackborder.setPosition(sf::Vector2f(815, 325));
        sliderbackborder.setFillColor(sf::Color(90, 90, 90));

        //Sliderbox
        sliderbox.setSize(sf::Vector2f(12.5f, 12.5f));
        sliderbox.setPosition(sf::Vector2f(822.5f, 332.5f));
        sliderbox.setFillColor(sf::Color::White);
        sliderbox.setOrigin(sf::Vector2f(sliderbox.getGlobalBounds().getSize().x / 2, sliderbox.getGlobalBounds().getSize().y / 2));

        //Back Button
        buttonmaker(BackButton, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Back Button.png", BackButtonTexture, sf::Vector2f(0, 0), sf::Vector2f(0.1f, 0.1f), sf::Color::White);

        //BackBorder for buttons
        BackBorder.setSize(sf::Vector2f(200, 450));
        BackBorder.setFillColor(sf::Color(128, 128, 128));
        BackBorder.setPosition(sf::Vector2f(800, 0));

        //confirm button for importing
        buttonmaker(Confirm, "C:\\Users\\Ahmed\\Documents\\Kinemechanics assets\\Collisions\\Confirm Button.png", ConfirmTexture, sf::Vector2f(465, 289), sf::Vector2f(0.075f, 0.075f), sf::Color::White);
        
        //BackBorder for the textfile downloader
        BackBoxDownload.setSize(sf::Vector2f(350, 100));
        BackBoxDownload.setFillColor(sf::Color(128, 128, 128));
        BackBoxDownload.setOrigin(sf::Vector2f(BackBoxDownload.getSize().x/2,BackBoxDownload.getSize().y/2));
        BackBoxDownload.setPosition(sf::Vector2f(1980/4, 1080/4));

        BackBorderDownload.setSize(sf::Vector2f(350 * 1.025, 100 * 1.1));
        BackBorderDownload.setFillColor(sf::Color(54, 69, 79));
        BackBorderDownload.setOrigin(sf::Vector2f(BackBorderDownload.getSize().x / 2, BackBorderDownload.getSize().y / 2));
        BackBorderDownload.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        //BackBorder for the textfile importer
        BackBoxImport.setSize(sf::Vector2f(350, 100));
        BackBoxImport.setFillColor(sf::Color(128, 128, 128));
        BackBoxImport.setOrigin(sf::Vector2f(BackBoxImport.getSize().x / 2, BackBoxDownload.getSize().y / 2));
        BackBoxImport.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        BackBorderImport.setSize(sf::Vector2f(350 * 1.025, 100 * 1.1));
        BackBorderImport.setFillColor(sf::Color(54, 69, 79));
        BackBorderImport.setOrigin(sf::Vector2f(BackBorderImport.getSize().x / 2, BackBorderDownload.getSize().y / 2));
        BackBorderImport.setPosition(sf::Vector2f(1980 / 4, 1080 / 4));

        bcircle.setRadius(50); //max 210
        bcircle.setFillColor(sf::Color::Blue);
        bcircle.setOrigin(sf::Vector2f((bcircle.getGlobalBounds().getSize().x / 2), (bcircle.getGlobalBounds().getSize().y / 2)));
        bcircle.setPosition(sf::Vector2f(980 * 0.6, 480 * 0.5));

        rcircle.setRadius(50);
        rcircle.setOrigin(sf::Vector2f((rcircle.getGlobalBounds().getSize().x / 2), (rcircle.getGlobalBounds().getSize().y / 2)));
        rcircle.setPosition(sf::Vector2f(980 * 0.2, 480 * 0.5));
        rcircle.setFillColor(sf::Color(225, 36, 0));

        //cursor reset
        cursor.loadFromSystem(sf::Cursor::Arrow);

        //Text initialize
        Mass1.TextReset();
        Mass2.TextReset();
        Velocity1.TextReset();
        Velocity2.TextReset();
        DownloadInput.TextReset();
        ImportInput.TextReset();

        Mass1.ButtonMaker("Mass of object A / kg", 825, 55, 140, 20, 14,true,20);
        Mass2.ButtonMaker("Mass of object B / kg", 825, 105, 140, 20, 14,true,20);

        Velocity1.ButtonMaker("Velocity of object A / m/s", 825, 185, 140, 20, 14,true,20);
        Velocity2.ButtonMaker("Velocity of object B / m/s", 825, 235, 140, 20, 14,true,20);

        DownloadInput.ButtonMaker("Please input a suitable name for the text file", (1980 / 4)-143, (1080 / 4)-4, 285, 20, 14, false,41);
        ImportInput.ButtonMaker("Please enter the name of the text file to import", (1980 / 4) - 150, (1080 / 4) - 4, 300, 20, 14, false, 41);


        
        CollisionRanOnce = true;
    }
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))window.close();



        if (isSpriteHover(BackButton.getGlobalBounds(), worldPos)) {
            BackButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                CurrentState = 1;
            MenuRanOnce = false;
        }

        else {
            BackButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(SaveButton.getGlobalBounds(), worldPos)) {
            SaveButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !DownloadInput.InputText.isEmpty() && run == true) {
                showsaved = true;
                timer = 100;
                ShowDownloadUI = -1;
                std::string tostrdi = (DownloadInput.InputText + ".txt");
                filehandler.open(tostrdi, std::ios::out);
                if (!filehandler) {
                    std::cout << "File not created!";
                }
                else {
                    std::cout << "File created successfully!";
                    filehandler << "Red Object / Object A's Mass: " + std::string(Mass1.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Blue Object / Object B's Mass: " + std::string(Mass2.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << std::endl << std::endl;
                    filehandler << "Red Object / Object A's Initial Velocity: " + std::string(Velocity1.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Red Object / Object A's Initial Momentum: " + std::to_string(std::stof(std::string(Velocity1.InputText)) * std::stof(std::string(Mass1.InputText)));
                    filehandler << std::endl << std::endl;
                    filehandler << std::endl << std::endl;
                    filehandler << "Blue Object / Object B's Initial Velocity: " + std::string(Velocity2.InputText);
                    filehandler << std::endl << std::endl;
                    filehandler << "Blue Object / Object B's Initial Momentum: " + std::to_string(std::stof(std::string(Velocity2.InputText)) * std::stof(std::string(Mass2.InputText)));
                    filehandler << std::endl << std::endl;
                    filehandler << std::endl << std::endl;
                    filehandler << std::string(elasticitydisplay.getString());
                    if ((std::stof(std::string(Velocity1.InputText)) <= 0 && std::stof(std::string(Velocity2.InputText)) >= 0) || ((std::stof(std::string(Velocity1.InputText)) >= 0 && std::stof(std::string(Velocity2.InputText)) >= 0) && (std::stof(std::string(Velocity2.InputText)) > std::stof(std::string(Velocity1.InputText)))) || ((std::stof(std::string(Velocity1.InputText)) <= 0 && std::stof(std::string(Velocity2.InputText)) <= 0) && (std::stof(std::string(Velocity1.InputText)) < std::stof(std::string(Velocity2.InputText)))) || (std::stof(std::string(Velocity1.InputText)) == std::stof(std::string(Velocity2.InputText)))) {
                        filehandler << std::endl << std::endl;
                        filehandler << "No collision occured";
                    }
                    else {
                        momentum1 = std::stof(std::string(Mass1.InputText)) * (std::stof(std::string(Velocity1.InputText)));
                        momentum2 = std::stof(std::string(Mass2.InputText)) * (std::stof(std::string(Velocity2.InputText)));

                        float velocity1after = ((momentum1 + momentum2) - ((std::stof(std::string(Velocity1.InputText)) - std::stof(std::string(Velocity2.InputText))) * (elasticity * std::stof(std::string(Mass2.InputText))))) / (std::stof(std::string(Mass1.InputText)) + std::stof(std::string(Mass2.InputText)));
                        float velocity2after = ((elasticity * (std::stof(std::string(Velocity1.InputText)) - std::stof(std::string(Velocity2.InputText)))) + velocity1after);

                        filehandler << std::endl << std::endl;
                        filehandler << std::endl << std::endl;
                        filehandler << "Red Object / Object A's Final Velocity: " + std::to_string(velocity1after);
                        filehandler << std::endl << std::endl;
                        filehandler << "Red Object / Object A's Final Momentum: " + std::to_string(velocity1after * std::stof(std::string(Mass1.InputText)));
                        filehandler << std::endl << std::endl;
                        filehandler << std::endl << std::endl;
                        filehandler << "Blue Object / Object B's Final Velocity: " + std::to_string(velocity2after);
                        filehandler << std::endl << std::endl;
                        filehandler << "Blue Object / Object B's Final Momentum: " + std::to_string(velocity2after * std::stof(std::string(Mass2.InputText)));
                    }
                    

                }
                filehandler.close();
                successsave.setString("The file\n'" + DownloadInput.InputText + "'\nhas been saved");
            }
            if (run != true && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !DownloadInput.InputText.isEmpty()) {
                showrunerror = true;
                timer2 = 100;
                ShowDownloadUI = -1;
            }
        }
        else {
            SaveButton.setColor(sf::Color::White);
        }



        if (isSpriteHover(RunButton.getGlobalBounds(), worldPos))
        {
            RunButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && Mass1.InputText != "" && Mass2.InputText != "" && Velocity1.InputText != "" && Velocity2.InputText != "") {
                run = true;
            }
        }
        else {
            RunButton.setColor(sf::Color::White);
        }

        if (isSpriteHover(CloseButton.getGlobalBounds(), worldPos) && ShowDownloadUI == 1) {
            CloseButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowDownloadUI = -1;
            }
        }
        else {
            CloseButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(ImportCloseButton.getGlobalBounds(), worldPos) && ShowImportUI == 1) {
            ImportCloseButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowImportUI = -1;
            }
        }
        else {
            ImportCloseButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(Confirm.getGlobalBounds(), worldPos) && ShowImportUI == 1) {
            Confirm.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left&&!ImportInput.InputText.isEmpty()) {
                filehandler.open(std::string(ImportInput.InputText)+".txt", std::ios::in);
                if (!filehandler) {
                    std::cout << "Doesnt exit";
                    timer4 = 100;
                    showimporterror = true;
                }
                else {
                    timer5 = 40;
                    showsuccess = true;
                    CollisionRanOnce = false;
                    std::cout << "all working";
                    filenameholder = ImportInput.InputText;
                    SuccessImport.setString("The file\n'" + filenameholder + ".txt'" + "\nhas been succesfully imported");
                }
                filehandler.close();
                ShowImportUI = -1;
            }
        }
        else {
            Confirm.setColor(sf::Color::White);
        }
        if (ShowDownloadUI == -1) {
            DownloadInput.TextReset();
        }
        if (ShowImportUI == -1) {
            ImportInput.TextReset();
        }
        if (isSpriteHover(ResetButton.getGlobalBounds(), worldPos))
        {
            ResetButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                CollisionRanOnce = false;
            }
        }
        else {
            ResetButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(DownloadButton.getGlobalBounds(), worldPos)) {
            DownloadButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowDownloadUI = ShowDownloadUI * -1;
                if (ShowDownloadUI == 1) {
                    ShowImportUI = -1;
                }
            }
        }
        else {
            DownloadButton.setColor(sf::Color::White);
        }
        if (isSpriteHover(ImportButton.getGlobalBounds(), worldPos))
        {
            ImportButton.setColor(sf::Color(192, 192, 192));
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                ShowImportUI = ShowImportUI * -1;
                if (ShowImportUI == 1) {
                    ShowDownloadUI = -1;
                }
            }
        }
        else {
            ImportButton.setColor(sf::Color::White);
        }

        if (isSpriteHover(sliderbox.getGlobalBounds(), worldPos) && event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mousepressslider = true;
        }
        else if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            mousepressslider = false;
        }
        if (mousepressslider == true) {
            sliderbox.setPosition(worldPos.x, 332.5f);
        }
        if (sliderbox.getGlobalBounds().getPosition().x < sliderbackborder.getGlobalBounds().left) {
            sliderbox.setPosition(822.5f, 332.5f);
        }
        else if (sliderbox.getGlobalBounds().getPosition().x > (sliderbackborder.getGlobalBounds().left + sliderbackborder.getGlobalBounds().width) - sliderbox.getGlobalBounds().width) {
            sliderbox.setPosition(sliderbackborder.getGlobalBounds().left + sliderbackborder.getGlobalBounds().width - sliderbox.getGlobalBounds().width / 2, 332.5f);
        }
            Mass1.ButtonEventLogic(event, isSpriteHover(Mass1.ButtonsRectangle.getGlobalBounds(), worldPos));
            Mass2.ButtonEventLogic(event, isSpriteHover(Mass2.ButtonsRectangle.getGlobalBounds(), worldPos));
            Velocity1.ButtonEventLogic(event, isSpriteHover(Velocity1.ButtonsRectangle.getGlobalBounds(), worldPos));
            Velocity2.ButtonEventLogic(event, isSpriteHover(Velocity2.ButtonsRectangle.getGlobalBounds(), worldPos));
        
        if (ShowDownloadUI == 1) {
            DownloadInput.ButtonEventLogic(event, isSpriteHover(DownloadInput.ButtonsRectangle.getGlobalBounds(), worldPos));
        }
        if (ShowImportUI == 1) {
            ImportInput.ButtonEventLogic(event, isSpriteHover(ImportInput.ButtonsRectangle.getGlobalBounds(), worldPos));
        }
    }
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        worldPos = window.mapPixelToCoords(pixelPos);

        
            Mass1.ButtonDisplayLogic();
            Mass2.ButtonDisplayLogic();
            Velocity1.ButtonDisplayLogic();
            Velocity2.ButtonDisplayLogic();
        
        if (ShowImportUI == 1) {
            ImportInput.ButtonDisplayLogic();
        }
        if (ShowDownloadUI == 1) {
            DownloadInput.ButtonDisplayLogic();
        }
        //cursor hover detection
        if (isSpriteHover(Mass1.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(Mass2.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(Velocity1.ButtonsRectangle.getGlobalBounds(), worldPos) || isSpriteHover(Velocity2.ButtonsRectangle.getGlobalBounds(), worldPos)||(isSpriteHover(DownloadInput.ButtonsRectangle.getGlobalBounds(),worldPos)&&ShowDownloadUI==1)||(isSpriteHover(ImportInput.ButtonsRectangle.getGlobalBounds(),worldPos)&&ShowImportUI==1)) {
            cursor.loadFromSystem(sf::Cursor::Text);

        }
        else if (isSpriteHover(BackButton.getGlobalBounds(), worldPos) || isSpriteHover(RunButton.getGlobalBounds(), worldPos) || isSpriteHover(ImportButton.getGlobalBounds(), worldPos) || mousepressslider || isSpriteHover(ResetButton.getGlobalBounds(), worldPos) || isSpriteHover(DownloadButton.getGlobalBounds(), worldPos)||(isSpriteHover(CloseButton.getGlobalBounds(),worldPos)&&ShowDownloadUI==1)||(isSpriteHover(SaveButton.getGlobalBounds(), worldPos)&&ShowDownloadUI==1)||(isSpriteHover(ImportCloseButton.getGlobalBounds(),worldPos)&&ShowImportUI==1)||(isSpriteHover(Confirm.getGlobalBounds(),worldPos)&&ShowImportUI==1)) {
            cursor.loadFromSystem(sf::Cursor::Hand);
        }
        else {
            cursor.loadFromSystem(sf::Cursor::Arrow);
        }


        rcircle.setOrigin(sf::Vector2f((rcircle.getGlobalBounds().getSize().x / 2), (rcircle.getGlobalBounds().getSize().y / 2)));
        bcircle.setOrigin(sf::Vector2f((bcircle.getGlobalBounds().getSize().x / 2), (bcircle.getGlobalBounds().getSize().y / 2)));
        if (bcircle.getRadius() < 10) {
            bcircle.setRadius(10);
        }

        if (bcircle.getRadius() > 210) {
            bcircle.setRadius(210);
        }


        if (Mass1.FinishedClicking == false && !Mass1.InputText.isEmpty() && Mass1.Check(window) && std::stof(std::string(Mass1.InputText)) > 0) {
            rcircle.setRadius(std::stof(std::string(Mass1.InputText)) * 0.5);
        }
        if (rcircle.getRadius() > 190) {
            rcircle.setRadius(190);
        }
        else if (rcircle.getRadius() < 10) {
            rcircle.setRadius(10);
        }

        if (Mass2.FinishedClicking == false && !Mass2.InputText.isEmpty() && Mass2.Check(window)&&std::stof(std::string(Mass2.InputText))>0) {
            bcircle.setRadius(std::stof(std::string(Mass2.InputText)) * 0.5);
        }
        if (bcircle.getRadius() > 190) {
            bcircle.setRadius(190);
        }
        else if (bcircle.getRadius() < 10) {
            bcircle.setRadius(10);
        }
        maxelasticity = ((sliderbackborder.getGlobalBounds().left + sliderbackborder.getGlobalBounds().width - sliderbox.getGlobalBounds().width) - 816.25f);
        elasticity = ((sliderbox.getGlobalBounds().getPosition().x - 816.25f) / (maxelasticity));

        elasticitydisplay.setString("Elasticity: " + (std::to_string(std::round(elasticity * 1000) / 1000)).substr(0, 5));
        Velocity1Out.setString("Red Objects Velocity: " + std::to_string(velocity1) + " m/s");
        Velocity2Out.setString("Blue Objects Velocity " + std::to_string(velocity2) + " m/s");

        if ((Velocity1.InputText != ""&&Velocity1.Check(window) == true) && Velocity1.FinishedClicking == false && run == false) {
            velocity1 = std::stof(std::string(Velocity1.InputText));
        }
        if ((Velocity2.InputText != "" && Velocity2.Check(window) == true) && Velocity2.FinishedClicking == false && run == false) {
            velocity2 = std::stof(std::string(Velocity2.InputText));
        }

        if (run == true) {
            rcircle.setPosition(rcircle.getPosition().x + (velocity1/7.5f), rcircle.getPosition().y);
            bcircle.setPosition(bcircle.getPosition().x + (velocity2/7.5f), bcircle.getPosition().y);
            momentum1 = std::stof(std::string(Mass1.InputText)) * (std::stof(std::string(Velocity1.InputText)));
            momentum2 = std::stof(std::string(Mass2.InputText)) * (std::stof(std::string(Velocity2.InputText)));

            Mass1.FinishedClicking = false;
            Mass2.FinishedClicking = false;

            Velocity1.FinishedClicking = false;
            Velocity2.FinishedClicking = false;

            if (bcircle.getGlobalBounds().intersects(rcircle.getGlobalBounds())) {
                if (singlecollision == true) {
                    float velocity1after = ((momentum1 + momentum2) - ((velocity1 - velocity2) * (elasticity * std::stof(std::string(Mass2.InputText))))) / (std::stof(std::string(Mass1.InputText)) + std::stof(std::string(Mass2.InputText)));
                    float velocity2after = ((elasticity * (velocity1 - velocity2)) + velocity1after);

                    velocity1 = velocity1after;
                    velocity2 = velocity2after;
                    singlecollision = false;

                }

            }
        }
        if (Mass1.FinishedClicking == false && Mass1.Check(window) && !Mass1.InputText.isEmpty()) {
            if (std::stof(std::string(Mass1.InputText))<=0) {
                    timer3 = 100;
                    showmasserror = true;
                    CollisionRanOnce = false;
                
            }
        }
        if (Mass2.FinishedClicking == false && Mass2.Check(window) && !Mass2.InputText.isEmpty()) {
            if (std::stof(std::string(Mass2.InputText))<=0) {
                    timer3 = 100;
                    showmasserror = true;
                    CollisionRanOnce = false;
                
            }
        }
        if (timer > 0) {
            timer -= 1;
        }
        else {
            showsaved = false;
        }
        if (timer2 > 0) {
            timer2 -= 1;
        }
        else {
            showrunerror = false;
        }
        if (timer3 > 0) {
            timer3 -= 1;
        }
        else {
            showmasserror = false;
        }
        if (timer4 > 0) {
            timer4 -= 1;
        }
        else {
            showimporterror = false;
        }
        if (timer5 > 0) {
            timer5 -= 1;
        }
        else {
            showsuccess = false;
        }
        if (timer5 == 20) {
            Mass1.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 1)));
            Mass2.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 3)));
            Velocity1.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 7)));
            Velocity2.InputText = std::to_string(extractFloatFromString(getLineFromFile(filenameholder + ".txt", 13)));
            sliderbox.setPosition((sf::Vector2f((extractFloatFromString(getLineFromFile(filenameholder + ".txt", 19))* maxelasticity) + 822.5f, sliderbox.getPosition().y)));
        }

        window.clear(sf::Color(185, 185, 185));


        window.draw(bcircle);
        window.draw(rcircle);
        window.draw(BackButton);

        //Border / Input boxes
        window.draw(BackBorder);

        Mass1.DrawButton(window);
        Mass2.DrawButton(window);

        Velocity1.DrawButton(window);
        Velocity2.DrawButton(window);

        
        if (ShowDownloadUI == 1) {
            window.draw(BackBorderDownload);
            window.draw(BackBoxDownload);
            DownloadInput.DrawButton(window);
            window.draw(CloseButton);
            DownloadInput.Check(window);
            window.draw(SaveButton);
        }

        if (ShowImportUI == 1) {
            window.draw(BackBorderImport);
            window.draw(BackBoxImport);
            ImportInput.DrawButton(window);
            ImportInput.Check(window);
            window.draw(ImportCloseButton);
            window.draw(Confirm);
        }
        window.draw(sliderbackborder);
        window.draw(sliderbox);

        window.draw(elasticitytxt);
        window.draw(RunButton);
        window.draw(ImportButton);
        window.draw(DownloadButton);
        
        window.draw(elasticitydisplay);
        window.draw(ResetButton);
        window.draw(Direction);
        
        window.draw(Velocity1Out);
        window.draw(Velocity2Out);
        if (showsaved == true) {
            window.draw(successsave);
        }
        if (showrunerror == true) {
            window.draw(NotRunError);
        }
        if (showmasserror == true) {
            window.draw(MassError);
        }
        if (showimporterror == true) {
            window.draw(TxtNotFound);
        }
        if (showsuccess == true) {
            window.draw(SuccessImport);
        }
        Mass1.Check(window);
        Mass2.Check(window);
        Velocity1.Check(window);
        Velocity2.Check(window);


        window.display();
        return false;
    }
