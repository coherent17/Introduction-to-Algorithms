#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10
typedef long long int llint;

void parser(char *filename, llint *Nptr, llint *Aptr, llint *Bptr, llint **R){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%lld %lld %lld", &(*Nptr), &(*Aptr), &(*Bptr));
    fgetc(input);

    *R = (llint *)malloc(sizeof(llint) * (*Nptr));
    for(int i = 0; i < (*Nptr); i++){
        char buffer[BUFFER_SIZE];
        fscanf(input, "%s", buffer);
        (*R)[i] = atoi(buffer);
    }
    fclose(input);
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

int *Maximum_Performance(llint N, llint A, llint B, llint *R, llint *result){

    llint *dp1 = (llint *)malloc(sizeof(llint) * N);
    llint *dp2 = (llint *)malloc(sizeof(llint) * N);

    //record the path:
    int *path1 = (int *)malloc(sizeof(int) * N);
    int *path2 = (int *)malloc(sizeof(int) * N);
    int *path = (int *)malloc(sizeof(int) * N);

    dp1[0] = 0 + A - 1 * 1 * B;
    dp2[0] = 0 - R[0];

    llint no_resting_day = 1;

    for(int i = 1; i < N; i++){
        if(dp1[i - 1] + A - (no_resting_day + 1) * (no_resting_day + 1) * B  > dp2[i - 1] + A - B){
            dp1[i] = dp1[i - 1] + A - (no_resting_day + 1) * (no_resting_day + 1) * B;
            no_resting_day++;
            path1[i-1] = 1;
        }
        else{
            dp1[i] = dp2[i - 1] + A - B;
            no_resting_day = 1;
            path1[i-1] = 2;
        }

        if(dp1[i - 1] - R[i] > dp2[i - 1] - R[i]){
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

void outputAnswer(char *outputname, int *path, llint result, int N){
    FILE *output = fopen(outputname, "w");

    fprintf(output, "%lld\n", result);

    for(int i = N-1; i >= 0; i--){
        fprintf(output, "%d ", path[i]);
    }
    fclose(output);
}


int main(int argc, char *argv[]){

    llint N, A, B, result;
    llint *R = NULL;
    parser(argv[1], &N, &A, &B, &R);
    int *path = Maximum_Performance(N, A, B, R, &result);
    outputAnswer(argv[2], path, result, N);

    free(path);
    free(R);
    return 0;
}