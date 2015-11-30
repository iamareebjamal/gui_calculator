/***** Mouse *****/

/*** Mouse Handling ***/

void detect() {
    int x, y;
    while (!keypressed()) {
        getmousebuttons(&x, &y);
        if (getpressevent()) clickLookup(whichButton(x, y));
        if (getreleaseevent()) normalize(prev);
        hoverLookup(x, y);
        delay(100);
    }
}

int initmouse() {
    i.x.ax = 0;
    int86(0X33,&i,&o);
    return ( o.x.ax );
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

void hidemouseptr() {
    i.x.ax = 2;
    int86(0X33,&i,&o);
}

void showmouseptr() {
    i.x.ax = 1;
    int86(0X33,&i,&o);
}

void getmousebuttons(int *x, int *y) {
    i.x.ax = 3;
    int86(0X33,&i,&o);
    *x = o.x.cx;
    *y = o.x.dx;
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

/*** Cartesian Boolean ***/

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
    return -90;
}

/*** Click Mapping ***/

void clickLookup(int id) {

    int doubleOp = (id>=14&&id<=17)&&(prev>=13&&prev<=17);
    int equalClr = (prev==13&&(id>=0&&id<=9));
    prev = id;

    if(id > 20 || id < 0) return;

    hover(id);

    if(equalClr)
        operation(12);

    if(doubleOp) {
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
    } else if(id>=11&&id<=17) {
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


/*** Handling Keyboard Interrupts ***/

void onKeyPress(int key) {
    clickLookup(key);
    delay(100);
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
        } else if(key=='p'){
            precision++;
            calc(13);
        } else if(key>='0'&&key<='9') {
            onKeyPress(key-'0');
        } else if (key=='+') {
            onKeyPress(17);
        } else if (key=='-') {
            onKeyPress(16);
        } else if (key=='*') {
            onKeyPress(15);
        } else if (key=='/') {
            onKeyPress(14);
        } else if (key=='='||key==13) {
            onKeyPress(13);
        } else if(key=='.') {
            onKeyPress(11);
        } else if (key==8) {
            onKeyPress(12);
        }

        return (key==27);
    } else
        return 0;
}

////////////////////////////////////////////////////////////////////////