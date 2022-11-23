#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NODE_SIZE 4
#define ABSOLUTE_PARENT -1

typedef struct _edge{
    int u;
    int v;
}edge;

void printParent(int *parent){
    for(int i = 0; i < NODE_SIZE; i++){
        printf("%d ", parent[i]);
    }
    printf("\n\n");
}


//find the absolute root for the given vertex
int Find(int *parent, int v){
    if(parent[v] == ABSOLUTE_PARENT) return v;
    return Find(parent, parent[v]);
}

void Union(int *parent, int fromParent, int toParent){
    parent[fromParent] = toParent;
}


bool hasCycle(int *parent, edge e){

    int fromParent = Find(parent, e.u);
    int toParent = Find(parent, e.v);

    if(fromParent == toParent) return true;
    return false;
}

int main(){

    int *parent = malloc(sizeof(int) * NODE_SIZE);
    for(int i = 0; i < NODE_SIZE; i++){
        parent[i] = ABSOLUTE_PARENT;
    }

    edge *edges = malloc(sizeof(edge) * NODE_SIZE);
    edges[0].u = 0; edges[0].v = 1;
    edges[1].u = 0; edges[1].v = 3;
    edges[2].u = 2; edges[2].v = 3;
    edges[3].u = 1; edges[3].v = 2;

    for(int i = 0; i < NODE_SIZE; i++){
        printf("Add edge : (%d %d)\n", edges[i].u, edges[i].v);
        if(hasCycle(parent, edges[i])){
            printf("Cycle detected!!\n");
            continue;
        }
        Union(parent, Find(parent, edges[i].u), Find(parent, edges[i].v));
        printParent(parent);
    }

    free(parent);
    free(edges);
}