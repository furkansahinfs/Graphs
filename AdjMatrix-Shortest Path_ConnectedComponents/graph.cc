#include <iostream>
#include <queue>
#include <vector>
#include "graph.hpp"

using namespace std;

GraphAdjMat::GraphAdjMat(int numVertices) 
{
    this->numVertices = numVertices;
    adjMatrix = new bool*[numVertices];
    for (int i = 0; i < numVertices; i++) 
    {
      adjMatrix[i] = new bool[numVertices];

      for (int j = 0; j < numVertices; j++)
        adjMatrix[i][j] = false;
    }
}

  // Add edges
  void GraphAdjMat::insert(int i, int j) 
  {
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
  }

  bool** GraphAdjMat::returnMatrix() 
  {
   return adjMatrix;
  }

  // Print the martix
  void GraphAdjMat::print() 
  {

    //Print as matrix
    for (int i = 0; i < numVertices; i++) {
      cout << i << " : ";
      for (int j = 0; j < numVertices; j++)
        cout << adjMatrix[i][j] << " ";
      cout << "\n";
    }

    cout << "\n";
    //Print normally
    for (int i = 0; i < numVertices; i++) {
      cout << i << " : ";
      for (int j = 0; j < numVertices; j++)
        if(adjMatrix[i][j]){
          cout << j<< " ";
        }
      cout << "\n";
    }
  }

  GraphAdjMat::~GraphAdjMat() 
  {
    for (int i = 0; i < numVertices; i++)
      delete[] adjMatrix[i];
    delete[] adjMatrix;
  }
  



int GraphAdjMat::shortest_path(int src, int dst,stack<int>& path)
{
      bool* mark = new bool[numVertices];
      queue<int> bfs_queue;
      int* pred = new int[numVertices];


      bfs_queue.push(src);
      mark[src] = true;
      pred[src] = -1;

      while (!bfs_queue.empty())
      {
        int current = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < numVertices; i++)
        {
            if ( (adjMatrix[current][i]) && (!mark[i]) )
            {
                pred[i] = current;
                mark[i] = true;
                bfs_queue.push(i);
            }          
        }
      }

    if(mark[dst])
    {
      for (int v = dst; v != -1; v = pred[v])
        path.push(v);

      return path.size();
    }

     
    else
    {
      return 0;
    }
     
     
}

int GraphAdjMat::connected_components(vector<int> &ids)
{
    int cc_id=0;
    queue<int> queue;
    int n = numVertices;
    bool* mark = new bool[n];

    for(int i=1;i<n;i++)
        mark[i]=false;

    mark[0]=true;
    queue.push(0);

    while(!queue.empty())
    {
        int current = queue.front();
        queue.pop();  
        list<int> neighborsList = getNeighbors(current); //returns list of neighbours of given vertice
        ids.push_back(cc_id);
        
        if(!neighborsList.empty())
        {
            list<int>::iterator it;
            for (it=neighborsList.begin(); it!=neighborsList.end(); it++)
            {
                if(mark[*it]==false)
                {
                    queue.push(*it);
                    mark[*it]=true;
                }
                
            }
        }

        if(queue.empty())
        {
            cc_id++;
            for(int i=0;i<n;i++)
            {
                if(mark[i]==false)
                {
                    queue.push(i);
                    mark[i]=true;
                    break;
                }
            }
            
        }
    }

    return cc_id;
}


list<int> GraphAdjMat::getNeighbors(int v)
 {
    list<int> x;
    int n = numVertices;
    bool* visited = new bool[n];
    if(v<0||v>=n)
      return x;

     for(int j=0;j<n;j++)
     {
        if(adjMatrix[v][j]!=0){
            x.push_front(j);
        }

     }
     return x;
 }




