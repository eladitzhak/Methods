#pragma once

#include "Controller.h"

#include <string>
#include <algorithm>

using namespace std;

class TextBox : public Controller {
    private:
        string text;
        int maxLength;
        int currentPosition;
    public:
        TextBox(const Controller& controller, int maximalSize);
        void setText(string input);
        string getText();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void setCursorPosition(int);
        int getCursorPosition();
        void draw();
        void focus();
};
