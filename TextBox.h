#pragma once

#include "Controller.h"
#include <string>
#include <algorithm>

class TextBox : public Controller {
    private:
        std::string text;
        int maxLength;
        int currentPosition;
    public:
        TextBox(const Controller& controller);
        void setText(std::string input);
        std::string getText();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void setCursorPosition(int);
        int getCursorPosition();
        void draw();
        void focus();
};
