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