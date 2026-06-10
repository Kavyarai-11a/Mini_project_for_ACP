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