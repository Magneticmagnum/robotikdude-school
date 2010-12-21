#include "Graph.h"

Graph::Vertex::Vertex(int v, Graph* self)
{
  vertex_ = v;
  self_ = self;
}

int Graph::Vertex::id()
{
  return vertex_;
}

Graph::Edge* Graph::Vertex::getEdges()
{
  return self_->edges_ + self_->x_adj[vertex_];
}

int Graph::Vertex::size()
{
  return self_->x_adj[vertex_ + 1] - self_->x_adj[vertex_];
}

int Graph::Vertex::getNumEdges()
{
  return size();
}

Graph::Edge& Graph::Vertex::operator[](const int i)
{
  return self_->edges_[self_->x_adj[vertex_] + i];
}

Graph::Vertex::operator int() const
{
  return vertex_;
}

bool Graph::Vertex::operator==(const Graph::Vertex& v)
{
  return (this->vertex_ == v.vertex_);
}
