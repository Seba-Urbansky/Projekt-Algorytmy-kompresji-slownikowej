#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lz78.h"

#define MAX 2048

// to jest milestone1 - algorytm LZ78

// http://fizyka.umk.pl/~leii/wskaznikiStrukturyAiR.pAf

struct slownik
{
    int index;
    struct slownik *znaki[100];
}; // slownik lz78

void menu_kompresuj(char* oryginalny_plik_nazwa, char* skompresowany_plik_nazwa);
void menu_dekompresuj(char* oryginalny_plik_nazwa, char* skompresowany_plik_nazwa);
void wyjscie();
void menu();

void menu_kompresuj(char* oryginalny_plik_nazwa, char* skompresowany_plik_nazwa)
{
    char tekst[MAX];
    char resultat[MAX];
    FILE *plik = fopen(oryginalny_plik_nazwa, "r");
    fscanf(plik, "%s", &tekst);
    kompresuj(&resultat, &tekst, strlen(tekst));
    FILE *skompresowany_plik = fopen(skompresowany_plik_nazwa, "w");
    fprintf(skompresowany_plik, "%s", resultat);
}

void menu_dekompresuj(char* oryginalny_plik_nazwa, char* skompresowany_plik_nazwa)
{
    char tekst[MAX];
    char resultat[MAX];
    FILE *plik = fopen(skompresowany_plik_nazwa, "r");
    fscanf(plik, "%s", &tekst);
    dekompresuj(&resultat, &tekst, strlen(tekst));
    FILE *zdekompresowany_plik = fopen(oryginalny_plik_nazwa, "w");
    fprintf(zdekompresowany_plik, "%s", resultat);
}

void wyjscie()
{
}

void menu()
{
    inicjalizuj();
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
        menu_kompresuj(&nazwa_pliku, &skompresowany_nazwa_pliku);
        break;
    case 2:
        menu_dekompresuj(&nazwa_pliku, &skompresowany_nazwa_pliku);
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
