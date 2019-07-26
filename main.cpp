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

int main(int argc, char const *argv[]) 
{
    // Panel + Radiobox example
    std::vector<std::string> options;
    options.push_back("Option 1");
    options.push_back("Option 2");
    options.push_back("Option 3");
    options.push_back("Option 4");

    RadioBox rl({10,5}, 15, 4, white, black, OneLine);
    rl.setOptions(options);

    RadioBox r2({30,5}, 20,7, white, blue, TwoLines);
    r2.setOptions(options);

    Label label(Controller({10,12}, 15,4, white, black, OneLine),"Some text");

    Button button(Label(Controller({5,1}, 15, 4, gray, red, TwoLines), "Press here"));

    TextBox textBox(Controller({10,20}, 15, 1, white, black, OneLine), 4);
    textBox.setText("Amen yaavod");

    NumericBox numericBox(Controller({5,9}, 0, 0), 1, 10);

    ComboBox comboBox(Controller({10,24}, 15, 1), options);

    CheckList checkList(Controller({5,14}, 20, 5), options);

    Panel p({0,0}, 110,50);
    p.add(rl);
    p.add(r2);
    p.add(textBox);
    p.add(label);
    p.add(comboBox);
    
    Panel p2({60,5}, 40,30);
    p2.add(button);
    p2.add(numericBox);
    p2.add(checkList);

    p.add(p2);

    GeneralInterface* gui = &GeneralInterface::getInstance();
    gui->addPanel(p);
    gui->startInput();
}
