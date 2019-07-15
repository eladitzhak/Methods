#include "GeneralInterface.h"
#include "Controller.h"
#include "Panel.h"
#include "RadioBox.h"

int main(int argc, char const *argv[]) 
{
    // Panel + Radiobox example
    std::vector<std::string> options;
    options.push_back("Option 1");
    options.push_back("Option 2");
    options.push_back("Option 3");
    options.push_back("Option 4");

    RadioBox rl({10,5}, 15,4, white, black, OneLine);
    rl.setOptions(options);

    RadioBox r2({30,5}, 20,7, white, blue, TwoLines);
    r2.setOptions(options);

    
    RadioBox r3({5,3}, 20,7, black, lightYellow, None);
    r3.setOptions(options);
    
    Panel p({0,0}, 110,20);
    p.add(rl);
    p.add(r2);

    Panel p2({60,5}, 40,10);
    p2.add(r3);
    p.add(p2);

    GeneralInterface* gui = &GeneralInterface::getInstance();
    gui->addPanel(p);
    gui->startInput();
}
