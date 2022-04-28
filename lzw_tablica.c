#include <stdio.h>
#include "lzw.h"


Element_slownik Tablica_slownik[4095];


void dodanie_tablicy_slownika(int prefiks, int postac, int warotosclzw) {
    Tablica_slownik[warotosclzw].prefiks = prefiks;
    Tablica_slownik[warotosclzw].postac = postac;
}

int slownik_tablica_prefiks(int wartosc) {
    return Tablica_slownik[wartosc].prefiks;
}

int slownik_tablica_postac(int wartosc) {
    return Tablica_slownik[wartosc].postac;
}
