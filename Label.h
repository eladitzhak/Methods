#pragma once
#include "Controller.h"
#include <iostream>
#include <string>
#include <windows.h>

class Label : public Controller {
    protected:
        std::string text;
    public:
        Label(const Controller& controller, std::string _text);
        std::string getText();
        void setText(std::string newText);
        void draw();
        void focus();
};
