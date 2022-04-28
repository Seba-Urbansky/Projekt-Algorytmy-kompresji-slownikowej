

#ifndef LZW_H
#define LZW_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int prefiks; 
    int postac; 
} Element_slownik;

struct slownik_wezel {
    int wartosclzw; 
    int prefiks; 
    int postac; 
    struct slownik_wezel *nastepny;
};

enum {
    slownik_wielkosc = 4095, 
    kod_dlugosc = 12, 
    max_wartosc = slownik_wielkosc - 1
};

enum {
    pusty_prefiks = -1 
};

void dodanie_tablicy_slownika(int prefiks, int postac, int wartosclzw);
int slownik_tablica_prefiks(int wartosc_lzw);
int slownik_tablica_postac(int wartosclzw);
void kompresuj_LZW(FILE *wejscie_plik, FILE *wyjscie_plik);
void dekompresuj_LZW(FILE *wejscie_plik, FILE *wyjscie_plik);
int dekoduj(int kod, FILE * wyjscie_plik);
void slownik_w_tym();
void dodaj_wezel(struct slownik_wezel *wezel);
void slownik_zniszcz();
int slownik_zajrzyj(int prefiks, int postac);
int slownik_prefiks(int wartosclzw);
int slownik_postac(int wartosclzw);
void slownik_dodaj(int prefiks, int postac, int wartosclzw);



#endif