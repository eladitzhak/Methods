#pragma once

#include "Controller.h"
#include <WinUser.h>
#include <string>

enum Answer { Cancel, Ok };

class Messagebox : public Controller {
    private:
        std::string message;
        bool answer;
    public:
        Messagebox(const Controller& controller, std::string msg = "Are you sure?");
        Answer showPopup(std::string);
        Answer showPopup();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void focus();
        void draw();
};
