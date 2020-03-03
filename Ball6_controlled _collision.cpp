//controlled collision
//”правл€емое столкновение двух шаров


 #include "TXLib.h"

 #define X 800
 #define Y 600

 struct Ball
    {
    double  x,  y;
    double Vx, Vy;
    double ax, ay;
    double r;
    };

struct Drawww
    {
    COLORREF colorLine;
    double width;
    COLORREF colorFon;
    };

 void MoveBall (Ball ball1, Ball ball2);

 void Phisics  (Ball* ball, bool Ftrenia = false, double dt = 2);
 void DrawBall (Ball ball, Drawww coloring);

 void BarrierArrow (Ball* ball);
 void BarrierWASZ  (Ball* ball);

 double Distance (Ball ball1, Ball ball2);
 void DrawText (double x, double y, const char* text, int size, COLORREF color);

 int main()
    {
    txCreateWindow (X, Y);

    txSetFillColor (TX_BLACK);
    txClear();

    Ball ball1 = { 10,  10,  2, 5, 0, 0, 20};
    Ball ball2 = {700, 500, -3, 2, 0, 0, 20};
    Ball ball3 = {200, 200,  2, 2, 0, 0, 10};
    Ball ball4 = {700, 500, -3, 2, 0, 0, 20};

    MoveBall (ball1, ball2);

    return 0;
    }

void MoveBall (Ball ball1, Ball ball2)
    {
    double width1 = 2, width2 = 2,
           oldx1 = ball1.x, oldy1 = ball1.y, oldx2 = ball2.x, oldy2 = ball2.y;

    COLORREF colorLine1 = RGB (255, 255,   0),
             colorFon1  = RGB ( 11, 206,   0),
             colorLine2 = RGB (155, 255, 155),
             colorFon2  = RGB (  0,  37, 205);

    Drawww coloring1   = {RGB (255, 255,   0), 2, RGB ( 11, 206,   0)},
           coloring2   = {RGB (155, 255, 155), 2, RGB (  0,  37, 205)},
           coloringWin = {TX_RED, 5, TX_RED};

    while ((Distance (ball1, ball2) >= ball1.r + ball2.r) && (!(txGetAsyncKeyState (VK_ESCAPE))))
        {
        if (txGetAsyncKeyState (VK_SPACE))
            {
            ball1.Vx = 0;
            ball1.Vy = 0;
            ball2.Vx = 0;
            ball2.Vy = 0;
            }

        Ball old1 = ball1, old2 = ball2;

        BarrierArrow (&ball1);
        Phisics      (&ball1);

        DrawBall (ball1, coloring1);

        BarrierWASZ  (&ball2);
        Phisics      (&ball2);

        DrawBall (ball2, coloring2);

        txSleep (20);

        if (Distance (ball1, ball2) <= ball1.r + ball2.r)
            {
            char win = '?';
            if (Distance (ball1, old1) < Distance (ball2, old2))
                {
                win = '1';
                coloringWin.colorFon  = coloring1.colorFon;
                coloringWin.colorLine = coloring1.colorLine;
                }
            else if (Distance (ball1, old1) > Distance (ball2, old2))
                    {
                    win = '2';
                    coloringWin.colorFon  = coloring2.colorFon;
                    coloringWin.colorLine = coloring2.colorLine;
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

            ball2.r *= 5;
            DrawBall (ball2, coloringWin);
            DrawText (ball2.x - ball2.r/2, ball2.y, "BOOM", 48, TX_GREEN);
            }
        }
    }

 void Phisics (Ball* ball, bool Ftrenia, double dt)
    {
    if (Ftrenia == true) { (*ball).Vx *= 0.999; }

    (*ball).x += ((*ball).Vx)*dt + ((*ball).ax)*dt*dt/2;
    (*ball).y += ((*ball).Vy)*dt + ((*ball).ay)*dt*dt/2;

    if ((*ball).x + (*ball).r > X)
        {
        (*ball).x  = X - (*ball).r;
        (*ball).Vx = -((*ball).Vx);
        }
    if ((*ball).y + (*ball).r > Y)
        {
        (*ball).y  = Y - (*ball).r;
        (*ball).Vy = -((*ball).Vy);
        }

    if ((*ball).x - (*ball).r < 0)
        {
        (*ball).x  = (*ball).r;
        (*ball).Vx = -((*ball).Vx);
        }
    if ((*ball).y - (*ball).r < 0)
        {
        (*ball).y  = (*ball).r;
        (*ball).Vy = - ((*ball).Vy);
        }
    }

 void BarrierArrow (Ball* ball)
    {
    if (txGetAsyncKeyState (VK_LEFT))   { (*ball).x -= 10; }
    if (txGetAsyncKeyState (VK_RIGHT))  { (*ball).x += 10; }
    if (txGetAsyncKeyState (VK_UP))     { (*ball).y -= 10; }
    if (txGetAsyncKeyState (VK_DOWN))   { (*ball).y += 10; }
    }

 void BarrierWASZ (Ball* ball)
    {
    if (txGetAsyncKeyState ('A') || txGetAsyncKeyState ('a'))  { (*ball).x -= 10; }
    if (txGetAsyncKeyState ('D') || txGetAsyncKeyState ('d'))  { (*ball).x += 10; }
    if (txGetAsyncKeyState ('S') || txGetAsyncKeyState ('s'))  { (*ball).y += 10; }
    if (txGetAsyncKeyState ('W') || txGetAsyncKeyState ('w'))  { (*ball).y -= 10; }
    }

 void DrawBall (Ball ball, Drawww coloring)
    {
    txSetColor     (coloring.colorLine, coloring.width);
    txSetFillColor (coloring.colorFon);

    txCircle  (ball.x, ball.y, ball.r);
    }

 double Distance (Ball ball1, Ball ball2)
    {
    return sqrt((ball1.x - ball2.x)*(ball1.x - ball2.x) + (ball1.y - ball2.y)*(ball1.y - ball2.y));
    }

void DrawText(double x, double y, const char* text, int size, COLORREF color)
    {
    txSetColor (color);
    txSelectFont ("Times New Roman", size);
    txTextOut (x, y, text);
    }

