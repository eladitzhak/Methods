#include "GeneralInterface.h"
#include "Button.h"

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
                for(auto panel : panels)
                    CheckCoordinatesInPanel(panel, ir.Event.MouseEvent);
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

void GeneralInterface::CheckCoordinatesInPanel(Panel* panel, MOUSE_EVENT_RECORD& event) {
    Controller* child;
    for(int i  = 0; i < panel->size(); i++) {
        child = panel->getChild(i);
        if(dynamic_cast<Panel*>(child)){
            CheckCoordinatesInPanel(dynamic_cast<Panel*>(child), event);
        }
        else
            child->handleMouseInput(event);
    }
}