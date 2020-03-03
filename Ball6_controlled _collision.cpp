//controlled collision
//Управляемое столкновение двух шаров
//для Юли ;-))

 #include "TXLib.h"

 #define X 800
 #define Y 600

 void MoveBall (double x1, double y1, double Vx1, double Vy1,
                double x2, double y2, double Vx2, double Vy2);

 void Phisics  (double* x, double* y, double* Vx, double* Vy, double ax = 0, double ay = 0, bool Ftrenia = false, double dt = 2, double r = 20);
 void DrawBall (double x, double y, double r, COLORREF colorLine, double width, COLORREF colorFon);

 void BarrierArrow (double* x, double* y);
 void BarrierWASZ  (double* x, double* y);

 double Distance (double x1, double y1, double x2, double y2);
 void DrawText (double x, double y, const char* text, int size, COLORREF color);

 int main()
    {
    txCreateWindow (X, Y);

    txSetFillColor (TX_BLACK);
    txClear();

    MoveBall (10, 10, 2, 5, 700, 500, -3, 2);

    return 0;
    }

void MoveBall (double x1, double y1, double Vx1, double Vy1,
               double x2, double y2, double Vx2, double Vy2)
    {
    double r1 = 20, width1 = 2, r2 = 20, width2 = 2,
           oldx1 = x1, oldy1 = y1, oldx2 = x2, oldy2 = y2;

    COLORREF colorLine1 = RGB (255, 255,   0),
             colorFon1  = RGB ( 11, 206,   0),
             colorLine2 = RGB (155, 255, 155),
             colorFon2  = RGB (  0,  37, 205);

    while ((Distance (x1, y1, x2, y2) >= r1 + r2) && (!(txGetAsyncKeyState (VK_ESCAPE))))
        {
        if (txGetAsyncKeyState (VK_SPACE))
            {
            Vx1 = 0;
            Vy1 = 0;
            }

        oldx1 = x1, oldy1 = y1, oldx2 = x2, oldy2 = y2;

        BarrierArrow (&x1, &y1);
        Phisics      (&x1, &y1, &Vx1, &Vy1);

        DrawBall (x1, y1, r1, colorLine1, width1, colorFon1);

        BarrierWASZ  (&x2, &y2);
        Phisics      (&x2, &y2, &Vx2, &Vy2);

        DrawBall (x2, y2, r2, colorLine2, width2, colorFon2);

        txSleep (20);
        COLORREF colorWin;

        if (Distance (x1, y1, x2, y2) <= r1 + r2)
            {
            char win = '?';
            if (Distance (x1, y1, oldx1, oldy1) < Distance (x2, y2, oldx2, oldy2))
                {
                win = '1';
                colorWin = colorFon1;
                }
            else if (Distance (x1, y1, oldx1, oldy1) > Distance (x2, y2, oldx2, oldy2))
                    {
                    win = '2';
                    colorWin = colorFon2;
                    }
                 else
                    {
                    win = '0';
                    }
            txSetFillColor (TX_BLACK);
            txClear();

            char s[200] = "";
            sprintf (s, "... Game Over. Winner %c player", win);
            DrawText (50, 50, s, 42, TX_WHITE);


            DrawBall (x2, y2, r2*5, colorLine2, width2, colorWin);
            DrawText (x2, y2, "BOOM", 48, TX_GREEN);
            }
        }
    }

 void Phisics (double* x, double* y, double* Vx, double* Vy, double ax, double ay, bool Ftrenia, double dt, double r)
    {
    if (Ftrenia == true) { *Vx *= 0.999; }

    *x += (*Vx)*dt + ax*dt*dt/2;
    *y += (*Vy)*dt + ay*dt*dt/2;

    if (*x + r > X)
        {
        *x  = X - r;
        *Vx = -(*Vx);
        }
    if (*y + r > Y)
        {
        *y  = Y - r;
        *Vy = -(*Vy);
        }

    if (*x - r < 0)
        {
        *x  = r;
        *Vx = -(*Vx);
        }
    if (*y - r < 0)
        {
        *y  = r;
        *Vy = - (*Vy);
        }
    }

 void BarrierArrow (double* x, double* y)
    {
    if (txGetAsyncKeyState (VK_LEFT))   { *x -= 10; }
    if (txGetAsyncKeyState (VK_RIGHT))  { *x += 10; }
    if (txGetAsyncKeyState (VK_UP))     { *y -= 10; }
    if (txGetAsyncKeyState (VK_DOWN))   { *y += 10; }
    }

 void BarrierWASZ (double* x, double* y)
    {
    if (txGetAsyncKeyState ('A') || txGetAsyncKeyState ('a'))  { *x -= 10; }
    if (txGetAsyncKeyState ('D') || txGetAsyncKeyState ('d'))  { *x += 10; }
    if (txGetAsyncKeyState ('S') || txGetAsyncKeyState ('s'))  { *y += 10; }
    if (txGetAsyncKeyState ('W') || txGetAsyncKeyState ('w'))  { *y -= 10; }
    }

 void DrawBall (double x, double y, double r, COLORREF colorLine, double width, COLORREF colorFon)
    {
    txSetColor     (colorLine, width);
    txSetFillColor (colorFon);

    txCircle  (x, y, r);
    }

 double Distance (double x1, double y1, double x2, double y2)
    {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }

void DrawText(double x, double y, const char* text, int size, COLORREF color)
    {
    txSetColor (color);
    txSelectFont ("Times New Roman", size);
    txTextOut (x, y, text);
    }

