#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>

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

int abs(int x){
    return x >= 0 ? x : -x;
}

int find(int *parent, int i) {
    return parent[i] < 0 ? i : parent[i] = find(parent, parent[i]);
}

struct larger{
    bool operator()(element& a, element& b) const{
        return (a.weight > b.weight);
    }
};

vector<element> parser(char *filename, int *nptr){
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

    vector<element> elements;

    for (int i = 0; i < *nptr; i++){
        for (int j = i + 1; j < *nptr; j++) {
            elements.push_back({matrix[i][j], i, j});
        }
    }

    for(int i = 0; i < (*nptr); i++){
        free(matrix[i]);
    }
    free(matrix);
    free(points);
    return elements;
}

void Kruskal(vector<element> elements, int n, int *cost, vector <edge>& addEdges){

    *cost= 0;
    int *parent = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        parent[i] = -1;
    }

    make_heap(elements.begin(), elements.end(), larger());

    while (!elements.empty()) {
        pop_heap(begin(elements), end(elements), larger());
        auto ele = elements.back();
        int w = ele.weight;
        int u = ele.x;
        int v = ele.y;
        int i = ele.x;
        int j = ele.y;
        elements.pop_back();
        i = find(parent, i), j = find(parent, j);
        if (i != j) {
            if(w != 0){
                edge temp;
                temp.u = u;
                temp.v = v;
                addEdges.push_back(temp);
            }
            *cost += w;
            parent[i] += parent[j];
            parent[j] = i;
            if (parent[i] == -n)
                break;
        }
    }
    free(parent);
}

void outputResult(char *filename, int cost, vector <edge> &addEdges){
    FILE *output = fopen(filename, "w");
    fprintf(output, "%d\n", cost);
    for(int i = 0; i < (int)addEdges.size(); i++){
        fprintf(output, "%d %d\n", addEdges[i].u, addEdges[i].v);
    }
}


int main(int argc, char *argv[]){
    int n;
    vector <element> elements = parser(argv[1], &n);

    int cost;
    vector <edge> addEdges;
    Kruskal(elements, n, &cost, addEdges);
    outputResult(argv[2], cost, addEdges);
    return 0;
}