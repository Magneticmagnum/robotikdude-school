#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>
#include <cstdlib>

class Graph
{
  public:
    class Edge;
    class Vertex;

  private:
    // number of vertexes
    int n;
    // number of edges
    int m;
    // vertex weight, size n
    //    int* v_wgt;
    // start point of each edge list, size n+1
    int* x_adj;
    // edge list, size m
    int* adj;
    // edge weight, size m
    int* adj_wgt;

    // same as v_wgt
    Graph::Vertex* vertexes_;

    // same as adj and adj_wgt combined
    Graph::Edge* edges_;

  public:
    virtual ~Graph()
    {
      free (x_adj);
      free (adj);
      free (adj_wgt);
      free (vertexes_);
      free (edges_);
    }

    static Graph* build(const std::string& file);

    // size of graph, number of vertexes
    int size();

    Graph::Vertex& getVertex(const int v);

    Graph::Edge& getEdge(const int v, const int u);

    Graph::Vertex& operator[](const int i);

    void print()
    {
      int start = 0;
      for (int i = 0; i < m; i++) {
        if (i >= x_adj[start + 1])
          start++;
        std::cout << start << " " << adj[i] << " " << adj_wgt[i] << std::endl;
      }
    }
};

class Graph::Edge
{
  private:
    int edge_;
    Graph* self_;

  public:
    Edge(int e, Graph* self);

    int getWeight();
    Graph::Vertex& followArrow();
    operator int() const;
};

class Graph::Vertex
{
  private:
    int vertex_;
    Graph* self_;

  public:
    Vertex(int v, Graph* self);

    int id();
    int getWeight();
    Graph::Edge* getEdges();
    int getNumEdges();

    // returns the number of edges leaving this vertex
    int size();

    Graph::Edge& operator[](const int i);
    operator int() const;
    bool operator==(const Graph::Vertex& v);
};

#endif /* GRAPH_H_ */
