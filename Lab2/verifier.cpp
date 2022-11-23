#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <boost/functional/hash.hpp>

using namespace std;

namespace std {
template <> struct hash<std::pair<int, int>> {
    inline size_t operator()(const std::pair<int, int> &v) const {
        std::hash<int> int_hasher;
        return int_hasher(v.first) ^ int_hasher(v.second);
    }
};

}

int main(int argc, char *argv[]){
    FILE *in1 = fopen(argv[1], "r");
    FILE *in2 = fopen(argv[2], "r");
    int c1;
    int c2;
    fscanf(in1, "%d", &c1);
    fscanf(in2, "%d", &c2);

    if(c1 != c2){
        printf("Cost error!\n");
        return 0;
    }

    unordered_set <pair<int, int>> usp1;
    unordered_set <pair<int, int>> usp2;

    int u;
    int v;
    while(fscanf(in1, "%d %d", &u, &v)!=EOF){
        usp1.insert(make_pair(u,v));
        usp1.insert(make_pair(v,u));
    }

    while(fscanf(in2, "%d %d", &u, &v)!=EOF){
        usp2.insert(make_pair(u,v));
        usp2.insert(make_pair(v,u));
    }

    


    // if(vp2.size() == 0) printf("Pass\n");
    // else printf("failed\n");
    return 0;
}