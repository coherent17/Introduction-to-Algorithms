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

int abs(int x){
    return x >= 0 ? x : -x;
}

int find(vector<int> &ds, int i) {
    return ds[i] < 0 ? i : ds[i] = find(ds, ds[i]);
}

struct larger{
    bool operator()(element& a, element& b) const{
        return (a.weight > b.weight);
    }
};

void parser(char *filename, int *nptr, point **points){
    FILE *input = fopen(filename, "r");
    fscanf(input, "%d", &(*nptr));
    *points = (point *)malloc(sizeof(point) * (*nptr));
    for(int i = 0; i < *nptr; i++){
        fscanf(input, "%d %d", &((*points)[i].x), &((*points)[i].y));
    }

    int res = 0;
    vector<int> ds(*nptr, -1);
    vector<element> elements;

    //calculate the manhattan disatnce for each node
    for (int i = 0; i < *nptr; i++){
        for (int j = i + 1; j < *nptr; j++) {
            elements.push_back({abs((*points)[i].x - (*points)[j].x) + abs((*points)[i].y - (*points)[j].y), i, j});
        }
    }

    //for those originally exist routing segment, set the weight to 0
    int i, j;
    while(fscanf(input, "%d %d", &i, &j) != EOF){
        elements.push_back({0, i, j});
    }
    

    make_heap(elements.begin(), elements.end(), larger());

    for(int i = 0; i < elements.size(); i++){
        cout << elements[i].weight << endl;
    }

    while (!elements.empty()) {
        pop_heap(begin(elements), end(elements), larger());
        auto ele = elements.back();
        int dist = ele.weight;
        int i = ele.x;
        int j = ele.y;
        elements.pop_back();
        i = find(ds, i), j = find(ds, j);
        if (i != j) {
            res += dist;
            ds[i] += ds[j];
            ds[j] = i;
            if (ds[i] == -(*nptr))
                break;
        }
    }

    printf("res = %d\n", res);
    fclose(input);
}




int main(int argc, char *argv[]){
    int n;
    point *points;
    parser(argv[1], &n, &points);
    free(points);
    return 0;
}