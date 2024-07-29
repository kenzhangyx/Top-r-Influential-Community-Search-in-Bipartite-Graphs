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
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "bipartite.h"
#include "utility.h"
#include <unordered_map>
#include <unordered_set>

void compute_beta_max(BiGraph& g,int alpha, vector<unordered_map<int, int>>& beta_max);
void compute_alpha_max(BiGraph& G, int beta, vector<unordered_map<int, int>>& alpha_max);
bool is_alpha_beta(int alpha,int beta,BiGraph& g);
double compute_avg(BiGraph& g);
Hcore BasicDecom(BiGraph& G);