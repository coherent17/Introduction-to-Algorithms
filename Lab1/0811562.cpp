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

int max(int a, int b){
    return a > b ? a : b;
}

int main(int argc, char *argv[]){

    int N, A, B;
    int *R = NULL;
    int R_size;
    parser(argv[1], &N, &A, &B, &R, &R_size);
    printf("%d %d %d %d\n", N, A, B, R_size);
    printArray(R, R_size);

    int *dp1 = (int *)malloc(sizeof(int) * N);
    int *dp2 = (int *)malloc(sizeof(int) * N);
    int *path1 = (int *)malloc(sizeof(int) * N);
    int *path2 = (int *)malloc(sizeof(int) * N);
    int *path = NULL;

    int no_resting_day = 1;

    //base case:
    dp1[0] = A - 1 * 1 * B;
    dp2[0] = 0 - R[0];

    // dp1[1] = max(dp1[0] + A - 2 * 2 * B, dp2[0] + A - B);   //right
    // dp2[1] = max(dp1[0] - R[1], dp2[0] - R[1]);             //left

    // dp1[2] = max(dp1[1] + A - 2 * 2 * B, dp2[1] + A - B);   //right
    // dp2[2] = max(dp1[1] - R[2], dp2[1] - R[2]);             //right


    

    for(int i = 1; i < N; i++){
        if(dp1[i - 1] + A - (no_resting_day + 1) * (no_resting_day + 1) * B  >= dp2[i - 1] + A - B){
            dp1[i] = dp1[i - 1] + A - (no_resting_day + 1) * (no_resting_day + 1) * B;
            no_resting_day++;
            path1[i] = 1;
        }
        else{
            dp1[i] = dp2[i - 1] + A - B;
            no_resting_day = 1;
            path1[i] = 0;
        }

        if(dp1[i - 1] - R[i] >= dp2[i - 1] - R[i]){
            dp2[i] = dp1[i - 1] - R[i];
            path2[i] = 1;
        }
        else{
            dp2[i] = dp2[i - 1] - R[i];
            path2[i] = 0;
        }
    }

    // int temp;
    // if(dp1[N-1] <= dp2[N-1]){
    //     path = path2;
    //     temp = 0;
    // }
    // else{
    //     path = path1;
    //     temp = 1;
    // }

    // printf("line %d, N=N-1\n", temp);
    // for(int j = N-1; j >= 1; j--){
    //     i = path
    //     printf("%d -> ", path[j]);
    // }

    //printArray(dp1, N);
    //printArray(dp2, N);
    printf("%d\n", dp1[N-1]);
    printf("%d\n", dp2[N-1]);
    free(R);
    return 0;
}