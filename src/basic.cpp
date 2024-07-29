//
// Created by 张 ken on 2024/4/6.
//
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
// #include "bipartite.cpp"
#include <unordered_map>
#include <unordered_set>
#include "basic.h"
// #include "utility.h"
bool is_alpha_beta(int alpha,int beta,BiGraph& g){
    BiGraph GPrime=g;
    while (!GPrime.v1.empty())
    {
        int u=GPrime.v1.back();
        GPrime.v1.pop_back();
        if(GPrime.getV1Degree(u)<alpha){
            return false;
        }
    }
    while (!GPrime.v2.empty())
    {
        int v=GPrime.v2.back();
        GPrime.v2.pop_back();
        if(GPrime.getV2Degree(v)<beta){
            return false;
        }
    }
    return true;
}
double compute_avg(BiGraph& g){
    BiGraph GPrime=g;
    double sum_u=0;
    double sum_v=0;
    double res=0;//结果
    while (!GPrime.v1.empty())
    {
        int u=GPrime.v1.back();
        GPrime.v1.pop_back();
        sum_u+=u;
    }
    while (!GPrime.v2.empty())
    {
        int v=GPrime.v2.back();
        GPrime.v2.pop_back();
        sum_v+=v;
    }
    res=sum_u/GPrime.getV1Num()+sum_v/GPrime.getV2Num();
    return res;
}

void compute_beta_max(BiGraph& g,int alpha, vector<unordered_map<int, int>>& beta_max){
    vector<int> vis_u(g.num_v1,0);
    vector<int> vis_v(g.num_v2,0);
    BiGraph GPrime=g;
    //cout<<GPrime.num_edges<<endl;
    for (int u = 0; u < g.getV1Num(); ++u)
    {
        //cout<<GPrime.getV1Degree(u)<<endl;
        if (GPrime.getV1Degree(u)<alpha)
        {
            GPrime.deleteVertex(true,u);
            cout<<u<<" ";
            vis_u[u]=1;//表示已经删除
        }
    }
    cout<<endl;
    //cout<<GPrime.getV1Num()<<endl;
    while (GPrime.getV1Num()!=0&&GPrime.getV2Num()!=0)//图不为空
    {

        //cout<<GPrime.getV2Num()<<endl;
        //cout<<GPrime.getV2Degree(1)<<endl;
        while (GPrime.getV2Num()!=0)
        {
            int beta=4;
            //cout<<beta<<endl;
            for (int v = 0; v < g.getV2Num(); ++v)
            {
                if (vis_v[v]==0)
                {
                    cout<<v<<"  is  ";
                    beta=min(beta,GPrime.getV2Degree(v));
                    cout<<beta<<endl;
                }
            }
            cout<<"-------------------------"<<endl;
            for (int v = 0; v < g.getV2Num(); ++v) {
                //cout<<v<<"is"<<GPrime.getV2Degree(v)<<" ";
                if (GPrime.getV2Degree(v) <= beta&&vis_v[v]==0) {
                    GPrime.deleteVertex(false, v);
                    vis_v[v]=1;
                    cout<<v<<"has been shan"<<endl;
                }
                //cout<<endl;
                //cout<<GPrime.getV1Degree(2)<<endl;
                for (int u = 0; u < g.getV1Num(); ++u) {
                    if (GPrime.getV1Degree(u)<alpha&&vis_u[u]==0) {
                        beta_max[u][alpha]=beta;
                        //cout<<u<<"-"<<beta_max[u][alpha]<<endl;
                        GPrime.deleteVertex(true, u);
                        vis_u[u]=1;

                    }
                }
            }
        }
    }

}
void compute_alpha_max(BiGraph& G, int beta, vector<unordered_map<int, int>>& alpha_max) {
    BiGraph GPrime = G;
    for (int v = 0; v < G.getV2Num(); ++v) {
        if (GPrime.getV2Degree(v) < beta) {
            GPrime.deleteVertex(false, v);
            GPrime.num_v2--;

        }
    }

    while (!GPrime.getV2Num()) {
        int alpha = GPrime.getV1Degree(0);
        for (int u = 1; u < GPrime.getV1Num(); ++u) {
            alpha = std::min(alpha, GPrime.getV1Degree(u));
        }

        for (int u = 0; u < GPrime.getV1Num(); ++u) {
            if (GPrime.getV1Degree(u) <= alpha) {
                GPrime.deleteVertex(true, u);
                GPrime.num_v1--;
            }
        }

        for (int v = 0; v < GPrime.getV2Num(); ++v) {
            if (GPrime.getV2Degree(v) < beta) {
                alpha_max[v][beta]=alpha;
                //cout<<v<<"-"<<alpha_max[v][beta]<<endl;
                GPrime.deleteVertex(false, v);
            }
        }
    }
}
Hcore BasicDecom(BiGraph& G){
    vector<unordered_map<int, int>> beta_max(G.num_v1), alpha_max(G.num_v2);
    int dmaxU=G.v1_max_degree;
    int dmaxV=G.v2_max_degree;
    for (int alpha = 1; alpha <= dmaxU; ++alpha) {
        compute_beta_max(G, alpha, beta_max);
    }
    for (int beta = 1; beta <= dmaxV; ++beta)
    {
        compute_alpha_max(G,beta,alpha_max);
    }
    return {beta_max,alpha_max};
}
