#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>
#include <iostream>
using namespace std;


class GraphAdjMat {
public:

  GraphAdjMat(int numVertices);
  ~GraphAdjMat();

  int V() const { return numVertices; }
  void insert(int i, int j);
  void print();
  bool** returnMatrix();
  int shortest_path(int src, int dst,std::stack<int>& path);
  int connected_components(std::vector<int> &ids);
  list<int> getNeighbors(int v);


 private:
  bool** adjMatrix;
  int numVertices;
};

#endif
