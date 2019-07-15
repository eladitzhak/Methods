#include "CheckList.h"

int main(int argc, char const *argv[])
{
    auto handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(handle, fdwMode);

    std::vector<std::string> options;
    options.push_back("Option 1");
    options.push_back("Option 2");
    options.push_back("Option 3");
    options.push_back("Option 4");

    CheckList tb(12, 2, 2, options);
    tb.draw();
    
    while (1)
    {
        INPUT_RECORD ir;
        DWORD count;

        ReadConsoleInput(handle, &ir, 1, &count);

        if (count)
        {
            if (ir.EventType == KEY_EVENT)
            {
                tb.handleKeyboardEvent(ir.Event.KeyEvent);
            }
            else if (ir.EventType == MOUSE_EVENT)
            {
                tb.handleMouseEvent(ir.Event.MouseEvent);
            }
        }
    }

    return 0;
}
