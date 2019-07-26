#include "Messagebox.h"

Messagebox::Messagebox(const Controller& controller, std::string msg) 
: Controller(controller), message(msg)
{

}

Answer Messagebox::showPopup(std::string toDisplay) {
    message = toDisplay;
    draw();
}

Answer Messagebox::showPopup() {
    draw();
}

void Messagebox::handleKeyboardInput(KEY_EVENT_RECORD& event) {

}

void Messagebox::handleMouseInput(MOUSE_EVENT_RECORD& event) {

}

void Messagebox::focus() {

}

void Messagebox::draw() {

}
