#include "GeneralInterface.h"

void GeneralInterface::addPanel(Panel& panel) 
{
    panels.push_back(&panel);
}

void GeneralInterface::startInput() 
{
    if(panels.empty())
        return;
    auto handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(handle, fdwMode);
    draw();
    currPanel=-1;
    setFocus();

    if(panels.size() <= 0)
    {
        return;
    }
    
    while (1) {
        INPUT_RECORD ir;
        DWORD count;

        ReadConsoleInput(handle, &ir, 1, &count);

        if (count && focus) {
            if (ir.EventType == KEY_EVENT) {
                focus->handleKeyboardInput(ir.Event.KeyEvent);
            }
            else if (ir.EventType == MOUSE_EVENT) {
                focus->handleMouseInput(ir.Event.MouseEvent);
            }
        }
    }
}

void GeneralInterface::setFocus(Controller* controller)
{
    focus = controller;
    controller->focus();
}

void GeneralInterface::setFocus()
{
    if(++currPanel < panels.size())
        panels[currPanel]->focus();
    else if(panels.size() > 0){
        currPanel = 0;
        panels[0]->focus();
    }
}

void GeneralInterface::draw() 
{
    for(auto panel : panels) 
    {
        panel->draw();
    }
}