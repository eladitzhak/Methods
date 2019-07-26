#pragma once

#include "Controller.h"
#include "Button.h"

class NumericBox : public Controller {
    private:
        int maxValue;
        int minValue;
        int currentValue;
        Button increment;
        Button decrement;
    public:
        NumericBox(const Controller& controller, int min, int max);
        void plusResponse();
        void minusResponse();
        void setValue(int);
        int getValue();
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void draw();
        void focus();
};