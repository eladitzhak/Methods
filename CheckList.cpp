#include "CheckList.h"

CheckList::CheckList(const Controller& controller, std::vector<std::string> list)
: Controller(controller), allValues(list), currentValueIndex(-1)
{ 
    setHidden(true);
}

void CheckList::setSelectedValues(std::vector<std::string> newList) {
    selectedValues = newList;
}

std::vector<std::string> CheckList::getSelectedValues() {
    return allValues;
}

void CheckList::addSelectedValue(std::string valueToAdd) {
    selectedValues.push_back(valueToAdd);
}

void CheckList::removeSelectedValue(std::string valueToRemove) {
    for(int i = 0; i < selectedValues.size(); ++i) {
        if(valueToRemove == selectedValues[i]) {
            selectedValues.erase(selectedValues.begin() + i);
        }
    }
}

bool CheckList::isSelected(std::string stringToCheck) {
    for(int i = 0; i < selectedValues.size(); ++i) {
        if(stringToCheck == selectedValues[i]) {
            return true;
        }
    }
    return false;
}

void CheckList::handleKeyboardInput(KEY_EVENT_RECORD& event) {
    Controller::handleKeyboardInput(event);
    if (!event.bKeyDown) return;

    WORD pressedKey = event.wVirtualKeyCode;

    if (pressedKey == VK_TAB) {
        if(currentValueIndex == allValues.size() - 1)
        {
            currentValueIndex = -1;
            nextInstance();
        }
        else
            currentValueIndex++;
        draw();
    }

    bool upKeyWasPressed = pressedKey == VK_UP || pressedKey == VK_NUMPAD8;
    bool downKeyWasPressed = pressedKey == VK_DOWN || pressedKey == VK_NUMPAD2;
    bool selectKeyPressed = pressedKey == VK_RETURN || pressedKey == VK_SPACE;

    if(upKeyWasPressed && currentValueIndex > 0) {
        currentValueIndex--;
    }

    if(downKeyWasPressed && currentValueIndex < allValues.size() - 1) {
        currentValueIndex++;
    }

    if(selectKeyPressed) {
        isSelected(allValues[currentValueIndex]) ? removeSelectedValue(allValues[currentValueIndex]) : addSelectedValue(allValues[currentValueIndex]);
    }

    draw();
}

void CheckList::handleMouseInput(MOUSE_EVENT_RECORD& event) {
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        bool pressInsideX = event.dwMousePosition.X >= position.x + borderOffset && event.dwMousePosition.X <= position.x + borderOffset + width;
        bool pressInsideY = event.dwMousePosition.Y >= position.y + borderOffset && event.dwMousePosition.Y <= position.y + borderOffset + allValues.size() - 1; 
        bool pressInsideBox = pressInsideX && pressInsideY; 

        if(pressInsideBox) {
            currentValueIndex = event.dwMousePosition.Y - position.y - borderOffset;
            isSelected(allValues[currentValueIndex]) ? removeSelectedValue(allValues[currentValueIndex]) : addSelectedValue(allValues[currentValueIndex]);
        }
        else {
            currentValueIndex = -1;
        }
        draw();
    }
}

void CheckList::draw() {
    Controller::draw();

    COORD coord = { SHORT(position.x + borderOffset), SHORT(position.y + borderOffset) };
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    SetConsoleCursorPosition(handle, coord);

    for(int i = 0; i < allValues.size(); ++i) {
        SetConsoleCursorPosition(handle, {coord.X, SHORT(coord.Y+i)});
        SetConsoleTextAttribute(handle, font | (backgroundColor << 4));
        
        if(i == currentValueIndex) {
            SetConsoleTextAttribute(handle, (font^0xF | ((backgroundColor^0xF) << 4)));
        }

        for(int j = 0; j < width; j++) {
            if(j > 0 && j <= allValues[i].size()) {
                std::cout << allValues[i][j-1];
            } else if(j == width - 3 && isSelected(allValues[i])) {
                std::cout << "*";
            } else {
                std::cout << " ";
            } 
        }
    }
}

void CheckList::focus() {
    currentValueIndex = 0;
    draw();
}
    