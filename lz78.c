#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "lz78.h"

void DodajPotomek(lista **Dziecko, indeks idx, char znak)
{
    if (*Dziecko == NULL)
    {
        *Dziecko = (lista *)malloc(sizeof(lista));
        if (*Dziecko == NULL)
        {
            exit(0);
        }
        else
        {
            (*Dziecko)->Node.idx = idx;
            (*Dziecko)->Node.znak = znak;
            (*Dziecko)->Node.dziecko = NULL;
            (*Dziecko)->pNext = NULL;
        }
    }
    else
    {
        lista *biezacy = *Dziecko;

        while (biezacy->pNext != NULL)
            biezacy = biezacy->pNext;

        biezacy->pNext = (lista *)malloc(sizeof(lista));
        if (biezacy->pNext == NULL)
        {
            exit(0);
        }
        else
        {
            biezacy->pNext->Node.idx = idx;
            biezacy->pNext->Node.znak = znak;
            biezacy->pNext->Node.dziecko = NULL;
            biezacy->pNext->pNext = NULL;
        }
    }
}

lista *ZnajdzPotomka(lista *Dziecko, char znak)
{
    if (Dziecko != NULL)
    {
        while (Dziecko != NULL && Dziecko->Node.znak != znak)
            Dziecko = Dziecko->pNext;
        if (Dziecko != NULL && Dziecko->Node.znak == znak)
            return Dziecko;
    }
    return NULL;
}

drzewo *Znajdz(drzewo *Rodzic, char *znak, long long int *pozycja, long long int RozmiarNapisu)
{
    lista *Dziecko;
    char character = znak[(*pozycja)];

    // dop�ki nie mamy ko�ca listy dzieci
    while (Rodzic != NULL)
    {
        Dziecko = ZnajdzPotomka(Rodzic->dziecko, character); // Zwraca element zawieraj�cy szukany znak (je�li nie ma takiego, zwraca null).

        if ((*pozycja) < RozmiarNapisu - 1 && Dziecko != NULL)
        {
            (*pozycja)++;
            Rodzic = &(Dziecko->Node);
            character = znak[(*pozycja)];
        }
        else
            break;
    }
    return Rodzic;
}

void Kompresja(char *znak, long long int RozmiarNapisu, char *nazwa_pliku_wyjsciowego)
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
        Slownik->znak = NULL; // Jest niewa�ny
        Slownik->dziecko = NULL;

        long long int pozycja = 0;    // kt�ry z kolei znak rozpatrujemy.
        long long int IndeksNowy = 1; // indeks zapisywany w slowniku.

        while (pozycja < RozmiarNapisu)
        {
            drzewo *Rodzic = Znajdz(Slownik, znak, &pozycja, RozmiarNapisu); // Szukamy, czy mamy ju� cz�� ci�gu.

            if (pozycja < RozmiarNapisu)
            {
                if (IndeksNowy < UCHAR_MAX) // Sprawdzamy, czy osi�gni�to maksymalny rozmiar indeksu.
                {
                    fwrite(&(Rodzic->idx), sizeof(indeks), 1, wyjsciowy); // wpisuje indeksy do pliku
                    fwrite(&znak[pozycja], sizeof(char), 1, wyjsciowy);   // wpisuje znaki do pliku
                    DodajPotomek(&(Rodzic->dziecko), IndeksNowy, znak[pozycja]);
                    pozycja++;
                    IndeksNowy++;
                }
                else
                {
                    UsunSlownik(Slownik);
                    exit(0);
                }
            }
            else
                break;
        }
        UsunSlownik(Slownik);
    }
    fclose(wyjsciowy);
}

long long int DlugoscSlowa(indeks *idx, long long int pozycja)
{
    long long int licznik = 1;
    indeks IndeksPoprzedni = idx[pozycja];

    while (IndeksPoprzedni != 0)
    {
        IndeksPoprzedni = idx[IndeksPoprzedni - 1];
        licznik++;
    }

    return licznik;
}

char *CzytajSlowo(indeks *idx, char *znak, long long int pozycja, long long int RozmiarSlowa, char *slowo)
{
    indeks IndeksPoprzedni = idx[pozycja];
    long long int pos = RozmiarSlowa - 1;
    slowo[pos] = znak[pozycja];

    while (IndeksPoprzedni != 0)
    {
        pos--;
        slowo[pos] = znak[IndeksPoprzedni - 1];
        IndeksPoprzedni = idx[IndeksPoprzedni - 1];
    }

    return slowo;
}

void Dekompresja(indeks *idx, char *znak, long long int RozmiarTablic, char *nazwa_pliku_wyjsciowego)
{
    FILE *wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");

    long long int pozycja = 0;
    while (pozycja < RozmiarTablic)
    {
        long long int RozmiarSlowa = DlugoscSlowa(idx, pozycja);
        char *slowo = (char *)malloc(sizeof(char) * RozmiarSlowa);
        slowo = CzytajSlowo(idx, znak, pozycja, RozmiarSlowa, slowo);
        fwrite(slowo, sizeof(char), RozmiarSlowa, wyjsciowy);
        free(slowo);
        pozycja++;
    }

    fclose(wyjsciowy);
}

void WczytajKompresja(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego)
{
    // Otwieranie pliku.
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

        // Alokacja pami�ci.
        char *napis = (char *)malloc(sizeof(char) * RozmiarPliku);
        if (napis == NULL)
        {
            exit(0);
        }
        else
        {
            // Kopiowanie zawarto�ci pliku do bufora.
            long long int i = 0;
            while (1)
            {
                fread(&napis[i], sizeof(char), 1, plik);
                if (feof(plik))
                    break;
                i++;
            }

            Kompresja(napis, RozmiarPliku, nazwa_pliku_wyjsciowego);

            // Uwolnienie bufora.
            free(napis);

            fclose(plik);
        }
    }
}

void WczytajDekompresja(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego)
{

    // Otwieranie pliku.
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
        long long int RozmiarTablicy = RozmiarPliku / (sizeof(indeks) + sizeof(char));
        // Alokacja pami�ci.
        indeks *idx = (indeks *)malloc(sizeof(indeks) * RozmiarTablicy); // tablica indeks�w
        char *znak = (char *)malloc(sizeof(char) * RozmiarTablicy);      // tablica znak�w
        if (idx == NULL || znak == NULL)
        {
            exit(0);
        }
        else
        {
            // Kopiowanie zawarto�ci pliku do bufora.
            long long int i = 0;
            while (1)
            {
                fread(&idx[i], sizeof(indeks), 1, plik);
                fread(&znak[i], sizeof(char), 1, plik);
                if (feof(plik))
                    break;
                i++;
            }

            Dekompresja(idx, znak, RozmiarTablicy, nazwa_pliku_wyjsciowego);

            // Uwolnienie bufora.
            free(idx);
            free(znak);

            fclose(plik);
        }
    }
}

void UsunSlownik(drzewo *Drzewo)
{
    if (Drzewo != NULL)
    {
        lista *PoprzednieDziecko = NULL;
        while (Drzewo->dziecko)
        {
            UsunSlownik(&(Drzewo->dziecko->Node));
            PoprzednieDziecko = Drzewo->dziecko;
            Drzewo->dziecko = Drzewo->dziecko->pNext;
            free(PoprzednieDziecko);
        }
        free(Drzewo->dziecko);
        UsunSlownik(Drzewo->dziecko);
    }
}