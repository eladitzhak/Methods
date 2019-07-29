#include "Messagebox.h"
#include "Label.h"
#include "GeneralInterface.h"
#include <iostream>

Messagebox::Messagebox(Point position, int width, int height, std::string msg, Color font, Color backgroundColor, Border border) 
: Controller(position, width, height, font, backgroundColor, border), message(msg), answer(NoAnswer)
{
    setHidden(true);
}

void Messagebox::showPopup(std::string toDisplay) {
    message = toDisplay;
    draw();
}

void Messagebox::showPopup() {
    draw();
    auto handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    SetConsoleMode(handle, fdwMode);
    while (!answer) {
        INPUT_RECORD ir;
        DWORD count;

        ReadConsoleInput(handle, &ir, 1, &count);

        if (count && ir.EventType == MOUSE_EVENT) 
            handleMouseInput(ir.Event.MouseEvent);
    }
}

void Messagebox::handleKeyboardInput(KEY_EVENT_RECORD& event) {

}

void Messagebox::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        bool pressInsideXCancel = event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + borderOffset + width/2 - 2;
        bool pressInsideXOk = event.dwMousePosition.X >= position.x + borderOffset + width/2  && event.dwMousePosition.X <= position.x + borderOffset + width -2 ;
        bool pressInsideY = event.dwMousePosition.Y >= position.y + borderOffset + height - 3 && event.dwMousePosition.Y <= position.y + borderOffset + height - 2; 
        bool pressInsideCancel = pressInsideXCancel && pressInsideY; 
        bool pressInsideOk= pressInsideXOk && pressInsideY; 

        if(pressInsideCancel)
            answer = Cancel;
        if(pressInsideOk)
            answer = Ok;
        if(answer)
            GeneralInterface::getInstance().draw();
    }
}

void Messagebox::focus() {

}

void Messagebox::draw() {
    Controller::draw();

    COORD coord = { SHORT(position.x + borderOffset), SHORT(position.y + borderOffset) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));
    for (int i = 0; i < width; i++)
        std::cout << (i >= message.length() ? ' ' : message[i]);

    Label(Controller({SHORT(position.x + borderOffset), SHORT(position.y + borderOffset + height - 3)}, width/2 - 2, 1, font, backgroundColor), "Cancel").draw();
    Label(Controller({SHORT(position.x + borderOffset + width/2), SHORT(position.y + borderOffset + height - 3)}, width/2 - 2, 1, font, backgroundColor), "Ok").draw();
}

Answer Messagebox::getAnswer() {
    return answer;
}
