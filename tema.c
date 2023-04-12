#include <stdio.h>
#include <stdlib.h>

struct Player
{
    char* firstName;
    char* secondName;
    int points;
};

struct Team{
    int numPlayers;
    char *name;
    struct Player *P;
};

struct lstTeam{
    struct Team *T;
    struct lstTeam *next, *prev;
};

int main(){
    FILE *d;
    if((d=fopen("d.in","r+t"))==NULL)
    {
        printf("Fisierul nu poate fi deschis !\n");
        exit(1);
    }
}