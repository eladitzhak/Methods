#include "TextBox.h"
#include <iostream>

TextBox::TextBox(const Controller& controller, int maximalSize)
: Controller(controller) { 
    currentPosition = -1; 
    setHeight(1);
    setWidth(maxLength = maximalSize);
}

void TextBox::setText(string input) {
    for(int i = 0; i < input.size() && i < maxLength; ++i) {
        text.push_back(input[i]);
    }
    draw();
}

string TextBox::getText() {
    return text;
}

void TextBox::handleKeyboardInput(KEY_EVENT_RECORD& event) {
    Controller::handleKeyboardInput(event);
    if (!event.bKeyDown) return;

    WORD pressedKey = event.wVirtualKeyCode;

    bool leftkeyPressed = pressedKey == VK_LEFT || pressedKey == VK_NUMPAD4;
    bool rightkeyPressed = pressedKey == VK_RIGHT || pressedKey == VK_NUMPAD6;
    bool deleteKeyPressed = pressedKey == VK_DELETE;
    bool backspaceKeyPressed = pressedKey == VK_BACK;
    bool numberKeyPressed = pressedKey >= 0x30 && pressedKey <= 0x39;
    bool letterKeyPressed = pressedKey >= 0x41 && pressedKey <= 0x5A;
    bool tabKeyPressed = pressedKey == VK_TAB;
    
    if(leftkeyPressed) { 
        int newCursorPosition = currentPosition == 0 ? currentPosition : currentPosition - 1;  
        setCursorPosition(newCursorPosition);
    } 
    
    if(rightkeyPressed) { 
        int newCursorPosition = currentPosition == maxLength - 1 ? currentPosition : currentPosition + 1;  
        setCursorPosition(newCursorPosition);    
    }
    
    if(deleteKeyPressed) {
        text.erase(currentPosition, 1);
    }
    
    if(backspaceKeyPressed) { 
        text.erase(currentPosition, 1);
        int newCursorPosition = currentPosition == 0 ? currentPosition : currentPosition - 1;  
        setCursorPosition(newCursorPosition);
     }
    
    if(numberKeyPressed || letterKeyPressed) {
        text.insert(currentPosition, string(1, (char)pressedKey));
        if(text.size() > maxLength) {
            text.pop_back();
        }
        int newCursorPosition = currentPosition == maxLength - 1 ? currentPosition : currentPosition + 1;  
        setCursorPosition(newCursorPosition);
     }

     if(tabKeyPressed) {
        currentPosition = -1; 
        Controller::nextInstance();
     }

     draw();
}

void TextBox::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        bool pressInsideX = event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + borderOffset + width; 
        bool pressInsideY = event.dwMousePosition.Y >= position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + height; 
        bool pressInsideTextBox = pressInsideX && pressInsideY; 

        if(pressInsideTextBox) {
            currentPosition = event.dwMousePosition.X - position.x - borderOffset;
        } else {
            currentPosition = text.size() - 1;
        }
        draw();
    }
}

void TextBox::setCursorPosition(int newPosition) {
    currentPosition = newPosition;
}

int TextBox::getCursorPosition() {
    return currentPosition;
}

void TextBox::draw() {
    Controller::draw();

    COORD coord = { SHORT(position.x + borderOffset), SHORT(position.y + borderOffset) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);

    for(int i = 0; i < text.size(); i++) {
        SetConsoleTextAttribute(handle, (font | backgroundColor << 4));
        if(i==currentPosition) {
            SetConsoleTextAttribute(handle, (font^0xF | ((backgroundColor^0xF) << 4)));
        }
        cout << text[i];
    }
}

void TextBox::focus(){
    currentPosition = 0;
    draw();
}