#include <stdio.h>
#include "lzw_tablica.h"

/*! \fn TablicaElement tablica[4096];
    \brief
    Korzystam tutaj z talicy 4096.
   
*/

TablicaElement tablica[4096];

/*! \fn void tablica_dodaj(int prefiks, int znak, int warotosclzw)
    \brief
    W funkcji dodaj do tablicy.
    Prefiks jest rowny tablica od wartosci lzw. prefiks
    Znak jest rowny tablicy od wartosci lzw. znak
    
    \param prefiks
    \param znak
    \param wartosclzw
   
*/

void tablica_dodaj(int prefiks, int znak, int warotosclzw) {
    tablica[warotosclzw].prefiks = prefiks;
    tablica[warotosclzw].znak = znak;
}

/*! \fn int tablica_prefiks(int wartosc)
    \brief
    Funkcja zwraca wartosci tablicy dla prefiksa.
    \param wartosc
    \return Zwraca wartosc liczbowa tablicy.prefiks
 
   
*/

int tablica_prefiks(int wartosc) {
    return tablica[wartosc].prefiks;
}

/*! \fn int tablica_znak(int wartosc)
    \brief
    Funkcja zwraca wartosci tablicy dla prefiksa.
    \param wartosc
    \return Zwraca wartosc liczbowa tablicy
 
   
*/

int tablica_znak(int wartosc) {
    return tablica[wartosc].znak;
}
