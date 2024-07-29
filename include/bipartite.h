#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <unordered_set>
#include "utility.h"

struct Edge {
    int u, v;
    friend bool operator==(Edge a, Edge b);
    friend bool operator < (Edge a, Edge b);
};
class BiGraph
{

public:

    BiGraph(std::string dir);
    BiGraph(std::string dir, std::string perck);
    BiGraph();
    BiGraph(int n1,int n2);
    ~BiGraph() {}

    void addEdge(int u, int v);//加边
    void addVertex(bool is_u,int u);//加点
    void deleteEdge(int u, int v);//删边
    void deleteEdge2(int u, int v);//删边
    void deleteVertex(bool is_u, int u);//删点
    bool isEdge(int u, int v);//两个顶点是否有边
    int getV1Num() { return num_v1; }//上层顶点的数量
    int getV2Num() { return num_v2; }//下层顶点的数量
    int getV1Degree(int u) { return degree_v1[u]; }//上层顶点的度数
    int getV2Degree(int u) { return degree_v2[u]; }//下层顶点的度数
    std::vector<int>& getV2Neighbors(int u) { return neighbor_v2[u]; }//邻居
    std::vector<int>& getV1Neighbors(int u) { return neighbor_v1[u]; }

public:

    void init(unsigned int num_v1, unsigned int num_v2);//初始化，具体描述在cpp里
    void loadGraph(std::string dir);//具体描述在cpp里
    void loadGraph(std::string dir, std::string perck);//没用到
    bool desc(int a,int b);

    static BiGraph NullBigraph();

    std::string dir;
    int num_v1;//上层顶点数量
    int num_v2;//下层顶点数量
    int num_edges;//边的总数

    std::vector<int> v1;//上层顶点的集合
    std::vector<int> v2;//下层顶点的集合

    std::vector<std::vector<int>> neighbor_v1;//上层顶点的邻居
    std::vector<std::vector<int>> neighbor_v2;//下层顶点的邻居

    std::vector<std::unordered_set<int>> neighborHash_v1;
    std::vector<std::unordered_set<int>> neighborHash_v2;

    std::vector<int> degree_v1;//上层顶点度数，下面同理
    std::vector<int> degree_v2;

public:


    std::vector<std::vector<int>> left_index;//没用到
    std::vector<std::vector<int>> right_index;
    int v1_max_degree;//最大度数
    int v2_max_degree;

    int v1_max_attr;//没用到
    int v2_max_attr;
    std::vector<bool> left_delete;//没用到
    std::vector<bool> right_delete;
    // for dynamic update
    std::vector<std::vector<int>> left_index_old;//没用到
    std::vector<std::vector<int>> right_index_old;
    //BiGraph operator=(const BiGraph& g);
};
bool check_same(BiGraph& g1, BiGraph& g2);
