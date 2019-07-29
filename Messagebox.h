#pragma once

#include "Controller.h"
#include <WinUser.h>
#include <string>

enum Answer { NoAnswer, Cancel, Ok };

class Messagebox : public Controller {
    private:
        std::string message;
        Answer answer;
    public:
        Messagebox(Point, int, int height, std::string msg, Color font = white, Color backgroundColor = black, Border border = OneLine);
        void showPopup(std::string);
        void showPopup();
        Answer getAnswer();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void focus();
        void draw();
};
