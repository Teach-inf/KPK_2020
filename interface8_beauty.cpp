
#include "TXLib.h"
#include <iostream>

const int Bubble    = 0,
          Selection = 1,
          Three     = 2,
          Clear     = 3,
          Exit      = 5,
          PrintBub  = 4;

const int X = 1000, Y = 650;

struct Button
    {
    int Number;
    double x, y, width, height;
    COLORREF colorFon, colorText;
    char* text;

    void Draw();                     // рисование кнопки
    bool  Belongs (POINT point);     // если щелчок мыши в области кнопки, то функция возвращает номер кнопки, иначе -1
    int SignClick();                 // проверка клика
    void  ActionClick();             // действия, если клик совершен (возвращает 1 для выхода, и 0 в остальных случаях)
    };

struct Array
    {
    int Data[1000];
    int SizeData;

    void RandomData();
    void PrintDataFile (char fileName[], char method[]);

    void BubbleSort (int* exchange, int* compare);
    void SelectionSort (int* exchange, int* compare);
    void PrintBeautyBubble();
    };

void ButtonsDraw   (Button Buttons[], int Size);
void ButtonsChoise (Button Buttons[], int Size);

void ClearScreen();
void DrawGrid();

void Analysis(int i);

void DrawPix (double x, double y, COLORREF color);
void DrawText (double x, double y, const char* text, int size, COLORREF color);

int main()
    {
    txCreateWindow (X, Y);

    txSetFillColor (RGB (32, 22, 118));
    txClear();

                        //Number         x     y width, height  цвет_фона_кнопки  цвет_текста  текст
    Button Buttons[6] = {{Bubble,    X - 170, 100, 130, 40, RGB(145, 255, 145), RGB(0, 0, 0), "Bubble"},
                         {Selection, X - 170, 170, 130, 40, RGB(145, 255, 145), RGB(0, 0, 0), "Selection"},
                         {Three,     X - 170, 240, 130, 40, RGB(145, 255, 145), RGB(0, 0, 0), "Three"},
                         {Clear,     X - 170, 310, 130, 40, RGB(145, 255, 145), RGB(0, 0, 0), "Clear"},
                         {PrintBub,  X - 170, 450, 130, 40, RGB(145, 255, 145), RGB(0, 0, 0), "Print Bubble"},
                         {Exit,      X - 170, 380, 130, 40, RGB(145, 255, 145), RGB(0, 0, 0), "Exit"},};

    ButtonsDraw   (Buttons, 6);
    ButtonsChoise (Buttons, 6);

    return 0;
    }

void Button :: Draw()
    {
    txSetColor (TX_WHITE, 4);
    txSetFillColor (colorFon);
    txRectangle (x, y, x + width, y + height);

    txSetColor (colorText);
    txSelectFont ("Times New Roman", 24, 10, 800);
    txTextOut (x + 3, y + 5, text);
    }

bool Button :: Belongs (POINT point)
    {
    return ((point.x > x) && (point.x < x + width) && (point.y > y) && (point.y < y + height));
    }

int  Button :: SignClick()
    {
    if ((Belongs(txMousePos())) && (txMouseButtons() == 1)) return Number;
    return -1;
    }

void Button :: ActionClick()
    {
    switch (Number)
        {
        case Bubble    : Analysis(Bubble);    break;
        case Selection : Analysis(Selection); break;
        case Three     : printf ("3");        break;
        case Clear     : ClearScreen();       break;
        case PrintBub  : Analysis(PrintBub);       break;
        //case Exit    : break;
        }
    }

void ButtonsDraw (Button Buttons[], int Size)
    {
    ClearScreen();
    for (int i = 0; i < Size; i++) Buttons[i].Draw();
    }

void ButtonsChoise (Button Buttons[], int Size)
    {
    while ((Buttons[Exit].SignClick() != Exit) && (!(txGetAsyncKeyState (VK_ESCAPE))))
        {
        int Choise = -1;
        for (int i = 0; i < Size; i++)
            {
            Choise = Buttons[i].SignClick();
            //printf ("%d\n", Choise);
            Buttons[Choise].ActionClick();
            txSleep(1);
            }
        }
    }

void ClearScreen()
    {
    int widthLine = 8;

    POINT point1 = { 50 - widthLine, 50 - widthLine },
          point2 = { 50 + (X - 200 - 120) / 2 + widthLine,  Y  - 50 + widthLine },
          point3 = { 100 + (X - 200 - 120) / 2 - widthLine, 50      - widthLine },
          point4 = { 100 + (X - 200 - 120)     + widthLine, Y  - 50 + widthLine };

    txSetFillColor (RGB (32, 22, 118));
    txSetColor (RGB (32, 22, 118), 0);
    txRectangle (point1.x-widthLine, point1.y-widthLine, point4.x+widthLine, point4.y+widthLine);

    txSetColor (TX_GRAY, widthLine);
    txSetFillColor (TX_BLACK);
    txRectangle (point1.x, point1.y, point2.x, point2.y);
    txRectangle (point3.x, point3.y, point4.x, point4.y);

    DrawGrid();
    }

void DrawGrid()
    {
    txSetColor (RGB (70, 70, 70));

    for (int i = 1; i< 28; i++)
        {
        txLine (50, Y - 50 - 20*i, 50 + (X - 200 - 120) / 2, Y - 50 - 20*i);
        txLine (100 + (X - 200 - 120) / 2, Y - 50 - 20*i, 100 + (X - 200 - 120), Y - 50 - 20*i);
        }

    for (int i = 1; i< 17; i++)
        {
        txLine (50 + 20*i, 50, 50 + 20*i, Y - 50);
        txLine (100 + (X - 200 - 120) / 2 + 20*i, 50, 100 + (X - 200 - 120) / 2 + 20*i, Y - 50);
        }

    txSetColor (TX_WHITE);
    txSelectFont ("Times New Roman", 24, 10, 200);
    txTextOut (70, Y - 30, "Кол-во обменов");
    txTextOut (120 + (X - 200 - 120) / 2, Y - 30, "Кол-во сравнений");

    txSelectFont ("Times New Roman", 14, 10, 10);
    txTextOut (10, 50, "300");
    txTextOut (20 + (X - 200 - 120)/2, Y - 40, "100");
    txTextOut (10 + 50 + (X - 200 - 120)/2, 50, "300");
    txTextOut (30 + 50 + (X - 200 - 120), Y - 40, "100");
    }

void Array :: RandomData()
    {
    for (int i = 0; i < SizeData; i++)
        {
        assert ((0 <= i) && (i < SizeData));
        Data[i] = rand()/1000*10 + i;
        //Data[i] = rand()/100;
        }
    }

void Array :: PrintDataFile(char fileName[], char method[])
    {
    FILE* file = fopen (fileName, method);
    if (!file) { printf ("Файл 12.txt не открыт. \n\n"); }
    else
        {
        fprintf (file, "\n\nData ");
        for (int i = 0; i < SizeData; i++)
            {
            assert (0 <= i && i < SizeData);
            fprintf (file, "[%d]     ", i);
            }

        fprintf (file, "\n  ");
        for (int i = 0; i < SizeData; i++)
            {
            assert (0 <= i && i < SizeData);
            fprintf (file, "%8d", Data[i]);
            }
        }
    fclose (file);
    }

void Array :: BubbleSort    (int* exchange, int* compare)
    {
    for (int i = SizeData - 1; i > 0; i--)
        {
        assert ((0 < i) && (i < SizeData));
        for (int j = 0; j < i; j++)
            {
            if (Data [j] > Data [j + 1])
                {
                int temp = Data [j];
                Data [j] = Data [j + 1];
                Data [j + 1] = temp;
                (*exchange) ++;
                }
            (*compare) ++;
             }
        }
    }

void Array :: SelectionSort (int* exchange, int* compare)
    {
    for (int i = 0; i < SizeData - 1; i++)
        {
        int minInd = i;
        for (int j = i + 1; j < SizeData; j++)
            {
            if (Data [j] < Data [minInd]) minInd = j;
            (*compare) ++;
            }
        int temp = Data [i];
        Data [i] = Data [minInd];
        Data [minInd] = temp;
        (*exchange) ++;
        }
    }

void Analysis(int i)
    {
    for (int j = 0; j < 100; j++)
        {
        Array massiv = {{}, 10 + j*5};
        massiv.RandomData();

        int exchange = 0,
            compare  = 0;

        switch (i)
            {
            case Bubble    : massiv.BubbleSort (&exchange, &compare);
                             DrawPix (50 + j, (Y - 50) - exchange/300, TX_LIGHTGREEN);
                             DrawPix (100 + (X - 200 - 120)/2 + j, Y - 50 - compare/300, TX_LIGHTGREEN);
                             break;
            case Selection : massiv.SelectionSort (&exchange, &compare);
                             DrawPix (50 + j, (Y - 50) - exchange/300, TX_LIGHTBLUE);
                             DrawPix (100 + (X - 200 - 120)/2 + j, Y - 50 - compare/300, TX_LIGHTBLUE);
                             break;
            case Three     : printf ("3"); break;
            case PrintBub  : if (massiv.SizeData == 10) massiv.PrintBeautyBubble(); break;
            }
        }
    }

void DrawPix (double x, double y, COLORREF color)
    {
    txSetColor (color);
    txSetFillColor (color);
    txCircle (x, y, 3);
    }

void Array :: PrintBeautyBubble()
    {
     txSetFillColor (TX_BLACK);
    int widthLine = 8;
    txSetColor (TX_GRAY, widthLine);

    double x1 = 50 - widthLine;
    double y1 = 50 - widthLine;
    double x2 = 100 + (X - 200 - 120) + widthLine;
    double y2 = Y  - 50 + widthLine;

    txRectangle (x1, y1, x2, y2);

    if (SizeData = 10)
        {
        for (int i = 0; i < SizeData; i++)
            {
            char s[100] = "";
            sprintf  (s, "[%d]", i);
            DrawText (x1 + 20 + i*70, y1 + 20, s, 12, TX_WHITE);
            sprintf  (s, "%d", Data[i]);
            DrawText (x1 + 20 + i*70, y1 + 35, s, 20, TX_LIGHTGREEN);
            }

        int compare = 0;
        for (int i = SizeData - 1; i > 0; i--)
            {
            assert ((0 < i) && (i < SizeData));
            for (int j = 0; j < i; j++)
                {
                if (Data [j] > Data [j + 1])
                    {
                    int temp = Data [j];
                    Data [j] = Data [j + 1];
                    Data [j + 1] = temp;
                    }
                }
            compare ++;

            int interval = 1;
            for (int i = 0; i < SizeData; i++)
                {

                char s[100] = "";
                sprintf  (s, "[%d]", i);
                DrawText (x1 + 20 + i*70, y1 + 50 + compare*25, s, 14, TX_WHITE);
                sprintf  (s, "%d", Data[i]);
                DrawText (x1 + 20 + i*70, y1 + 65 + compare*25, s, 20, TX_LIGHTGREEN);
                }
            compare ++;
            }
        }
    }

void DrawText (double x, double y, const char* text, int size, COLORREF color)
    {
    txSetColor (color);
    txSelectFont ("Times New Roman", size, 10, 20);
    txTextOut (x, y, text);
    }
