#include "GeneralInterface.h"
#include "Controller.h"
#include "Panel.h"
#include "RadioBox.h"
#include "Label.h"
#include "Button.h"
#include "TextBox.h"
#include "NumericBox.h"
#include "ComboBox.h"
#include "CheckList.h"
#include "Messagebox.h"

void buttonAction();

int main(int argc, char const *argv[]) 
{
    std::vector<std::string> options;
    options.push_back("Option 1");
    options.push_back("Option 2");
    options.push_back("Option 3");
    options.push_back("Option 4");

    Label header(Controller({3,1}, 15,1, green, black, None),"Windows Console Graphic User Interface");

    Label labelr1(Controller({10,4}, 15,1, white, black, None),"RadioBox");
    RadioBox rl({10,5}, 15, 4, white, black, OneLine);
    rl.setOptions(options);

    Label labelr2(Controller({30,4}, 15,1, white, black, None),"RadioBox: color & border");
    RadioBox r2({30,5}, 20,7, white, blue, TwoLines);
    r2.setOptions(options);

    Label labeltb(Controller({10,15}, 15,1, white, black, None),"Textbox");
    TextBox textBox(Controller({10,16}, 30, 1, white, black, OneLine));

    Label labelcb(Controller({10,20}, 15,1, white, black, None),"Combobox");
    ComboBox comboBox(Controller({10,21}, 30, 1), options);

    Label labelpanel(Controller({60,4}, 15,1, white, black, None),"Interior Panel");

    Button button(Label(Controller({10,28}, 35, 2, gray, red, TwoLines), "Press Button to Open Messagebox"));
    button.setAction(&buttonAction);

    Label labelnb(Controller({5,2}, 15,1, white, black, None),"Numeric Box");
    NumericBox numericBox(Controller({5,3}, 15, 3), 1, 10);

    Label labelcl(Controller({5,13}, 15,1, white, black, None),"Check List");
    CheckList checkList(Controller({5,14}, 20, 5), options);

    Panel p({0,0}, 110,32, green);
    p.add(header);
    p.add(rl);
    p.add(r2);
    p.add(textBox);
    p.add(labelr1);
    p.add(labelr2);
    p.add(labeltb);
    p.add(labelcb);
    p.add(labelpanel);
    p.add(comboBox);
    p.add(button);
    
    Panel p2({60,5}, 40,24);
    p2.add(numericBox);
    p2.add(checkList);
    p2.add(labelcl);
    p2.add(labelnb);

    p.add(p2);

    GeneralInterface* gui = &GeneralInterface::getInstance();
    gui->addPanel(p);
    gui->startInput();
}

void buttonAction() {
    Messagebox messagebox({50,10}, 26, 7, "Message Box");
    messagebox.showPopup();
}