#include <stdio.h>
#include "lzw_tablica.h"

TablicaElement tablica[4096];

void tablica_dodaj(int prefiks, int znak, int warotosclzw) {
    tablica[warotosclzw].prefiks = prefiks;
    tablica[warotosclzw].znak = znak;
}

int tablica_prefiks(int wartosc) {
    return tablica[wartosc].prefiks;
}

int tablica_znak(int wartosc) {
    return tablica[wartosc].znak;
}
