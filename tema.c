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

typedef struct lstTeam lstTeam;
typedef struct Team Team;
typedef struct Player Player;

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
    l = l->prev;
  }
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  int pivot = array[high];  // select the rightmost element as pivot
                            // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;

      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);

  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

void delNode(lstTeam *l) {}

void Eliminate(lstTeam *l, int n) {
  int i, m = 1, diff;
  float v[n];
  lstTeam *p = l, *q;
  for (i = 0; i < n; i++, p = p->next) {
    v[i] = p->T.teamScore;
  }

  quickSort(v, 0, n - 1);

  while (m < n) {
    m = m * 2;
  }
  m = m / 2;
  diff = n - m;
  m=diff;
  i=0;
  diff = v[diff - 1];
  p = l;
  while (p) {
    if (diff >= p->T.teamScore && i<diff) {
      lstTeam *temp;
      temp=p;
      q=p->prev;
      p=p->next;
      q->next=p;
      p->prev=q;
      free(temp);
    }
  }
}

int main(int argc, char *argv[]) {
  FILE *d;
  FILE *r;
  FILE *c;
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

  ch = getc(c);
  fseek(c, 0L, SEEK_SET);
  while (ch != EOF) {
    fscanf(c, "%d", &i);
    cerinte = cerinte + i;
    ch = getc(c);
  }

  printf("cerinte = %d\n", cerinte);

  switch (cerinte) {
    case 1:
      n = citireF(d, lista);
      scriereF(r, lista);
      break;
    case 2:
      n = citireF(d, lista);
      scriereF(r, lista);
      break;
    case 3:
      n = citireF(d, lista);
      scriereF(r, lista);
      break;
    case 4:
      n = citireF(d, lista);
      scriereF(r, lista);
      break;
    default:
      printf("Nu au fost executate cerintele!\n");
      break;
  }
}