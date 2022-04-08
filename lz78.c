#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "lz78.h"

void dodaj_potomka(lista **dziecko, indeks idx, char znak)
{
    if (*dziecko == NULL)
    {
        *dziecko = (lista *)malloc(sizeof(lista));
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
        lista *aktualny = *dziecko;

        while (aktualny->nastepny != NULL)
            aktualny = aktualny->nastepny;

        aktualny->nastepny = (lista *)malloc(sizeof(lista));
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

lista *wyszukaj_potomka(lista *dziecko, char znak)
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

drzewo *wyszukaj(drzewo *Rodzic, char *znak, long long int *pozycja, long long int dlugosc_napisu)
{
    lista *Dziecko;
    char character = znak[(*pozycja)];

    
    while (Rodzic != NULL)
    {
        Dziecko = wyszukaj_potomka(Rodzic->dziecko, character); 

        if ((*pozycja) < dlugosc_napisu - 1 && Dziecko != NULL)
        {
            (*pozycja)++;
            Rodzic = &(Dziecko->wezel);
            character = znak[(*pozycja)];
        }
        else
            break;
    }
    return Rodzic;
}

void kompresuj(char *znak, long long int RozmiarNapisu, char *nazwa_pliku_wyjsciowego)
{
    FILE *wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");

    drzewo *Slownik = (drzewo *)malloc(sizeof(drzewo));
    if (Slownik == NULL)
    {
        exit(0);
    }
    else
    {
        Slownik->idx = 0;
        Slownik->znak = NULL; 
        Slownik->dziecko = NULL;

        long long int pozycja = 0;    
        long long int nowy_indeks = 1; 

        while (pozycja < RozmiarNapisu)
        {
            drzewo *Rodzic = wyszukaj(Slownik, znak, &pozycja, RozmiarNapisu); 

            if (pozycja < RozmiarNapisu)
            {
                if (nowy_indeks < UCHAR_MAX) 
                {
                    fwrite(&(Rodzic->idx), sizeof(indeks), 1, wyjsciowy); 
                    fwrite(&znak[pozycja], sizeof(char), 1, wyjsciowy);   
                    dodaj_potomka(&(Rodzic->dziecko), nowy_indeks, znak[pozycja]);
                    pozycja++;
                    nowy_indeks++;
                }
                else
                {
                    usun_slownik(Slownik);
                    exit(0);
                }
            }
            else
                break;
        }
        usun_slownik(Slownik);
    }
    fclose(wyjsciowy);
}

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
        long long int RozmiarPliku = ftell(plik);
        fseek(plik, 0, 0);
        long long int rozmiar_tablicy = RozmiarPliku / (sizeof(indeks) + sizeof(char));
        
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

void usun_slownik(drzewo *drzewo)
{
    if (drzewo != NULL)
    {
        lista *poprzednie_dziecko = NULL;
        while (drzewo->dziecko)
        {
            usun_slownik(&(drzewo->dziecko->wezel));
            poprzednie_dziecko = drzewo->dziecko;
            drzewo->dziecko = drzewo->dziecko->nastepny;
            free(poprzednie_dziecko);
        }
        free(drzewo->dziecko);
        usun_slownik(drzewo->dziecko);
    }
}