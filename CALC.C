#include "variable.h"
#include "ui.c"
#include "mouse.c"

///////////////////////////////////////////////

int huge Mode() {
    return 6;
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

    closegraph();
    return 0;
}

////////////////////////////////////////////////////////////////////////

/***** Calculator Logic *****/

void calc(int id) {

    if(prevOp==17) {  //Add
        res=res+input;
    } else if(prevOp==16) {  //Subtract
        res=res-input;
    } else if(prevOp==15) {  //Multiply
        res=res*input;
    } else if(prevOp==14) {  //Divide
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
    } else if(id==12) {  //Clear
        res=0;
        input=0;
        prevOp = 17;
        decimal_mode = 0;
        order=0.1;
        setText(toStr(res));
    } else {
        calc(id);
    }

}