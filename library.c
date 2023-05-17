#include "library.h"

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
  newNode->T = v;
  newNode->next = *top;
  *top = newNode;
}
Team pop(Node **top) {
  Node *temp = (*top);
  Team aux = temp->T;
  *top = (*top)->next;
  free(temp);
  return aux;
}
int isEmptyS(Node *top) { return top == NULL; }
Team top(Node *top) {
  Team empty;
  if (isEmptyS(top)) return empty;
  return top->T;
}
void deleteNode(Node **top) {
  Node *temp;
  while ((*top) != NULL) {
    temp = *top;
    *top = (*top)->next;
    free(temp);
  }
}

void initTree(N_tree **root, Team t) {
  *root = (N_tree *)malloc(sizeof(N_tree));
  (*root)->left = (*root)->right = NULL;
  (*root)->T = t;
}

int isEmpty(N_tree *root)

{
  return (root == NULL);
}

int isInterior(N_tree *n)

{
  return (n->left != NULL || n->right != NULL);
}

int isLeaf(N_tree *n) {
  // return !isInterior(n);
  return (n->left == NULL && n->right == NULL);
}

void preorder(N_tree *root) {
  if (root) {
    printf("%s  %.2f  H:%d\n", root->T.name, root->T.teamScore, root->height);
    preorder(root->left);
    preorder(root->right);
  }
}
void postorder(N_tree *root) {
  if (root) {
    postorder(root->left);
    postorder(root->right);
    printf("%s  %.2f  H:%d\n", root->T.name, root->T.teamScore, root->height);
  }
}

void in_order(N_tree *root) {
  if (root) {
    in_order(root->right);
    printf("%s  %.2f  H:%d\n", root->T.name, root->T.teamScore, root->height);
    in_order(root->left);
  }
}
int height(N_tree *root) {
  int hs, hd;
  if (root == NULL) return -1;
  // inaltimea subarborelui stang
  hs = height(root->left);
  // inaltimea subarborelui drept
  hd = height(root->right);
  // returneaza inaltimea nodului
  return 1 + ((hs > hd) ? hs : hd);
}

N_tree *newN_tree(Team data) {
  N_tree *n_tree = (N_tree *)malloc(sizeof(N_tree));
  n_tree->T = data;
  n_tree->left = n_tree->right = NULL;
  return n_tree;
}
N_tree *insert(N_tree *n_tree, Team key) {
  if (n_tree == NULL) return newN_tree(key);
  if (key.teamScore == n_tree->T.teamScore &&
      strcmp(key.name, n_tree->T.name) < 0) {
    Team temp;
    temp = n_tree->T;
    n_tree->T = key;
    key = temp;
  }
  if (key.teamScore < n_tree->T.teamScore)
    n_tree->left = insert(n_tree->left, key);
  else if (key.teamScore >= n_tree->T.teamScore)
    n_tree->right = insert(n_tree->right, key);

  return n_tree;
}

N_tree *construct_avl(Team sorted_array[], int start, int end) {
  if (start > end) return NULL;

  int mid = (start + end) / 2;
  N_tree *root = newN_tree(sorted_array[mid]);

  root->left = construct_avl(sorted_array, start, mid - 1);
  root->right = construct_avl(sorted_array, mid + 1, end);

  root->height = 1 + max(height(root->left), height(root->right));

  return root;
}

void printLevel(FILE *f, N_tree *root, int level) {
  if (root == NULL) return;
  if (level == 1)
    fprintf(f, "%s\n", root->T.name);
  else if (level > 1) {
    printLevel(f, root->left, level - 1);
    printLevel(f, root->right, level - 1);
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