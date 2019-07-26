#pragma once
#include "Controller.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Label : public Controller {
    protected:
        string text;
    public:
        Label(const Controller& controller, string _text);
        string getText();
        void setText(string newText);
        void draw();
        void focus();
};
