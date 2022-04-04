#include <stdio.h>
#include <stdlib.h>

#define MAX 32

// to jest milestone1 - algorytm LZ78

// http://fizyka.umk.pl/~leii/wskaznikiStrukturyAiR.pAf

struct slownik {
        int index;
        struct slownik* znaki[100];
}; // slownik lz78


void kompresuj(struct slownik *znaki);
void dekompresuj(struct slownik *znaki);
void wyjscie();
void menu();
void wczytaj();
void zapis();


void menu() {
    int wybor;

    printf("Menu LZ78");
    printf("\n\n");
    printf("1. Wpisz tekst do kompresji");
    printf("\n");
    printf("2. Dekompresuj tekst");
    printf("\n");
    printf("3. Wyjście z programu");
    printf("\n");
    printf("4. Powrot do menu");
    printf("\n");
switch (wybor) {

case 1:
    kompresuj();
    break;

case 2:
    dekompresuj();
    break;
case 3
    wyjscie();
    break;
case 4
    menu();
    break;


default: {
    printf("Niepoprawna instrukcja");
    break;
}

}

}

void kompresuj()
{
    char tekst[MAX];
    printf("Wpisz tekst ktory chcesz zaszyfrowac");
    scanf("%d", &tekst)
}

void wczytaj (struct slownik* znaki ) {
   
FILE *plik;
if (plik != NULL) {
plik = fopen("LZ78.csv", "r");

while (plik != EOF) {
    fscanf(plik, "%s");
}

void zapis (struct slownik* znaki ) {
   
FILE *plik;
if (plik != NULL) {
plik = fopen("LZ78.csv", "w");

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
