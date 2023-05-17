#include "library.h"

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
    l->T.name[strlen(l->T.name) - 2] = '\0';
    if (l->T.name[strlen(l->T.name) - 1] == ' ') {
      l->T.name[strlen(l->T.name) - 1] = '\0';
    }
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

int Eliminate(lstTeam *l, int n) {
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
  return m;
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

    n = 67 - strlen(M.Team2.name);
    fputs(M.Team1.name, f);
    for (i = strlen(M.Team1.name); i < n; i++) {
      if (i == 33) {
        fputc('-', f);
        continue;
      }
      fputc(' ', f);
    }
    fputs(M.Team2.name, f);
    fputc('\n', f);
    if (M.Team1.teamScore > M.Team2.teamScore) {
      push(W, M.Team1);
      push(L, M.Team2);
    } else {
      push(L, M.Team1);
      push(W, M.Team2);
    }
  }
}

void FINAL(FILE *f, Queue *q, int c) {
  Match M;
  Team T;
  fprintf(f, "\n--- ROUND NO:%d\n", c);
  M = (q->front)->Match;
  int i, n;
  fseek(f, 0L, SEEK_END);
  n = 67 - strlen(M.Team2.name);
  fputs(M.Team1.name, f);
  for (i = strlen(M.Team1.name); i < n; i++) {
    if (i == 33) {
      fputc('-', f);
      continue;
    }
    fputc(' ', f);
  }
  fputs(M.Team2.name, f);
  fputc('\n', f);
  if (M.Team1.teamScore > M.Team2.teamScore) {
    T = M.Team1;
  } else {
    T = M.Team2;
  }
  T.teamScore = T.teamScore + 1;
  for (i = 0; i < T.numPlayers; i++) {
    T.P[i].points = T.P[i].points + 1;
  }
  fprintf(f, "\nWINNERS OF ROUND NO:%d\n", c);
  fputs(T.name, f);
  n = 37;
  for (i = strlen(T.name); i < n; i++) {
    if (i == 34) {
      fputc('-', f);
      continue;
    }
    fputc(' ', f);
  }
  fprintf(f, "%.2f", T.teamScore);
  fputc('\n', f);
}

void transfer(FILE *f, Node *L, Node *W, Queue *q) {
  fseek(f, 0L, SEEK_END);
  int i, n = 37;

  int b = 0;
  while (W != NULL) {
    Team T;
    W->T.teamScore = W->T.teamScore + 1;
    for (i = 0; i < W->T.numPlayers; i++) {
      W->T.P[i].points = W->T.P[i].points + 1;
    }
    fputs(W->T.name, f);
    for (i = strlen(W->T.name); i < n; i++) {
      if (i == 34) {
        fputc('-', f);
        continue;
      }
      fputc(' ', f);
    }
    fprintf(f, "%.2f", W->T.teamScore);
    fputc('\n', f);
    if (b == 0) {
      T = W->T;
      b = 1;
    } else if (b == 1) {
      enQueue(q, T, W->T);
      // printf("%s vs %s\n", (q->rear)->Match.Team1.name,
      // (q->rear)->Match.Team2.name);
      b = 0;
    }
    // printf("%s\n", W->T.name);
    W = W->next;
  }
}

void create_tree(Node *q, N_tree **root) {
  while (q) {
    *root = insert(*root, q->T);
    // printf("%.2f  - %s\n", q->T.teamScore, q->T.name);
    q = q->next;
  }
}

void print_tree(FILE *f, N_tree *root) {
  fseek(f, 0L, SEEK_END);
  int i, n;
  if (root) {
    print_tree(f, root->right);
    root->height = height(root);
    // printf("Height: %d  Name: %s  Score: %.2f\n", root->height, root->T.name,
    // root->T.teamScore);
    fputs(root->T.name, f);
    n = 37;
    for (i = strlen(root->T.name); i < n; i++) {
      if (i == 34) {
        fputc('-', f);
        continue;
      }
      fputc(' ', f);
    }
    fprintf(f, "%.2f", root->T.teamScore);
    fputc('\n', f);
    print_tree(f, root->left);
  }
}

void BSTtoARRAY(N_tree *root, Node **st) {
  if (root) {
    BSTtoARRAY(root->left, st);
    push(st, root->T);
    BSTtoARRAY(root->right, st);
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
  N_tree *root;
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
      n = Eliminate(lista, n);
      scriereF(r, lista);

      add_queue(lista, queue);
      for (i = 0, n = n / 2; n > 1; i++, n = n / 2) {
        fprintf(r, "\n--- ROUND NO:%d\n", (i + 1));

        Play(r, queue, &Losers, &Winners);
        fprintf(r, "\nWINNERS OF ROUND NO:%d\n", (i + 1));

        transfer(r, Losers, Winners, queue);
        deleteNode(&Losers);
        deleteNode(&Winners);
      }
      FINAL(r, queue, i + 1);

      break;

    case 4:
      n = citireF(d, lista);
      n = Eliminate(lista, n);
      scriereF(r, lista);

      add_queue(lista, queue);
      for (i = 0, n = n / 2; n > 1; i++, n = n / 2) {
        fprintf(r, "\n--- ROUND NO:%d\n", (i + 1));

        Play(r, queue, &Losers, &Winners);
        fprintf(r, "\nWINNERS OF ROUND NO:%d\n", (i + 1));

        transfer(r, Losers, Winners, queue);

        if (n == 8) {
          create_tree(Winners, &root);
        }

        deleteNode(&Losers);
        deleteNode(&Winners);
      }
      FINAL(r, queue, i + 1);
      fprintf(r, "\nTOP 8 TEAMS:\n");
      print_tree(r, root);
      break;

    case 5:
      n = citireF(d, lista);
      n = Eliminate(lista, n);
      scriereF(r, lista);

      add_queue(lista, queue);
      for (i = 0, n = n / 2; n > 1; i++, n = n / 2) {
        fprintf(r, "\n--- ROUND NO:%d\n", (i + 1));

        Play(r, queue, &Losers, &Winners);
        fprintf(r, "\nWINNERS OF ROUND NO:%d\n", (i + 1));

        transfer(r, Losers, Winners, queue);

        if (n == 8) {
          create_tree(Winners, &root);
        }

        deleteNode(&Losers);
        deleteNode(&Winners);
      }
      FINAL(r, queue, i + 1);
      fprintf(r, "\nTOP 8 TEAMS:\n");
      print_tree(r, root);
      N_tree *avl;
      Node *st;

      BSTtoARRAY(root, &st);
      Team Tmm[8];
      for (i = 0; i < 8; i++) {
        Tmm[i] = st->T;
        pop(&st);
      }
      fprintf(r, "\nTHE LEVEL 2 TEAMS ARE: \n");
      avl = construct_avl(Tmm, 0, 7);
      printLevel(r, avl, 3);
      break;
    default:
      printf("Nu au fost executate cerintele!\n");
      break;
  }
}