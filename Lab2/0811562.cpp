#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <queue>

#define ABSOLUTE_PARENT -1
#define EMPTY_RANK 0

using namespace std;

typedef struct _point{
    int x;
    int y;
}point;

typedef struct _element{
    int weight;
    int x;
    int y;
}element;

typedef struct _edge{
    int u;
    int v;
}edge;

typedef struct _node{
    int parent;
    int rank;
}node;

int abs(int x){
    return x >= 0 ? x : -x;
}

//path compression
int DS_Find(node *disjointSetArray, int v){
	if(disjointSetArray[v].parent == ABSOLUTE_PARENT) return v;
	return DS_Find(disjointSetArray, disjointSetArray[v].parent);
}

void DS_Union(node *disjointSetArray, int fromParent,int toParent){

	if(disjointSetArray[fromParent].rank > disjointSetArray[toParent].rank)
		disjointSetArray[toParent].parent = fromParent;
	else if(disjointSetArray[fromParent].rank < disjointSetArray[toParent].rank)
		disjointSetArray[fromParent].parent = toParent;
	else{
		disjointSetArray[fromParent].parent = toParent;
		disjointSetArray[toParent].rank +=1;
	}
}

bool hasCycle(node *disjointSetArray, element e){

	int fromParent = DS_Find(disjointSetArray, e.x);
	int toParent = DS_Find(disjointSetArray, e.y);

	if(fromParent == toParent) return true;
	DS_Union(disjointSetArray, fromParent, toParent);
	return false;
}

struct cmp{
    bool operator()(element& a, element& b) const{
        return (a.weight > b.weight);
    }
};

int **parser(char *filename, int *nptr){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%d", &(*nptr));
    point *points = (point *)malloc(sizeof(point) * (*nptr));
    for(int i = 0; i < *nptr; i++){
        fscanf(input, "%d %d", &(points[i].x), &(points[i].y));
    }

    int **matrix = (int **)malloc(sizeof(int *) * (*nptr));
    for(int i = 0; i < (*nptr); i++){
        matrix[i] = (int *)malloc(sizeof(int) * (*nptr));
    }

    for(int i = 0; i < (*nptr); i++){
        for(int j = i + 1; j < (*nptr); j++){
            int distance = abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
            matrix[i][j] = distance;
            matrix[j][i] = distance;
        }
    }

    //for those originally exist routing segment, set the weight to 0
    int i, j;
    while(fscanf(input, "%d %d", &i, &j) != EOF){
        matrix[i][j] = 0;
        matrix[j][i] = 0;
    }

    fclose(input);
    free(points);
    return matrix;
}

void Kruskal(int **matrix, int n, int *cost, vector <edge>& addEdges){

    int MST_edges = 0;
    *cost= 0;
    node *disjointSetArray = (node *)malloc(sizeof(node) * n);
    //init for parent and rank
    for(int i = 0; i < n; i++){
        disjointSetArray[i].parent = ABSOLUTE_PARENT;
        disjointSetArray[i].rank = EMPTY_RANK;
    }
    

    //make min heap
    priority_queue <element, vector<element>, cmp> pq;

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++) {
            pq.push({matrix[i][j], i, j});
        }
    }

    while(!pq.empty() && MST_edges < n - 1){
        element current = pq.top();
        pq.pop();

        if(!hasCycle(disjointSetArray, current)){
            *cost += current.weight;
            if(current.weight != 0) addEdges.push_back({current.x, current.y});
        }
    }
    free(disjointSetArray);
}

void outputResult(char *filename, int cost, vector <edge> &addEdges){
    FILE *output = fopen(filename, "w");
    fprintf(output, "%d\n", cost);
    for(int i = 0; i < (int)addEdges.size(); i++){
        fprintf(output, "%d %d\n", addEdges[i].u, addEdges[i].v);
    }
    fclose(output);
}

void freeMatrix(int **matrix, int n){
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}


int main(int argc, char *argv[]){
    int n;
    int **matrix = parser(argv[1], &n);
    int cost;
    vector <edge> addEdges;
    Kruskal(matrix, n, &cost, addEdges);
    outputResult(argv[2], cost, addEdges);
    freeMatrix(matrix, n);
    return 0;
}