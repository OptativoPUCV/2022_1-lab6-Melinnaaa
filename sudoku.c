#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct
{
  int sudo[9][9];
}Node;

Node* createNode()
{
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n)
{
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node* read_file (char* file_name)
{
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      if(!fscanf (file, "%d", &n->sudo[i][j]))
      {
        printf("failed to read data!");
      }
    }
  }
  fclose (file);
  return n;
}

void print_node(Node* n)
{
  int i,j;
  for(i=0;i<9;i++){
      for(j=0;j<9;j++)
        printf("%d ", n->sudo[i][j]);
      printf("\n");
  }
  printf("\n");
}

void cleanArray(int appears[10])
{
  for (int i = 0 ; i < 9 ; i = i + 1)
  {
    appears[i] = 0;
  }
}

int checkAppears(int appears[10])
{
  for (int i = 0 ; i < 9 ; i = i + 1)
  {
    if (appears[i] > 1) return 0;
  }
  return 1;
}

int checkCols(Node* n)
{
  int appears [10];
  int num;
  for (int i = 0 ; i < 9 ; i = i + 1)
  {
    cleanArray(appears);
    for (int j = 0 ; j < 9 ; j = j + 1)
    {
      num = n->sudo[i][j];
      appears[num-1] = appears[num-1] + 1;
    }
    if (checkAppears(appears) == 0) return 0;
  }
  return 1;
}

int checkFils (Node* n)
{
  int appears [10];
  int num;
  for (int i = 0 ; i < 9 ; i = i + 1)
  {
    cleanArray(appears);
    for (int j = 0 ; j < 9 ; j = j + 1)
    {
      num = n->sudo[j][i];
      appears[num-1] = appears[num-1] + 1;
    }
    if (checkAppears(appears) == 0) return 0;
  }
  return 1;
}

int checkSubMatrix(Node* n)
{
  int appears [10];
  int num;
  for (int m = 0 ; m < 9 ; m = m + 1)
  {
    cleanArray(appears);
    for (int p = 0 ; p < 9 ; p = p + 1)
    {
        int i=3*(m/3) + (p/3);
        int j=3*(m%3) + (p%3);
        num = n->sudo[i][j];
        appears[num-1] = appears[num-1] + 1;
    }
    if (checkAppears(appears) == 0) return 0;
  }
  return 1;
}

int is_valid(Node* n)
{
  //Se comprueban las filas
  if (checkFils(n) == 0) return 0;
  //Se comprueban las columnas
  if (checkCols(n) == 0) return 0;
  //Se comprueban las sub-matrices
  if (checkSubMatrix(n) == 0) return 0;
  return 1;
}

List* get_adj_nodes(Node* n)
{
  List* list=createList();
  for (int i = 0 ; i < 9 ; i = i + 1)
  {
    for (int j = 0 ; j < 9 ; j = j + 1)
    {
      if (n->sudo[i][j] == 0)
      {
        for (int num = 1 ; num < 10 ; num = num + 1) //Numero que rellena las casillas
        {
          n->sudo[i][j] = num;
          if (is_valid(n) == 1)
          {
            Node* adj_node = copy(n);
            pushBack(list, adj_node);
          }
        }
      }
    }
  }
  return list;
}


int is_final(Node* n)
{
  for (int i = 0; i < 9; i = i + 1)
  {
    for (int j = 0 ; j < 9 ; j = j + 1)
    {
      if (n->sudo[i][j] == 0) return  0;  
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* S = createStack();
  push(S, initial);
  *cont = 1;
  while (*cont != 0)
  {    
    Node* n = top(S);
    pop(S);
    *cont = *cont - 1;
    if (is_final(n) == 1) return n;
    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);
    while (aux != NULL)
    {
      push(S, aux);
      *cont = *cont + 1;
      aux = next(adj);
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