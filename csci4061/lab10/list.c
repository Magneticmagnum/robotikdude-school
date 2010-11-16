#include <stdio.h>
#include <stdlib.h>

struct item
{
  char letter;
  struct item *next;
};
typedef struct item node;

//pointer to first node in the list
node *first;

int main(int argc, char *argv[])
{
  //create node to store 'a' and assign first to point to it
  node* a = (node*) malloc(sizeof(node));
  a->letter = 'a';
  a->next = NULL;
  first = a;

  //create nodes for 'b' 'c' 'd' and 'e' and insert into the list
  node* b = (node*) malloc(sizeof(node));
  b->letter = 'b';
  b->next = a;
  first = b;

  node* c = (node*) malloc(sizeof(node));
  c->letter = 'c';
  c->next = b;
  first = c;

  node* d = (node*) malloc(sizeof(node));
  d->letter = 'd';
  d->next = c;
  first = d;

  node* e = (node*) malloc(sizeof(node));
  e->letter = 'e';
  e->next = d;
  first = e;

  //Iterate through list and print out each character to the screen
  node* temp = first;
  while (temp != NULL) {
    printf("%c, ", temp->letter);
    temp = temp->next;
  }
  printf("\n");

  //delete the last node and reprint
  temp = first;
  if (temp != NULL && temp->next != NULL) {
    while (temp->next->next != NULL)
      temp = temp->next;
    free(temp->next);
    temp->next = NULL;
  }
  temp = first;
  while (temp != NULL) {
    printf("%c, ", temp->letter);
    temp = temp->next;
  }
  printf("\n");

  //delete the first node and reprint
  temp = first;
  if (temp != NULL) {
    first = first->next;
    free(temp);
  }
  temp = first;
  while (temp != NULL) {
    printf("%c, ", temp->letter);
    temp = temp->next;
  }
  printf("\n");

  //delete the node labeled 'c' and reprint
  temp = first;
  if (temp != NULL && temp->next != NULL) {
    while (temp->next != NULL && temp->next->letter != 'c')
      ;
    if (temp->next != NULL) {
      node* c = temp->next;
      temp->next = temp->next->next;
      free(c);
    }
  }
  temp = first;
  while (temp != NULL) {
    printf("%c, ", temp->letter);
    temp = temp->next;
  }
  printf("\n");

  //exit
  return 0;
}
