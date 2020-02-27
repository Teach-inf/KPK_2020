
#include "DinoLib.h"

int main()
    {
    txCreateWindow (800, 600);
    txSetFillColor (RGB (85, 185, 0));
    txClear();

    DrawDino (500, 400);
    DrawDino ( 50,  50, 0.75, 0.5,  20,   0, 10,  0, TX_GREEN);
    DrawDino ( 50, 100,  0.5, 0.5,   0,   0,  0,  0,  TX_BLUE);
    DrawDino (350, 100,  0.5, 0.5,   0,   0,  0, 20,  TX_BLUE);
    DrawDino (150, 200,    2,   1,   0,   0,  3,  0, TX_BROWN);

    return 0;
    }


