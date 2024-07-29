
#include <atomic>
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
#include "basic.h"
#include "bipartite.h"
#include "utility.h"
#include<chrono>
#include<queue>
#define MAXSIZE 1000
using namespace std;

int Alpha,Beta;
int r;
vector<vector<vector<int>>> topr;

double max(double x, double y)
{
    if (x>y) return x;
    else return y;
}

double avg(vector<int>& nodeset)
{
    double sum;
    for (int i:nodeset)
    {
        sum+=i;
    }
    return sum/nodeset.size();
}



bool existU(int node, BiGraph& g)
{
    for (auto i:g.v1)
    {
        if (node == i) return true;
    }
    return false;
}

bool existV(int node, BiGraph& g)
{
    for (auto i:g.v2)
    {
        if (node == i) return true;
    }
    return false;
}

bool compareinf(vector<vector<int>>& g1, vector<vector<int>>& g2)
{
    if (avg(g1[0]) + avg(g1[1]) < avg(g2[0]) + avg(g2[1])) return true;
    else return false;
}

void update(vector<vector<int>>& tmp)   //update top-r array
{
        double val=avg(tmp[0])+avg(tmp[1]);
        sort(topr.begin(), topr.end(), compareinf); //make top-r ascending
        if (topr.size()<r)
        {
           topr.push_back(tmp);
            return ;
        }
        else
        {     
            auto i=topr[0];
            if (avg(i[0])+ avg(i[1])< val || (avg(i[0]) + avg(i[1]) == val && i[0].size()+i[1].size()<tmp[0].size()+tmp[1].size()))
            {
                topr[0] = tmp;
                return ;
            }
        }
}

bool desc(int a,int b)
{
    return a>b;
}


vector<int> bitv1;
vector<int> bitv2;
BiGraph findabcore(BiGraph &g) {
  vector<int> v11=g.v1;
  vector<int> v22=g.v2;
  queue<int> q1; // U中受影响的点
  queue<int> q2;
  //vector<int> bitv1(g.num_v1, 0);
  //vector<int> bitv2(g.num_v2, 0);
  // 先删除上层顶点小于a的顶点
  while (!v11.empty())
  {
    int a=v11.front();
    v11.erase(v11.begin());
    if (g.getV1Degree(a) < Alpha) {
      g.deleteVertex(true, a);
      
    }
  }

  while (!v22.empty())
  {
    int a=v22.front();
    v22.erase(v22.begin());
    if (g.getV2Degree(a) < Beta) {
        for (auto j:g.getV2Neighbors(a))
        {
        if (g.getV1Degree(j) < Alpha + 1) {   
          if (bitv1[j] == 0) {
            q1.push(j);
            bitv1[j] = 1;
          }
           
        }
        }
        
      g.deleteVertex(false, a);
      
    }
  }

  // V中受影响的点
  // 删除下层顶点小于b的点，此时U中受影响的点只能是被删除点的邻居，加入到队列q1中
 

  // 跟上述同理，受影响的只能是邻居节点
  while (!q1.empty() || !q2.empty()) {
    while (!q1.empty()) {
      int u = q1.front();
      q1.pop();
      for (auto v : g.getV1Neighbors(u)) {
        if (g.getV2Degree(v) < Beta + 1) {
          
            if (bitv2[v] == 0) {
            q2.push(v);
            bitv2[v] = 1;
          }
         
        }
      }
      g.deleteVertex(true, u);
      
    }
    while (!q2.empty()) {
      int v = q2.front();
      q2.pop();
      for (auto u : g.getV2Neighbors(v)) {
        if (g.getV1Degree(u) < Alpha + 1) {
          
         
           if (bitv1[u] == 0) {
            q1.push(u);
            bitv1[u] = 1;
          }
        }
      }
      g.deleteVertex(false, v);
      
    }
  }
  
  return g;
}

BiGraph fabc(BiGraph &g)
{
  
    vector<int> del1,del2;
    queue<int> q1; // U中受影响的点
    queue<int> q2;
    std::vector<int> deg1(g.num_v1, 0);

    std::vector<int> deg2(g.num_v2, 0);

    for (auto i:g.v1) deg1[i]=g.getV1Degree(i);
    for (auto i:g.v2) deg2[i]=g.getV2Degree(i);
    vector<int> v11=g.v1;
    vector<int> v22=g.v2;
    for (auto a:v11)
    {
    if (deg1[a] < Alpha) {
      deg1[a] = -1;
      del1.push_back(a);
      for (auto nei:g.getV1Neighbors(a))
      {
        deg2[nei]--;
      }
      bitv1[a] = 1;
    }
    } 

  for (auto a:v22)
  {
    if (deg2[a]< Beta && bitv2[a] == 0) {
        for (auto j:g.getV2Neighbors(a))
        {
        if (deg1[j] < Alpha+1) {   
          if (bitv1[j] == 0) {
            q1.push(j);
            bitv1[j] = 1;
          }
           
        }
        }
      deg2[a] = -1;
      for (auto nei:g.getV2Neighbors(a))
      {
        deg1[nei]--;
      }  
      del2.push_back(a);
      bitv2[a] = 1;
    }
  }

  // V中受影响的点
  // 删除下层顶点小于b的点，此时U中受影响的点只能是被删除点的邻居，加入到队列q1中
 

  // 跟上述同理，受影响的只能是邻居节点
  while (!q1.empty() || !q2.empty()) {
    while (!q1.empty()) {
      int u = q1.front();
      q1.pop();
      for (auto v : g.getV1Neighbors(u)) {
        if (deg2[v] < Beta + 1) {
          
            if (bitv2[v] == 0) {
            q2.push(v);
            bitv2[v] = 1;
          }
         
        }
      }
      deg1[u] = -1;
      del1.push_back(u);
      for (auto nei:g.getV1Neighbors(u))
      {
        deg2[nei]--;
      }
    }
    while (!q2.empty()) {
      int v = q2.front();
      q2.pop();
      for (auto u : g.getV2Neighbors(v)) {
        if (deg1[u] < Alpha + 1) {
          
         
           if (bitv1[u] == 0) {
            q1.push(u);
            bitv1[u] = 1;
          }
        }
      }
      deg2[v] = -1;
      del2.push_back(v);
      for (auto nei:g.getV2Neighbors(v))
      {
        deg1[nei]--;
      }
      
    }
  }
  // auto remain1 = g.v1;
  // auto remain2 = g.v2;
  // std::set<int> itemsToRemove(del1.begin(), del1.end());

  //   remain1.erase(std::remove_if(remain1.begin(), remain1.end(),
  //                             [&itemsToRemove](const int& item) {
  //                                 return itemsToRemove.count(item) > 0;
  //                             }),
  //              remain1.end());
  // std::set<int> itemsToRemove2(del2.begin(), del2.end());

  //   remain2.erase(std::remove_if(remain2.begin(), remain2.end(),
  //                             [&itemsToRemove2](const int& item) {
  //                                 return itemsToRemove2.count(item) > 0;
  //                             }),
  //              remain2.end());

  std::vector<bool> remain1(g.num_v1, true);
  std::vector<bool> remain2(g.num_v2, true);  
  for (auto i:del1) remain1[i] = false;
  for (auto i:del2) remain2[i] = false;

  BiGraph G(g.num_v1,g.num_v2);
  std::vector<int> visit2(g.num_v2, 0);
  std::vector<int> label2(g.num_v2);
  int count1=0;
  int count2=0;
  for (auto v1:g.v1)
  {
    if (remain1[v1] == true)
    {
      count1++;
      G.addVertex(true,count1);
      for (auto nei:g.getV1Neighbors(v1))
      {
        if (remain2[nei] == true) 
        {
          if (visit2[nei] == 1) G.addEdge(count1, label2[nei]);
          else{
            visit2[nei] = 1;
            count2++;
            label2[nei] = count2;
            G.addVertex(false, label2[nei]);
            G.addEdge(count1, label2[nei]);
          }
        }
      }
    }
  }
  cout<<G.num_v1+G.num_v2<<endl;
  cout<<"ab-core found"<<endl;
  return G;
  
}

vector<BiGraph> connect(BiGraph& g)
{
    vector<BiGraph> s;
    vector<bool> visit1(g.num_v1+5,false);
    vector<bool> visit2(g.num_v2+5,false);
    for (auto i:g.v1)
    {
        if (visit1[i] == false)
        {
            vector<vector<int>> nodeset;
            nodeset.push_back({});
            nodeset.push_back({});

            queue<int> q1;
            queue<int> q2;
            q1.push(i);
            visit1[i] = true;
            nodeset[0].push_back(i);
            int side;//0 is upper; 1 is lower
            while(q1.empty()==false || q2.empty()==false)
            {
                int node;
                bool flag=false;
                if (q1.empty()==false) {node = q1.front(); q1.pop(); side=0; flag=true; }
                if (q2.empty()==false && flag==false ) {node = q2.front(); q2.pop(); side=1;}
                if (side == 0) //select from lower set
                {
                    for (auto j:g.getV1Neighbors(node))
                    {
                        if (visit2[j] == false)
                        {
                            visit2[j] = true;
                            nodeset[1].push_back(j);
                            q2.push(j);
                        }
                    }
                }
                else //select form upper set
                {
                    for (auto j:g.getV2Neighbors(node))
                    {
                        if (visit1[j] == false)
                        {
                            visit1[j] = true;
                            nodeset[0].push_back(j);
                            q1.push(j);
                        }
                    }
                }
            }

            BiGraph tmpg = g;

            for (auto ii:g.v1)
            {
                if (std::count(nodeset[0].begin(), nodeset[0].end(), ii) == 0) tmpg.deleteVertex(true,ii);
                
            }
            for (auto ii:g.v2)
            {
                if (std::count(nodeset[1].begin(), nodeset[1].end(), ii) == 0) tmpg.deleteVertex(false,ii);
                
            }

            
            s.push_back(tmpg);
        } 
    }
    return s;
}

bool vecfind(vector<int>& candi,int node)
{
    for (auto i:candi)
    {
        if (node == i) return true;
    }
    return false;
}

void Find(BiGraph& g)
{ 
    vector<BiGraph> setlist = connect(g);
    cout<<"connected:"<<setlist.size()<<endl;
    for (auto cg:setlist)
    {
        for (auto i:cg.v1)
        {
            bool skip = false;
            vector<bool> visit1;
            visit1.resize(g.v1.size()+10, false);
            vector<bool> visit2;
            visit2.resize(g.v2.size()+10, false);
            vector<vector<int>> nodeset;
            nodeset.push_back({});
            nodeset.push_back({});

            queue<int> q1;
            queue<int> q2;
            q1.push(i);
            visit1[i] = true;
            nodeset[0].push_back(i);
            int side;//0 is upper; 1 is lowwer
            while(q1.empty()==false || q2.empty()==false)
            {
                int node;
                bool flag=false;
                if (q1.empty()==false) {node = q1.front(); q1.pop(); side=0; flag=true; }
                if (q2.empty()==false && flag==false ) {node = q2.front(); q2.pop(); side=1;}
                if (side == 0) //select from lower set  //take alpha nodes
                {
                    
                    int cnt=0;
                    for (auto k:cg.getV1Neighbors(node))
                    {
                        cnt++;
                        if (visit2[k] == false) 
                        {
                            visit2[k] = true;
                            if (cnt<=Alpha)
                            {
                            nodeset[1].push_back(k);
                            q2.push(k);
                            }
                        }
                        
                    }
                    
                    
                }
                else //select form upper set
                {
           
                    int cnt = 0;
                    for (auto k:cg.getV2Neighbors(node))
                    {
                        if (visit1[k] == false) 
                        {
                            visit1[k] = true;
                            if (cnt <= Beta) {
                            nodeset[0].push_back(k);
                            q1.push(k);
                            }
                        }
                        
                    }
                }
                if (topr.size()==r && avg(nodeset[0])+avg(nodeset[1]) < avg(topr[0][0]) + avg(topr[0][1]))
                {
                    skip = true;
                    break;
                }
            }

            if (skip == false)
            {    
            update(nodeset);
            }
        } 
    }
    
}

int main(){
    cout<<"write alpha,Beta:";
    cin>>Alpha>>Beta;
    cout<<endl<<"write r:";
    cin>>r;

    string dir="/home/desc/111abcore_topr/influencecommunity/";
    BiGraph g(dir);
    bitv1=vector<int>(g.num_v1,0);
    bitv2=vector<int>(g.num_v2,0);

    

    auto start = std::chrono::high_resolution_clock::now();
g = fabc(g);
   Find(g);

    auto stop = std::chrono::high_resolution_clock::now();

    // 计算持续时间
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // 输出结果
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  for (auto i:topr)
    {
        cout<<"V1:  ";
        for (auto j:i[0]) cout<<j<<" ";
        cout<<"   V2:  ";
        for (auto j:i[1]) cout<<j<<" ";
        cout<<endl;
    }
    return  0;


}