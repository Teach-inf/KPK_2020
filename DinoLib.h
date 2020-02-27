//! @file           DinoLib.cpp
//!
//! @mainpage
//!                 Главный герой динозавр
//!                 - @ref DrawDino()
//!                 - @ref DrawEgg()
//!
//! @par            Библиотека предназначена для работы с героями мира динозавров ...


//! @author         КПК Гербут Светлана
//!                 Dino v1.1

#include "TXLib.h"
#include <math.h>

//!                 Константа TX_LIGHTLIGHTBLUE создана для первой сцены
const COLORREF TX_LIGHTLIGHTBLUE = RGB (166, 220, 220);
//!                 Константа TX_DARKBLUE создана для второй сцены
const COLORREF TX_DARKBLUE       = RGB ( 85,  98, 168);

//! @brief          <b>Рисование динозавра </b>

//! @param          x         - координата по оси х
//! @param          у         - координата по оси у
//! @param          zoomX     - масштаб по оси х (<i> по умолчанию значение 1  соответсвует 100% </i>)
//! @param          zoomY     - масштаб по оси у (<i> по умолчанию значение 1  соответсвует 100% </i>)
//! @param          scallopUp - изменение высоты гребешка на заданное число точек по оси у
//!                             (отрицательные значения для уменьшения, положительные для увеличения высоты), <i> по умолчанию значение 0 точек </i>
//! @param          legs      - изменение положения ног относительно стандартного положения (<i> по умолчанию значение 0 точек </i>)
//! @param          mouth     - изменение степени расрытия пасти(<i> по умолчанию значение 0 точек </i>)
//! @param          tailDown  - изменение положения хвоста вверх/вниз (<i> по умолчанию значение 0 точек </i>)
//! @param          color     - цвет динозавра (<i> по умолчанию значение цвета TX_GREEN </i>)
void DrawDino (double x, double y, double zoomX = 1, double zoomY = 1, double scallopUp = 0, double legs = 0, double mouth = 0, double tailDown=0, COLORREF color = TX_GREEN);

//!                 <b> Рисование яйца </b>

//! @param          x     - координата по оси х
//! @param          у     - координата по оси у
//! @param          zoom  - масштаб (<i> значение 1  соответсвует 100% </i>)
//! @param          color - цвет скорлупы (<i> по умолчанию значение цвета TX_GREEN </i>)

void DrawEgg (double x, double y, double zoom, COLORREF color);

//!                <b> Рисование разбитого яйца  </b>

//! @param          x     - координата по оси х
//! @param          у     - координата по оси у
//! @param          zoom  - масштаб (<i> значение 1  соответсвует 100% </i>)
//! @param          color - цвет скорлупы (<i> по умолчанию значение цвета TX_GREEN </i>)
void DrawEggCrush (double x, double y, double zoom, COLORREF color);

//!                 <b> Рисование горы </b>

//! @param          x       - координата по оси х
//! @param          у       - координата по оси у
//! @param          zoom    - масштаб (<i> значение 1  соответсвует 100% </i>)
//! @param          volcano - логический параметр гора вулкан или нет (<i> по умолчанию значение <b>false</b> не вулкан </i>)
//! @param          summer  - логический параметр на горе цветочки (летом) или нет (<i> по умолчанию значение <b>false</b> не лето </i>)


void DrawMountain (double x, double y, double zoom, bool volcano = false, bool summer = false);

//!                 <b> Титры </b>
void DrawText (int x, int y, const char* text, int size, COLORREF color);

//!                 <b> Рисование солнца </b>
void DrawSun (double lengthRay, double zoom, int count, COLORREF color);

//!                 <b> Рисование лучей солнца </b>
void myLineRotate (double x, double y, double r, double alpha);


//!                 <b> Рисование фона </b>
void Background (double t);
void BackgroundBack (double t);

//!                 <b> Движение сцен</b>
void MoveTitle (const char* text, int T = 255);
void Move1 (int xFlag, int xT = 300);
void Move2 (int xFlag, int xT = 300);




void MoveTitle (const char* text, int T)
    {
    int t = 1;

    while (t <= T)
        {
        txSetFillColor (RGB (85, 185, t % 256));
        txClear();

        DrawText (800 - t*3, 30, text, 48, TX_GREEN);
        t++;

        txSleep (3);
        }

    }

void Move1 (int xFlag, int xT)
    {
    int t = xFlag;  xT += xFlag;
    while (t <= xT)
        {
        txSetFillColor (TX_LIGHTLIGHTBLUE);
        txClear();
        Background (t*0.3);

        DrawDino (800 - t*0.5, 400, 1, 1, abs(t%8 - 4)*3, abs(t%4 - 2)*10, 0, abs(t%4 - 2)*8, TX_GREEN);

        t++;
        txSleep (10);
        }

    xFlag = 800 - t;
    t = 1;
    while (t <= xT/5)
        {
        txSetFillColor (TX_LIGHTLIGHTBLUE);
        txClear();
        Background ((t + xFlag)*0.3);

        DrawEgg  (500 - t*0.1, 450, 0.5, TX_WHITE);

        DrawDino (xFlag - t/2 - t*0.5, 400, 1, 1, abs(t%8 - 4)*3, abs(t%4 - 2)*10, 0, abs(t%4 - 2)*8, TX_GREEN);

        t++;
        txSleep (10);
        }

    xFlag = 800 - xFlag - t;
    }

void Move2 (int xFlag, int xT)
    {
    int t = xFlag;  xT += xFlag;
    Background (t*0.3);
    while (t <= xT)
        {
        txSetFillColor (TX_DARKBLUE);
        txClear();
        BackgroundBack (t*0.3);

        DrawEggCrush  (500, 450, 0.5, TX_LIGHTGRAY);
        DrawDino (-100 + t*0.3, 400, 1, 1, abs(t%8 - 4)*3, abs(t%4 - 2)*10, 0, abs(t%4 - 2)*8, TX_GREEN);
        DrawDino (500 - t*0.3, 500, 0.3, 0.3, abs(t%100)*0.2,  abs(t%4 - 2)*10, 0, abs(t%4 - 2)*8, TX_LIGHTGREEN);
        DrawDino (600 - t*0.3, 550, 0.3, 0.3, abs(t%100)*0.2,  abs(t%4 - 2)*10, 0, abs(t%4 - 2)*8, TX_LIGHTGREEN);

        t++;
        txSleep (10);
        }

    xFlag += t;
    }

//-----------------------------------------------------------------------------

void Background (double t)
    {
    DrawSun  (200 + t*0.5, 1, 8, TX_YELLOW);
    DrawMountain (t-90 + t*0.5, 400, t/200, true, true );
    DrawMountain (t+100 + t*0.5, 400, t/200, true, false);
    }

void BackgroundBack (double t)
    {
    DrawSun  (200 - t*0.5, 1, 8, TX_YELLOW);
    DrawMountain (t - t*0.5, 400, t/200, true, true );
    DrawMountain (t - t*0.5, 400, t/200, true, false);
    }


//-----------------------------------------------------------------------------


void DrawDino (double x, double y, double zoomX, double zoomY, double scallopUp, double legs, double mouth, double tailDown, COLORREF color)
    {
    txSetFillColor (color);
    txSetColor (color, 1);

    txEllipse (x, y, x + 110*zoomX, y + 60*zoomY);
    txEllipse (x + 80*zoomX, y + 20*zoomY, x + 265*zoomX, y + 130*zoomY);
    txEllipse (x +  87*zoomX - legs/2, y + 116*zoomY, x + 135*zoomX - legs/2, y + 145*zoomY);
    txEllipse (x + 201*zoomX + legs/2, y + 119*zoomY, x + 252*zoomX + legs/2, y + 145*zoomY);

    txSetColor (color, 7);

    POINT Scallop[9] = {{ROUND(x + 19*zoomX), ROUND(y + 8*zoomY)}, {ROUND(x + 26*zoomX), ROUND(y - 17*zoomY - scallopUp)}, {ROUND(x + 40*zoomX), ROUND(y + 5*zoomY)}, {ROUND(x + 47*zoomX), ROUND(y - 22*zoomY - scallopUp)}, {ROUND(x + 56*zoomX), ROUND(y + 4*zoomY)}, {ROUND(x + 66*zoomX), ROUND(y - 16*zoomY - scallopUp)}, {ROUND(x + 75*zoomX), ROUND(y + 8*zoomY)}, {ROUND(x + 84*zoomX), ROUND(y - 11*zoomY - scallopUp)}, {ROUND(x + 90*zoomX), ROUND(y + 11*zoomY)}};
    txPolygon (Scallop, 9);

    POINT Tail[3] = {{ROUND(x + 245*zoomX), ROUND(y + 46*zoomY)}, {ROUND(x + 303*zoomX), ROUND(y + 3*zoomY + tailDown)}, {ROUND(x + 257*zoomX), ROUND(y + 66*zoomY)}};
    txPolygon (Tail, 3);

    txSetColor (TX_RED, 3);
    txSetFillColor (TX_RED);

    txEllipse (x + 12*zoomX, y + (47 - mouth)*zoomY, x + 40*zoomX, y + 55*zoomY);

    txSetColor (TX_BLACK, 2);
    txSetFillColor (TX_BLACK);
    txCircle  (x + 35*zoomX, y + 26*zoomY, 5*zoomX);
    }

//-----------------------------------------------------------------------------

void DrawEgg (double x, double y, double zoom, COLORREF color)
    {
    txSetColor (TX_BLACK, 7);
    txSetFillColor (color);

    txEllipse (x, y, x + 174*zoom, y + 244*zoom);

    txSetFillColor (TX_TRANSPARENT);

    POINT Egg[7] = {};
    double x1 = x + 4, x2 = x + 174, d = (x2 - x1) / 6;

    for (int i=0; i<7; i++)
        {
           Egg[i].x = ROUND(x1 + i*d*zoom);
           Egg[i].y = ROUND(y + 100*zoom + 30 * ((i+1)%2)*zoom);
        }

    HDC dc = txDC() ;
    Win32::Polyline (dc, Egg, 7);
    }

void DrawEggCrush (double x, double y, double zoom, COLORREF color)
    {
    txSetColor (TX_GREEN, 3);
    txSetFillColor (TX_GREEN);

    zoom *= 2; y += 100*zoom;
    POINT Scallop[9] = {{ROUND(x + 9*zoom), ROUND(y + 8*zoom)}, {ROUND(x + 16*zoom), ROUND(y - 17*zoom)}, {ROUND(x + 30*zoom), ROUND(y + 5*zoom)}, {ROUND(x + 37*zoom), ROUND(y - 22*zoom)}, {ROUND(x + 46*zoom), ROUND(y + 4*zoom)}, {ROUND(x + 56*zoom), ROUND(y - 16*zoom)}, {ROUND(x + 65*zoom), ROUND(y + 8*zoom)}, {ROUND(x + 74*zoom), ROUND(y - 11*zoom)}, {ROUND(x + 80*zoom), ROUND(y + 11*zoom)}};
    txPolygon (Scallop, 9);

    txSetColor (TX_BLACK, 7);
    txSetFillColor (color);

    y-=50*zoom; zoom/=2;
    txPie (x, y, x + 174*zoom, y + 244*zoom, 180, 180);
    POINT Egg[7];
    double d = 170 / 6;

    for (int i=0; i<7; i++)
        {
           Egg[i].x = ROUND(x + 4 + i*d*zoom);
           Egg[i].y = ROUND(y + 100*zoom + 30 * ((i+1)%2)*zoom);
        }

    HDC dc = txDC() ;
    Win32::Polyline (dc, Egg, 7);
    }

//-----------------------------------------------------------------------------

void DrawMountain(double x, double y, double zoom, bool volcano, bool summer)
    {
    txSetColor (TX_BLACK, 7);
    if (volcano == false) { txSetFillColor (TX_WHITE); }
        else { txSetFillColor (TX_RED); }

    POINT MountainTop[7] = {{ROUND(x), ROUND(y)}, {ROUND(x + 24*zoom), ROUND(y - 89*zoom)}, {ROUND(x + 55*zoom), ROUND(y + 8*zoom)}, {ROUND(x + 46*zoom), ROUND(y + 26*zoom)}, {ROUND(x + 30*zoom), ROUND(y)}, {ROUND(x + 13*zoom), ROUND(y + 29*zoom)}, {ROUND(x), ROUND(y)}};
    txPolygon (MountainTop, 7);

    txSetFillColor (TX_LIGHTGREEN);

    POINT MountainBottom[7] = {{ROUND(x - 48*zoom), ROUND(y + 169*zoom)}, {ROUND(x + 105*zoom), ROUND(y + 169*zoom)}, {ROUND(x + 55*zoom), ROUND(y + 8*zoom)}, {ROUND(x + 46*zoom), ROUND(y + 26*zoom)}, {ROUND(x + 30*zoom), ROUND(y)}, {ROUND(x + 13*zoom), ROUND(y + 29*zoom)}, {ROUND(x), ROUND(y)}};
    txPolygon (MountainBottom, 7);

    if (summer == true)
        {
        txSetColor (TX_RED, 3);
        txSetFillColor (TX_RED);
        txEllipse (x + 15*zoom, y +  50*zoom, x + 25*zoom, y +  60*zoom);
        txEllipse (x -  5*zoom, y +  70*zoom, x +  5*zoom, y +  80*zoom);
        txEllipse (x + 30*zoom, y +  85*zoom, x + 40*zoom, y +  95*zoom);
        txEllipse (x + 50*zoom, y + 100*zoom, x + 60*zoom, y + 110*zoom);
        txEllipse (x + 10*zoom, y + 130*zoom, x + 20*zoom, y + 140*zoom);
        }
    }

//-----------------------------------------------------------------------------

void DrawText(int x, int y, const char* text, int size, COLORREF color)
    {
    txSetColor (color);
    txSelectFont ("Times New Roman", size);
    txSetTextAlign (TA_CENTER);
    txTextOut (x, y, text);
    }

//-----------------------------------------------------------------------------

void DrawSun(double lengthRay, double zoom, int count, COLORREF color)
    {
    txSetColor (color, 3);
    txSetFillColor (color);
    zoom--;

    double r = 100 * zoom;
    txPie (700 - r, -100 - r, 900 + r, 100 + r, 180, 90);

    txSetColor (color, 6);

    r = r + lengthRay;
    double alpha = txPI / 2 / (count - 1);

    for (int i = 0; i < count; i++)
        {
        myLineRotate (800, 0, r, alpha*i);
        }
    }


//-----------------------------------------------------------------------------

void myLineRotate (double x, double y, double r, double alpha)
    {
    txLine (x, y, 800 - r * cos(alpha), r * sin(alpha));
    }
