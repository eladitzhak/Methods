#include "ComboBox.h"

ComboBox::ComboBox(const Controller& controller, std::vector<std::string> list) 
: Controller(controller), valuesList(list), selected(-1), current(-1), isListHidden(true)
{ 
    setHidden(true);
} 

int ComboBox::getSelectedIndex() {
    return selected;
}

void ComboBox::setSelectedIndex(int newSelection) {
    selected = newSelection;
}

std::string ComboBox::getContent() {
    int index = selected;
    if(index < 0 || index >= valuesList.size()) {
        return "";
    }
    return valuesList[index];
}

void ComboBox::hideList() {
    isListHidden = true;
    setHeight(1);
}

void ComboBox::showList() {
    current = 0;
    isListHidden = false;
    setHeight(1 + valuesList.size());
}

void ComboBox::handleKeyboardInput(KEY_EVENT_RECORD& event) {
    Controller::handleKeyboardInput(event);
    if (!event.bKeyDown) return;

    if(isListHidden == false) {
        WORD pressedKey = event.wVirtualKeyCode;

        if (pressedKey == VK_TAB) {
            current = -1;
            hideList();
            draw();
            nextInstance();
        }

        bool upKeyWasPressed = pressedKey == VK_UP || pressedKey == VK_NUMPAD8;
        bool downKeyWasPressed = pressedKey == VK_DOWN || pressedKey == VK_NUMPAD2;
        bool selectKeyPressed = pressedKey == VK_RETURN || pressedKey == VK_SPACE;

        if(upKeyWasPressed && current > 0) {
            current--;
        }

        if(downKeyWasPressed && current < valuesList.size() - 1) {
            current++;
        }

        if(selectKeyPressed) {
            selected = current;
            hideList();
        }

        draw();
    }
}

void ComboBox::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        if(isListHidden == true) {
            
            bool pressInsideX = event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + borderOffset + width;
            bool pressInsideY = event.dwMousePosition.Y >= position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + 1; 
            bool pressInsideBox = pressInsideX && pressInsideY; 

            if(pressInsideBox) {
                showList();
                draw();
            }
        } else {
            
            bool pressInsideX = event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + borderOffset + width;
            bool pressInsideY = event.dwMousePosition.Y > position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + valuesList.size(); 
            bool pressInsideBox = pressInsideX && pressInsideY;

            if(pressInsideBox) { 
                selected = event.dwMousePosition.Y - position.y - borderOffset - 1;
                current = 0;
                hideList();
            } else {
                hideList();
            }
            draw();
        }
    }
    Controller::handleMouseInput(event);
}

void ComboBox::draw() {
    Controller::draw();

    COORD coord = { SHORT(position.x + borderOffset), SHORT(position.y + borderOffset) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, font | (backgroundColor << 4));
    
    for(int i=0; i<width; ++i) {
        if(i < getContent().size() && isListHidden) {
            std::cout << getContent()[i];
        } else if(i != width - 1) {
            std::cout << " ";
        } else {
            std::cout <<  (isListHidden ? "v" : "^");
        }
    }

    for(int i = 0; i < valuesList.size(); i++) {
        SetConsoleTextAttribute(handle, (font | backgroundColor << 4));
        if(isListHidden) {
            SetConsoleCursorPosition(handle, {SHORT(coord.X - 1), SHORT(coord.Y + i + 2)});
            for(int i=0; i<=width+borderOffset*2; ++i) {
                std::cout << " ";
            }
        } else {
            if(i==current) {
                SetConsoleTextAttribute(handle, (font^0xF | ((backgroundColor^0xF) << 4)));
            }
            SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y + i + 1)});
            std::cout << (std::string)valuesList[i];
        }
    }
}

void ComboBox::focus(){
    if(isListHidden)
        nextInstance();
}
