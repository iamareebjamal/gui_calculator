#ifndef __VARIABLE_H
#define __VARIABLE_H

#include <conio.h>
#include <dos.h>
#include <graphics.h>

/*
IDs for click mapping

0  - 0
1  - 1
2  - 2
3  - 3
4  - 4
5  - 5
6  - 6
7  - 7
7  - 7
8  - 8
9  - 9
10 - Close
11 - .
12 - C
13 - =
14 - /
15 - *
16 - -
17 - +

*/

#define ABS(x) ((x)<0)?(0-(x)):(x)
#define APP_BAR_HEIGHT 40
#define SCREEN_HEIGHT  200

struct ButtonPositions {
    //Mode of Button
    int mode;
    //Circle
    int x, y, radius;
    char text;
    //Rect
    int xMin, xMax, yMin, yMax;
} buttons[20];



/* UI */

int TOP, BOTTOM, RIGHT, MID_X, MID_Y, LEFT;
int RECT = 200, CIRC = 314;
int radius = 45;
int side = 100;
int padX, padY;
int prev = -90;

char message[22];

void setText(const char* text);

void makeCalculator();

void hover(int id);
void normalize(int id);

void splash();
void clearScreen();
void closeButton();
void createAppBar();
void createInfoBar();
void createClearButton();
void createButtonMatrix();
void createOperationButtons();
void squareButton(char text, int x, int y);
void createCloseButton(int hover, int pressed);
void hoverRoundButton(char text, int x, int y);
void hoverSquareButton(char text, int x, int y);
void normalRoundButton(char text, int x, int y);
void normalSquareButton(char text, int x, int y);
void createRoundButton(char text, int x, int y, int id);
void createSquareButton(char text, int x, int y, int id);
void setCircCoords(int index, char t, int x1, int y1, int r);
void setRectCoords(int index, char t, int x1, int y1, int x2, int y2);

// Utils

const char* toStr(double ld);
char getNumChar(int num);


/* Mouse Interrupt Handling */

union REGS i, o;

void detect();
int initmouse();
int getpressevent();
int getreleaseevent();
void hidemouseptr();
void showmouseptr();
void clickLookup(int id);
void hoverLookup(int x, int y);
int whichButton(int x, int y);
void getmousebuttons(int *x, int *y);
void restrictmouseptr(int x1, int y1, int x2, int y2);

int isInRect(int x, int y, struct ButtonPositions rect);
int isInCircle(int xCoord, int yCoord, struct ButtonPositions circle);


//Keyboard Handling
int keypressed();
void onKeyPress(int key);


/* Calculator Logic */

long double res = 0;
long double input = 0;
int prevOp = 17;
int decimal_mode = 0;
int precision = 0;
float order = 0.1;

void calc(int id);
void operation(int id);

/* Themes */

int roll=1;
int themesno = 7;
char themename[20] = "Default Theme";

int BG_COLOR = 18;
int ROUND_BUTTON_COLOR = 17;
int ROUND_BUTTON_HOVER = WHITE;
int ROUND_BUTTON1_COLOR = 34;
int ROUND_BUTTON1_HOVER = WHITE;
int RB_TEXT = WHITE;
int RB_TEXT_HOVER = BLACK;
int SRB_TEXT = WHITE;
int SRB_TEXT_HOVER = BLACK;
int SQUARE_BUTTON_COLOR = 20;
int SQUARE_BUTTON_HOVER = 23;
int SB_TEXT = WHITE;
int SB_TEXT_HOVER = WHITE;
int SCREEN_COLOR = WHITE;
int SCREEN_TEXT_COLOR = DARKGRAY;

void showToast();
void setTheme(int index);
void setThemeName(const char* name);

#endif