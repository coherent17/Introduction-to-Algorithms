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

void getPath(int *path, int *path1, int *path2, int end_in_which, int N){
    int index = 0;
    path[index++] = end_in_which == 1 ? 1 : 0;
    for(int i = N-2; i >= 0; i--){
        if(end_in_which == 1) end_in_which = path1[i];
        else end_in_which = path2[i];
        path[index++] = end_in_which == 1 ? 1 : 0;
    }
}

int *Maximum_Performance(int N, int A, int B, int *R, int R_size, int *result){

    //dynamic programming to solve the problem:
    
    //define dp1[i] : maximum performance if the ith day exercise
    //define dp2[i] : maximum performance if the ith day rest

    //base case:
    //dp1[0] = 0 + A - 1 * 1 * B
    //dp2[0] = 0 - R[0]

    //transition function:
    // dp1[i] = max(dp1[i-1] + A - X * X * B, dp2[i-1] + A - B);
    // dp2[i] = max(dp1[i-1] - R[i], dp2[i-1] - R[i]);

    int *dp1 = (int *)malloc(sizeof(int) * N);
    int *dp2 = (int *)malloc(sizeof(int) * N);

    //record the path:
    int *path1 = (int *)malloc(sizeof(int) * N);
    int *path2 = (int *)malloc(sizeof(int) * N);
    int *path = (int *)malloc(sizeof(int) * N);

    dp1[0] = 0 + A - 1 * 1 * B;
    dp2[0] = 0 - R[0];

    int no_resting_day = 1;

    for(int i = 1; i < N; i++){
        if(dp1[i - 1] + A - (no_resting_day + 1) * (no_resting_day + 1) * B  >= dp2[i - 1] + A - B){
            dp1[i] = dp1[i - 1] + A - (no_resting_day + 1) * (no_resting_day + 1) * B;
            no_resting_day++;
            path1[i-1] = 1;
        }
        else{
            dp1[i] = dp2[i - 1] + A - B;
            no_resting_day = 1;
            path1[i-1] = 2;
        }

        if(dp1[i - 1] - R[i] >= dp2[i - 1] - R[i]){
            dp2[i] = dp1[i - 1] - R[i];
            path2[i-1] = 1;
        }
        else{
            dp2[i] = dp2[i - 1] - R[i];
            path2[i-1] = 2;
        }
    }

    int end_in_which;
    if(dp1[N-1] > dp2[N-1]){
        *result = dp1[N-1];
        end_in_which = 1; 
    }
    else{
        *result = dp2[N-1];
        end_in_which = 2;
    }

    getPath(path, path1, path2, end_in_which, N);

    free(dp1);
    free(dp2);
    free(path1);
    free(path2);
    return path;
}

void outputAnswer(char *outputname, int *path, int result, int N){
    FILE *output = fopen(outputname, "w");

    fprintf(output, "%d\n", result);

    for(int i = N-1; i >= 0; i--){
        fprintf(output, "%d ", path[i]);
    }
    fclose(output);
}


int main(int argc, char *argv[]){

    int N, A, B;
    int *R = NULL;
    int R_size;
    int result;
    parser(argv[1], &N, &A, &B, &R, &R_size);
    int *path = Maximum_Performance(N, A, B, R, R_size, &result);
    outputAnswer(argv[2], path, result, N);

    free(path);
    free(R);
    return 0;
}