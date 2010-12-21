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

  for (int i = 0; i < G->size(); i++) {
    key[i] = 9000000;
    (*tree)[i] = -1;
  }

  key[r] = 0;

  MinHeap<int, Graph::Vertex> Q(G->size());
  Q.add(key + r, (*G)[r]);
  Q.build();

  // Solution
  MinHeap<int, Graph::Vertex> S(G->size());

  while (!Q.empty()) {

    Graph::Vertex u = Q.extractMin();
    S.add(key + u, u);

    // for each v element of Adj[u]
    for (int i = 0; i < u.size(); i++) {
      Graph::Vertex v = u[i].followArrow();

      if (!Q.contains(v)) {
        if (!S.contains(v)) {
          Q.add(key + v, v);
        }
      }

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
  output << "Prim's time: " << ptime << std::endl;
  for (int i = 0; i < g->size(); i++) {
    if (tree[i] != -1) {
      output << i + 1 << " " << tree[i] + 1 << std::endl;
    }
  }

  free(tree);
  delete (g);
  return 0;
}
