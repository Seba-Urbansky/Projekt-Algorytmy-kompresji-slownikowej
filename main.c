#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lz78.h"

#define MAX 32

// to jest milestone1 - algorytm LZ78

// http://fizyka.umk.pl/~leii/wskaznikiStrukturyAiR.pAf


void wyjscie()
{
    exit(0);
}

void wyswietl_wynik(char *plikw) {
char s[100];
FILE *plik = fopen(plikw, "rb");

if (plik) {
        fseek(plik,0,SEEK_SET);
    while(!feof(plik)) {
fread(s,sizeof(s),1,plik);
printf("%s", s);

}
}


fclose(plik);
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
    printf("3. Powrot do menu");
    printf("\n");
    printf("4. Wyjscie z programu");
    printf("\n");

    scanf("%d", &wybor);
    printf("\n");

    switch (wybor)
    {
    case 1:
        wczytaj_kompresje(&nazwa_pliku, &skompresowany_nazwa_pliku);
        //wyswietl_wynik(&skompresowany_nazwa_pliku);
        printf("\n");
        menu();
        break;
    case 2:
        wczytaj_dekompresje(&skompresowany_nazwa_pliku, &nazwa_pliku);
        wyswietl_wynik(&nazwa_pliku);
        printf("\n");
        menu();
        break;
    case 3:
        menu();
        break;
    case 4:
        wyjscie();
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
