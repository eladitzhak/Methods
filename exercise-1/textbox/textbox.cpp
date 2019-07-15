#include "textbox.h"
#include <iostream>
#include <algorithm>

TextBox::TextBox(short width, short top, short left, std::string value) : 
    width(width), top(top), value(value), left(left),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0), pos(value.length())  { }

void TextBox::handleKeyboardEvent(KEY_EVENT_RECORD& event)
{
    if (!event.bKeyDown) return;

    // Add character to value and redraw
    if (event.wVirtualKeyCode >= 0x30 && event.wVirtualKeyCode <= 0x5a || event.wVirtualKeyCode == 0x20)
    {
        if(value.length() < width)
        {
            if(pos == value.length())
                value.push_back(event.uChar.AsciiChar);
            else
                value.insert(pos, 1, event.uChar.AsciiChar);
            pos++;
            draw();
        }
    }

    // Move cursor position
    if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT)
    {
        int textWidth = value.length();
        CONSOLE_SCREEN_BUFFER_INFO info;
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(handle, &info);
        auto offset = info.dwCursorPosition.X - this->left - 1;

        if (offset > 0 && event.wVirtualKeyCode == VK_LEFT)
        {
            SetConsoleCursorPosition(handle,{ SHORT(info.dwCursorPosition.X - 1), info.dwCursorPosition.Y });
            pos--;
        }

        if (offset < textWidth && event.wVirtualKeyCode == VK_RIGHT)
        {
            SetConsoleCursorPosition(handle,{ SHORT(info.dwCursorPosition.X + 1), info.dwCursorPosition.Y });
            pos++;
        }
    }

    // Erase character from value and redraw
    if (event.wVirtualKeyCode == VK_BACK)
    {
        if(value.length() > 0 && pos > 0)
        {
            value.erase(pos-1,1);
            pos--;
            draw();
        }
    }
}

void TextBox::draw()
{
    COORD coord = { left, top };
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));
    
    // Print top border
    std::cout << (char) 0xda;
    for (int i=0; i<width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;

    // Print left border
    SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y+1)});
    std::cout << (char) 0xb3;
    
    // Print value string
    for (int i =0; i < width; i++)
        std::cout << (i >= value.length() ? ' ' : value[i]);
    
    // Print right border
    SetConsoleCursorPosition(handle, { SHORT(left + width + 1), SHORT(top + 1) });
    std::cout << (char) 0xb3;

    // Print bottom border
    SetConsoleCursorPosition(handle, { left, SHORT(top + 2) });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;

    SetConsoleCursorPosition(handle, { SHORT(left + pos + 1), (SHORT)(top+1) });
}

