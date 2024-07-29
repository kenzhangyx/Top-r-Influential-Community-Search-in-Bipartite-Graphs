//
// Created by 张 ken on 2024/4/6.

#include <string>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <cstdlib>
#include <fstream>
#include "utility.h"
#include<ctime>
using namespace std;

//在邻接表中删除某个点
void erase(vector<int>& v, int value) {
    auto it = find(v.begin(), v.end(), value);
    if (it != v.end()) {
        v.erase(it);
    }
}
//下面都没用到
bool cmp(pair<int, double> p1, pair<int, double> p2) {
    return p1.second > p2.second;
}

bool isFileExists(string& name) {
    ifstream f(name.c_str());
    return f.good();
}

bool vm_same(vector<unordered_map<int, int>>& vm1, vector<unordered_map<int, int>>& vm2) {
    if (vm1.size() != vm2.size()) {
        cout << "Error: size not same" << endl;
        return false;
    }
    for (int i = 0; i < vm1.size(); i++) {
        if (vm1[i] != vm2[i]) {
            cout << "Error: value not same" << endl;
            return false;
        }
    }
    return true;
}
void hcore_same(Hcore& hcore1, Hcore& hcore2) {
    cout << "beta_max:" << endl;
    if(vm_same(hcore1.beta_max, hcore2.beta_max)) cout<<"same"<<endl;
    cout << "alpha_max:" << endl;
    if (vm_same(hcore1.alpha_max, hcore2.alpha_max)) cout << "same" << endl;
}

//没用到
void preserveVertex(string dir, int perc) {
    unsigned int sumNode, n1, n2;
    int u, v, r;
    string metaFile = dir + "node2.txt";
    string edgeFile = dir + "edge2.txt";

    FILE* metaGraph = fopen(metaFile.c_str(), "r");
    FILE* edgeGraph = fopen(edgeFile.c_str(), "r");

    if (fscanf(metaGraph, "%d\n%d", &n1, &n2) != 2)
    {
        fprintf(stderr, "Bad file format: n1 n2 incorrect\n");
        exit(1);
    }
    unordered_map<int, bool> use1, use2;
    int n = round(n1 * perc * 0.01), m = round(n2 * perc * 0.01);
    srand((unsigned)time(NULL));
    while (n--) {
        int t;
        do {
            t = rand() % n1 + 1;
        } while (use1[t]);
        use1[t] = true;
    }
    while (m--) {
        int t;
        do {
            t = rand() % n2 + 1;
        } while (use2[t]);
        use2[t] = true;
    }
    string edgeKFile = dir +  "20edge2.txt";
    ofstream ofile;
    ofile.open(edgeKFile);
    while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
    {
        if (r != 2)
        {
            fprintf(stderr, "Bad file format: u v incorrect\n");
            exit(1);
        }
        if (use1[u] && use2[v]) ofile << u << " " << v << endl;
    }
    ofile.close();
    fclose(metaGraph);
    fclose(edgeGraph);
}
