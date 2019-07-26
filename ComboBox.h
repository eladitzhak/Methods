#pragma once

#include <vector>
#include <iostream>

#include "Controller.h"

class ComboBox : public Controller {
    private:
        std::vector<std::string> valuesList;
        int current;
        int selected;
        bool isListHidden;
    public:
        ComboBox(const Controller&, std::vector<std::string>);
        int getSelectedIndex();
        void setSelectedIndex(int);
        std::string getContent();
        void hideList();
        void showList();
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void draw();
        void focus();
};