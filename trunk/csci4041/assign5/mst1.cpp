/**
 * CSci4041 F2010 Assignment 5
 * section: 3
 * login: norma272
 * date: 12/20/10
 * name: Brian Norman
 * id: 4332223
 */
#include "Graph.h"
#include "MinHeap.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <ctime>

//MST-PRIM(G, weight, r)
//  for each u element of V[G]
//    do key[u] = infinity
//      parent[u] = NULL
//  key[r] = 0
//  Q = V[G]
//  while Q is not empty
//    do u = EXTRACT-MIN(Q)
//      for each v element of Adj[u]
//        do if v element of Q and weight(u, v) < key[v]
//          then parent[v] = u
//            key[v] = weight(u, v)
long long prim(Graph* G, int r, int** tree)
{
  if (G == NULL) {
    // error
    return 0;
  }
  else if (G->size() <= 1) {
    // error
    return 0;
  }
  else if (r < 0 || r >= G->size()) {
    // error
    return 0;
  }

  int* key = (int*) malloc(sizeof(int) * G->size());
  *tree = (int*) malloc(sizeof(int) * G->size());

  // for each u element of V[G]
  for (int i = 0; i < G->size(); i++) {
    // key[u] = infinity
    key[i] = 9000000;
    // parent[u] = NULL
    (*tree)[i] = -1;
  }

  // key[r] = 0
  key[r] = 0;

  // Q = V[G]
  MinHeap<int, Graph::Vertex> Q(G->size());
  for (int i = 0; i < G->size(); i++) {
    Q.add(key + i, (*G)[i]);
  }
  Q.build();

  // while Q is not empty
  while (!Q.empty()) {
    // u = EXTRACT-MIN(Q)
    Graph::Vertex u = Q.extractMin();

    // for each v element of Adj[u]
    for (int i = 0; i < u.size(); i++) {
      Graph::Vertex v = u[i].followArrow();

      // do if v element of Q and weight(u, v) < key[v]
      if (Q.contains(v) && u[i].getWeight() < key[v]) {
        // parent[v] = u
        (*tree)[v] = u;
        // key[v] = weight(u, v)
        key[v] = u[i].getWeight();
      }
    }

    Q.build();
  }

  long long mst = 0;
  for (int i = 0; i < G->size(); i++) {
    if (key[i] == 9000000)
      std::cout << "ERROR: never visited " << i << std::endl;
    else
      mst += key[i];
  }

  free(key);
  return mst;
}

void usage(char* prog)
{
  std::cout << "USAGE " << prog << " <graph> <output tree>" << std::endl;
}

int main(int argc, char** argv)
{
  if (argc != 3) {
    usage(argv[0]);
    exit(0);
  }

  Graph* g = Graph::build(argv[1]);
  if (g == 0) {
    std::cout << "Could not create graph" << std::endl;
    usage(argv[0]);
    exit(0);
  }

  time_t start, end;
  int* tree;
  int ptime;

  std::cout << "Running Prim's algorithm" << std::endl;
  time(&start);
  ptime = prim(g, 0, &tree);
  time(&end);
  std::cout << "Took " << difftime(end, start) << " seconds" << std::endl;

  std::ofstream output(argv[2]);
  if (output.fail()) {
    std::cout << "Could not open output file" << std::endl;
    usage(argv[0]);
    exit(0);
  }
  output << "MST: " << ptime << std::endl;
  for (int i = 0; i < g->size(); i++) {
    if (tree[i] != -1) {
      output << i + 1 << " " << tree[i] + 1 << std::endl;
    }
  }

  free(tree);
  delete (g);
  return 0;
}
