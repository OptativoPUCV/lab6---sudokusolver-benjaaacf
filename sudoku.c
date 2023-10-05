#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) { return 1; }

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int i, j, valor;

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        for (valor = 1; valor < 10; valor++) {
          n->sudo[i][j] = valor;
          if (is_valid(n)) {
            Node *adj = copy(n);
            pushBack(list, adj);
          }
        }
        n->sudo[i][j] = 0;
        return list;
      }
    }
  }

  return list;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) {
  Stack *stack;
  stack = createStack();
  push(stack, initial);
  *cont = 0;
  while (get_size(stack) != 0) {
    Node *nodo;
    nodo = top(stack);
    pop(stack);
    *cont = *cont - 1;
    if (is_final(nodo) == 10) {
      return NULL;
    }
    if (is_final(nodo) == 1) {
      return nodo;
    }

    List *adj = get_adj_nodes(nodo);
    Node *copia = first(adj);
    while (copia != NULL) {
      push(stack, copia);
      copia = next(adj);
      *cont = *cont + 1;
    }
  }

  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/