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
void addObject() {
    if(objectCount>=MAX_OBJECTS) return;

    Shape s;
    printf("Choose shape type:\n");
    printf("1. Line\n2. Rectangle\n3. Circle\n4. Triangle\n");
    printf("Enter shape type: ");
    scanf("%d",&s.type);
    s.active=1;

    switch(s.type) {
        case 1:
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d",&s.p[0],&s.p[1],&s.p[2],&s.p[3]);
            break;
        case 2:
            printf("Enter top-left x y and bottom-right x y: ");
            scanf("%d%d%d%d",&s.p[0],&s.p[1],&s.p[2],&s.p[3]);
            break;
        case 3:
            printf("Enter center x y and radius: ");
            scanf("%d%d%d",&s.p[0],&s.p[1],&s.p[2]);
            break;
        case 4:
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                  &s.p[0],&s.p[1],&s.p[2],
                  &s.p[3],&s.p[4],&s.p[5]);
            break;
        default:
            printf("Invalid shape.\n");
            return;
    }

    objects[objectCount++] = s;
    redrawCanvas();
}
void deleteObject() {
    int idx;
    printf("Enter object index: ");
    scanf("%d",&idx);

    if(idx>=0 && idx<objectCount) {
        objects[idx].active=0;
        redrawCanvas();
    }
}
void modifyObject() {
    int idx;
    printf("Enter object index: ");
    scanf("%d",&idx);

    if(idx<0 || idx>=objectCount || !objects[idx].active) {
        printf("Invalid index\n");
        return;
    }

    Shape *s=&objects[idx];

    switch(s->type) {
        case 1:
        case 2:
            printf("Enter new x1 y1 x2 y2: ");
            scanf("%d%d%d%d",&s->p[0],&s->p[1],&s->p[2],&s->p[3]);
            break;
        case 3:
            printf("Enter new center x y radius: ");
            scanf("%d%d%d",&s->p[0],&s->p[1],&s->p[2]);
            break;
        case 4:
            printf("Enter new x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                  &s->p[0],&s->p[1],&s->p[2],
                  &s->p[3],&s->p[4],&s->p[5]);
            break;
    }
    redrawCanvas();
}
void listObjects() {
    for(int i=0;i<objectCount;i++) {
        if(objects[i].active)
            printf("Index %d : Type %d\n",i,objects[i].type);
    }
}int main() {
    int choice;
    clearPicture();

    printf("2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);

    while(1) {
        printf("\nMenu\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Picture\n");
        printf("5. List Objects\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        scanf("%d",&choice);

        switch(choice) {
            case 1: addObject(); break;
            case 2: deleteObject(); break;
            case 3: modifyObject(); break;
            case 4: displayPicture(); break;
            case 5: listObjects(); break;
            case 0: printf("Goodbye.\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
