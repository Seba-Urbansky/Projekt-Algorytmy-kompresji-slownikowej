

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw_algorytmy.c" 
#include "lzw.h"

FILE *wejscie_plik;
FILE *wyjscie_plik;

int main(int argumenty, char** argv) { 
    
    if (argumenty > 2) {
        if (strcmp(argv[1], "c") == 0) { 
            wejscie_plik = fopen(argv[2], "r"); 
            wyjscie_plik = fopen(strcat(argv[2], ".lzw"), "w+b"); 
            
            if (wyjscie_plik == NULL || wejscie_plik == NULL) {
                printf("Nie mozna otworzyc plikow\n'"); return 0;
            }
            
            kompresuj_LZW(wejscie_plik, wyjscie_plik);
        } else { 
            wejscie_plik = fopen(argv[2], "rb"); 

            char tymczasowa[20]; int dlugosc = strlen(argv[2])-4;
            strncpy(tymczasowa, argv[2], dlugosc);
            tymczasowa[dlugosc] = '\0';
            wyjscie_plik = fopen(tymczasowa, "w"); 
            
            if (wyjscie_plik == NULL || wejscie_plik == NULL) {
                printf("Nie mozna otworzyc plikow\n'"); return 0;
            }
            
            dekompresuj_LZW(wejscie_plik, wyjscie_plik);
        }
        
        fclose(wejscie_plik); fclose(wyjscie_plik); 
    } else {
        
       
        printf("<Commands>\n  c       Kompresja_LZW\n  d       Dekompresja_LZW\n");
    }
    
    return 0;
}
