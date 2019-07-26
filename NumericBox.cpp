#include "NumericBox.h"

NumericBox::NumericBox(const Controller& controller, int min, int max) 
: Controller(controller), minValue(min), maxValue(max), currentValue(min), 
decrement(Button(Label(Controller({position.x,position.y},3,1), " - "))),
increment(Button(Label(Controller({position.x+9,position.y},3,1)," + ")))
{
    // Controller* c = this;
    // int totalPositionX = position.x + borderOffset, totalPositionY = position.y + borderOffset;
    // while(c->getParent() != NULL) {
    //     totalPositionX += c->getParent()->getPosition().x;
    //     totalPositionY += c->getParent()->getPosition().y;
    //     c = c->getParent();   
    // }
    // decrement.setPosition({totalPositionX, totalPositionY});
    // increment.setPosition({totalPositionX + 9, totalPositionY});
    Controller::setHeight(3);
    Controller::setWidth(15);
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

void NumericBox::handleMouseInput(MOUSE_EVENT_RECORD& event) {}

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
