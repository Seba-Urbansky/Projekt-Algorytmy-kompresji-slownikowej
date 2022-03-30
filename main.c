#include <stdio.h>
#include <stdlib.h>

#define MAX 32

// to jest milestone1 - algorytm LZ78

// http://fizyka.umk.pl/~leii/wskaznikiStrukturyAiR.pAf

struct slownik {
        int index;
        struct slownik* znaki[100];
}; // slownik lz78



void menu() {
    int wybor;
printf("Wybierz");
printf("\n");
printf("1 - Kompresuj\n");
printf("2 - Dekompresuj\n");

switch (wybor) {

case 1:
    //kompresuj();
    break;

case 2:
    //dekompresuj();
    break;

default: {
    printf("Niepoprawna instrukcja");
    break;
}

}

}

void zaladuj (struct slownik* znaki ) {
    char wybranyplik;

printf("Podaj nazwe pliku\n");
scanf("%s", &wybranyplik);

FILE *plik;
if (plik != NULL) {
plik = fopen(wybranyplik, "r");

while (plik != EOF) {
    fscanf(plik, "%s");
}

fclose(plik);
}
}




int main() {
    struct slownik;
zaladuj(slownik);

menu();

}
