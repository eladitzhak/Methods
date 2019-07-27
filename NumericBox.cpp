#include "NumericBox.h"

NumericBox::NumericBox(const Controller& controller, int min, int max) 
: Controller(controller), minValue(min), maxValue(max), currentValue(min),
decrement(Button(Label(Controller({position.x+border,position.y+border},3,1), " - "))),
increment(Button(Label(Controller({position.x+width-border-3-1,position.y+border},3,1)," + ")))
{

}

void NumericBox::setParent(Controller* controller) {
    Controller::setParent(controller);
    decrement.setParent(controller);
    increment.setParent(controller);
}

void NumericBox::plusResponse() {
    if(currentValue < maxValue) {
        currentValue++;
    }
}

void NumericBox::minusResponse() {
    if(currentValue > minValue) {
        currentValue--;
    }
}

void NumericBox::setValue(int newValue) {
    currentValue = newValue;
}

int NumericBox::getValue() {
    return currentValue;
}

void NumericBox::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        bool pressInsideXdecrement = event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + borderOffset + 3;
        bool pressInsideXincrement = event.dwMousePosition.X >= position.x + borderOffset + width - 5  && event.dwMousePosition.X <= position.x + borderOffset + width - 2;
        bool pressInsideY = event.dwMousePosition.Y >= position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + 1; 
        bool pressInsideDecrement = pressInsideXdecrement && pressInsideY; 
        bool pressInsideIncrement= pressInsideXincrement && pressInsideY; 

        if(pressInsideDecrement)
            minusResponse();
        if(pressInsideIncrement)
            plusResponse();

        draw();
    }
}

void NumericBox::draw() {
    Controller::draw();
    
    decrement.draw();

    COORD coord = { SHORT(position.x + borderOffset + 5), SHORT(position.y + borderOffset + 1) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));
    cout << currentValue;
    
    increment.draw();
}

void NumericBox::focus() { 
        nextInstance();
}
