#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include<conio.h>//方向键输入 
#define Key_Up 0x4800    // 向上方向键 　　 
#define Key_Down 0x5000  // 向下方向键 
#define Key_Right 0x4d00  // 向右方向键 
#define Key_Left 0x4b00   // 向左方向键 

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h> //用到了time函数

int game[16];//游戏数组
int forgame[16];
int record[16];//游戏记录数组  
int forrecord[16]; 
int score,lastscore=0;//计分     
void comenumber();//产生2或4   line914           
int random1();//产生随机数     line582
int random2();//产生随机数     line593
void directW();//上移函数      line601
void directA();//左移函数      line618
void directS();//下移函数      line635
void directD();//右移函数      line688
void addW();//上合并函数       line741
void addA();//左合并函数       line759
void addS();//下合并函数       line777
void addD();//右合并函数       line795
int judgeW();//上移判断函数    line813
int judgeA();//左移判断函数    line829
int judgeS();//下移判断函数    line845
int judgeD();//右移判断函数    line861
void print();//输出函数        line877
int over();//判断游戏是否结束  line901
char direct; 

void drawnum1(int a, double x, double y,double l);  // create number 2,4,8                           line199 
void drawnum2(int a, double x, double y,double l);  // create number 16,32,64                        line256
void drawnum3(int a, double x, double y,double l);  // create number 128,256,512                     line336
void drawnum4(int a, double x, double y,double l);  // create number 1024,2048,4096                  line426
void creatnum(int num, double x,double y,double l); // used together with drawcube to put numbers into the field line536
void drawcube(int a,int num,double x,double y, double l); //                    line 555
void leaveout();                                    // to clear out the field   line569
void drawfield(double xc,double yc,double cl);       //to draw the field        Line 188

void KeyboardEventProcess(int key,int event);                 // line 928
void MouseEventProcess(int x, int y, int button, int event);  // Line 135

void countscore();  //to sum up the score line997
void exam();        //to exam whether you have got 2048 Line1023
void leaveout_0();  //to restart Line103 
void draw_back();   // the restart button  Line 168
void drawexit();    // the exit button     Line 178
void turnback();
void forgive();

double x0, y0, xc, yc, cl;
int x, i, j, count=1, temp, fulltemp;
int laz;  	 
int isforgive=0;

void Main()
{
	srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样
    InitGraphics();
//    InitConsole();
    
    x0 = GetWindowWidth() ;
    y0 = GetWindowHeight();
    
    cl=y0*0.2;
    xc=x0-cl*4.5;
    yc=0.1*y0;
    
   	for(i=0;i<16;i++)
	{
	    game[i]=0;
	    record[i]=0;
    }
	x=random2();
	game[x]=random1();
	record[x]=1;
	comenumber();
    drawfield(xc,yc,cl);
	for(i=0;i<16;i++){
	    laz=game[i];
	    drawcube(i,laz,xc,yc,cl);
    }
    
    draw_back();
    drawexit();
    turnback();
    
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
}

void leaveout_0(){
	
	StartFilledRegion(0.99);
    SetPenColor("White");
    MovePen(0.2*x0,0.39*y0);
    DrawLine(0.6*x0,0);
    DrawLine(0,0.22*y0);
    DrawLine(-0.6*x0,0);
    DrawLine(0,-0.22*y0);
    EndFilledRegion();
    
    leaveout();
    
	for(i=0;i<16;i++)
	{
	    game[i]=0;
	    record[i]=0;
	    forgame[i]=0;
    }
	x=random2();
	forgame[x]=game[x]=random1();
	record[x]=1;
	comenumber();
	
    drawfield(xc,yc,cl);

	for(i=0;i<16;i++){
    		laz=forgame[i];
    		drawcube(i,laz,xc,yc,cl);
    	}
    	
    score=0;
    lastscore=score;
    countscore();
    SetPenColor("Black");
    turnback();
}

void MouseEventProcess(int x, int y, int button, int event){
//    printf("%d %d\n",x,y);
	if(event==MOUSEMOVE){
		if((x>=360&&x<=423)&&(y>=636&&y<=660)){
			SetPenColor("Blue");
			MovePen(xc+0.1*cl,yc-0.35*cl);
            DrawTextString("restart");
            SetPenColor("Black");
		    }
		else if((x>=840&&x<=893)&&(y>=636&&y<=660)){
			SetPenColor("Blue");
			MovePen(xc+3.7*cl,yc-0.35*cl);
            DrawTextString("Exit");
            SetPenColor("Black");
		    }
		else{
			MovePen(xc+0.1*cl,yc-0.35*cl);
            DrawTextString("restart");
            MovePen(xc+3.7*cl,yc-0.35*cl);
            DrawTextString("Exit");
		}
	 }
	 if(event==BUTTON_DOWN&&button==LEFT_BUTTON){
		if((x>=360&&x<=423)&&(y>=636&&y<=660))
			leaveout_0();
		else if((x>=840&&x<=893)&&(y>=636&&y<=660))
			ExitGraphics();
		else if((x>=67&&x<=336)&&(y>=134&&y<=403)){
			forgive();
		}
		else;
		}
	 
    
}


void draw_back(){
     MovePen(xc+0.5*cl,yc-0.4*cl);
     DrawLine(0,cl/6);
     DrawLine(-0.45*cl,0);
     DrawLine(0,-cl/6);
     DrawLine(0.45*cl,0);
     MovePen(xc+0.1*cl,yc-0.35*cl);
     DrawTextString("restart");	
}

void drawexit(){
    MovePen(xc+4*cl,yc-0.4*cl);
    DrawLine(0,cl/6);
    DrawLine(-0.4*cl,0);
    DrawLine(0,-cl/6);
    DrawLine(0.4*cl,0);
    MovePen(xc+3.7*cl,yc-0.35*cl);
    DrawTextString("Exit");
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

void drawnum1(int a, double x, double y,double l)
{
	double nx , ny, nl;
	int siz;
	
	siz=GetPenSize();
	
	nx=x+0.25*l;
	ny=y+0.1*l;
	nl=0.45*l;
	if(a==2)
	{
		SetPenSize(10);
		MovePen(nx+nl,ny);
		DrawLine(-nl,0);
        DrawLine(0.9*nl,nl);
        DrawArc(0.5*nl,-30,200);
	}
	else if(a==4){
		StartFilledRegion(0.2);
    	SetPenColor("Brown");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(10);
		MovePen(nx+0.4*nl,ny+1.8*nl);
		DrawLine(-0.5*nl,-1.2*nl);
		DrawLine(1.4*nl,0);
		MovePen(nx+0.9*nl,ny-0.1*nl);
		DrawLine(0,1.9*nl);
	}
	else if(a==8)
	{
		StartFilledRegion(0.2);
    	SetPenColor("Orange");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(10);
		MovePen(nx+0.5*nl,ny+0.9*nl);
		DrawArc(0.5*nl,-90,360);
		DrawArc(0.5*nl,90,360);
	}
	else;
	SetPenSize(siz);
}



void drawnum2(int a, double x, double y,double l)
{
     double x1 , x2, ny, nl;	
	int siz;
	
	siz=GetPenSize();
	
	nl=0.35*l;
	ny=y+0.15*l;
	x1=x+0.1*l;
	x2=x+0.55*l;
	
	if(a==16)
	{
		StartFilledRegion(0.8);
    	SetPenColor("Orange");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(8);
		MovePen(x1+0.5*nl,ny);
		DrawLine(0,2*nl);           /*1*/
		
		MovePen(x2-0.2*nl,ny+0.5*nl);
        DrawArc(0.6*nl,180,360);
        DrawLine(0,nl);
        DrawArc(0.6*nl,180,-180);   /*6*/
	}
	else if(a==32)
	{
		StartFilledRegion(0.2);
    	SetPenColor("Red");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(8);
		MovePen(x1+0.4*nl,ny+nl);
        DrawArc(0.5*nl,-100,240);
        MovePen(x1+0.4*nl,ny+nl);
        DrawArc(0.5*nl,100,-240);  /*3*/
        
		MovePen(x2+nl,ny+0.1*nl);
		DrawLine(-nl,0);
        DrawLine(0.9*nl,1.1*nl);
        DrawArc(0.5*nl,-30,200);   /*2*/
	}
	else if(a==64){
		StartFilledRegion(0.2);
    	SetPenColor("Green");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(7);
		MovePen(x1-0.05*nl,ny+0.5*nl);
        DrawArc(0.6*nl,180,360);
        DrawLine(0,nl);
        DrawArc(0.6*nl,180,-180);    /*6*/
		
		MovePen(x2+0.4*nl,ny+2.1*nl);
		DrawLine(-0.4*nl,-1.2*nl);
		DrawLine(1.1*nl,0);
		MovePen(x2+0.8*nl,ny);
		DrawLine(0,2.1*nl);      /*4*/
	}
	else;
	SetPenSize(siz);
}

void drawnum3(int a, double x, double y,double l)
{
	double x1,x2, x3, ny, nl;
	int siz;
	siz=GetPenSize();
	nl=l*0.25;
	x1=x+0.07*l;
	x2=x1+0.3*l;
	x3=x2+0.3*l;
	ny=y+0.25*l;
	
	if(a==128)
	{
		StartFilledRegion(0.2);
    	SetPenColor("Blue");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(5);
		MovePen(x1+0.2*nl,ny);
		DrawLine(0,1.8*nl);     /*1*/
		MovePen(x2+0.8*nl,ny);
		DrawLine(-nl,0);
        DrawLine(0.9*nl,1.1*nl);
        DrawArc(0.5*nl,-30,200);        /*2*/
		MovePen(x3,ny);
		MovePen(x3+0.4*nl,ny+0.9*nl);
		DrawArc(0.5*nl,-90,360);
		DrawArc(0.5*nl,90,360);      /*8*/
	}
	else if(a==256)
	{
		StartFilledRegion(0.2);
    	SetPenColor("Gray");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(5);
		MovePen(x1+nl,ny);
		DrawLine(-nl,0);
        DrawLine(0.9*nl,1.1*nl);
        DrawArc(0.5*nl,-30,200);      /*2*/
		
		MovePen(x2,ny+0.1*nl);
        DrawArc(0.6*nl,-130,260);
		DrawLine(0,0.8*nl);
		DrawLine(0.8*nl,0);                           /*5*/
		
		MovePen(x3,ny+0.5*nl);
        DrawArc(0.55*nl,180,360);
        DrawLine(0,0.8*nl);
        DrawArc(0.55*nl,180,-180);     /*6*/
	}
	else if(a==512)
	{
		StartFilledRegion(0.9);
    	SetPenColor("Blue");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(5);
		MovePen(x1+0.1*nl,ny+0.1*nl);
        DrawArc(0.6*nl,-130,260);
		DrawLine(0,0.8*nl);
		DrawLine(0.8*nl,0);      /*5*/
		
		MovePen(x2+0.5*nl,ny);
		DrawLine(0,1.9*nl);      /*1*/
		
		MovePen(x3+0.9*nl,ny+0.1*nl);
		DrawLine(-nl,0);
        DrawLine(0.9*nl,1.1*nl);
        DrawArc(0.5*nl,-30,200);      /*2*/
	}
	else;
	SetPenSize(siz);
}

void drawnum4(int a, double x, double y,double l)
{
	double x1, x2, x3, x4, ny, nl;
	int siz;
	siz=GetPenSize();
	nl=0.2*l;
	x1=x+0.04*l;
	x2=x1+0.24*l;
	x3=x2+0.24*l;
	x4=x3+0.24*l;
	ny=y+0.3*l;
	
	if(a==1024)
	{
		StartFilledRegion(0.9);
    	SetPenColor("Green");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(5);
	    MovePen(x1+0.5*nl,ny);
	    DrawLine(0,2.2*nl);      /*1*/	
	
	    MovePen(x2-0.2*nl,ny+0.4*nl);
        DrawArc(0.4*nl,-180,180);
        DrawLine(0,1.4*nl);
        DrawArc(0.4*nl,0,180);
        DrawLine(0,-1.4*nl);     /*0*/
	
	    MovePen(x3+0.8*nl,ny+0.1*nl);
		DrawLine(-1.1*nl,0);
        DrawLine(1.1*nl,1.3*nl);
        DrawArc(0.55*nl,-30,200);      /*2*/
	
	    MovePen(x4+0.2*nl,ny+2.2*nl);
		DrawLine(-0.4*nl,-1.4*nl);
		DrawLine(1.1*nl,0);
		MovePen(x4+0.7*nl,ny);
		DrawLine(0,2.2*nl);        /*4*/
	}
	else if(a==2048)
	{
		StartFilledRegion(0.9);
    	SetPenColor("Red");
    	MovePen(x,y);
    	DrawLine(cl,0);
    	DrawLine(0,cl);
    	DrawLine(-cl,0);
    	DrawLine(0,-cl);
    	EndFilledRegion();
    	SetPenColor("Black");
    	SetPenSize(5);
	    MovePen(x1+nl,ny);
 		DrawLine(-1.1*nl,0);
        DrawLine(1.1*nl,1.3*nl);
        DrawArc(0.55*nl,-30,200);        /*2*/
	 
	    MovePen(x2+0.1*nl,ny+0.3*nl);
        DrawArc(0.4*nl,-180,180);
        DrawLine(0,1.4*nl);
        DrawArc(0.4*nl,0,180);
        DrawLine(0,-1.4*nl);     /*0*/	
  	 
  	    MovePen(x4-0.85*nl,ny+2.1*nl);
		DrawLine(-0.4*nl,-1.4*nl);
		DrawLine(1.1*nl,0);
		MovePen(x4-0.35*nl,ny-0.1*nl);
		DrawLine(0,2.2*nl);        /*4*/
	 
	    MovePen(x4,ny);
		MovePen(x4+0.6*nl,ny+nl);
		DrawArc(0.6*nl,-90,360);
		DrawArc(0.6*nl,90,360);       /*8*/
	}
	else if(a==4096){
		MovePen(x1+0.4*nl,ny+2.1*nl);
		DrawLine(-0.4*nl,-1.4*nl);
		DrawLine(1.1*nl,0);
		MovePen(x1+0.9*nl,ny-0.1*nl);
		DrawLine(0,2.2*nl);      /*4*/
		
		MovePen(x2+0.1*nl,ny+0.2*nl);
        DrawArc(0.4*nl,-180,180);
        DrawLine(0,1.5*nl);
        DrawArc(0.4*nl,0,180);
        DrawLine(0,-1.5*nl);      /*0*/	
  	    
  	    MovePen(x3+nl,ny+1.3*nl);
  	    DrawLine(0,0.3*nl);
		DrawArc(0.5*nl,0,180);
  	    DrawLine(0,-0.3*nl);
  	    DrawArc(0.5*nl,-180,180);
  	    DrawLine(0,-1.1*nl);
  	    DrawArc(0.5*nl,0,-180);   /*9*/
  	    
  	    MovePen(x4+0.05*nl,ny+0.5*nl);
        DrawArc(0.5*nl,180,-180);
        DrawLine(0,-0.3*nl);
        DrawArc(0.5*nl,0,-180);
        DrawLine(0,0.3*nl);
        DrawLine(0,1.1*nl);
        DrawArc(0.5*nl,180,-180);   /*6*/
	}
}


void creatnum(int num, double x,double y,double l)
{
	switch(num){
		case 2:    drawnum1(2,x,y,l);    break;
		case 4:    drawnum1(4,x,y,l);    break;
	    case 8:    drawnum1(8,x,y,l);    break;
	    case 16:   drawnum2(16,x,y,l);   break;
	    case 32:   drawnum2(32,x,y,l);   break;
	    case 64:   drawnum2(64,x,y,l);   break;
	    case 128:  drawnum3(128,x,y,l);  break;
	    case 256:  drawnum3(256,x,y,l);  break;
	    case 512:  drawnum3(512,x,y,l);  break;
	    case 1024: drawnum4(1024,x,y,l); break;
	    case 2048: drawnum4(2048,x,y,l); break;
	    case 4096: drawnum4(4096,x,y,l); break;
	    default:  ;
	}
}

void drawcube(int a,int num,double x,double y, double l)
{
	int px, py;
	double xr,yr;	
	SetPenColor("Black");
	px=a%4;
	py=3-a/4;
	
	xr=x+px*l;
	yr=y+py*l;
	
	creatnum(num,xr,yr,l);
}

void leaveout(){
	StartFilledRegion(0.99);
    SetPenColor("White");
    MovePen(xc,yc);
    DrawLine(4*cl,0);
    DrawLine(0,4*cl);
    DrawLine(-4*cl,0);
    DrawLine(0,-4*cl);
    EndFilledRegion();
    SetPenColor("Black");
    drawfield(xc,yc,cl);
}

int random1()//随机产生数字2或4，数字2产生概率80%，数字4产生概率20% 
{ 
   int i,number;
  
   number = rand() % 10; //随机产生1或2
   if(number<9)
        return 2;
   else 
        return 4;
}

int random2()//随机产生数组中的坐标
{ 
   int i,number;

   number = rand() % 16;//随机产生0到15的随机数 
   return number;
}

void directW()
{
    int i, j;
	for(i=4;i<16;i++)
	{
		j=i;
		while(record[j-4]==0&&record[j]!=0&&j>3)
		{
			game[j-4]=game[j];
			game[j]=0;
			record[j-4]=1;
			record[j]=0;
			j=j-4;
		}
	}
}

void directS()
{
	int i, j; 
	for(i=11;i>=0;i--)
	{
		j=i;
		while(record[j+4]==0&&record[j]!=0&&j<12)
		{
			game[j+4]=game[j];
			game[j]=0;
			record[j+4]=1;
			record[j]=0;
			j=j+4;
		}
	}
}

void directA()
{
	int i, j; 
	for(i=1;i<4;i++)
	{
		j=i;
		while(record[j-1]==0&&record[j]!=0&&j>0)
		{
			game[j-1]=game[j];
			game[j]=0;
			record[j-1]=1;
			record[j]=0;
			j=j-1;
		}
	}
	for(i=5;i<8;i++)
	{
		j=i;
		while(record[j-1]==0&&record[j]!=0&&j>4)
		{
			game[j-1]=game[j];
			game[j]=0;
			record[j-1]=1;
			record[j]=0;
			j=j-1;
		}
	}
	for(i=9;i<12;i++)
	{
		j=i;
	    while(record[j-1]==0&&record[j]!=0&&j>8)
		{
			game[j-1]=game[j];
			game[j]=0;
			record[j-1]=1;
			record[j]=0;
			j=j-1;
		}
	}
	for(i=13;i<16;i++)
	{
		j=i;
		while(record[j-1]==0&&record[j]!=0&&j>12)
		{
			game[j-1]=game[j];
			game[j]=0;
			record[j-1]=1;
			record[j]=0;
			j=j-1;
		}
	}
}

void directD()
{
	int i, j;       
	for(i=2;i>=0;i--)
	{
		j=i;
		while(record[j+1]==0&&record[j]!=0&&j<3)
		{
			game[j+1]=game[j];
			game[j]=0;
			record[j+1]=1;
			record[j]=0;
			j=j+1;
		}
	}
	for(i=6;i>=4;i--)
	{
		j=i;
		while(record[j+1]==0&&record[j]!=0&&j<7)
		{
			game[j+1]=game[j];
			game[j]=0;
			record[j+1]=1;
			record[j]=0;
			j=j+1;
		}
	}
	for(i=10;i>=8;i--)
	{
		j=i;
		while(record[j+1]==0&&record[j]!=0&&j<11)
		{
			game[j+1]=game[j];
			game[j]=0;
			record[j+1]=1;
			record[j]=0;
			j=j+1;
		}
	}
	for(i=14;i>=12;i--)
	{
		j=i;
		while(record[j+1]==0&&record[j]!=0&&j<15)
		{
			game[j+1]=game[j];
			game[j]=0;
			record[j+1]=1;
			record[j]=0;
			j=j+1;
		}
	}
}

void addW()
{
	int i, j;
	for(j=0;j<4;j++)
	for(i=j;i<=j+12;i=i+4)
	{
		if(game[i]==game[i-4]&&game[i]!=0)
		{
			game[i]=0;
			game[i-4]=2*game[i-4];
			score=score+game[i-4];
			record[i]=0;
			i=i-4;
		}
	}
	directW();
}

void addA()
{
	int i, j;
	for(j=0;j<4;j++)
	for(i=4*j;i<=3+4*j;i++)
	{
		if(game[i]==game[i-1]&&game[i]!=0)
		{
			game[i]=0;
			game[i-1]=2*game[i-1];
			score=score+game[i-1];
			record[i]=0;
			i=i-1;
		}
	}
	directA();
}

void addS()
{
	int i, j;
	for(j=0;j<4;j++)
	for(i=12+j;i>=j;i=i-4)
	{
		if(game[i]==game[i+4]&&game[i]!=0)
		{
			game[i]=0;
			game[i+4]=2*game[i+4];
			score=score+game[i+4];
			record[i]=0;
			i=i+4;
		}
	}
	directS();
}

void addD()
{
	int i, j;
	for(j=0;j<4;j++)
	for(i=4*j+3;i>=4*j;i--)
	{
		if(game[i]==game[i+1]&&game[i]!=0)
		{
			game[i]=0;
			game[i+1]=2*game[i+1];
			score=score+game[i+1]; 
			record[i]=0;
			i=i+1;
		}
	}
	directD();
}

int judgeW()
{
	int i, j, judge=0;
	for(j=1;j<4;j++)
	{
		for(i=4*j;i<4*j+4;i++)
	    {
		    if((record[i]!=0&&record[i-4]==0)||(game[i-4]==game[i]&&record[i]!=0))
		    judge++;
	    }
	    if(judge!=0)
	           break;
	}
    return judge;
}

int judgeA()
{
	int i, j ,judge=0;
	for(i=1;i<=3;i++)
	{
		for(j=i;j<=12+i;j=j+4)
		{
			if((record[j]!=0&&record[j-1]==0)||(game[j-1]==game[j]&&record[j]!=0))
		    judge++;
	    }
		if(judge!=0)
		       break;
	}
	return judge;
}

int judgeS()
{
	int i, j, judge=0;
	for(j=3;j>0;j--)
	{
		for(i=4*j-4;i<4*j;i++)
	    {
		    if((record[i]!=0&&record[i+4]==0)||(game[i+4]==game[i]&&record[i]!=0))
		    judge++;
	    }
	    if(judge!=0)
	          break;
	}
    return judge;
}

int judgeD()
{
	int i, j ,judge=0;
	for(i=2;i>=0;i--)
	{
		for(j=i;j<=12+i;j=j+4)
		{
			if((record[j]!=0&&record[j+1]==0)||(game[j+1]==game[j]&&record[j]!=0))
			judge++;
		}
		if(judge!=0)
		      break;
	}
	return judge;
}

void print()
{	
    StartFilledRegion(0.8);
    SetPenColor("Green");
    MovePen(0.3*x0,0.4*y0);
    DrawLine(0.4*x0,0);
    DrawLine(0,0.2*y0);
    DrawLine(-0.4*x0,0);
    DrawLine(0,-0.2*y0);
    EndFilledRegion();
    
    SetPenColor("Red");
    MovePen(0.45*x0,0.5*y0);
    DrawTextString("Surprise! You Lose it !"); 
	SetPenColor("Black"); 
	  
    MovePen(0.3*x0,0.4*y0);
    DrawLine(0.4*x0,0);
    DrawLine(0,0.2*y0);
    DrawLine(-0.4*x0,0);
    DrawLine(0,-0.2*y0);
    MovePen(0.45*x0,0.5*y0);
}

int over()
{
	int i;
	if(judgeW()==0&&judgeA()==0&&judgeS()==0&&judgeD()==0)
	    return 0;
	else {
		for(i=0;i<16;i++)
			if(game[i]==2048)
				printf("Good Job! You've made 2048 successfully\n");
		return 1;
	}
}

void comenumber()
{	int x;
	while(1)
	{
		x=random2();
		if(record[x]==0)
		{
			game[x]=random1();
			record[x]=1;
			break;
		}
	}
}

void KeyboardEventProcess(int key,int event)
{	int k;
    if(isforgive){
        turnback();
        isforgive=0;
	}
	if(key==VK_DOWN&&event==KEY_DOWN)
	    direct='s';
	else if(key==VK_UP&&event==KEY_DOWN)
	    direct='w';
	else if(key==VK_LEFT&&event==KEY_DOWN)
	    direct='a';
	else if(key==VK_RIGHT&&event==KEY_DOWN)
	    direct='d';
	else 
	    return ;
	for(k=0;k<16;k++)
		forgame[k]=game[k];
	for(k=0;k<16;k++)
		forrecord[k]=record[k];
	if(direct=='w')
    {
        temp=judgeW();
        if(temp!=0)
        {
            directW();
            addW();
		}
	}
	else
	if(direct=='s')
	{
        temp=judgeS();
        if(temp!=0)
        {
            directS();
            addS();
		}
	}
	else
	if(direct=='a')
    {
        temp=judgeA();
        if(temp!=0)
        {
            directA();
            addA();
		}
	}
	else
	if(direct=='d')
    {
        temp=judgeD();
        if(temp!=0)
        {
            directD();
            addD();
		}
	}
	if(temp) 
	    comenumber();
	    leaveout();
	for(i=0;i<16;i++)
	{
    	laz=game[i];
    	drawcube(i,laz,xc,yc,cl);
    }
    
    if(over()==0)
        print();
        
    countscore();
    exam();
}


void countscore()
{
	char string[50];
	
	StartFilledRegion(0.8);
    SetPenColor("White");
    MovePen(xc-cl,yc);
	DrawLine(0,cl);
	DrawLine(-1.5*cl,0);
	DrawLine(0,-cl);
	DrawLine(1.5*cl,0);
    EndFilledRegion();
    
	SetPenColor("Black");
	MovePen(xc-cl,yc);
	DrawLine(0,cl);
	DrawLine(-1.5*cl,0);
	DrawLine(0,-cl);
	DrawLine(1.5*cl,0);
	
	SetPenColor("Red");
    MovePen(xc-2.3*cl,yc+0.5*cl);
    sprintf(string,"Now your score is:%d",score);
    DrawTextString(string);
}

void exam()
{
	int i;
	for(i=0;i<16;i++)
	{
		if(game[i]==2048)
		{
			SetPenColor("Black");
			MovePen(xc-0.15*cl,yc+3*cl);
			DrawLine(0,cl);
			DrawLine(-2.3*cl,0);
			DrawLine(0,-cl);
			DrawLine(2.3*cl,0);
			SetPenColor("Red");
		    MovePen(xc-2.4*cl,yc+3.5*cl);
		    DrawTextString("Congratuation!You've made 2048 succeffully!");
		    break;
		}
	}	
}

void turnback()
{
	StartFilledRegion(0.8);
    SetPenColor("Green");
	MovePen(0.15*cl,yc+1.5*cl);
	DrawLine(1.5*cl,0);
	DrawLine(0,cl);
	DrawLine(-1.5*cl,0);
	DrawLine(0,-cl);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(0.15*cl,yc+1.5*cl);
	DrawLine(1.5*cl,0);
	DrawLine(0,cl);
	DrawLine(-1.5*cl,0);
	DrawLine(0,-cl);
	
	MovePen(0.3*cl,yc+2.0*cl);
	DrawTextString("我想要后悔一步怎么办？"); 
		
}

void forgive()
{
	if(isforgive)
	      return;
	
	SetPenColor("Blue");
	MovePen(0.3*cl,yc+1.8*cl);
	DrawTextString("当然是原谅你咯");
	SetPenColor("Black");
	
	leaveout();
	for(i=0;i<16;i++){
		game[i]=forgame[i];
	}
	for(i=0;i<16;i++)
		record[i]=forrecord[i];
	drawfield(xc,yc,cl);

	for(i=0;i<16;i++){
    		laz=game[i];
    		drawcube(i,laz,xc,yc,cl);
   	}
    score-=lastscore;
    countscore();
    isforgive=1;
}

