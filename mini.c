#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_OBJECTS 100
#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];

typedef struct {
    int type;      /* 1=line 2=rectangle 3=circle 4=triangle */
    int active;
    int p[6];
} Shape;
Shape objects[MAX_OBJECTS];
int objectCount = 0;

void clearPicture() {
    for(int i=0;i<HEIGHT;i++)
        for(int j=0;j<WIDTH;j++)
            picture[i][j]=EMPTY;
}

void displayPicture() {
    for(int i=0;i<HEIGHT;i++) {
        for(int j=0;j<WIDTH;j++)
            putchar(picture[i][j]);
        putchar('\n');
    }
}
void setPixel(int x,int y) {
    if(x>=0 && x<WIDTH && y>=0 && y<HEIGHT)
        picture[y][x]=PIXEL;
}

void drawLine(int x1,int y1,int x2,int y2) {
    int dx=abs(x2-x1), dy=abs(y2-y1);
    int sx=(x1<x2)?1:-1;
    int sy=(y1<y2)?1:-1;
    int err=dx-dy;

    while(1) {
        setPixel(x1,y1);
        if(x1==x2 && y1==y2) break;

        int e2=2*err;
        if(e2>-dy){ err-=dy; x1+=sx; }
        if(e2< dx){ err+=dx; y1+=sy; }
    }
}
void drawRectangle(int x1,int y1,int x2,int y2) {
    drawLine(x1,y1,x2,y1);
    drawLine(x2,y1,x2,y2);
    drawLine(x2,y2,x1,y2);
    drawLine(x1,y2,x1,y1);
}
void drawCircle(int cx,int cy,int r) {
    int x=r,y=0,p=1-r;
    while(x>=y) {
        setPixel(cx+x,cy+y); setPixel(cx-x,cy+y);
        setPixel(cx+x,cy-y); setPixel(cx-x,cy-y);
        setPixel(cx+y,cy+x); setPixel(cx-y,cy+x);
        setPixel(cx+y,cy-x); setPixel(cx-y,cy-x);

        y++;
        if(p<=0) p+=2*y+1;
        else { x--; p+=2*y-2*x+1; }
    }
}

void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3) {
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}
void redrawCanvas() {
    clearPicture();

    for(int i=0;i<objectCount;i++) {
        if(!objects[i].active) continue;

        switch(objects[i].type) {
            case 1:
                drawLine(objects[i].p[0],objects[i].p[1],
                         objects[i].p[2],objects[i].p[3]);
                break;
            case 2:
                drawRectangle(objects[i].p[0],objects[i].p[1],
                              objects[i].p[2],objects[i].p[3]);
                break;
            case 3:
                drawCircle(objects[i].p[0],objects[i].p[1],
                           objects[i].p[2]);
                break;
            case 4:
                drawTriangle(objects[i].p[0],objects[i].p[1],
                             objects[i].p[2],objects[i].p[3],
                             objects[i].p[4],objects[i].p[5]);
                break;
        }
    }
}