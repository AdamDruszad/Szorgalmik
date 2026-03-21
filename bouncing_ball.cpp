#include <iostream>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);

    int w = 40, h = 20;
    int x = 0, y = 0;
    int dx = 1, dy = 1;

    while (true)
    {
        gotoxy(x, y);
        std::cout << " ";

        x += dx; y += dy;

        if (x <= 0 || x >= w - 1)
            dx *= -1;
        if (y <= 0 || y >= h - 1)
            dy *= -1;

        gotoxy(x, y);
        std::cout << "O";

        Sleep(80);

        if (_kbhit() && _getch() == 27) break;
    }

    return 0;
}