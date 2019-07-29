#include "Label.h"

Label::Label(const Controller& controller, std::string _text)
: Controller(controller), text(_text) {
    setHidden(true);
}

std::string Label::getText() {
    return text;
}

void Label::setText(std::string newText) {
    text = newText;
}

void Label::draw() {
    Controller::draw();

    COORD coord = { SHORT(position.x + borderOffset), SHORT(position.y + borderOffset) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    COORD oldCoord = info.dwCursorPosition;
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));
    std::cout << text;
}

void Label::focus() {
    nextInstance();
}
