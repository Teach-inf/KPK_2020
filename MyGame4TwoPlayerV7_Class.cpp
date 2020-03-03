
#include "TXLib.h"

struct Player
    {
    double x,  y;
    double r;
    int bug;
    double oldX, oldY;
    COLORREF color;
    void DrawCar ()const;
    void barrierControlArrows (COLORREF colorControl, COLORREF color, int step);
    void barrierControlWADS   (COLORREF colorControl, COLORREF color, int step);
    void ControlLose (int k);
    };

void DrawText(double x, double y, const char* text, int size, COLORREF color);

int main()
    {
    txCreateWindow (720, 720);
    txBegin();

    HDC trackImage = txLoadImage ("3.bmp");
    HDC backImage  = txLoadImage ("33.bmp");

    Player player1 = {65, 130, 10, 0, 65, 130, TX_LIGHTGREEN},
           player2 = {95, 130, 10, 0, 85, 130, RGB (105, 224, 218)};

    DrawText (100, 100, "Управление шариками: Первый игрок - стрелками, ", 26, TX_WHITE);
    DrawText (100, 130, "Второй игрок - клавиши WADS (на английской раскладке)!!!", 26, TX_WHITE);
    DrawText (100, 160, "Выйти из игры в любой момент можно, нажав кнопку ESC", 26, TX_WHITE);
    DrawText (100, 190, "Главная задача - не касаться края дороги", 26, TX_WHITE);
    DrawText (100, 220, "Проигрывает тот, кто коснулся края 20 раз...", 26, TX_WHITE);

    txSleep (13000);

    for (int t = 0; ((!(txGetAsyncKeyState (VK_ESCAPE))) && (player1.bug < 20) && (player2.bug < 20)); t++)
        {
        txBitBlt (txDC(), 0, 0, 0, 0, backImage);

        COLORREF color1 = txGetPixel (player1.x, player1.y);
        COLORREF color2 = txGetPixel (player2.x, player2.y);

        //if (!GetKeyState (VK_CAPITAL))
        txBitBlt (txDC(), 0, 0, 0, 0, trackImage);

        player1.DrawCar ();
        player2.DrawCar ();

        int step = 1;

        player1.barrierControlArrows (RGB (0, 255, 0), color1, step);
        player2.barrierControlWADS   (RGB (0, 255, 0), color2, step);

        player1.ControlLose (20);
        player2.ControlLose (20);

        char s[100] = "";

        sprintf  (s, "Player 1: %d collisions", player1.bug);
        DrawText (20, 600, s, 26, player1.color);

        sprintf  (s, "Player 2: %d collisions", player2.bug);
        DrawText (20, 630, s, 26, player2.color);

        txSleep();
        }

    txSleep(2000);
    txDeleteDC (trackImage);
    txDeleteDC (backImage);
    return 0;
    }

void Player :: DrawCar ()const
    {
    txSetColor (color, 5);
    txCircle (x, y, r);
    }

void DrawText(double x, double y, const char* text, int size, COLORREF color)
    {
    txSetColor (color);
    txSelectFont ("Times New Roman", size);
    txTextOut (x, y, text);
    }

//COLORREF colorControl - цвет, за который нельзя заступать, COLORREF color - текущий цвет пикселя
//Player* player - игрок, int step - шаг

void Player :: barrierControlArrows (COLORREF colorControl, COLORREF color, int step)
    {
    if (GetAsyncKeyState (VK_RIGHT))
        if (color == colorControl) { x = oldX - 10; bug ++; }
        else x += step;

    if (GetAsyncKeyState (VK_LEFT))
        if (color == colorControl) { x = oldX + 10; bug ++; }
        else x -= step;

    if (GetAsyncKeyState (VK_UP))
        if (color == colorControl) { y = oldY + 10; bug ++; }
        else y -= step;

    if (GetAsyncKeyState (VK_DOWN))
        if (color == colorControl) { y = oldY - 10; bug ++; }
        else y += step;
    }

void Player :: barrierControlWADS (COLORREF colorControl, COLORREF color, int step)
    {
    if (txGetAsyncKeyState ('A') || txGetAsyncKeyState ('a'))
        if (color == colorControl) { x = oldX + 10; bug ++; }
        else x -= step;
    if (txGetAsyncKeyState ('D') || txGetAsyncKeyState ('d'))
        if (color == colorControl) { x = oldX - 10; bug ++; }
        else x += step;
    if (txGetAsyncKeyState ('S') || txGetAsyncKeyState ('s'))
        if (color == colorControl) { y = oldY - 10; bug ++; }
        else y += step;
    if (txGetAsyncKeyState ('W') || txGetAsyncKeyState ('w'))
        if (color == colorControl) { y = oldY + 10; bug ++; }
        else y -= step;
    }

void Player :: ControlLose (int k)
    {
    if (bug == k) DrawText(x, y + 20, "Player LOSE", 40, color);

    oldX = x;
    oldY = y;
    }
