#pragma once
#include <windows.h>

enum Border { None, OneLine, TwoLines };
enum Color { black, blue, green, aqua, red, purple, yellow, white, gray, lightBlue, lightGreen, lightAqua, lightRed, lightPurple, lightYellow, brightWhite };

typedef struct _Point {
    short x;
    short y;
} Point;

class Controller
{
    public:
        Controller(Point position, int width, int height, Color font = white, Color backgroundColor = black, Border border = OneLine);
        void setHidden(bool);
        Controller* getParent();
        Point getPosition();
        void setPosition(Point);
        int getHeight() { return height; };
        int getWidth() { return width; };
        void setHeight(int h) { height = h; };
        void setWidth(int w) { width = w; };
        virtual void setParent(Controller*);
        virtual void nextInstance();
        virtual void add(Controller&);
        virtual Controller* getChild(int); 
        virtual void handleKeyboardInput(KEY_EVENT_RECORD&);
        virtual void handleMouseInput(MOUSE_EVENT_RECORD&);
        virtual void focus();
        virtual void draw();

    protected:
        Border border;
        Color backgroundColor;
        Color font;
        int height;
        int width;
        short borderOffset;
        Point position;
        bool isHidden;
        Controller* parent;

    private:
        void drawOneLineBorder();
        void drawTwoLinesBorder();
};