#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "lz78.h"
/*! \fn void dodaj_potomka(Lista **dziecko, indeks idx, char znak)
    \brief
    Jesli wskaznik na dziecko jest pusty alkokujemy pamiec na dziecko
    - Nastepnie jesli wskaznik na dziecko jest pusty to wtedy wychodzimy z program
    - W przeciwnym wypadku idx jest rowne wskaznikowi dziecka na wezel idx, znak jest
    rowny wskaznikowi dziecka na wezel znaku, natomiast wskaznik dziecka na wezel dziecka
    sa puste, wskaznik dziecka na nastepny tez jest pusty
    - W nastepnym przeciwnym wypadku wskaznik na aktualny jest rowny wskaznikowi na dziecko
    - Korzystam z warunku while i w nim jesli wskaznik akutualnego na nastepny nie jest pusty
    i aktualny jest rowny wskaznikowi aktualnego na nastepny
    - Jesli wskaznik aktualnego na nastepny jest pusty to wtedy wychodzimy z programu
    - Nastepnie w przeciwnym wypadku idx jest rowne wskaznikowi aktualnego na nastepny element oraz 
    na wezel idx, znak jest rowny wskaznikowi aktualnego na nastepny element oraz 
    na wezel znaku, natomiast wskaznik aktualnego na nastepny i na wezel dziecka sa puste,
    wskaznik aktualnego na nastepny sa puste

    \param dziecko 
    \param idx
    \param znak
*/

void dodaj_potomka(Lista **dziecko, indeks idx, char znak)
{
    if (*dziecko == NULL)
    {
        *dziecko = (Lista *)malloc(sizeof(Lista));
        if (*dziecko == NULL)
        {
            exit(0);
        }
        else
        {
            (*dziecko)->wezel.idx = idx;
            (*dziecko)->wezel.znak = znak;
            (*dziecko)->wezel.dziecko = NULL;
            (*dziecko)->nastepny = NULL;
        }
    }
    else
    {
        Lista *aktualny = *dziecko;

        while (aktualny->nastepny != NULL)
            aktualny = aktualny->nastepny;

        aktualny->nastepny = (Lista *)malloc(sizeof(Lista));
        if (aktualny->nastepny == NULL)
        {
            exit(0);
        }
        else
        {
            aktualny->nastepny->wezel.idx = idx;
            aktualny->nastepny->wezel.znak = znak;
            aktualny->nastepny->wezel.dziecko = NULL;
            aktualny->nastepny->nastepny = NULL;
        }
    }
}

/*! \fn Lista *wyszukaj_potomka(Lista *dziecko, char znak)
    \brief
    Funkcja ta jest odpowiedzialna za wyszukiwanie potomka.
    - Jesli dziecko nie jest pusta wartoscia to we while jesli dziecko nie jest pusta watoscia
    oraz jesli znak jest rowny wskaznikowi dziecka na wezel znaku to wtedy dziecko jest rowne
    wskaznikowi dziecka na nastepny element
    - Jesli dziecko nie jest pusta wartoscia oraz znak jest rowny wskaznikowi dziecka na wezel znak
    to wtedy zwroc dziecko
    - a na koncu zwroc pusta wartosc

    \param dziecko 
    \param znak
   
*/

Lista *wyszukaj_potomka(Lista *dziecko, char znak)
{
    if (dziecko != NULL)
    {
        while (dziecko != NULL && dziecko->wezel.znak != znak)
            dziecko = dziecko->nastepny;
        if (dziecko != NULL && dziecko->wezel.znak == znak)
            return dziecko;
    }
    return NULL;
}

/*! \fn Wezel *wyszukaj(Wezel *rodzic, char *znak, long long int *pozycja, long long int dlugosc_napisu)
    \brief
    Funkcja w petli while jesli rodzic nie jest pusty, to wyszukuje potomka.
    - Jesli wskaznik na pozycje jest mniejszy od dlugosci napisu - 1 oraz dziecko nie 
    jest puste to wtedy dodajemy do pozycji, a rodzic jest rowny wskaznikowi dziecka na wezel, 
    charakter jest rowny znakowi(*pozycja)

    \param rodzic
    \param znak
    \param pozycja
    \param dlugosc_napisu
   
    
   
*/


Wezel *wyszukaj(Wezel *rodzic, char *znak, long long int *pozycja, long long int dlugosc_napisu)
{
    Lista *dziecko;
    char character = znak[(*pozycja)];

    
    while (rodzic != NULL)
    {
        dziecko = wyszukaj_potomka(rodzic->dziecko, character); 

        if ((*pozycja) < dlugosc_napisu - 1 && dziecko != NULL)
        {
            (*pozycja)++;
            rodzic = &(dziecko->wezel);
            character = znak[(*pozycja)];
        }
        else
            break;
    }
    return rodzic;
}

/*! \fn void kompresuj(char *znak, long long int dlugosc_napisu, char *nazwa_pliku_wyjsciowego)
    \brief
    Na poczatku funkcji deklarujemy strumien wyjsciowy pliku oraz wezel slownika.
    - Jesli slownik jest pusty to wtedy wychodzimy z programu
    - W przeciwnym wypadku wskazujemy slownikiem na idx i to jest rowne 0, wskazujemy
    slownikiem na dziecko i to jest pusta wartoscia, pozycje deklarujemy jako 0, oraz nowy 
    indeks jako 1
    - W petli while dopoki pozycja jest mniejsza od dlugosci napisu, definujemy wskaznik
    na rodzica
    -Jesli pozycja jest mniejsza od dlugosci napisu oraz jesli nowy indeks jest mniejszy
    od UCHAR_MAX to wtedy w fwrite ustalamy strumienie wyjsciowe i korzystamy z funkcji
    dodaj potomka, zwiekszamy pozycje oraz nowy_indeks, w przeciwnym wypadku korzystamy
    z funkcji usun_slownik i wychodzimy z programu

    \param znak
    \param nazwa_pliku_wyjsciowego
    \param dlugosc_napisu
   
*/


void kompresuj(char *znak, long long int dlugosc_napisu, char *nazwa_pliku_wyjsciowego)
{
    FILE *wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");

    Wezel *slownik = (Wezel *)malloc(sizeof(Wezel));
    if (slownik == NULL)
    {
        exit(0);
    }
    else
    {
        slownik->idx = 0;
        
        slownik->dziecko = NULL;

        long long int pozycja = 0;    
        long long int nowy_indeks = 1; 

        while (pozycja < dlugosc_napisu)
        {
            Wezel *rodzic = wyszukaj(slownik, znak, &pozycja, dlugosc_napisu); 

            if (pozycja < dlugosc_napisu)
            {
                if (nowy_indeks < UCHAR_MAX) 
                {
                    fwrite(&(rodzic->idx), sizeof(indeks), 1, wyjsciowy); 
                    fwrite(&znak[pozycja], sizeof(char), 1, wyjsciowy);   
                    dodaj_potomka(&(rodzic->dziecko), nowy_indeks, znak[pozycja]);
                    pozycja++;
                    nowy_indeks++;
                }
                else
                {
                    usun_slownik(slownik);
                    exit(0);
                }
            }
            else
                break;
        }
        usun_slownik(slownik);
    }
    fclose(wyjsciowy);
}

/*! \fn long long int dlugosc_slowa(indeks *idx, long long int pozycja)
    \brief
    Na poczatku funkcji deklaujemy licznik, ktory na poczatku jest rowny 1 oraz zrownujemy
    indeks poprzedni_indeks z idx od pozycji
    - Dopoki poprzedni indeks nie jest rowny 0 to wtedy poprzedni indeks jest rowny
    idx(a w nim poprzedniemu_indeksowi - 1), dodajemy do licznika oraz zwracamy ten licznik
    

    \param idx
    \param pozycja
   
   
*/



long long int dlugosc_slowa(indeks *idx, long long int pozycja)
{
    long long int licznik = 1;
    indeks poprzedni_indeks = idx[pozycja];

    while (poprzedni_indeks != 0)
    {
        poprzedni_indeks = idx[poprzedni_indeks - 1];
        licznik++;
    }

    return licznik;
}

/*! \fn char *czytaj_slowo(indeks *idx, char *znak, long long int pozycja, long long int dlugosc_slowa, char *slowo)
    \brief
    Na poczatku indeks indeks_poprzedni jest rowny id(pozycje), zmienna pos jest rowna dlugosci slowa -1,
    slowo(pos) jest rowne znakowi(pozycji)
    - Dopoki indeks_poprzedni nie jest rowny 0, to zmniejszamy pos oraz slowo(pos) jest rowne 
    znakowi(indeks_poprzedni - 1), indeks_poprzedni jest rowny idx(indeks_poprzedni - 1)
    - A na koncu zwracamy slowo


    \param idx
    \param znak
    \param pozycja
    \param dlugosc_slowa
    \param slowo
*/

char *czytaj_slowo(indeks *idx, char *znak, long long int pozycja, long long int dlugosc_slowa, char *slowo)
{
    indeks indeks_poprzedni = idx[pozycja];
    long long int pos = dlugosc_slowa - 1;
    slowo[pos] = znak[pozycja];

    while (indeks_poprzedni != 0)
    {
        pos--;
        slowo[pos] = znak[indeks_poprzedni - 1];
        indeks_poprzedni = idx[indeks_poprzedni - 1];
    }

    return slowo;
}

/*! \fn void dekompresuj(indeks *idx, char *znak, long long int rozmiar_tablic, char *nazwa_pliku_wyjsciowego)
    \brief
   Najpierw definiujemy strumien wyjsciowy, deklarujemy pozycje jako 0.
   - Dopoki pozycja jest mniejsza od rozmiaru_tablic, to wtedy rozmiar slowa jest rowny
   dlugosci_slowa(idx, pozycji), wskaznik na slowo jest rowny alokacji pamieci na wskaznik
   rozmiaru slowa, a slowo jest rowne funkcji czytaj_slowo


    \param idx
    \param znak
    \param rozmiar_tablic
    \param nazwa_pliku_wyjsciowego
    
*/

void dekompresuj(indeks *idx, char *znak, long long int rozmiar_tablic, char *nazwa_pliku_wyjsciowego)
{
    FILE *wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");

    long long int pozycja = 0;
    while (pozycja < rozmiar_tablic)
    {
        long long int rozmiar_slowa = dlugosc_slowa(idx, pozycja);
        char *slowo = (char *)malloc(sizeof(char) * rozmiar_slowa);
        slowo = czytaj_slowo(idx, znak, pozycja, rozmiar_slowa, slowo);
        fwrite(slowo, sizeof(char), rozmiar_slowa, wyjsciowy);
        free(slowo);
        pozycja++;
    }

    fclose(wyjsciowy);
}

void wczytaj_kompresje(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego)
{
    
    FILE *plik = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik == NULL)
    {
        exit(0);
    }
    else
    {
        fseek(plik, 0, SEEK_END);
        long long int rozmiar_pliku = ftell(plik);
        fseek(plik, 0, 0);

        char *napis = (char *)malloc(sizeof(char) * rozmiar_pliku);
        if (napis == NULL)
        {
            exit(0);
        }
        else
        {
            
            long long int i = 0;
            while (1)
            {
                fread(&napis[i], sizeof(char), 1, plik);
                if (feof(plik))
                    break;
                i++;
            }

            kompresuj(napis, rozmiar_pliku, nazwa_pliku_wyjsciowego);

           
            free(napis);

            fclose(plik);
        }
    }
}

void wczytaj_dekompresje(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego)
{

    
    FILE *plik = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik == NULL)
    {
        exit(0);
    }
    else
    {
        fseek(plik, 0, SEEK_END);
        long long int rozmiar_pliku = ftell(plik);
        fseek(plik, 0, 0);
        long long int rozmiar_tablicy = rozmiar_pliku / (sizeof(indeks) + sizeof(char));
        
        indeks *idx = (indeks *)malloc(sizeof(indeks) * rozmiar_tablicy); 
        char *znak = (char *)malloc(sizeof(char) * rozmiar_tablicy);      
        if (idx == NULL || znak == NULL)
        {
            exit(0);
        }
        else
        {
            
            long long int i = 0;
            while (1)
            {
                fread(&idx[i], sizeof(indeks), 1, plik);
                fread(&znak[i], sizeof(char), 1, plik);
                if (feof(plik))
                    break;
                i++;
            }

            dekompresuj(idx, znak, rozmiar_tablicy, nazwa_pliku_wyjsciowego);

           
            free(idx);
            free(znak);

            fclose(plik);
        }
    }
}

void usun_slownik(Wezel *drzewo)
{
    if (drzewo != NULL)
    {
        Lista *poprzednie_dziecko = NULL;
        while (drzewo->dziecko)
        {
            usun_slownik(&(drzewo->dziecko->wezel));
            poprzednie_dziecko = drzewo->dziecko;
            drzewo->dziecko = drzewo->dziecko->nastepny;
            free(poprzednie_dziecko);
        }
        
        usun_slownik(&(drzewo->dziecko->wezel));
        free(drzewo->dziecko);
    }
}
