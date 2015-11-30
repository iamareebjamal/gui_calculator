#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>

#define ABS(x) ((x)<0)?(0-(x)):(x)
#define APP_BAR_HEIGHT 40
#define SCREEN_HEIGHT  200

union REGS i, o;

/*
Rectangle - rectangle(left, top, right, bottom)
Circle    - circle(x, y, radius)
Text      - outtextxy(left, top, "Text")
*/

/*
IDs for lookup

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
12 - =
13 - C
14 - CE  // Cancelled
15 - /
16 - *
17 - -
18 - +

*/

int TOP, BOTTOM, RIGHT, MID_X, MID_Y, LEFT;

int RECT = 200, CIRC = 314;

void getmousebuttons(int*, int*);
void showmouseptr();
void hidemouseptr();

/* Themes */
///////////////////////////////////////////////

/* Default Theme */

int themesno = 3;

enum themes {
    DEFAULT_THEME =  0,
    DARK_GRAY      = 1,
};


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

void setThemeName(const char* name) {
    sprintf(themename, "%s", name);
}

void showToast() {
    setfillstyle(SOLID_FILL, 17);
    bar(MID_X-50, BOTTOM-150, MID_X+100, BOTTOM-100);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(MID_X, BOTTOM-130, themename);
    delay(250);
    setfillstyle(SOLID_FILL, BG_COLOR);
    bar(MID_X-50, BOTTOM-150, MID_X+100, BOTTOM-100);
}

void setTheme(int index) {
    hidemouseptr();
    switch(index) {
    case 0:                         //Default
        setThemeName("Default");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = WHITE;
        ROUND_BUTTON1_COLOR = 34;
        ROUND_BUTTON1_HOVER = WHITE;
        RB_TEXT = WHITE;
        RB_TEXT_HOVER = BLACK;
        SRB_TEXT = WHITE;
        SRB_TEXT_HOVER = 34;
        SQUARE_BUTTON_COLOR = 20;
        SQUARE_BUTTON_HOVER = 23;
        SB_TEXT = WHITE;
        SB_TEXT_HOVER = WHITE;
        SCREEN_COLOR = WHITE;
        SCREEN_TEXT_COLOR = DARKGRAY;
        break;
    case 1:                         //Light
        setThemeName("Light");
        BG_COLOR = 29;
        ROUND_BUTTON_COLOR = 25;
        ROUND_BUTTON_HOVER = WHITE;
        ROUND_BUTTON1_COLOR = 34;
        ROUND_BUTTON1_HOVER = WHITE;
        RB_TEXT = WHITE;
        RB_TEXT_HOVER = DARKGRAY;
        SRB_TEXT = WHITE;
        SRB_TEXT_HOVER = 34;
        SQUARE_BUTTON_COLOR = 27;
        SQUARE_BUTTON_HOVER = 22;
        SB_TEXT = 20;
        SB_TEXT_HOVER = WHITE;
        SCREEN_COLOR = 22;
        SCREEN_TEXT_COLOR = 29;
        break;
    case 2:                         //Darcula
        setThemeName("Darcula");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = 12;
        ROUND_BUTTON1_COLOR = 12;
        ROUND_BUTTON1_HOVER = 64;
        RB_TEXT = 12;
        RB_TEXT_HOVER = WHITE;
        SRB_TEXT = WHITE;
        SRB_TEXT_HOVER = 17;
        SQUARE_BUTTON_COLOR = 12;
        SQUARE_BUTTON_HOVER = 64;
        SB_TEXT = WHITE;
        SB_TEXT_HOVER = 17;
        SCREEN_COLOR = 23;
        SCREEN_TEXT_COLOR = 12;
        break;
    }
    showmouseptr();
}

///////////////////////////////////////////////


struct ButtonPositions {
    //Mode of Button
    int mode;
    //Circle
    int x, y, radius;
    char text;
    //Rect
    int xMin, xMax, yMin, yMax;
} buttons[20];



void setCircCoords(int index, char t, int x1, int y1, int r) {
    buttons[index].mode = CIRC;
    buttons[index].x = x1;
    buttons[index].y = y1;
    buttons[index].text = t;
    buttons[index].radius = r;
}

void setRectCoords(int index, char t, int x1, int y1, int x2, int y2) {
    buttons[index].mode=RECT;
    buttons[index].xMin = x1;
    buttons[index].xMax = x2;
    buttons[index].yMin = y1;
    buttons[index].yMax = y2;
    buttons[index].text = t;
}

/* App Bar */

void createCloseButton(int hover, int pressed) {
    if(hover) {
        hidemouseptr();
        setfillstyle(SOLID_FILL, LIGHTRED);
    } else if(pressed)
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
    else
        setfillstyle(SOLID_FILL, RED);
    bar(RIGHT-75, TOP, RIGHT, APP_BAR_HEIGHT);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);
    outtextxy(RIGHT-40, TOP+5, "x");

    setRectCoords(10, 'x', RIGHT-50, TOP, RIGHT, APP_BAR_HEIGHT); //Close ID 10
    showmouseptr();
}

void closeButton() {
    closegraph();
    exit(0);
}

void createAppBar() {
    setfillstyle(SOLID_FILL, 34);
    bar(LEFT, TOP, RIGHT, APP_BAR_HEIGHT);
    setfillstyle(SOLID_FILL, WHITE);
    bar(LEFT+10, TOP+8, LEFT+30, TOP+28);
    setfillstyle(SOLID_FILL, 34);
    bar(LEFT+12, TOP+13, LEFT+28, TOP+26);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);
    setcolor(WHITE);
    outtextxy(LEFT+40, TOP+7, "Calculator++");
    createCloseButton(0, 0);
}

/* Info Bar */

void createInfoBar() {
    setfillstyle(SOLID_FILL, 34);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    bar(0, BOTTOM-50, RIGHT, BOTTOM);
    outtextxy(20, BOTTOM-50, "Modes : m:Switch Theme | Enter:Evaluate | Backspace:Clear | 0~9:Enter Number | Esc:Quit                        Created by iamareebjamal");
    outtextxy(20, BOTTOM-30, "Licensed under GPL v2. All recources except BGI drivers are copyright of Areeb Jamal under GNU Public License");
}

/* Calculator Screen */

char message[20];

const char* toStr(double d) {
    sprintf(message, "%g", d);
    return message;
}

void clearScreen() {
    setfillstyle(SOLID_FILL, SCREEN_COLOR);
    bar(LEFT+40, APP_BAR_HEIGHT+40, RIGHT-120, SCREEN_HEIGHT);
}

void setText(const char* text) {
    clearScreen();
    setcolor(SCREEN_TEXT_COLOR);
    moveto(RIGHT-170, SCREEN_HEIGHT-SCREEN_HEIGHT/4);
    settextjustify(2,0);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
    outtext(text);
    settextjustify(0,2);
}

/* Button Matrix */

char getNumChar(int num) {
    return '0' + num;
}


int radius = 45;
int padX;
int padY;

void hoverRoundButton(char text, int x, int y) {
    int FORE=ROUND_BUTTON_HOVER, BACK=ROUND_BUTTON_COLOR;
    char s[1];
    sprintf(s, "%c", text);
    setcolor(RB_TEXT_HOVER);
    if(text=='.'||text=='=') {
        FORE = ROUND_BUTTON1_HOVER;
        BACK = ROUND_BUTTON1_COLOR;
        setcolor(SRB_TEXT_HOVER);
    }
    setfillstyle(SOLID_FILL, BACK);
    fillellipse(x, y, radius, radius);
    setfillstyle(SOLID_FILL, FORE);
    fillellipse(x, y, radius, radius);
    moveto(x-padX+3, y-padY+2);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
    outtext(s);
}


void normalRoundButton(char text, int x, int y) {
    int FORE=ROUND_BUTTON_COLOR, BACK=ROUND_BUTTON_HOVER;
    char s[1];
    sprintf(s, "%c", text);
    setcolor(RB_TEXT);
    if(text=='.'||text=='=') {
        FORE = ROUND_BUTTON1_COLOR;
        BACK = ROUND_BUTTON1_HOVER;
        setcolor(SRB_TEXT);
    }
    setfillstyle(SOLID_FILL, BACK);
    fillellipse(x, y, radius, radius);
    setfillstyle(SOLID_FILL, FORE);
    fillellipse(x, y, radius-2, radius-2);
    moveto(x-padX+3, y-padY+2);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
    outtext(s);
}

void createRoundButton(char text, int x, int y, int id) {
    normalRoundButton(text, x, y);
    setCircCoords(id, text, x, y, radius);
}

void createButtonMatrix() {
    int startX = LEFT + 450, startY = SCREEN_HEIGHT+100, i = 9, x, y;
    int padding = 200, j, k;
    x = startX;
    y = startY;

    padX = radius/4;
    padY = radius/2;

    for(j = 3; j > 0; j--) {
        for(k = 3; k > 0; k--) {
            createRoundButton(getNumChar(i), x, y, i);
            x+=padding;
            i--;
        }
        x =  startX;
        y += padding-50;
    }
    createRoundButton('.', x, y, 11);           //ID of . is 11
    x+=padding;
    createRoundButton(getNumChar(i), x, y, i); //ID of 0 is 0
    x+=padding;
    createRoundButton('=', x, y, 12);           //ID of = is 12

}

/* Operation Array */

int side = 100;

void squareButton(char text, int x, int y) {
    char str[1];
    str[0] = text;
    str[1] = '\0';
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
    bar(x, y, x+side, y+side);
    outtextxy(x+side/2-8, y+side/4, str);
}

void normalSquareButton(char text, int x, int y) {
    setcolor(SB_TEXT);
    setfillstyle(SOLID_FILL, SQUARE_BUTTON_COLOR);
    squareButton(text, x, y);
}

void hoverSquareButton(char text, int x, int y) {
    setcolor(SB_TEXT_HOVER);
    setfillstyle(SOLID_FILL, SQUARE_BUTTON_HOVER);
    squareButton(text, x, y);
}

void createSquareButton(char text, int x, int y, int id) {
    normalSquareButton(text, x, y);
    setRectCoords(id, text, x, y, x+side, y+side);
}

void createClearButton() {
    /*Clear Button*/
    radius = 25;
    padX= 10, padY = 25;
    createRoundButton('x', RIGHT-60, TOP+140, 13);
    radius = 45;
    padX= radius/4, padY = radius/2;
}

void createOperationButtons() {
    int startX = RIGHT-250, startY=SCREEN_HEIGHT+130, j;
    char op[4] = { 246, 'x', '-', '+'};
    for(j = 0; j<4; j++) {
        createSquareButton(op[j], startX, startY, 15+j);
        startY+=100;
    }
    createClearButton();
}

/* Cartesian Boolean */

int isInCircle(int xCoord, int yCoord, struct ButtonPositions circle) {
    int dx = ABS(xCoord-circle.x);
    int dy = ABS(yCoord-circle.y);

    if(dx >  circle.radius) return 0;

    if(dy >  circle.radius) return 0;

    if(dx+dy <= circle.radius) return 1;

    return(dx*dx + dy*dy <= circle.radius*circle.radius);
}

int isInRect(int x, int y, struct ButtonPositions rect) {
    return x>=rect.xMin&&x<=rect.xMax&&y>=rect.yMin&&y<=rect.yMax;
}

int whichButton(int x, int y) {
    int id;

    for(id=0; id<19; id++) {
        if(buttons[id].mode==RECT&&isInRect(x, y, buttons[id]))
            return id;
        if(buttons[id].mode==CIRC&&isInCircle(x, y, buttons[id]))
            return id;
    }
    return 90;
}

/* Mouse Initialization */

int initmouse() {
    i.x.ax = 0;
    int86(0X33,&i,&o);
    return ( o.x.ax );
}

void showmouseptr() {
    i.x.ax = 1;
    int86(0X33,&i,&o);
}

void hidemouseptr() {
    i.x.ax = 2;
    int86(0X33,&i,&o);
}

void restrictmouseptr(int x1, int y1, int x2, int y2) {
    i.x.ax = 7;
    i.x.cx = x1;
    i.x.dx = x2;
    int86(0X33,&i,&o);

    i.x.ax = 8;
    i.x.cx = y1;
    i.x.dx = y2;
    int86(0X33,&i,&o);
}

void getmousebuttons(int *x, int *y) {
    int86(0X33,&i,&o);
    *x = o.x.cx;
    *y = o.x.dx;
}

int getpressevent() {
    i.x.ax = 5;
    int86(0X33,&i,&o);
    return o.x.bx;
}

int getreleaseevent() {
    i.x.ax = 6;
    int86(0X33,&i,&o);
    return o.x.bx;
}

int prev = 666;

void hover(id) {
    hidemouseptr();

    if(id==13) {
        radius = 25;
        padX= 10, padY = 25;
    }

    if(buttons[id].mode==RECT)
        hoverSquareButton(buttons[id].text, buttons[id].xMin, buttons[id].yMin);
    if(buttons[id].mode==CIRC)
        hoverRoundButton(buttons[id].text, buttons[id].x, buttons[id].y);
    showmouseptr();
}

void normalize(int id) {
    hidemouseptr();

    if(buttons[id].mode==CIRC)
        normalRoundButton(buttons[id].text, buttons[id].x, buttons[id].y);
    if(buttons[id].mode==RECT)
        normalSquareButton(buttons[id].text, buttons[id].xMin, buttons[id].yMin);
    showmouseptr();

    radius = 45;
    padX= radius/4, padY = radius/2;
}

/* Calculator Logic */

long double res = 0;
long double input = 0;
int prevOp = 18;
int decimal_mode = 0;
float order = 0.1;

void calc(int id) {

    if(prevOp==18) {  //Add
        res=res+input;
    } else if(prevOp==17) {  //Subtract
        res=res-input;
    } else if(prevOp==16) {  //Multiply
        res=res*input;
    } else if(prevOp==15) {  //Divide
        res=res/input;
    }

    setText(toStr(res));
    input=0;
    decimal_mode=0;
    order=0.1;
    prevOp=id;
}

void operation(int id) {

    if(id==11) {
        decimal_mode=1;
    } else if(id==13) {  //Clear
        res=0;
        input=0;
        prevOp = 18;
        decimal_mode = 0;
        order=0.1;
        setText(toStr(res));
    } else {
        calc(id);
    }

}


/* Click Mapping */

void clickLookup(int id) {

    int doubleOp = (id>=15&&id<=18||id==12)&&(prev>=15&&prev<=18||prev==12);
    int equalClr = (prev==12&&(id>=0&&id<=9));
    prev = id;

    if(id > 20 || id < 0) return;

    hover(id);

    if(equalClr)
        operation(13);

    if(doubleOp) {
        if(id!=12)
            prevOp=id;
        return;
    }

    if(id==10) {
        createCloseButton(0, 1);
        closeButton();
    } else if(id>=0&&id<=9) {
        if(decimal_mode) {
            input+=order*id;
            order/=10;
        } else
            input=input*10+id;
        setText(toStr(input));
    } else if(id>=11&&id<=18) {
        operation(id);
    }


}

void hoverLookup(int x, int y) {
    int id = whichButton(x, y);

    if(id==10) {
        createCloseButton(1, 0);
    } else
        createCloseButton(0, 0);
    showmouseptr();
}

void makeCalculator();

int roll=1;

/* Handling Keyboard Interrupts */

void onKeyPress(int key) {
    clickLookup(key);
    delay(150);
    normalize(key);
}

int keypressed() {
    if(kbhit()) {
        char key = getch();
        if(key=='m') {
            if(roll>=themesno)
                roll=0;
            setTheme(roll);
            roll++;
            makeCalculator();
            showToast();
        } else if(key>='0'&&key<='9') {
            onKeyPress(key-'0');
        } else if (key=='+') {
            onKeyPress(18);
        } else if (key=='-') {
            onKeyPress(17);
        } else if (key=='*') {
            onKeyPress(16);
        } else if (key=='/') {
            onKeyPress(15);
        } else if (key=='='||key==13) {
            onKeyPress(12);
        } else if(key=='.') {
            onKeyPress(11);
        } else if (key==8) {
            onKeyPress(13);
        } else if(key==27) {
            closeButton();
        }
        return (key==27);
    } else
        return 0;
}

void detect() {
    int x, y;
    while (!keypressed()) {
        i.x.ax = 3;
        getmousebuttons(&x, &y);
        if (getpressevent()) clickLookup(whichButton(x, y));
        if (getreleaseevent()) normalize(prev);
        hoverLookup(x, y);
        delay(100);
    }
}

void makeCalculator() {
    hidemouseptr();
    cleardevice();
    setfillstyle(SOLID_FILL, BG_COLOR);
    bar(TOP, LEFT, RIGHT, BOTTOM);
    restrictmouseptr(TOP,LEFT,RIGHT-5,BOTTOM-5);
    /* App Bar */
    createAppBar();
    createInfoBar();
    /* Initialize Text */
    setText(message);
    /* Setup Buttons */
    createButtonMatrix();
    createOperationButtons();
    showmouseptr();
}



void splash() {
    int tri1[8] = {0, 0,   0, 0,   0, 0,   0, 0};
    tri1[2]=RIGHT;
    tri1[5]=BOTTOM;

    setfillstyle(SOLID_FILL, 56);
    bar(LEFT, TOP, RIGHT, BOTTOM);
    setfillstyle(SOLID_FILL, 34);
    setcolor(34);
    fillpoly(4, tri1);
    setfillstyle(SOLID_FILL, 103);
    setcolor(103);
    pieslice(MID_X, MID_Y-100, 50, 320, 60);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 9);
    outtextxy(MID_X+80, MID_Y-170, "++");
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
    outtextxy(MID_X-textwidth("Calculator++")/2, MID_Y, "Calculator++");
    settextstyle(8, HORIZ_DIR, 2);
    outtextxy(MID_X-textwidth("by iamareebjamal")/2, MID_Y+50, "by iamareebjamal");
    delay(2000);
}

int huge Mode() {
    return(6);
}

int main() {
    int gd = DETECT, gm, status;
    clrscr();
    installuserdriver("SVGA256M",Mode);
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    TOP    = 0;
    BOTTOM = getmaxy();
    RIGHT  = getmaxx();
    MID_X  = getmaxx()/2;
    MID_Y  = getmaxy()/2;
    LEFT   = 0;

    status = initmouse();


    if ( status == 0 )
        printf("Mouse support not available.\n");
    else {
        splash();
        makeCalculator();
        setText("0");
        detect();
    }

    getch();
    closegraph();
    return 0;
}