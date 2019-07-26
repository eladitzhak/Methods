#pragma once

#include "Controller.h"
#include <vector>
#include <string>
#include <iostream>

class CheckList : public Controller {
    private:
        int currentValueIndex;
        std::vector<std::string> allValues;
        std::vector<std::string> selectedValues;
    public:
        CheckList(const Controller& controller, std::vector<std::string> list);
        void setSelectedValues(std::vector<std::string>);
        std::vector<std::string> getSelectedValues();
        void addSelectedValue(std::string);
        void removeSelectedValue(std::string);
        bool isSelected(std::string);
        void handleKeyboardInput(KEY_EVENT_RECORD&);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void draw();
        void focus();
};