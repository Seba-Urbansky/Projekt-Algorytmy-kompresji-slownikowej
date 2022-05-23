#ifndef LZW_H
#define LZW_H

#include <stdio.h>
#include <stdlib.h>
#include "lzw_slownik.h"
#include "lzw_tablica.h"

/*! \fn Deklaracja funkcji
    \brief
    Pod spodem sa zadeklarowane funkcje dla lzw.c
   
*/

void wczytaj_kompresje_LZW(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego);
void kompresuj_LZW(FILE *wejscie_plik, FILE *wyjscie_plik);
void wczytaj_dekompresje_LZW(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego);
void dekompresuj_LZW(FILE *wejscie_plik, FILE *wyjscie_plik);
int dekoduj_LZW(int kod, FILE * wyjscie_plik);
int dekoduj(int kod, FILE * wyjscie_plik);
void pisz_binarnie(FILE * wyjscie, int kod);
int czytaj_binarnie(FILE * wejscie);

#endif