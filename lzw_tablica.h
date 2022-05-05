#include <stdio.h>

typedef struct TablicaElementStruktura{
    int prefiks; 
    int znak; 
} TablicaElement;

void tablica_dodaj(int prefiks, int znak, int warotosclzw);
int tablica_prefiks(int wartosc);
int tablica_znak(int wartosc);
