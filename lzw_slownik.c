
#include <stdio.h>
#include <stdlib.h>
#include "lzw.h"
enum {
    pusty_prefiks = -1 
};

struct slownik_wezel *slownik, *tail;

void slownik_w_tym() {
    int i;
    struct slownik_wezel *node;
    for (i = 0; i < 256; i++) { // ASCII
        node = (struct slownik_wezel *)malloc(sizeof(struct slownik_wezel));
        node->prefiks = pusty_prefiks;
        node->postac = i;
        dodaj_wezel(node);
    }       
}



void dodaj_wezel(struct slownik_wezel *wezel) {
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

int slownik_zajrzyj(int prefiks, int postac) {
    struct slownik_wezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->next) { 
        if (wezel->prefiks == prefiks && wezel->postac == postac) return wezel->wartosclzw;
    }
    return pusty_prefix;
}

int slownik_prefiks(int value) {
    struct slownik_wezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->nastepny) { 
        if (wezel->wartosclzw == value) return wezel->prefiks;
    }
    return -1;
}

int slownik_postac(int value) {
    struct slownik_wezel *wezel;
    for (wezel = slownik; wezel != NULL; wezel = wezel->nastepny) { 
        if (wezel->wartosclzw == value) {
           
            return wezel->postac;
        }
    }
    return -1;
}


void slownik_dodaj(int prefiks, int postac, int wartosclzw) {
    struct slownik_wezel *wezel;
    wezel = (struct slownik_wezel *)malloc(sizeof(struct slownik_wezel));
    wezel->wartosclzw = wartosclzw;
    wezel->prefiks = prefiks;
    wezel->postac = postac;
    
    dodaj_wezel(wezel);
}
