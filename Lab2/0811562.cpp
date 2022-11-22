#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

typedef struct _point{
    int x;
    int y;
}point;

int abs(int x){
    return x >= 0 ? x : -x;
}

int **parser(char *filename, int *nptr, point **points){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%d", &(*nptr));
    *points = (point *)malloc(sizeof(point) * (*nptr));
    for(int i = 0; i < *nptr; i++){
        fscanf(input, "%d %d", &((*points)[i].x), &((*points)[i].y));
    }

    //build the adjacency matrix
    int **matrix = (int **)malloc(sizeof(int *) * (*nptr));
    for(int i = 0; i < (*nptr); i++){
        matrix[i] = (int *)malloc(sizeof(int) * (*nptr));
    }

    //init the matrix:
    for(int i = 0; i < (*nptr); i++){
        for(int j = 0; j < (*nptr); j++){
            matrix[i][j] = INT_MAX;
        }
    }

    for(int i = 0; i < *nptr; i++){
        for(int j = i + 1; j < *nptr; j++){
            matrix[i][j] = abs((*points)[i].x - (*points)[j].x) + abs((*points)[i].y - (*points)[j].y);
        }
    }

    int x, y;
    while(fscanf(input, "%d %d", &x, &y) != EOF){
        matrix[x][y] = 0;
    }

    fclose(input);
    return matrix;
}




int main(int argc, char *argv[]){
    int n;
    point *points;
    int **matrix;
    matrix = parser(argv[1], &n, &points);

    printf("%d\n", n);
    for(int i = 0; i < n; i++){
        printf("%d %d\n", points[i].x, points[i].y);
    }

    printf("-----------------------------\n");
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }


    free(points);
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}