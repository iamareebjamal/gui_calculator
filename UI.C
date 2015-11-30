/***** UI *****/

void makeCalculator() {
    hidemouseptr();
    cleardevice();
    setfillstyle(SOLID_FILL, BG_COLOR);
    bar(TOP, LEFT, RIGHT, BOTTOM);
    restrictmouseptr(TOP,LEFT,RIGHT-5,BOTTOM-5);
    /* App & Info Bar */
    createAppBar();
    createInfoBar();
    /* Initialize Text */
    setText(message);
    /* Setup Buttons */
    createButtonMatrix();
    createOperationButtons();
    showmouseptr();
}

/*** Calculator Screen ***/

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

/*** App Bar ***/

/* Close Button */

void closeButton() {
    closegraph();
    exit(0);
}

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

/* Info Bar */

void createInfoBar() {
    setfillstyle(SOLID_FILL, 34);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    bar(0, BOTTOM-50, RIGHT, BOTTOM);
    outtextxy(20, BOTTOM-50, "   Modes : m:Switch Theme | p:Toggle Precision Mode | Enter:Evaluate | Backspace:Clear | 0~9:Enter Number | Operators:operate | Esc:Quit");
    outtextxy(20, BOTTOM-30, "Licensed under GNU General Public License v2.                                           Created by Areeb Jamal, CS 2nd Year, ZHCET");
}

/* App Bar */

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

/*** Buttons ***/

/* Numbers and Operations */

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
    createRoundButton(getNumChar(i), x, y, i);  //ID of 0 is 0
    x+=padding;
    createRoundButton('=', x, y, 13);           //ID of = is 13
}

void createOperationButtons() {
    int startX = RIGHT-250, startY=SCREEN_HEIGHT+130, j;
    char op[4] = { 246, 'x', '-', '+'};
    for(j = 0; j<4; j++) {
        createSquareButton(op[j], startX, startY, 14+j);
        startY+=100;
    }
    createClearButton();
}

void createClearButton() {
    radius = 25;
    padX= 10, padY = 25;
    createRoundButton('x', RIGHT-60, TOP+140, 12);
    radius = 45;
    padX= radius/4, padY = radius/2;
}

/* Round Buttons and States */

void createRoundButton(char text, int x, int y, int id) {
    normalRoundButton(text, x, y);
    setCircCoords(id, text, x, y, radius);
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

/* Square Buttons and States */

void createSquareButton(char text, int x, int y, int id) {
    normalSquareButton(text, x, y);
    setRectCoords(id, text, x, y, x+side, y+side);
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

void squareButton(char text, int x, int y) {
    char str[1];
    str[0] = text;
    str[1] = '\0';
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
    bar(x, y, x+side, y+side);
    outtextxy(x+side/2-8, y+side/4, str);
}

/*** Mapping and Transitions ***/

/* Cartesian Setters */

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

/* State Transitions */

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

void hover(int id) {
    hidemouseptr();

    if(id==12) {
        radius = 25;
        padX= 10, padY = 25;
    }

    if(buttons[id].mode==RECT)
        hoverSquareButton(buttons[id].text, buttons[id].xMin, buttons[id].yMin);
    if(buttons[id].mode==CIRC)
        hoverRoundButton(buttons[id].text, buttons[id].x, buttons[id].y);
    showmouseptr();
}

/*** Splash Screen ***/

void splash() {
    int c;

    setfillstyle(SOLID_FILL, 34);
    bar(LEFT, TOP, RIGHT, BOTTOM);
    setcolor(34);
    setfillstyle(SOLID_FILL, 103);
    setcolor(103);
    setlinestyle(2,1,2);
    for(c=0;c<2*getmaxy()+30;c+=30){
        line(0, c, c, 0);
    }
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

/*** Utils ***/

const char* toStr(double d) {
    if(precision%2)
        sprintf(message, "%.20g", d);
    else
        sprintf(message, "%.7g", d);
    return message;
}

char getNumChar(int num) {
    return '0' + num;
}

////////////////////////////////////////////////////////////////////////


/* Themes */

void setThemeName(const char* name) {
    sprintf(themename, "%s", name);
}

void showToast() {
    setfillstyle(SOLID_FILL, ROUND_BUTTON1_COLOR);
    bar(MID_X-50, BOTTOM-150, MID_X+100, BOTTOM-100);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(MID_X, BOTTOM-130, themename);
    delay(500);
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
    case 1:                         //Darcula
        setThemeName("Darcula");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = 12;
        ROUND_BUTTON1_COLOR = 12;
        ROUND_BUTTON1_HOVER = 64;
        RB_TEXT = 12;
        RB_TEXT_HOVER = 17;
        SRB_TEXT = WHITE;
        SRB_TEXT_HOVER = 17;
        SQUARE_BUTTON_COLOR = 12;
        SQUARE_BUTTON_HOVER = 64;
        SB_TEXT = WHITE;
        SB_TEXT_HOVER = 17;
        SCREEN_COLOR = 23;
        SCREEN_TEXT_COLOR = 12;
        break;
    case 2:                         //Emerald
        setThemeName("Emerald");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = 51;
        ROUND_BUTTON1_COLOR = 51;
        ROUND_BUTTON1_HOVER = 75;
        RB_TEXT = 51;
        RB_TEXT_HOVER = 17;
        SRB_TEXT = 17;
        SRB_TEXT_HOVER = 23;
        SQUARE_BUTTON_COLOR = 51;
        SQUARE_BUTTON_HOVER = 75;
        SB_TEXT = 17;
        SB_TEXT_HOVER = 23;
        SCREEN_COLOR = 23;
        SCREEN_TEXT_COLOR = 51;
        break;
    case 3:                         //Blossom
        setThemeName("Blossom");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = 39;
        ROUND_BUTTON1_COLOR = 39;
        ROUND_BUTTON1_HOVER = 85;
        RB_TEXT = 39;
        RB_TEXT_HOVER = 17;
        SRB_TEXT = WHITE;
        SRB_TEXT_HOVER = 23;
        SQUARE_BUTTON_COLOR = 39;
        SQUARE_BUTTON_HOVER = 85;
        SB_TEXT = WHITE;
        SB_TEXT_HOVER = 23;
        SCREEN_COLOR = 23;
        SCREEN_TEXT_COLOR = 39;
        break;
    case 4:                         //Sunrise
        setThemeName("Sunrise");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = 41;
        ROUND_BUTTON1_COLOR = 41;
        ROUND_BUTTON1_HOVER = 65;
        RB_TEXT = 41;
        RB_TEXT_HOVER = 17;
        SRB_TEXT = WHITE;
        SRB_TEXT_HOVER = 23;
        SQUARE_BUTTON_COLOR = 41;
        SQUARE_BUTTON_HOVER = 65;
        SB_TEXT = WHITE;
        SB_TEXT_HOVER = 23;
        SCREEN_COLOR = 23;
        SCREEN_TEXT_COLOR = 41;
        break;
    case 5:                         //Sky
        setThemeName("Sky");
        BG_COLOR = 18;
        ROUND_BUTTON_COLOR = 17;
        ROUND_BUTTON_HOVER = 53;
        ROUND_BUTTON1_COLOR = 53;
        ROUND_BUTTON1_HOVER = 77;
        RB_TEXT = 53;
        RB_TEXT_HOVER = 17;
        SRB_TEXT = 17;
        SRB_TEXT_HOVER = 23;
        SQUARE_BUTTON_COLOR = 53;
        SQUARE_BUTTON_HOVER = 77;
        SB_TEXT = 17;
        SB_TEXT_HOVER = 23;
        SCREEN_COLOR = 23;
        SCREEN_TEXT_COLOR = 53;
        break;
    case 6:                         //Light
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
    }
    showmouseptr();
}

////////////////////////////////////////////////////////////////////////