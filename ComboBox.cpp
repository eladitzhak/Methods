#include "ComboBox.h"

using namespace std; 

ComboBox::ComboBox(const Controller& controller, vector<string> list) 
: Controller(controller), valuesList(list), selected(-1), current(-1), isListHidden(true)
{ } 

int ComboBox::getSelectedIndex() {
    return selected;
}

void ComboBox::setSelectedIndex(int newSelection) {
    selected = newSelection;
}

string ComboBox::getContent() {
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
    isListHidden = false;
    setHeight(1 + valuesList.size());
}

void ComboBox::handleKeyboardInput(KEY_EVENT_RECORD&) {

}

void ComboBox::handleMouseInput(MOUSE_EVENT_RECORD&) {

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
        if(i < getContent().size()) {
            cout << getContent()[i];
        } else if(i != width - 1) {
            cout << " ";
        } else {
            cout << "v";
        }
    }

    if(isListHidden == false) {
        for(int i = 0; i < valuesList.size(); i++) {
            SetConsoleTextAttribute(handle, (font | backgroundColor << 4));
            if(i==selected) {
                SetConsoleTextAttribute(handle, (font^0xF | ((backgroundColor^0xF) << 4)));
            }
            cout << endl << valuesList[i];
        }
    }
}

void ComboBox::focus(){
    nextInstance();
}
