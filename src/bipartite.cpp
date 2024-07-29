//
// Created by 张 ken on 2024/4/6.
//
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <unordered_set>
#include <map>
#include <set>
#include <cstdlib>
#include <fstream>
#include <queue>
//#include "utility.h"
#include "bipartite.h"
#define MAXSIZE 10000000
using namespace std;
static int attr_num=0;
bool operator==(Edge e1, Edge e2)
{
    return e1.u == e2.u && e1.v == e2.v;
}
bool operator < (Edge e1, Edge e2) {
    if (e1.u != e2.u) return e1.u < e2.u;
    return e1.v < e2.v;
}

BiGraph::BiGraph(){
    dir="";
    num_v1=0;//上层顶点的数量
    num_v2=0;//下层顶点的数量
    num_edges=0;//边的数量

    neighbor_v1.resize(10000000);
    neighbor_v2.resize(10000000);

    v1.clear();
    v2.clear();

    degree_v1.resize(10000000, 0);
    degree_v2.resize(10000000, 0);

    left_index.clear();
    right_index.clear();
    v1_max_degree = 0;//上层顶点最大的度数
    v2_max_degree = 0;//下层顶点最大的度数
    v1_max_attr = 0;
    v2_max_attr = 0;
}
BiGraph::BiGraph(int n1,int n2){
    dir="";
    num_v1=0;//上层顶点的数量
    num_v2=0;//下层顶点的数量
    num_edges=0;//边的数量

    neighbor_v1.resize(n1+5);
    neighbor_v2.resize(n2+5);

    v1.clear();
    v2.clear();

    degree_v1.resize(n1+5, 0);
    degree_v2.resize(n2+5, 0);

    left_index.clear();
    right_index.clear();
    v1_max_degree = 0;//上层顶点最大的度数
    v2_max_degree = 0;//下层顶点最大的度数
    v1_max_attr = 0;
    v2_max_attr = 0;
}
BiGraph::BiGraph(string dir){
    num_v1 = 0;
    num_v2 = 0;
    num_edges = 0;

    neighbor_v1.clear();
    neighbor_v2.clear();

    v1.clear();
    v2.clear();

    degree_v1.clear();
    degree_v2.clear();

    //KKCore index left (x,*) right (*,x)
    left_index.clear();
    right_index.clear();
    v1_max_degree = 0;
    v2_max_degree = 0;
    v1_max_attr = 0;
    v2_max_attr = 0;
    this->dir = dir;
    loadGraph(dir);
}
BiGraph::BiGraph(string dir, string perck)
{
    num_v1 = 0;
    num_v2 = 0;
    num_edges = 0;

    neighbor_v1.clear();
    neighbor_v2.clear();

    degree_v1.clear();
    degree_v2.clear();


    left_index.clear();
    right_index.clear();
    v1_max_degree = 0;
    v2_max_degree = 0;
    v1_max_attr = 0;
    v2_max_attr = 0;
    this->dir = dir;
    loadGraph(dir, perck);
}
//初始化函数，
void BiGraph::init(unsigned int num1, unsigned int num2)
{
    num_v1 = num1;
    num_v2 = num2;

    neighbor_v1.resize(num_v1);//初始化vector,存的是v1的邻居
    neighbor_v2.resize(num_v2);

    degree_v1.resize(num_v1);//初始化vector,存的是v1的度数
    degree_v2.resize(num_v2);

    fill_n(degree_v1.begin(), num_v1, 0);//度数初始都设置为0
    fill_n(degree_v2.begin(), num_v2, 0);

    left_delete.resize(num_v1);
    right_delete.resize(num_v2);
    for (int i = 0; i < num1; ++i)
	{
		v1.emplace_back(i);

	}
	for (int i = 0; i < num2; ++i)
	{
		v2.emplace_back(i);
	}
}
//存图
void BiGraph::loadGraph(string dir)
{
    unsigned int n1, n2;
    unsigned int edges = 0;
    int u, v, is_u;
    char chs[100];
    int r;

    string nodeFile = dir + "node2.txt";
    string edgeFile = dir + "edge2.txt";

    FILE* nodeGraph = fopen(nodeFile.c_str(), "r");
    FILE* edgeGraph = fopen(edgeFile.c_str(), "r");
   if (fscanf(nodeGraph, "%d\n%d\n%d",&edges, &n1, &n2) != 3)
    {
        fprintf(stderr, "Bad file format:edges n1 n2 incorrect\n");
        exit(1);
    }

    fprintf(stdout, "edges: %d,n1: %d, n2: %d\n",edges, n1, n2);

    init(n1, n2);

    while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
    {
        //fprintf(stderr, "%d, %d\n", u, v);
        if (r != 2)
        {
            fprintf(stderr, "Bad file format: u v incorrect\n");
            exit(1);
        }
        //v1.emplace_back(u-1);
        //v2.emplace_back(v-1);
        addEdge(u - 1, v - 1);//数据集编号从1开始，所以要-1
        //num_edges++;
    }

    fclose(nodeGraph);
    fclose(edgeGraph);

    for (int i = 0; i < num_v1; ++i)
    {
        neighbor_v1[i].shrink_to_fit();//将 neighbor_v1[i] 中的存储空间调整为其当前存储元素的最小可能大小，以节省内存
        sort(neighbor_v1[i].begin(), neighbor_v1[i].end(), [](int a, int b) {
        return a > b; // 降序，如果想要升序则使用 a < b
    });//将某个点的邻居按序号从小到大排序
    }
    for (int i = 0; i < num_v2; ++i)
    {
        neighbor_v2[i].shrink_to_fit();
        sort(neighbor_v2[i].begin(), neighbor_v2[i].end(), [](int a, int b) {
        return a > b; // 降序，如果想要升序则使用 a < b
    });
    }
}
//没用到
void BiGraph::loadGraph(string dir, string perck)
{
    unsigned int n1, n2;
    unsigned int edges = 0;
    int u, v, is_u;
    char chs[100];
    int r;

    string nodeFile = dir + "node.txt";
    string edgeFile = dir + "edge_" + perck + ".txt";

    FILE* nodeGraph = fopen(nodeFile.c_str(), "r");
    FILE* edgeGraph = fopen(edgeFile.c_str(), "r");

    if (fscanf(nodeGraph, "%d\n%d\n%d",&edges, &n1, &n2) != 3)
    {
        fprintf(stderr, "Bad file format:edges n1 n2 incorrect\n");
        exit(1);
    }

    fprintf(stdout, "edges: %d,n1: %d, n2: %d\n",edges, n1, n2);

    init(n1, n2);

    while ((r = fscanf(edgeGraph, "%d %d", &u, &v)) != EOF)
    {
        //fprintf(stderr, "%d, %d\n", u, v);
        if (r != 2)
        {
            fprintf(stderr, "Bad file format: u v incorrect\n");
            exit(1);
        }

        addEdge(u - 1, v - 1);
        //num_edges++;
    }

    fclose(nodeGraph);
    fclose(edgeGraph);

    for (int i = 0; i < num_v1; ++i)
    {
        neighbor_v1[i].shrink_to_fit();
        sort(neighbor_v1[i].begin(), neighbor_v1[i].end());
    }
    for (int i = 0; i < num_v2; ++i)
    {
        neighbor_v2[i].shrink_to_fit();
        sort(neighbor_v2[i].begin(), neighbor_v2[i].end());
    }
}

void BiGraph::addVertex(bool is_u,int u)
{
	if (is_u)
	{
		v1.emplace_back(u);
		++num_v1;
	}
	else{
		v2.emplace_back(u);
		++num_v2;
	}
}
//在两个顶点间增加边
void BiGraph::addEdge(int u, int v)
{
    neighbor_v1[u].emplace_back(v);//加入邻居
    ++degree_v1[u];//顶点度数增加
    if (degree_v1[u] > v1_max_degree) v1_max_degree = degree_v1[u];
    neighbor_v2[v].emplace_back(u);
    ++degree_v2[v];
    if (degree_v2[v] > v2_max_degree) v2_max_degree = degree_v2[v];
    num_edges++;
}
//删边
void BiGraph::deleteEdge(int u, int v)
{
    for (int i = 0; i < degree_v1[u]; ++i)
    {
        int vv = neighbor_v1[u][i];
        if (vv == v)
        {
            swap(neighbor_v1[u][i], neighbor_v1[u][degree_v1[u] - 1]);
            --degree_v1[u];
            neighbor_v1[u].pop_back();
            break;
        }
    }

    for (int i = 0; i < degree_v2[v]; ++i)
    {
        int uu = neighbor_v2[v][i];
        if (uu == u)
        {
            swap(neighbor_v2[v][i], neighbor_v2[v][degree_v2[v] - 1]);
            --degree_v2[v];
            neighbor_v2[v].pop_back();
            break;
        }
    }
}
void BiGraph::deleteEdge2(int u, int v){
    --degree_v1[u];
    --degree_v2[v];
    erase(neighbor_v1[u],v);//在u的邻居中删除v，即邻接表删除
    erase(neighbor_v2[v],u);

}
//删点
void BiGraph::deleteVertex(bool is_u, int u) {
    //is_u代表是否是U集合的点，即上层顶点
    if (is_u) {
        for (int v : neighbor_v1[u]) {
            erase(neighbor_v2[v], u);
            --degree_v2[v];
            --num_edges;
        }
        neighbor_v1[u].clear();
        degree_v1[u] = 0;
        --num_v1;
        erase(v1,u);
    }
    else {
        for (int v : neighbor_v2[u]) {
            erase(neighbor_v1[v], u);
            --degree_v1[v];
            --num_edges;
        }
        neighbor_v2[u].clear();
        degree_v2[u] = 0;
        --num_v2;
        erase(v2,u);
    }
}

//判断两个点之间是否有边
bool BiGraph::isEdge(int u, int v)
{

    for (auto it = neighbor_v1[u].begin(); it != neighbor_v1[u].end(); it++) {
        if (*it == v) return true;
    }
    return false;
}

//判断两个图是否一样
bool check_same(BiGraph& g1, BiGraph& g2) {
    if (g1.num_v1 != g2.num_v1 || g1.num_v2 != g2.num_v2) {
        cout << "Error: num_v not same" << endl;
        return false;
    }
    for (int i = 0; i < g1.num_v1; i++) {
        if (g1.degree_v1[i] != g2.degree_v1[i]) {
            cout << "Error: degree_v1 not same: " << g1.degree_v1[i] << " " << g2.degree_v1[i] << endl;
            return false;
        }
        unordered_map<int, bool> show;
        for (int& v : g1.neighbor_v1[i]) {
            if (show[v]) {
                cout << "Error: neighbor_v1 repeat" << endl;
                return false;
            }
            show[v] = true;
        }
        for (int& v : g2.neighbor_v1[i]) {
            if (!show[v]) {
                cout << "Error: g1.neighbor_v1 g2.neighbor_v1 not same" << endl;
                return false;
            }
        }
    }
    for (int i = 0; i < g1.num_v2; i++) {
        if (g1.degree_v2[i] != g2.degree_v2[i]) {
            cout << "Error: degree_v2 not same: " << g1.degree_v2[i] << " " << g2.degree_v2[i] << endl;
            return false;
        }
        unordered_map<int, bool> show;
        for (int& v : g1.neighbor_v2[i]) {
            if (show[v]) {
                cout << "Error: neighbor_v2 repeat" << endl;
                return false;
            }
            show[v] = true;
        }
        for (int& v : g2.neighbor_v2[i]) {
            if (!show[v]) {
                cout << "Error: g1.neighbor_v2 g2.neighbor_v2 not same" << endl;
                return false;
            }
        }
    }
    return true;
}


