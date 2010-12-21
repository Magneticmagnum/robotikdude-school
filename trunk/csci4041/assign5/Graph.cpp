#include "Graph.h"
//#include <climits>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>

int Graph::size()
{
  return n;
}

Graph::Vertex& Graph::getVertex(const int v)
{
  return vertexes_[v];
}

Graph::Vertex& Graph::operator[](const int i)
{
  return vertexes_[i];
}

Graph* Graph::build(const std::string& file)
{
  std::ifstream input(file.c_str());
  if (input.fail()) {
    // ERROR: failed to read file
    return 0;
  }

  const int BUFFER_SIZE = 1024;
  char buffer[BUFFER_SIZE];
  int n = 0;
  int m = 0;

  char* u_char;
  char* v_char;
  char* weight_char;
  int u;
  int v;
  int weight;

  // **************************************************************************
  // find n and m
  // **************************************************************************
  std::cout << "Finding n and m" << std::endl;
  while (!input.eof()) {
    input.getline(buffer, BUFFER_SIZE);
    if (!input.fail() //
        && (u_char = strtok(buffer, " ")) != 0 //
        && (v_char = strtok(0, " ")) != 0 //
        && (u = atoi(u_char)) != 0 //
        && (v = atoi(v_char)) != 0) {
      m += 2;
      n = std::max(n, std::max(u, v));
    } // else => failed to read line correctly
  }

  Graph* graph = new Graph();
  graph->n = n;
  graph->m = m;
  graph->x_adj = (int*) calloc(n + 1, sizeof(int));
  graph->adj = (int*) calloc(m, sizeof(int));
  graph->adj_wgt = (int*) calloc(m, sizeof(int));
  graph->edges_ = (Graph::Edge*) calloc(m, sizeof(Graph::Edge));
  graph->vertexes_ = (Graph::Vertex*) calloc(m, sizeof(Graph::Vertex));

  if (graph->x_adj == 0 || graph->adj == 0 || graph->adj_wgt == 0
      || graph->edges_ == 0 || graph->vertexes_ == 0) {
    // ERROR: failed to allocate memory
    return 0;
  }

  input.clear();
  input.seekg(0, std::ios::beg);

  // **************************************************************************
  // a count of how many edges connect to each vertex
  // **************************************************************************
  std::cout << "Counting edges for each vertex" << std::endl;
  int count[n];
  for (int i = 0; i < n; i++)
    count[i] = 0;

  // list goes from vertex #1 ... #n
  while (!input.eof()) {
    input.getline(buffer, BUFFER_SIZE);
    if (!input.fail() //
        && (u_char = strtok(buffer, " ")) != 0 //
        && (v_char = strtok(0, " ")) != 0 //
        && (u = atoi(u_char) - 1) != -1 // offset by 1
        && (v = atoi(v_char) - 1) != -1) { // offset by 1
      count[u]++;
      count[v]++;
    } // else => failed to read line correctly
  }

  graph->x_adj[0] = 0;
  graph->x_adj[n] = m;
  for (int i = 1; i < n; i++) {
    graph->x_adj[i] = graph->x_adj[i - 1] + count[i - 1];
  }
  if (graph->x_adj[n - 1] + count[n - 1] > m) {
    std::cout << "Weird error..." << std::endl;
  }

  input.clear();
  input.seekg(0, std::ios::beg);

  // **************************************************************************
  // resolving each edge
  // **************************************************************************
  std::cout << "Storing each edge" << std::endl;
  // use to count how many times we've seen each vertex so far
  for (int i = 0; i < n; i++)
    count[i] = 0;

  // list goes from vertex #1 ... #n
  while (!input.eof()) {
    input.getline(buffer, BUFFER_SIZE);
    if (!input.fail() //
        && (u_char = strtok(buffer, " ")) != 0 //
        && (v_char = strtok(0, " ")) != 0 //
        && (weight_char = strtok(0, " ")) != 0 //
        && (u = atoi(u_char) - 1) != -1 // offset by 1
        && (v = atoi(v_char) - 1) != -1 // offset by 1
        && (weight = atoi(weight_char)) != 0) {
      //      if (graph->x_adj[u] + count[u] >= m) {
      //        std::cout << "SEG u=" << u << " x_adj=" << graph->x_adj[u] << " count="
      //            << count[u] << std::endl;
      //        std::cout << u_char << " " << v_char << " " << weight_char << std::endl;
      //      }
      //      if (graph->x_adj[v] + count[v] >= m) {
      //        std::cout << "SEG u=" << u << " v=" << v << " x_adj="
      //            << graph->x_adj[v] << " count=" << count[v] << std::endl;
      //        std::cout << u_char << " " << v_char << " " << weight_char << std::endl;
      //      }
      graph->adj[graph->x_adj[u] + count[u]] = v;
      graph->adj[graph->x_adj[v] + count[v]] = u;
      graph->adj_wgt[graph->x_adj[u] + count[u]] = weight;
      graph->adj_wgt[graph->x_adj[v] + count[v]] = weight;

      count[u]++;
      count[v]++;
    } // else => failed to read line correctly
  }

  // **************************************************************************
  // build the Vertex and Edge lists
  // **************************************************************************
  std::cout << "Building vertex and edge lists" << std::endl;
  for (int i = 0; i < n; i++) {
    graph->vertexes_[i] = Graph::Vertex(i, graph);
  }

  for (int i = 0; i < m; i++) {
    graph->edges_[i] = Graph::Edge(i, graph);
  }

  return graph;
}
