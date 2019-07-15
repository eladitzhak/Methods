#include <string>
#include <windows.h>

class TextBox
{
    public:

        TextBox(short width, short top, short left, std::string value);
        void draw();
        void handleKeyboardEvent(KEY_EVENT_RECORD&);
        std::string getValue() {return value;};

    private:
        short width;
        short top;
        short left;
        short pos;
        WORD color;
        WORD background;
        std::string value;
};