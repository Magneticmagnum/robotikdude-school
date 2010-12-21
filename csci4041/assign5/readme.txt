/**
 * CSci4041 F2010 Assignment 5
 * section: 3
 * login: norma272
 * date: 12/20/10
 * name: Brian Norman
 * id: 4332223
 */

To compile, simple type 'make', the make file will do the rest.
  $ make

Running follows the standards laid out by the assignment, the first argument
is the name of the graph file and the second is the file to store the resulting
MST value and edge listing.
  $ ./mst1 graph1.txt graph1.out
  $ ./mst2 graph3.txt graph3.out

mst1 is straight from the book, copied from the psudocode on page 634.

mst2 is an adjustment of mst1. Instead of preloading all the vertexes into the
queue, it attempts to load them on the fly as they are needed. (Doing so very
poorly as you will see.)