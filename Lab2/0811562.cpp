#include <stdio.h>
#include <stdlib.h>

typedef struct _point{
    int x;
    int y;
}point;

void parser(char *filename, int *nptr, point **points){
    FILE *input = fopen(filename, "r");
    
}


int main(int argc, char *argv[]){
    int n;
    point *points;
}