#include <iostream>
#include <Windows.h>

using namespace std;

enum InterfaceColor
{
    Default = 7,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Pink = 5,
    Yellow = 6,
    BrightWhite = 15
};

enum ConsoleBackgroundColor
{
    Black = 0,
    BlueBG = 16,
    GreenBG = 32,
    CyanBG = 48,
    RedBG = 64,
    MagentaBG = 80,
    YellowBG = 96,
    WhiteBG = 112
};

class Console
{
private:
    InterfaceColor _text_color;
    ConsoleBackgroundColor _background_color;

    void set_text_color(InterfaceColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    void set_background_color(ConsoleBackgroundColor bg_color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFOEX csbi;
        csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
        GetConsoleScreenBufferInfoEx(hConsole, &csbi);

        csbi.wAttributes = (csbi.wAttributes & 0x0F) | bg_color;
        SetConsoleScreenBufferInfoEx(hConsole, &csbi);
    }

public:
    Console(InterfaceColor text_color, ConsoleBackgroundColor bg_color)
        : _text_color(text_color), _background_color(bg_color)
    {
        set_text_color(_text_color);
        set_background_color(_background_color);
    }

    void display_text(string text)
    {
        cout << text << endl;
    }

    void change_interface_color(InterfaceColor new_text_color, ConsoleBackgroundColor new_bg_color)
    {
        _text_color = new_text_color;
        _background_color = new_bg_color;
        set_text_color(_text_color);
        set_background_color(_background_color);
    }

    ~Console()
    {
        set_text_color(InterfaceColor::Default);
        set_background_color(ConsoleBackgroundColor::Black);
    }
};

int main()
{
    Console* console = new Console(InterfaceColor::Blue, ConsoleBackgroundColor::Black);

    console->display_text("Welcome to the colorful console!");

    while (true)
    {
        int text_color, bg_color;
        cout << "Select text color (1: Blue, 2: Green, 3: Red, 4: Yellow, 5: Bright White, 0: Exit): ";
        cin >> text_color;

        if (text_color == 0) break;

        cout << "Select background color (0: Black, 16: Blue, 32: Green, 64: Red, 112: White): ";
        cin >> bg_color;

        console->change_interface_color(static_cast<InterfaceColor>(text_color), static_cast<ConsoleBackgroundColor>(bg_color));

        console->display_text("The interface color has been changed!");
    }

    delete console;
    return 0;
}