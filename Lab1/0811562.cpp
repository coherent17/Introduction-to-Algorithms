#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100000

void parser(char *filename, int *Nptr, int *Aptr, int *Bptr, int **R, int *R_sizeptr){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%d %d %d", &(*Nptr), &(*Aptr), &(*Bptr));
    fgetc(input);

    char buffer[BUFFER_SIZE];
    char buffer_copy[BUFFER_SIZE];

    fscanf(input, "%[^\n]", buffer);
    fgetc(input);
    fclose(input);
    strncpy(buffer_copy, buffer, strlen(buffer));
    buffer_copy[strlen(buffer)] = '\0';

    *R_sizeptr = 0;
    char *token = strtok(buffer, " ");
    while(token != NULL){
        (*R_sizeptr) = (*R_sizeptr) + 1;
        token = strtok(NULL, " ");
    }

    *R = (int *)malloc(sizeof(int) * (*R_sizeptr));  
    int index = 0;

    char *temp = strtok(buffer_copy, " ");
    while(temp != NULL){
        (*R)[index++] = atoi(temp);
        temp = strtok(NULL, " ");
    }
}

void printArray(int *R, int R_size){
    for(int i = 0; i < R_size; i++){
        printf("%d ", R[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){

    int N, A, B;
    int *R = NULL;
    int R_size;
    parser(argv[1], &N, &A, &B, &R, &R_size);
    printf("%d %d %d %d\n", N, A, B, R_size);
    printArray(R, R_size);


    free(R);
    return 0;
}