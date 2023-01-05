#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define NON_EXIST_PATH 100000000
#define ANNEALING_TEMPERATURE 0.002
#define TERMINATE_TEMPERATURE 0.00000000000000000000000000001
#define ALPHA 0.99
#define INNER_LOOP_TIMES 30000


int max_duration = 60;
clock_t start_time;

int getIntRandom(int lower, int upper){
	return (rand() % (upper - lower + 1)) + lower;
}

double getDoubleRandom(){
	return ((double)rand()/RAND_MAX);
}


int **parser(char *filename, int *nptr, int *mptr){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%d %d", &(*nptr), &(*mptr));

    int **graph = (int **)malloc(sizeof(int *) * (*nptr));
    for(int i = 0; i < (*nptr); i++){
        graph[i] = (int *)malloc(sizeof(int) * (*nptr));
    }

    for(int i = 0; i < (*nptr); i++){
        for(int j = 0; j < (*nptr); j++){
            graph[i][j] = NON_EXIST_PATH;
        }
    }

    for(int i = 0; i < (*mptr); i++){
        int a, b, cost;
        fscanf(input, "%d %d %d", &a, &b, &cost);
        graph[a][b] = cost;
        graph[b][a] = cost;
    }
    return graph;
}

void NearestNeighbor(int **g, int n, bool *visited, int currPos, int count, int *path, bool *finish){

    if(*finish == true){
        return;
    }

    if(count == n && g[currPos][0] != NON_EXIST_PATH){
        *finish = true;
        return;
    }

    int good_entry = -1;
    for(int i = 0; i < n; i++){

        bool *entry = (bool *)malloc(sizeof(bool) * n);
        for(int j = 0; j < n; j++){
            entry[j] = false;
        }

        int curr_min = __INT_MAX__;
        for(int j = 0; j < n; j++){
            if(!visited[j] && !entry[j] && g[currPos][j] != NON_EXIST_PATH && g[currPos][j] < curr_min){
                curr_min = g[currPos][j];
                good_entry = j;
            }
        }

        if(curr_min == __INT_MAX__){
            return;
        }

        entry[good_entry] = true;
        visited[good_entry] = true;
        path[count] = good_entry;

        NearestNeighbor(g, n, visited, good_entry, count + 1, path, finish);
        visited[good_entry] = false;
    }
}

bool isValidState(int *state, int n, int **g){
    if(!state) return false;

    int *visited = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }

    for(int i = 0; i < n; i++){
        visited[state[i]]++;
    }

    for(int i = 0; i < n; i++){
        if(visited[i] != 1) return false;
    }

    for(int i = 0; i < n - 1; i++){
        if(g[state[i]][state[i + 1]] == NON_EXIST_PATH) return false;
    }
    if(g[state[n - 1]][state[0]] == NON_EXIST_PATH) return false;
    return true;
}

int *getInitialState(int n, int **g){

    bool *visited = (bool *)malloc(sizeof(bool) * n);
    int *path = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        visited[i] = false;
        path[i] = -1;
    }
    visited[0] = true;
    path[0] = 0;
    bool finish = false;
    NearestNeighbor(g, n, visited, 0, 1, path, &finish);
    
    if(path == NULL) return NULL;   //time out

    int *initial_state = path;
    
    if(!isValidState(initial_state, n, g)){
        return NULL;
    }

    return initial_state;
}

unsigned long long int getCost(int *state, int n, int **g){
    if(!state) return NON_EXIST_PATH;

    unsigned long long int cost = 0;
    for(int i = 0; i < n - 1; i++){
        cost += g[state[i]][state[i + 1]];
    }
    cost += g[state[n - 1]][state[0]];
    return cost;
}


//define the neighborhod structure in simulate annealing
int *inverse(int *state, int n){
    int index1 = getIntRandom(0, n - 2);
    int index2 = getIntRandom(index1 + 1, n - 1);
    //printf("%d %d\n", index1, index2);

    int *inverseConservation = (int *)malloc(sizeof(int) * (index2 - index1 + 1));
    int inverseConservationIndex = 0;
    for(int i = index2; i >= index1; i--){
        inverseConservation[inverseConservationIndex++] = state[i];
    }
    
    int *newState = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        newState[i] = state[i];
    }
    for(int  i = index1; i <= index2; i++){
        newState[i] = inverseConservation[i - index1];
    }
    free(inverseConservation);
    return newState;
}

int *swap(int *state, int n){
    int index1 = getIntRandom(0, n - 2);
    int index2 = getIntRandom(index1 + 1, n - 1);
    //printf("%d %d\n", index1, index2);
    int *newState = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        newState[i] = state[i];
    }

    int a = state[index1];
    int b = state[index2];
    newState[index2] = a;
    newState[index1] = b;

    return newState;
}

int *insert(int *state, int n){
    int index1 = getIntRandom(0, n - 2);
    int index2 = getIntRandom(index1 + 1, n - 1);
    //printf("%d %d\n", index1, index2);
    int *newState = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        newState[i] = state[i];
    }

    int vertex = state[index1];
    for(int i = index1; i <= index2; i++){
        newState[i] = newState[i + 1];
    }
    newState[index2] = vertex;
    return newState;
}

int *getNeighbor(int *state, int n){
    int op = getIntRandom(0, 2);
    int *result = NULL;
    switch (op){
    case 0:
        result = swap(state, n);
        break;
    
    case 1:
        result = inverse(state, n);
        break;

    case 2:
        result = insert(state, n);
        break;
    
    default:
        printf("Error");
        break;
    }

    return result;
}

//f(delta c, T) = min(1, exp(-delta C / T))
double f(int delta_cost, double Temperature){
	double temp = -1 * delta_cost / Temperature;
	return exp(temp) < 1 ? exp(temp) : 1;
}

bool accept(unsigned long long int new_cost, unsigned long long int old_cost, double Temperature){
	int delta_cost = new_cost - old_cost;
    if(delta_cost <= 0) return true;
	double y = f(delta_cost, Temperature);
	double r = getDoubleRandom();

	if(r < y) return true;
	else return false;
}

int *SimulateAnnealing(int *initial_state, int n, int **g){
    double Current_Temperature = ANNEALING_TEMPERATURE;

    int **best_state_ptr = &initial_state;
    
    unsigned long long int best_cost = getCost(initial_state, n, g);

    while(Current_Temperature > TERMINATE_TEMPERATURE){

        int reject_count = 0;

        //stop condition
        clock_t current_time = clock();
        if(((current_time - start_time) / CLOCKS_PER_SEC) > max_duration - 5){
            break;
        }

        //start inner loop
        for(int i = 0; i < INNER_LOOP_TIMES; i++){

            int *newState = getNeighbor(*best_state_ptr, n);
            unsigned long long int old_cost = best_cost;
            unsigned long long int new_cost = getCost(newState, n, g);

            if(accept(new_cost, old_cost, Current_Temperature)){
                *best_state_ptr = newState;
                best_cost = new_cost;
                reject_count = 0;
            }
            else{
                reject_count++;
                if(reject_count >= INNER_LOOP_TIMES /10){
                    reject_count = 0;
                    break;
                }
            }
        }
        printf("\rCost = %lld, reject_count = %5d, T = %.30f", getCost(*best_state_ptr, n, g), reject_count, Current_Temperature);
        fflush(stdout);
        Current_Temperature = Current_Temperature * ALPHA;
    }
    return *best_state_ptr;
}

void outputFile(char *filename, int *result, int n, int **g){
    FILE *output = fopen(filename, "w");
    fprintf(output, "Yes\n");
    fprintf(output, "Path: ");
    for(int i = 0; i < n; i++){
        fprintf(output, "%d ", result[i]);
    }
    fprintf(output, "%d\n", result[0]);
    fprintf(output, "Cost: %lld\n", getCost(result, n, g));
    fclose(output);
}

void outputNo(char *filename){
    FILE *output = fopen(filename, "w");
    fprintf(output, "No\n");
    fclose(output);
}

int main(int argc, char *argv[]){
    start_time = clock();
    srand(time(NULL));
    int n, m;
    int **g = parser(argv[1], &n, &m);

    int *initial_state = getInitialState(n, g);

    printf("Cost: %lld\n", getCost(initial_state, n, g));
    printf("Valid? %d\n", isValidState(initial_state, n, g));

    if(initial_state){
        int *result = SimulateAnnealing(initial_state, n, g);
        outputFile(argv[2], result, n, g);
    }
    else{
        outputNo(argv[2]);
    }
    return 0;
}