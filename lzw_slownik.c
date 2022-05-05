#include <stdio.h>
#include <stdlib.h>
#include "lzw_slownik.h"

SlownikWezel *slownik, *ogon;

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

void dodaj_wezel(SlownikWezel *wezel) {
    if (slownik != NULL) ogon->nastepny = wezel;
    else slownik = wezel;
    ogon = wezel;
    wezel->nastepny = NULL;
}

void slownik_zniszcz() {
    while (slownik != NULL) {
        slownik = slownik->nastepny; 
    }
}

int slownik_szukaj(int prefiks, int znak) {
    SlownikWezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->nastepny) { 
        if (wezel->prefiks == prefiks && wezel->znak == znak) return wezel->wartosclzw;
    }
    return -1;
}

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
