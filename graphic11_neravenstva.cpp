
#include "TXLib.h"

void DrawPicture();

int main()
    {
    txCreateWindow (800, 600);
    DrawPicture();

    return 0;
    }

void DrawPicture()
    {
    for (double y = -10; y <= 10; y += 0.04)
    for (double x = -10; x <= 10; x += 0.04)
        {
        if ((x >= -4) && (y <= -0.5*x - 0.3) && (!((x >= -2.7) && (y <= -0.5*x - 1.6))))   txSetPixel (400 + 50*x, 300 - 50*y, TX_LIGHTGRAY);
        if ((x >= -2) && (y <= -0.5*x + 0.5))  txSetPixel (400 + 50*x, 300 - 50*y, TX_LIGHTBLUE);

        if (((x + 2)*(x + 2) + (y - 1.8)*(y - 1.8) <= 0.3) || ((x + 4)*(x + 4) + (y - 2)*(y - 2) <= 0.5))
            txSetPixel (400 + 50*x, 300 - 50*y, TX_LIGHTRED);

        if (y <= 0.5*x)  txSetPixel (400 + 50*x, 300 - 50*y, TX_LIGHTGREEN);

        for (int i = 0; i < 20; i += 2)
            {
            if ((y <= 0.5*fabs((sin (x*2))) + 2.5 - i    ) && (y <= 0.5*x)) txSetPixel (400 + 50*x, 300 - 50*y, TX_GREEN);
            if ((y <= 0.5*fabs((sin (x*2))) + 2.5 - i - 1) && (y <= 0.5*x)) txSetPixel (400 + 50*x, 300 - 50*y, TX_LIGHTGREEN);
            }

        if (((x - 1.5)*(x - 1.5) + (y - 5)*(y - 5) <= 0.5) && !((x - 2)*(x - 2) + (y - 5)*(y - 5) <= 0.5))
            txSetPixel (400 + 50*x, 300 - 50*y, TX_YELLOW);
        }
    }

