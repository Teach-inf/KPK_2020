
#include "DinoLib.cpp"

int main()
    {
    txCreateWindow (800, 600);
    txSetFillColor (RGB (85, 185, 0));
    txClear();

    int tekX = 0;

    MoveTitle("Dino-world for Danya...");
    Move1(tekX);
    Move2(tekX);
    MoveTitle("Thanks...", 150);

    return 0;
    }


