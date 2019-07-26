#pragma once

#include "Label.h"

class Button : public Label {
    public:
        Button(const Label& label);
        void handleMouseInput(MOUSE_EVENT_RECORD&);
        void doSomething();
};
