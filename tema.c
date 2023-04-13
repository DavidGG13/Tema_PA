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
  struct Player *P;
};

struct lstTeam {
  struct Team T;
  struct lstTeam *next, *prev;
};

typedef struct lstTeam lstTeam;
typedef struct Team Team;
typedef struct Player Player;

void citireF(FILE *f, lstTeam *l) {
  int n, i, j;
  fscanf(f, "%d", &n);
  //printf("Numarul de echipe este: %d\n", n);
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
    
    //printf("Nume echipa: %s  Numar membrii: %d\n", l->T.name, l->T.numPlayers);
    
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
      //printf("Nume: %s  Prenume: %s  Scor: %d\n", l->T.P[j].secondName, l->T.P[j].firstName, l->T.P[j].points);
    }
    
    lstTeam *p;
    p = (lstTeam *)malloc(sizeof(lstTeam));
    l->next = p;
    p->prev = l;
    l = l->next;
    l->next = NULL;
  }
  l=l->prev;
  l->next=NULL;
  fclose(f);
}


void scriereF (FILE *f, lstTeam *l){
  while(l->next!=NULL){ 
   l=l->next;
   }
  while(l!=NULL){ 
   fputs(l->T.name, f);
   l=l->prev;
   }
}

int main() {
  FILE *d; 
  FILE *r;
  FILE *c;
  if ((d = fopen("date/t1/d.in", "r+t")) == NULL ||(r = fopen("out/out1.out", "w+t") ) == NULL || (c = fopen("date/t1/c.in", "r+t")) == NULL) {
    printf("Unul sau ambele fisiere nu poate/pot fi deschis/e !\n");
    exit(1);
  }
  lstTeam *lista;
  lista = (lstTeam *)malloc(sizeof(lstTeam));
  lista->next = NULL;
  lista->prev = NULL;
  
  citireF(d, lista);
  scriereF(r, lista);
}