#include "Graph.h"

Graph::Edge::Edge(int e, Graph* self)
{
  edge_ = e;
  self_ = self;
}

int Graph::Edge::getWeight()
{
  return self_->adj_wgt[edge_];
}

Graph::Vertex& Graph::Edge::followArrow()
{
  return self_->vertexes_[self_->adj[edge_]];
}

Graph::Edge::operator int() const
{
  return edge_;
}
