#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10
#define LLINT_MIN -9223372036854775807
#define NEG_INF LLINT_MIN
typedef long long int llint;

void parser(char *filename, llint *Nptr, llint *Aptr, llint *Bptr, llint **R, llint *R_max){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%lld %lld %lld", &(*Nptr), &(*Aptr), &(*Bptr));
    fgetc(input);

    *R = (llint *)malloc(sizeof(llint) * ((*Nptr) + 1));
    *R_max = -1;
    int i;
    for(i = 1; i <= (*Nptr); i++){
        char buffer[BUFFER_SIZE];
        fscanf(input, "%s", buffer);
        (*R)[i] = atoi(buffer);
        (*R_max) = (*R_max) > atoi(buffer) ? (*R_max) : atoi(buffer);
    }
    fclose(input);
}


int *Maximum_Performance(llint N, llint A, llint B, llint *R, llint *result, llint R_max){

    llint *cw = (llint *)malloc(sizeof(llint) * (N + 1));       //continue working performance
    llint *r = (llint *)malloc(sizeof(llint) * (N + 1));        //best rest performance
    int *cut = (int *)malloc(sizeof(int) * (N + 1));            //record when to work continuesly on r[i]
    int *path = (int *)malloc(sizeof(int) * (N + 1));           //final path

    for(int i = 0; i <= N; i++){
        r[i] = NEG_INF;
        path[i] = 1;
    }


    //base case
    cw[0] = 0;
    cw[1] = A - B;

    r[0] = 0;
    r[1] = 0 - R[1];

    cut[0] = -2;
    cut[1] = 0;

    for(int i = 2; i <= N; i++){    
        cw[i] = cw[i - 1] + A - i * i * B;                  //calculate the performance of continous work
        for(int j = 0; j <= i - 1; j++){

            //early return condition:
            if(cw[j] < -1 * R_max * N) break;               //continue to work can't have larger performance, break it


            if(cw[j] + r[i - j - 1] > r[i]){
                //get the maximum value of best performance of rest i-j-1 day and work j days
                r[i] = cw[j] + r[i - j - 1];
                cut[i] = i - j  - 1;
            }
        }
        r[i]  = r[i] - R[i]; 
    }

    llint wn = NEG_INF;
    //construct best work performance on day N
    int end = -1;
    for(int i = 1; i <= N; i++){
        if(r[N-i] + cw[i] > wn){
            wn = r[N-i] + cw[i];
            end = N-i;
        }
    }


    if(wn > r[N]){
        *result = wn;
    }
    else{
        *result = r[N];
        path[N] = 0;
        end = cut[N];
    }

    //mark the day that no work
    while(end != -2){
        path[end] = 0;
        end = cut[end];
    }


    free(cw);
    free(r);
    free(cut);
    return path;
}

void OutputAnswer(char *filename, int *path, llint result, int N){
    FILE *out = fopen(filename, "w");
    fprintf(out, "%lld\n", result);

    for(int i = 1; i <= N; i++){
        fprintf(out, "%d ", path[i]);
    }
}



int main(int argc, char *argv[]){

    llint N, A, B, R_max, result;
    llint *R = NULL;
    parser(argv[1], &N, &A, &B, &R, &R_max);

    if(N == 1){
        FILE *output = fopen(argv[2], "w");
        
        llint r = 0 - R[1];
        llint w = A - B;
        if(r > w){
            fprintf(output, "%lld\n", r);
            fprintf(output, "0");
        }
        else{
            fprintf(output, "%lld\n", w);
            fprintf(output, "1");
        }
        fclose(output);
        free(R);
        return 0;
    }

    int *path = Maximum_Performance(N, A, B, R, &result, R_max);
    OutputAnswer(argv[2], path, result, N);

    free(R);
    free(path);
    return 0;
}