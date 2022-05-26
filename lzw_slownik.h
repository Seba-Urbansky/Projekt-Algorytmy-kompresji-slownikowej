#include <stdio.h>
#include <stdlib.h>

#define slownik_wielkosc 4096  /*!< zdefinowanie wielkosci uzywanego slownika */

    
 /*! \brief  To jest struktura calego wezla Slownika Zadeklarowane są w niej wartosclzw, prefiks, znak. */
typedef struct SlownikWezelStruktura {
    int wartosclzw; 
    int prefiks; 
    int znak; 
    struct SlownikWezelStruktura *nastepny;
} SlownikWezel;

/*! \fn Deklaracje funkcji
    \brief
    Tutaj sa deklaracje funkcji uzywane do slownika.
   
*/

void slownik_inicjalizacja();
void dodaj_wezel(SlownikWezel *wezel);
void slownik_zniszcz();
int slownik_szukaj(int prefiks, int znak);
int slownik_prefiks(int value);
int slownik_znak(int value);
void slownik_dodaj(int prefiks, int znak, int wartosclzw);
