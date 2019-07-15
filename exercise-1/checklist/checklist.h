#include <string>
#include <vector>
#include <windows.h>

class CheckList
{
    public:
        CheckList(short width, short top, short left, std::vector<std::string> options);
        void draw();
        void handleKeyboardEvent(KEY_EVENT_RECORD&);
        void handleMouseEvent(MOUSE_EVENT_RECORD&);
        std::string getSelected(){return options[select];};

    private:
        short width;
        short top;
        short left;
        short select;
        short index;
        WORD color;
        WORD highlightColor;
        WORD background;
        std::vector<std::string> options;
};