#include "RadioBox.h"
#include <iostream>
#include <algorithm>

RadioBox::RadioBox(Point position, int width, int height, Color font, Color backgroundColor, Border border) : 
    Controller(position, width, height, font, backgroundColor, border), select(-1), index(-1)  
{ 
    setHidden(true);
}

bool RadioBox::SelectedItem(int i) {
    if(i >= 0 && i < options.size())
    {
        select = i;
        return true;
    }
    return false;
}

bool RadioBox::ClearSelection() {
    if(select != -1)
    {
        select = -1;
        return true;
    }
    return false;
}

void RadioBox::handleKeyboardInput(KEY_EVENT_RECORD& event)
{
    Controller::handleKeyboardInput(event);

    if (!event.bKeyDown) return;

    // If tab is pressed then go to next controller or move selection
    if (event.wVirtualKeyCode == VK_TAB)
    {
        if(index == options.size() - 1)
        {
            index = -1;
            nextInstance();
        }
        else
            index++;
        draw();
    }

    // If space or enter is pressed then select current option
    if (event.wVirtualKeyCode == VK_SPACE || event.wVirtualKeyCode == VK_RETURN)
    {
        if(select != index)
            select = index;
        else
            ClearSelection();
        draw();
    }

    // If arrow keys pressed, move selection
    if (event.wVirtualKeyCode == VK_UP || event.wVirtualKeyCode == VK_DOWN || event.wVirtualKeyCode == VK_NUMPAD8 || event.wVirtualKeyCode == VK_NUMPAD2)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(handle, &info);

        if(index != 0 && (event.wVirtualKeyCode == VK_UP || event.wVirtualKeyCode == VK_NUMPAD8))
            index--;
        else if(event.wVirtualKeyCode == VK_UP || event.wVirtualKeyCode == VK_NUMPAD8)
            index = options.size()-1;

        if(index != options.size()-1 && (event.wVirtualKeyCode == VK_DOWN || event.wVirtualKeyCode == VK_NUMPAD2))
            index++;
        else if(event.wVirtualKeyCode == VK_DOWN || event.wVirtualKeyCode == VK_NUMPAD2)
            index = 0;
        
        draw();
    }
}

void RadioBox::handleMouseInput(MOUSE_EVENT_RECORD& event)
{
    // Check if position.x button is pressed and mouse is inside radiobox border
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        if (event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + width
            && event.dwMousePosition.Y >= position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + options.size() - 1)
        {
            // Set select to index of option that was clicked and redraw
            if(select != event.dwMousePosition.Y - (position.y + borderOffset))
                select = event.dwMousePosition.Y - (position.y + borderOffset);
            else
                ClearSelection();
            
            index = event.dwMousePosition.Y - (position.y + borderOffset);
        }
        else {
            index = -1;
        }
        draw();
    }
}

void RadioBox::draw()
{
    Controller::draw();

    COORD coord = { SHORT(position.x + borderOffset), SHORT(position.y + borderOffset) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));

    // Print option strings
    int i = 0;
    for (std::vector<std::string>::iterator it = options.begin(); it != options.end(); it++){
        SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y+i)});

        if(i == index)
            SetConsoleTextAttribute(handle, (font^0xF | ((backgroundColor^0xF) << 4)));

        if(i == select)
            std::cout << (char) 0x3e;
        else
            std::cout << (char) 0xf9;

        
        std::cout << ' ';
        for (int j = 0; j < width-2; j++)
            std::cout << (j >= it->length() ? ' ' : (*it)[j]);

        SetConsoleTextAttribute(handle, font | (backgroundColor << 4));

        i++;
    }
}

void RadioBox::focus(){
    index = 0;
    draw();
}

