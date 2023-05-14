#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
  char *firstName;
  char *secondName;
  int points;
};

struct Team {
  int numPlayers;
  char *name;
  float teamScore;
  struct Player *P;
};

struct lstTeam {
  struct Team T;
  struct lstTeam *next, *prev;
};

struct Node {
  struct Team T;
  struct Node *next;
};
struct Node_Q {
  struct Match {
    struct Team Team1;
    struct Team Team2;
  } Match;
  struct Node_Q *next;
};
struct Q {
  struct Node_Q *front, *rear;
};

struct N {  // nod arbore
  struct Team T;
  struct N *left, *right;
};

typedef struct N N_tree;
typedef struct Node_Q Node_Q;
typedef struct Match Match;
typedef struct Q Queue;
typedef struct lstTeam lstTeam;
typedef struct Team Team;
typedef struct Player Player;
typedef struct Node Node;

Queue *createQueue();
void enQueue(Queue *, Team, Team);
int isEmptyQ(Queue *);
Match deQueue(Queue *);
void deleteQueue(Queue *);

void push(Node **, Team);
Team pop(Node **);
int isEmptyS(Node *);
void deleteNode(Node **);
Team top(Node *);

void initTree(N_tree **, Team);
int isEmpty(N_tree *);
int isInterior(N_tree *);
int isLeaf(N_tree *);
void preorder(N_tree *);
void postorder(N_tree *);
N_tree *newN_tree(Team);
N_tree *insert(N_tree *, Team);

void swap(float *, float *);
int partition(float *, int, int);
void quickSort(float *, int, int);