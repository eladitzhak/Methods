#include "Button.h"

Button::Button(const Label& label) : Label(label) {}

void Button::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    bool firstCondition = event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED;
    bool secondCondition = event.dwMousePosition.X >= position.x + borderOffset;
    bool thirdCondotion = event.dwMousePosition.X <= position.x + width + borderOffset;
    bool fourthCondition = event.dwMousePosition.Y >= position.y + borderOffset;
    bool fifthCondition = event.dwMousePosition.Y <= position.y + borderOffset + height;

    if(firstCondition && secondCondition && thirdCondotion && fourthCondition && fifthCondition) {
        doSomething();  
        Label::draw();  
    }
}

void Button::doSomething() {
    Label::setText("Text was changed");
}