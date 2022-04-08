#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lz78.h"

#define MAX 32

// to jest milestone1 - algorytm LZ78

// http://fizyka.umk.pl/~leii/wskaznikiStrukturyAiR.pAf

void wyjscie();
void menu();

void wyjscie()
{
}

void menu()
{
    int wybor;
    char nazwa_pliku[MAX] = "LZ78.txt";
    char skompresowany_nazwa_pliku[MAX] = "LZ78.txt.compressed";
    printf("Menu LZ78");
    printf("\n\n");
    printf("1. Kompresuj plik");
    printf("\n");
    printf("2. Dekompresuj plik");
    printf("\n");
    printf("3. Wyjście z programu");
    printf("\n");
    printf("4. Powrot do menu");
    printf("\n");

    scanf("%d", &wybor);
    printf("\n");

    switch (wybor)
    {
    case 1:
        wczytaj_kompresje(&nazwa_pliku, &skompresowany_nazwa_pliku);
        break;
    case 2:
        wczytaj_dekompresje(&skompresowany_nazwa_pliku, &nazwa_pliku);
        break;
    case 3:
        wyjscie();
        break;
    case 4:
        menu();
        break;
    default:
        printf("Niepoprawna instrukcja");
        break;
    }
}

int main()
{

    menu();
}