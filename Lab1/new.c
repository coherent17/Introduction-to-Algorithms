#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 10
#define NEG_INF -9223372036854775807
typedef long long int llint;


llint max(llint a, llint b){
    return a > b ? a : b;
}

void parser(char *filename, llint *Nptr, llint *Aptr, llint *Bptr, llint **R){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%lld %lld %lld", &(*Nptr), &(*Aptr), &(*Bptr));
    fgetc(input);

    *R = (llint *)malloc(sizeof(llint) * ((*Nptr) + 1));
    int i;
    for(i = 1; i <= (*Nptr); i++){
        char buffer[BUFFER_SIZE];
        fscanf(input, "%s", buffer);
        (*R)[i] = atoi(buffer);
    }
    fclose(input);
}


void Maximum_Performance(llint N, llint A, llint B, llint *R, llint *result){

    llint *cw = (llint *)malloc(sizeof(llint) * (N + 1));
    llint *r = (llint *)malloc(sizeof(llint) * (N + 1));
    llint *w = (llint *)malloc(sizeof(llint) * (N + 1));

    int i, j;

    //get maxR:
    llint R_max = 1000000;
    llint max_conti = llint(sqrt((A + R_max) / B) + 1);

    for(i = 0; i <= N; i++){
        w[i] = NEG_INF;
        r[i] = NEG_INF;
    }

    //calculate continue working performance
    cw[0] = 0;
    cw[1] = A - B;
    for(i = 2; i <= N; i++){
        cw[i] = cw[i - 1] + A - i * i * B;
    }

    //construct best rest performance
    r[0] = 0;
    r[1] = 0 - R[1];

    for(i = 2; i <= N; i++){
        for(j = i - 1; j >= 0; j--){
            if(j > max_conti) continue;
            r[i] = max(cw[j] + r[i - j - 1], r[i]);
        }
        r[i]  = r[i] - R[i]; 
    }

    //construct best work performance
    w[0] = 0;
    w[1] = A - B;
    for(i = 2; i <= N; i++){
        for(j = i - 1; j >= 0; j--){
            if(i-j > max_conti) continue;
            w[i] = max(r[j] + cw[i - j], w[i]);
        }
    }

    printf("%lld\n", max(w[N], r[N]));

}




int main(int argc, char *argv[]){

    llint N, A, B, result;
    llint *R = NULL;
    parser(argv[1], &N, &A, &B, &R);
    Maximum_Performance(N, A, B, R, &result);

    return 0;
}