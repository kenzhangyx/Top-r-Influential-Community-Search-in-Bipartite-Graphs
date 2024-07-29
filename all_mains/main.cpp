
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

using namespace std;

int Alpha,Beta;
int r;
vector<BiGraph> topr;


bool notexist(BiGraph& g) 
{
    int flag=true;
    sort(g.v1.begin(), g.v1.end());
    sort(g.v2.begin(), g.v2.end());
    for  (auto i:topr)
    {
        if (i.num_v1==g.num_v1 && i.num_v2==g.num_v2)
        {
            sort(i.v1.begin(), i.v1.end());    
            sort(i.v2.begin(), i.v2.end());
            bool sig=false;
            int size1=g.v1.size();
            int size2=g.v2.size();
            for (int ii = 0; ii < size1-1; ii++) 
            {
            auto j = g.v1[ii];
            auto jj = i.v1[ii];
            if (j!=jj) sig=true;

            }
            for (int ii = 0; ii < size2-1; ii++) 
            {
            auto j = g.v2[ii];
            auto jj = i.v2[ii];
            if (j!=jj) sig=true;
             
            }
            if (sig==false) {
                return false;
            }
        }
    }
    return flag;
}

bool compareinf(BiGraph& g1, BiGraph& g2)
{
    if (compute_avg(g1) < compute_avg(g2)) return true;
    else return false;
}

void update(BiGraph& tmp)   //update top-r array
{
    if (notexist(tmp) == true)
    {
        double val=compute_avg(tmp);
        sort(topr.begin(), topr.end(), compareinf); //make top-r ascending
        if (topr.size()<r)
        {
           topr.push_back(tmp);
            return ;
        }
        else
        {     
            auto i=topr[0];
            if (compute_avg(i) < val || (compute_avg(i) == val && i.num_v1+i.num_v2<tmp.num_v1+tmp.num_v2))
            {
                topr[0] = tmp;
                return ;
            }
        }
    }
    
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

vector<BiGraph> connect(BiGraph& g)
{
    vector<BiGraph> s;
    map<int,bool> visit1;
    map<int,bool> visit2;
    for (auto i:g.v1)
    {
        visit1[i]=false;
    }
    for (auto i:g.v2)
    {
        visit2[i]=false;
    }
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
                    for (auto j:g.v2)
                    {
                        if (visit2[j] == false && g.isEdge(node,j))
                        {
                            visit2[j] = true;
                            nodeset[1].push_back(j);
                            q2.push(j);
                        }
                    }
                }
                else //select form upper set
                {
                    for (auto j:g.v1)
                    {
                        if (visit1[j] == false && g.isEdge(j,node))
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

void Find(BiGraph& g)
{
    BiGraph abcore = findabcore(g);
    
    vector<BiGraph> setlist = connect(abcore);

    for (auto subg:setlist)
    {
        update(subg);
    }

    for (auto subg:setlist)
    {
        for (auto i:subg.v1)
        {
            BiGraph tmp=subg;
            tmp.deleteVertex(true,i);
            Find(tmp);
        }
        for (auto i:subg.v2)
        {
            BiGraph tmp=subg;
            tmp.deleteVertex(false,i);
            Find(tmp);
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

    auto start = std::chrono::high_resolution_clock::now();
    bitv1=vector<int>(g.num_v1,0);
    bitv2=vector<int>(g.num_v2,0);
    //Find(g);
    for (size_t i = 0; i < g.neighbor_v1.size(); ++i) {
        std::cout << "Node " << i << ":";
        for (const int& neighbor : g.neighbor_v1[i]) {
            std::cout << " " << neighbor;
        }
        std::cout << std::endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    // 计算持续时间
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // 输出结果
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;


    for (auto i:topr)
    {
        cout<<"V1:";
        for (auto j:i.v1) cout<<j<<" ";
        cout<<"V2:";
        for (auto j:i.v2) cout<<j<<" ";
        cout<<endl;
    }

    return  0;


}