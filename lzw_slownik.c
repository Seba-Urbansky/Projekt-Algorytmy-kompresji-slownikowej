#include <stdio.h>
#include <stdlib.h>
#include "lzw_slownik.h"

SlownikWezel *slownik, *ogon;

/*! \fn void slownik_inicjalizacja()
    \brief
    Zadeklarowanie wezela (SlownikWezel), Uzywam petli i wypisuje w petli znaki ASCII.
    Node wskazuje na prefiks -1 oraz na znak ktory jest iteratorem. Na koncu uzywam funkcji
    dodaj_wezel;
   
*/


void slownik_inicjalizacja() {
    int i;
    SlownikWezel *node;
    for (i = 0; i < 256; i++) { // ASCII
        node = (SlownikWezel *)malloc(sizeof(SlownikWezel));
        node->prefiks = -1;
        node->znak = i;
        dodaj_wezel(node);
    }       
}

/*! \fn void dodaj_wezel(SlownikWezel *wezel) 
    \brief
    Jesli slownik nie jest pusty. W petli wezel jest rowny wskaznikowi ogona na nastepny element.
    - W przeciwnym wypadku slownik jest rowny wezel. Ogon jest rowny wezlowi. 
    - Pusty element jest rowny wskaznikowi wezla na nastepny element.

    \param wezel
   
*/


void dodaj_wezel(SlownikWezel *wezel) {
    if (slownik != NULL) ogon->nastepny = wezel;
    else slownik = wezel;
    ogon = wezel;
    wezel->nastepny = NULL;
}

/*! \fn void slownik_zniszcz() 
    \brief
    Dopoki slownik nie jest pusty. W petli while slownik jest rowny wskaznikowi slownikowi
    na nastepny element.
   
*/

void slownik_zniszcz() {
    while (slownik != NULL) {
        slownik = slownik->nastepny; 
    }
}

/*! \fn int slownik_szukaj(int prefiks, int znak) 
    \brief
   W petli wezel jest rowny slownikowi, jesli wezel nie jest pusty, wezel jest rowny wskaznikowi
   wezla na nastepny element.
    - W petli wystepuje warunek if prefiks jest rowny wskaznikowi wezla na prefiks oraz znak jest 
    rowny wskaznikowi wezla na znak. W warunku if returnem wskazujemy wezlem na wartosclzw.
    Na koncu zwracamy wartosc -1;


   \return Zwraca wartosc liczbowa szukana slownika
   \param prefiks
   \param znak
   
*/

int slownik_szukaj(int prefiks, int znak) {
    SlownikWezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->nastepny) { 
        if (wezel->prefiks == prefiks && wezel->znak == znak) return wezel->wartosclzw;
    }
    return -1;
}

/*! \fn int slownik_prefiks(int value) 
    \brief
  

   \return Zwraca wartosc liczbowa prefiks
   \param prefiks
   \param znak
   
*/


int slownik_prefiks(int value) {
    SlownikWezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->nastepny) { 
        if (wezel->wartosclzw == value) return wezel->prefiks;
    }
    return -1;
}

int slownik_znak(int value) {
    SlownikWezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->nastepny) { 
        if (wezel->wartosclzw == value) {
           
            return wezel->znak;
        }
    }
    return -1;
}


void slownik_dodaj(int prefiks, int znak, int wartosclzw) {
    SlownikWezel *wezel;
    wezel = (SlownikWezel *)malloc(sizeof(SlownikWezel));
    wezel->wartosclzw = wartosclzw;
    wezel->prefiks = prefiks;
    wezel->znak = znak;
    
    dodaj_wezel(wezel);
}
