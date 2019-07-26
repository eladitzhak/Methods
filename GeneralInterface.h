#pragma once
#include "Controller.h"
#include "Panel.h"
#include <vector>

class GeneralInterface {
    public:
        static GeneralInterface& getInstance() { 
            static GeneralInterface instance; 
            return instance;
        };
        void addPanel(Panel&);
        void startInput();
        void setFocus();
        void setFocus(Controller*);
        void draw();

    private:
        GeneralInterface() {};
        GeneralInterface(GeneralInterface const&);
        void operator=(GeneralInterface const&);
        std::vector<Panel*> panels;
        Controller* focus;
        int currPanel;
};
