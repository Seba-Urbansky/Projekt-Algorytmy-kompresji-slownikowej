#include <stdio.h>


/*! \brief  Tutaj jest zadeklarowana struktura dla tablicy element. */
typedef struct TablicaElementStruktura{
    int prefiks; 
    int znak; 
} TablicaElement;

/*! \fn Deklaracja funkcji
    \brief
    Tutaj sa zadeklarowane funkcje dla tablicy lzw.


*/

void tablica_dodaj(int prefiks, int znak, int warotosclzw);
int tablica_prefiks(int wartosc);
int tablica_znak(int wartosc);
