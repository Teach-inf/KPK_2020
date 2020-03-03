
#include "TXLib.h"

struct Coefficients
    {
    double k, n, b;
    };

void DrawGraphic(double (*func) (double x, Coefficients coef), COLORREF color);
void DrawAxes();
double SinKx (double x, Coefficients coef);
Coefficients ControlArrows (Coefficients* coef);

Coefficients SetCoeff ();


int main()
    {
    txCreateWindow (800, 600);
    DrawAxes();

    DrawGraphic(&SinKx, TX_LIGHTGREEN);

    return 0;
    }

// управление коэффициентами k, n функции f = n * sin (kx) + b
// Shift + стрелки вправо/влево для k,
// Shift + стрелки вверх/вниз для n

void DrawGraphic(double (*func) (double x, Coefficients coef), COLORREF color)
    {
    txSetColor (color);
    txSetFillColor (color);

    Coefficients coef = { 1, 1, 0 };
    //Coefficients coef = SetCoeff();

    for (int i = 0; (!(txGetAsyncKeyState (VK_ESCAPE))); i++)
        {
        coef = ControlArrows (&coef);
        double x = -10;
        while (x <= 10)
            {
            double y = (*func) (x, coef);
            txSetFillColor (TX_LIGHTGREEN);
            txCircle (400 + 50*x, 300 - 50*y, 3);
            x += 0.01;
            }
        if (GetAsyncKeyState (VK_SHIFT)) DrawAxes();
        }
    }


double SinKx (double x, Coefficients coef)
    {
    return coef.n * sin (coef.k * x) + coef.b;
    }

Coefficients SetCoeff ()
    {
    Coefficients coef;

    printf ("Введите значение коэффициентов для функции f = n * sin (kx) + b. В порядке: k, n, b \n");
    scanf  ("%lf%lf%lf", &coef.k, &coef.n, &coef.b);

    return coef;
    }

Coefficients ControlArrows (Coefficients* coef)
    {
    if (GetAsyncKeyState (VK_RIGHT)) (*coef).k += 0.3;
    if (GetAsyncKeyState (VK_LEFT))  (*coef).k -= 0.3;
    if (GetAsyncKeyState (VK_UP))    (*coef).n += 0.3;
    if (GetAsyncKeyState (VK_DOWN))  (*coef).n -= 0.3;

    return *coef;
    }

void DrawAxes()
    {
    txSetFillColor (TX_BLACK);
    txClear();
    txSetColor (TX_GRAY);
    txLine (800/2, 0, 800/2, 600);
    txLine (0, 600/2, 800, 600/2);
    txSetColor (TX_LIGHTGREEN);
    }

