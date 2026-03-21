#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "StatesManager.h"

int main()
{
    States simulation;
    
    //Starts the program
    simulation.start(1980 / 2, 1080 / 2);

    //Runs through all the different "Scenes / Rooms" the simulator can enter
        while (simulation.window.isOpen()) {
            simulation.window.setMouseCursor(simulation.cursor);
        switch (simulation.CurrentState) {
        case 1:
            simulation.menustate();
            break;
        case 2:
            simulation.projectilemotionstate();
            break;
        case 3:
            simulation.collisionstate();
            break;
        }
    }

    return 0;
}