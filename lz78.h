#ifndef LZ78_H
#define LZ78_H /*!< deklaracja lz78h */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char indeks;


/*! \fn typedef struct WezelStruktura
    \brief
    To jest struktura calego wezla
    Zadeklarowane są w niej idx, znak, dziecko.ś
   
*/

typedef struct WezelStruktura
{
    indeks idx;
    char znak;
    struct ListaStruktura* dziecko;
} Wezel;


/*! \fn ttypedef struct ListaStruktura
    \brief
    To jest struktura calego listy z wezlem
    Zadeklarowane są w niej wezel oraz nastepny
   
*/

typedef struct ListaStruktura
{
    struct WezelStruktura wezel;
    struct ListaStruktura* nastepny;
} Lista;

/*! \fn Deklaracje Funkcji
    \brief
    Pod spodem sa zadeklarowane funkcje dla lz78.c
   
*/


void dodaj_potomka(Lista** dziecko, indeks idx, char znak);


Lista* wyszukaj_potomka(Lista* dziecko, char znak);


Wezel* wyszukaj(Wezel* rodzic, char* znak, long long int* pozycja, long long int dlugosc_napisu);


void kompresuj(char* znak, long long int dlugosc_napisu, char* nazwa_pliku_wyjsciowego);


long long int dlugosc_slowa(indeks* idx, long long int pozycja);


char* czytaj_slowo(indeks* idx, char* znak, long long int pozycja, long long int dlugosc_slowa, char* slowo);


void dekompresuj(indeks* idx, char* znak, long long int rozmiar_tablic, char* nazwa_pliku_wyjsciowego);


void wczytaj_kompresje(char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);


void wczytaj_dekompresje(char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);


void usun_slownik(Wezel* drzewo);

#endif