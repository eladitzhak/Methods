#include "checklist.h"
#include <iostream>
#include <algorithm>

CheckList::CheckList(short width, short top, short left, std::vector<std::string> options) : 
    width(width), top(top), options(options), left(left),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    highlightColor(22),
    background(0), select(-1), index(0)  { }

void CheckList::handleKeyboardEvent(KEY_EVENT_RECORD& event)
{
    if (!event.bKeyDown) return;

    // If space is pressed then select current option
    if (event.wVirtualKeyCode == 0x20)
    {
        select = index;
        draw();
    }

    // If arrow keys pressed, move cursor
    if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT || event.wVirtualKeyCode == VK_UP || event.wVirtualKeyCode == VK_DOWN)
    {
        int textWidth = options[index].length();
        CONSOLE_SCREEN_BUFFER_INFO info;
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(handle, &info);
        auto offset = info.dwCursorPosition.X - this->left - 1;

        if (offset > 0 && event.wVirtualKeyCode == VK_LEFT)
        {
            SetConsoleCursorPosition(handle,{ SHORT(info.dwCursorPosition.X - 1), SHORT(info.dwCursorPosition.Y) });
        }

        if (offset < textWidth && event.wVirtualKeyCode == VK_RIGHT)
        {
            SetConsoleCursorPosition(handle,{ SHORT(info.dwCursorPosition.X + 1), SHORT(info.dwCursorPosition.Y) });
        }

        if(index != 0 && event.wVirtualKeyCode == VK_UP)
        {
            index--;
            SetConsoleCursorPosition(handle,{ SHORT(left + 1), SHORT(info.dwCursorPosition.Y - 1) });
        }

        if(index != options.size()-1 && event.wVirtualKeyCode == VK_DOWN)
        {
            index++;
            SetConsoleCursorPosition(handle,{ SHORT(left + 1), SHORT(info.dwCursorPosition.Y + 1) });
        }
    }
}

void CheckList::handleMouseEvent(MOUSE_EVENT_RECORD& event)
{
    // Check if left button is pressed and mouse is inside checklist border
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        if(event.dwMousePosition.X >= left + 1 && event.dwMousePosition.X <= left + width)
        {
            if(event.dwMousePosition.Y >= top + 1 && event.dwMousePosition.Y <= top + options.size())
            {
                // Set select to index of option that was clicked and redraw
                select = event.dwMousePosition.Y - (top + 1);
                draw();
            }
        }
    }
}

void CheckList::draw()
{
    COORD coord = { left, top };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    COORD oldCoord = info.dwCursorPosition;
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));
    
    // Print top border
    std::cout << (char) 0xda;
    for (int i=0; i<width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;


    // Print option strings inside border
    int i = 0;
    for (std::vector<std::string>::iterator it = options.begin(); it != options.end(); it++){
        SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y+1+i)});
        std::cout << (char) 0xb3;

        if(i == select)
            SetConsoleTextAttribute(handle, highlightColor);

        for (int j =0; j < width; j++)
            std::cout << (j >= it->length() ? ' ' : (*it)[j]);

        SetConsoleTextAttribute(handle, color | (background << 4));
        SetConsoleCursorPosition(handle, { SHORT(left + width + 1), SHORT(top + 1 + i) });
        std::cout << (char) 0xb3;

        i++;
    }

    // Print bottom border
    SetConsoleCursorPosition(handle, { left, SHORT(top + 1 + i) });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;

    // Return cursor to old position
    if(select == -1)
        SetConsoleCursorPosition(handle, { SHORT(left + 1), (SHORT)(top+1) });
    else
        SetConsoleCursorPosition(handle, oldCoord);
}

