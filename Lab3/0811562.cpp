#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define NON_EXIST_PATH -1

int max_cost = 0;

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
        max_cost = cost > max_cost ? cost : max_cost;
        graph[a][b] = cost;
        graph[b][a] = cost;
    }

    for(int i = 0; i < (*nptr); i++){
        for(int j = 0; j < (*nptr); j++){
            if(graph[i][j] == NON_EXIST_PATH){
                graph[i][j] = max_cost * (*nptr);
            }
        }
    }
    return graph;
}

void printGraph(int **g, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void NeareestNeighbor(int **g, int n,  bool *visited, int *path, int start){
    visited[start] = true;
    int min = max_cost;
    bool flag = false;
    int neighbor = -1;
    for(int i = 0; i < n; i++){
        if(i != start && visited[i] == false){
            if(g[start][i] <= min){
                min = g[start][i];
                flag = true;
                neighbor = i;
                path[start] = neighbor;
            }
        }
    }

    if(flag == false){
        return;
    }
    NeareestNeighbor(g, n,  visited, path, neighbor);
}

int *getInitialState(int n, int **g){

    int *path = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        path[i] = -1;
    }

    bool *visited = (bool *)malloc(sizeof(bool) * n);
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }

    NeareestNeighbor(g, n,  visited, path, 0);
    int *initial_state = (int *)malloc(sizeof(int) * n);
    initial_state[0] = 0;

    int result = path[0];
    int count = 1;
    while(result != -1){
        initial_state[count++] = result;
        result = path[result];
    }
    return initial_state;
}

unsigned long long int getCost(int *state, int n, int **g){
    unsigned long long int cost = 0;
    for(int i = 0; i < n - 1; i++){
        cost += g[state[i]][state[i + 1]];
    }
    cost += g[state[n - 1]][state[0]];
    return cost;
}

void printState(int *state, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", state[i]);
    }
    printf("\n");
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
        result = inverse(state, n);
        break;
    
    case 1:
        result = swap(state, n);
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
	// printf("temp = %lf\n", temp);
	// printf("exp(temp) = %lf\n", exp(temp));
	return 1 > exp(temp) ? exp(temp) : 1;
}

bool accept(unsigned long long int new_cost, unsigned long long int old_cost, double Temperature){
	int delta_cost = new_cost - old_cost;
	double y = f(delta_cost, Temperature);
	double r = getDoubleRandom();

	if(r < y) return true;
	else return false;
}

int *SimulateAnnealing(int *initial_state, int n, int **g){
    double ANNEALING_TEMPERATURE = 0.0001;
    double TERMINATE_TEMPERATURE = 0.0000000000000000001;
    double ALPHA = 0.95;
    int INNER_LOOP_TIMES = n * 50;
    double Current_Temperature = ANNEALING_TEMPERATURE;

    int **best_state_ptr = &initial_state;

    bool canBreak = false;
    int canBreakCount = 0;

    while(Current_Temperature > TERMINATE_TEMPERATURE){
        if(canBreak){
            break;
        }
        unsigned long long int old_cost = 0;
		unsigned long long int new_cost = 0;

        for(int i = 0; i < INNER_LOOP_TIMES; i++){
            int *newState = getNeighbor(*best_state_ptr, n);
            old_cost = getCost(*best_state_ptr, n, g);
            new_cost = getCost(newState, n, g);

            if(old_cost == new_cost){
                canBreakCount += 1;
                if(canBreakCount == 100) canBreak = true;
            }
            else{
                canBreak = 0;
            }

            if(accept(new_cost, old_cost, Current_Temperature)){
                //printf("Accept!\n");
                free(*best_state_ptr);
                *best_state_ptr = newState;
                printf("%lld\n", new_cost);
            }
            else{
                //printf("Rejected!\n");
            }
        }
        Current_Temperature = Current_Temperature * ALPHA;
    }
    return *best_state_ptr;
}

void outputFile(char *filename, int *result, int n, int **g){
    FILE *output = fopen(filename, "w");
    fprintf(output, "Path: ");
    for(int i = 0; i < n; i++){
        fprintf(output, "%d ", result[i]);
    }
    fprintf(output, "%d\n", result[0]);
    fprintf(output, "Cost: %lld\n", getCost(result, n, g));
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int n, m;
    int **g = parser(argv[1], &n, &m);
    int *initial_state = getInitialState(n, g);
    int *result = SimulateAnnealing(initial_state, n, g);
    outputFile(argv[2], result, n, g);
    return 0;
}