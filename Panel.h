#pragma once
#include "Controller.h"
#include <vector>

class Panel : public Controller {
    public:
        Panel(Point position, int width, int height, Color font = white, Color backgroundColor = black, Border border = OneLine);
        void add(Controller&);
        Controller* getChild(int);
        int size();
        void draw();
        void focus();
        void nextInstance();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);

    private:
        std::vector<Controller*> children;
        int currChild;
};
