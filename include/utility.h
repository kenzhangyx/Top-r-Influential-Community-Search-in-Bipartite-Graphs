#pragma once
#include <string>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <cstdlib>
using namespace std;
#define MIN(a, b) (a <= b ? a : b)
#define MAX(a, b) (a >= b ? a : b)
void erase(vector<int>& v, int value);
bool cmp(pair<int, double> p1, pair<int, double> p2);
bool isFileExists(string& name);
struct Hcore {
    vector<unordered_map<int, int>> beta_max;
    vector<unordered_map<int, int>> alpha_max;
};
bool vm_same(vector<unordered_map<int, int>>& vm1, vector<unordered_map<int, int>>& vm2);
void hcore_same(Hcore& hcore1, Hcore& hcore2);
void preserveVertex(string dir, int perc);//没用到