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
  struct Team val;
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
typedef struct Node_Q Node_Q;
typedef struct Match Match;
typedef struct Q Queue;
typedef struct lstTeam lstTeam;
typedef struct Team Team;
typedef struct Player Player;
typedef struct Node Node;

// FUNCTII COADA
Queue *createQueue() {
  Queue *q;
  q = (Queue *)malloc(sizeof(Queue));
  if (q == NULL) return NULL;
  q->front = q->rear = NULL;
  return q;
}
void enQueue(Queue *q, Team t1, Team t2) {
  Node_Q *newNode = (Node_Q *)malloc(sizeof(Node_Q));
  newNode->Match.Team1 = t1;
  newNode->Match.Team2 = t2;
  newNode->next = NULL;
  // nodurile noi se adauga la finalul cozii
  if (q->rear == NULL) q->rear = newNode;
  // daca nu exista niciun nod in coada
  else {
    (q->rear)->next = newNode;
    (q->rear) = newNode;
  }
  // daca exita un singur element in coada
  if (q->front == NULL) q->front = q->rear;
}
int isEmptyQ(Queue *q) { return (q->front == NULL); }
Match deQueue(Queue *q) {
  Node_Q *aux;
  Match m;
  aux = q->front;
  m.Team1 = aux->Match.Team1;
  m.Team2 = aux->Match.Team2;
  q->front = (q->front)->next;
  free(aux);
  return m;
}
void deleteQueue(Queue *q) {
  Node_Q *aux;
  while (!isEmptyQ(q)) {
    aux = q->front;
    q->front = q->front->next;
    // printf (”% d ” , aux -> val );
    free(aux);
  }
  free(q);
}

// FUNCTII STIVA
void push(Node **top, Team v) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->val = v;
  newNode->next = *top;
  *top = newNode;
}
Team pop(Node **top) {
  Node *temp = (*top);
  Team aux = temp->val;
  *top = (*top)->next;
  free(temp);
  return aux;
}
int isEmptyS(Node *top) { return top == NULL; }
Team top(Node *top) {
  Team empty;
  if (isEmptyS(top)) return empty;
  return top->val;
}
void deleteNode(Node **top) {
  Node *temp;
  while ((*top) != NULL) {
    temp = *top;
    *top = (*top)->next;
    free(temp);
  }
}

int citireF(FILE *f, lstTeam *l) {
  int n, i, j;
  fscanf(f, "%d", &n);
  // printf("Numarul de echipe este: %d\n", n);
  for (i = 0; i < n; i++) {
    fscanf(f, "%d", &(l->T.numPlayers));
    l->T.P = (Player *)malloc(sizeof(Player) * l->T.numPlayers);

    char *buffer;
    buffer = (char *)malloc(sizeof(char) * 100);
    fgetc(f);
    fgets(buffer, 100, f);
    l->T.name = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(l->T.name, buffer);
    free(buffer);
    l->T.name[strlen(l->T.name) - 1] = '\0';
    // printf("Nume echipa: %s  Numar membrii: %d\n", l->T.name,
    // l->T.numPlayers);
    l->T.teamScore = 0;

    for (j = 0; j < l->T.numPlayers; j++) {
      buffer = (char *)malloc(sizeof(char) * 100);
      fscanf(f, "%s", buffer);
      l->T.P[j].secondName = (char *)malloc(sizeof(char) * strlen(buffer));
      strcpy(l->T.P[j].secondName, buffer);
      free(buffer);

      buffer = (char *)malloc(sizeof(char) * 100);
      fscanf(f, "%s", buffer);
      l->T.P[j].firstName = (char *)malloc(sizeof(char) * strlen(buffer));
      strcpy(l->T.P[j].firstName, buffer);
      free(buffer);

      fscanf(f, "%d", &(l->T.P[j].points));
      // printf("Nume: %s  Prenume: %s  Scor: %d\n", l->T.P[j].secondName,
      // l->T.P[j].firstName, l->T.P[j].points);
      l->T.teamScore = l->T.teamScore + l->T.P[j].points;
    }
    l->T.teamScore = l->T.teamScore / l->T.numPlayers;
    // printf("Name: %s\nScore: %.2f\n", l->T.name, l->T.teamScore);
    lstTeam *p;
    p = (lstTeam *)malloc(sizeof(lstTeam));
    l->next = p;
    p->prev = l;
    l = l->next;
    l->next = NULL;
  }
  l = l->prev;
  l->next = NULL;
  fclose(f);
  return n;
}

void scriereF(FILE *f, lstTeam *l) {
  while (l->next != NULL) {
    l = l->next;
  }
  while (l != NULL) {
    fputs(l->T.name, f);
    fputc('\n', f);
    l = l->prev;
  }
}

void swap(float *a, float *b) {
  float t = *a;
  *a = *b;
  *b = t;
}

int partition(float array[], int low, int high) {
  float pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(float array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);

    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void Eliminate(lstTeam *l, int n) {
  int i, m = 1, diff;
  float *v, f;
  v = (float *)malloc(sizeof(float) * n);
  lstTeam *p = l, *q, *fin;
  for (i = 0; i < n; i++, p = p->next) {
    v[i] = p->T.teamScore;
  }

  quickSort(v, 0, n - 1);

  while (m <= n) {
    m = m * 2;
  }
  m = m / 2;
  diff = n - m;
  m = diff;
  f = v[diff - 1];
  p = l;
  i = 0;
  while (p->next) {
    p = p->next;
  }
  fin = p;
  while (p) {
    if (f > p->T.teamScore && i < diff) {
      lstTeam *temp;
      temp = p;
      q = p->next;
      if (p->prev) {
        p = p->prev;
      } else {
        q->prev = NULL;
        break;
      }
      p->next = q;
      if (q != NULL) {
        q->prev = p;
      }
      free(temp);
      i++;
      continue;
    }
    p = p->prev;
  }
  p = fin;
  while (p) {
    if (f == p->T.teamScore && i < diff) {
      lstTeam *temp;
      temp = p;
      q = p->next;
      if (p->prev) {
        p = p->prev;
      } else {
        q->prev = NULL;
        break;
      }
      p->next = q;
      if (q != NULL) {
        q->prev = p;
      }
      free(temp);
      i++;
      continue;
    }
    p = p->prev;
  }
}

void add_queue(lstTeam *l, Queue *q) {
  while (l->next) {
    l = l->next;
  }
  lstTeam *p;
  p = l->prev;
  while (l->prev) {
    enQueue(q, l->T, p->T);

    l = p->prev;
    if (l == NULL) break;
    p = l->prev;
  }
}

void Play(FILE *f, Queue *q, Node **L, Node **W) {
  Match M;
  int i, n;
  fseek(f, 0L, SEEK_END);
  while (q->front) {
    M = deQueue(q);
    M.Team1.name[strlen(M.Team1.name) - 1] = '\0';
    n = 68 - strlen(M.Team2.name);
    fputs(M.Team1.name, f);
    for (i = strlen(M.Team1.name); i < n; i++) {
      if (i == 34) {
        fputc('-', f);
        continue;
      }
      fputc(' ', f);
    }
    fputs(M.Team2.name, f);
    if (M.Team1.teamScore >= M.Team1.teamScore) {
      push(W, M.Team1);
      M.Team1.teamScore = M.Team1.teamScore + 1;
      for (i = 0; i < M.Team1.numPlayers; i++) {
        M.Team1.P->points = M.Team1.P->points + 1;
      }
      push(L, M.Team2);
    } else {
      push(L, M.Team1);
      push(W, M.Team2);
      M.Team2.teamScore = M.Team2.teamScore + 1;
      for (i = 0; i < M.Team2.numPlayers; i++) {
        M.Team2.P->points = M.Team2.P->points + 1;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  FILE *d;
  FILE *r;
  FILE *c;
  //"Tema/d.in" "Tema/r.out" "Tema/c.in"
  if ((d = fopen(argv[2], "r+t")) == NULL ||
      (r = fopen(argv[3], "w+t")) == NULL ||
      (c = fopen(argv[1], "r+t")) == NULL) {
    printf("Unul sau ambele fisiere nu poate/pot fi deschis/e !\n");
    exit(1);
  }
  int cerinte = 0, i, n, ch;
  lstTeam *lista;
  lista = (lstTeam *)malloc(sizeof(lstTeam));
  lista->next = NULL;
  lista->prev = NULL;
  printf("Verificare..\n");
  ch = getc(c);
  fseek(c, 0L, SEEK_SET);
  while (ch != EOF) {
    fscanf(c, "%d", &i);
    cerinte = cerinte + i;
    ch = getc(c);
  }
  Queue *queue;
  queue = createQueue();
  Node *Winners, *Losers;
  printf("cerinte = %d\n", cerinte);
  switch (cerinte) {
    case 1:
      n = citireF(d, lista);
      scriereF(r, lista);
      break;
    case 2:
      n = citireF(d, lista);
      Eliminate(lista, n);
      scriereF(r, lista);
      break;
    case 3:
      n = citireF(d, lista);
      Eliminate(lista, n);
      scriereF(r, lista);
      add_queue(lista, queue);
      Play(r, queue, &Losers, &Winners);
      break;
    case 4:
      n = citireF(d, lista);
      Eliminate(lista, n);
      scriereF(r, lista);
      add_queue(lista, queue);
      Play(r, queue, &Losers, &Winners);
      break;
    default:
      printf("Nu au fost executate cerintele!\n");
      break;
  }
}