#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lz78.h"
#include "lzw.h"

#define MAX 32 /*!< Deklaracja maksymalnej dlugosci tekstu  */



// to jest milestone1 - algorytm LZ78

// http://fizyka.umk.pl/~leii/wskaznikiStrukturyAiR.pAf

void wyjscie();
void menu();

void wyjscie()
{
}

/*! \fn void menu()
    \brief
    Ponizej jest menu calego programu.
   
*/

void menu()
{
    int wybor;
    char *nazwa_pliku = "LZ78.txt";
    char *nazwa_pliku_lzw = "LZW.txt";
    char *skompresowany_nazwa_pliku = "LZ78.txt.compressed";
    char *skompresowany_nazwa_pliku_lzw = "LZW.txt.compressed";
    printf("\nMenu LZ78 \n");
    printf("1. Kompresuj plik\n");
    printf("2. Dekompresuj plik\n\n");
    printf("Menu LZW\n");
    printf("3. Kompresuj plik\n");
    printf("4. Dekompresuj plik\n\n");
    printf("5. Wyjście z programu\n");
    printf("6. Powrot do menu\n\n");

    scanf("%d", &wybor);
    printf("\n");

    switch (wybor)
    {
    case 1:
        wczytaj_kompresje(nazwa_pliku, skompresowany_nazwa_pliku);
        break;
    case 2:
        wczytaj_dekompresje(skompresowany_nazwa_pliku, nazwa_pliku);
        break;
    case 3:
        wczytaj_kompresje_LZW(nazwa_pliku_lzw, skompresowany_nazwa_pliku_lzw);
        break;
    case 4:
        wczytaj_dekompresje_LZW(skompresowany_nazwa_pliku_lzw, nazwa_pliku_lzw);
        break;
    case 5:
        wyjscie();
        break;
    case 6:
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