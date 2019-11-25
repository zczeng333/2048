#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
void drawfield(double xc,double yc,double cl);
int main(){
	double x0, y0,xc,yc,cl;
    int x, i, j, count=1, temp, fulltemp;
    int laz;
	x0 = GetWindowWidth() ;
    y0 = GetWindowHeight();
    cl=y0*0.2;
    xc=x0-cl*4.5;
    yc=0.1*y0;
    drawfield(xc,yc,cl);
} 

void drawfield(double xc,double yc,double cl)
{
	int i;
	for(i=0;i<=4;i++){
		MovePen(xc+i*cl,yc);
		DrawLine(0,4*cl);
		MovePen(xc,yc+i*cl);
		DrawLine(4*cl,0);
	}
}
