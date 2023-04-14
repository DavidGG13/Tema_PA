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

void Eliminate(lstTeam *l, int n) {
  int i;
  float v[n];
  lstTeam *p = l;
  for (i = 0; i < n; i++, p = p->next) {
    v[i] = p->T.teamScore;
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