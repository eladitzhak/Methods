#include "Controller.h"
#include "GeneralInterface.h"
#include <iostream>

Controller::Controller(Point position, int width, int height, Color font, Color backgroundColor, Border border) : 
    position(position), width(width), height(height), font(font), backgroundColor(backgroundColor), border(border), isHidden(false), parent(NULL), borderOffset(0) { }

void Controller::setHidden(bool hidden) 
{
    isHidden = hidden;
}

Point Controller::getPosition() const {
    return position;
}

void Controller::setPosition(Point newPosition) {
    position = newPosition;
}

void Controller::handleKeyboardInput(KEY_EVENT_RECORD& event) {
    if (event.wVirtualKeyCode == VK_ESCAPE) {
        exit(1);
    }
}

void Controller::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        if (event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + width
            && event.dwMousePosition.Y >= position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + height)
        {
            if(GeneralInterface::getInstance().getFocus() != this)
            {
                GeneralInterface::getInstance().setFocus(this);
                Panel* parentPanel = dynamic_cast<Panel*>(parent);
                if(parentPanel)
                    parentPanel->setCurrent(this);
            }
                
        }
        draw();
    }
}

void Controller::nextInstance() 
{
    parent->nextInstance();
}

void Controller::setParent(Controller* controller) 
{
    if(parent == NULL)
        position = {SHORT(controller->position.x + position.x), SHORT(controller->position.y + position.y) };
    else 
        position = {SHORT(controller->position.x + position.x - parent->position.x), SHORT(controller->position.y + position.y  - parent->position.y)};

    parent = controller;
}

Controller* Controller::getParent() const {
    return parent;
}

Controller* Controller::getChild(int) 
{
    return NULL;
}

void Controller::draw() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);

    cursorInfo.bVisible = !isHidden;
    SetConsoleCursorInfo(handle, &cursorInfo);
    
    switch(border){
        case None:
            borderOffset = 0;
            break;
        case OneLine:
            borderOffset = 1;
            drawOneLineBorder();
            break;
        case TwoLines:
            borderOffset = 2;
            drawTwoLinesBorder();
            break;
    }
}

void Controller::drawOneLineBorder() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { position.x, position.y };
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));

    // Print top border
    std::cout << (char) 0xda;
    for (int i=0; i< width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;


    // Print side border
    int i;
    for (i = 0; i < height; i++){
        SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y+1+i)});
        std::cout << (char) 0xb3;

        for (int j = 0; j < width; j++)
            std::cout << ' ';

        std::cout << (char) 0xb3;
    }

    // Print bottom border
    SetConsoleCursorPosition(handle, { position.x, SHORT(position.y + 1 + i) });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
}

void Controller::drawTwoLinesBorder() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { position.x, position.y };
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));

    // Print outer top border
    std::cout << (char) 0xda;
    for (int i=0; i< width+2; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;

    // Print top inner border
    SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y + 1)});
    std::cout << (char) 0xb3;
    std::cout << (char) 0xda;
    for (int i=0; i< width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;
    std::cout << (char) 0xb3;


    // Print side border
    int i;
    for (i = 0; i < height; i++){
        SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y + 2 + i)});
        std::cout << (char) 0xb3;
        std::cout << (char) 0xb3;

        for (int j = 0; j < width; j++)
            std::cout << ' ';

        std::cout << (char) 0xb3;
        std::cout << (char) 0xb3;
    }

    // Print bottom inner border
    SetConsoleCursorPosition(handle, { position.x, SHORT(position.y + 1 + i) });
    std::cout << (char) 0xb3;
    std::cout << (char) 0xc0;
    for (int i=0; i< width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
    std::cout << (char) 0xb3;

    // Print bottom outer border
    SetConsoleCursorPosition(handle, { position.x, SHORT(position.y + 2 + i) });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width+2; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
}

void Controller::focus() { }
void Controller::add(Controller& controller) { }
