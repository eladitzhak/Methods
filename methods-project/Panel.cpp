#include "Panel.h"
#include "GeneralInterface.h"
#include <algorithm>

Panel::Panel(Point position, int width, int height, Color font, Color backgroundColor, Border border) : 
    Controller(position, width, height, font, backgroundColor, border), currChild(-1) { }

void Panel::add(Controller& controller) 
{
    children.push_back(&controller);
    controller.setParent(this);
}

Controller* Panel::getChild(int index) 
{
    if(index >= 0 && index < children.size())
        return children[0];
    return NULL;
}
void Panel::draw() 
{
    Controller::draw();
    for(auto child : children) 
    {
        child->draw();
    }
}

void Panel::handleKeyboardInput(KEY_EVENT_RECORD& event) 
{

}

void Panel::handleMouseInput(MOUSE_EVENT_RECORD& event) 
{

}

void Panel::nextInstance() 
{
    if(currChild + 1 < children.size())
    {
        currChild++;
        GeneralInterface::getInstance().setFocus(children[currChild]);
    }
    else if(parent != NULL)
    {
        currChild = -1;
        parent->nextInstance();
    }
    else 
    {
        currChild = -1;
        GeneralInterface::getInstance().setFocus();
    }
}

void Panel::focus() {
    draw();
    if(children.size() > 0)
        nextInstance();
}
