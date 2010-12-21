GCC = g++
CFLAGS = 
LDFLAGS = 

OBJS = \
	Graph.o \
	GraphVertex.o \
	GraphEdge.o

all: mst1 mst2

mst1: mst1.cpp $(OBJS) MinHeap.h
	$(GCC) $(CFLAGS) mst1.cpp $(OBJS) MinHeap.h -o mst1
	
mst2: mst2.cpp $(OBJS) MinHeap.h
	$(GCC) $(CFLAGS) mst2.cpp $(OBJS) MinHeap.h -o mst2

Graph.o: Graph.h Graph.cpp
	$(GCC) $(CFLAGS) -c Graph.cpp

GraphVertex.o: Graph.h GraphVertex.cpp
	$(GCC) $(CFLAGS) -c GraphVertex.cpp

GraphEdge.o: Graph.h GraphEdge.cpp
	$(GCC) $(CFLAGS) -c GraphEdge.cpp

clean:
	rm -f mst1 mst2 *.o