#pragma once
#include "Controller.h"
#include <string>
#include <vector>
#include <windows.h>

class RadioBox : public Controller
{
    public:
        RadioBox(Point position, int width, int height, Color font = white, Color backgroundColor = black, Border border = OneLine);
        void draw();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        bool SelectedItem(int);
        bool ClearSelection();
        void focus();
        void setOptions(std::vector<std::string> _options) { options = _options; };
        std::string getSelected() { return options[select]; };
    private:
        short select;
        short index;
        std::vector<std::string> options;
};