

#include <stdio.h>
#include "lzw.h"

void pisz_binarnie(FILE * output, int kod);
int czytaj_binarnie(FILE * input);

int resztki = 0;
int resztki_bity;

void pisz_binarnie(FILE * output, int kod) {
    if (resztki > 0) {
        int previousCode = (resztki_bity << 4) + (kod >> 8);
        
        fputc(previousCode, output);
        fputc(kod, output);
        
        resztki = 0; 
    } else {
        resztki_bity = kod & 0xF; 
        resztki = 1;
        
        fputc(kod >> 4, output);
    }
}

int czytaj_binarnie(FILE * wejscie) {
    int kod = fgetc(wejscie);    
    if (kod == EOF) return 0;

    if (resztki > 0) {
        kod = (resztki_bity << 8) + kod;
        
        resztki = 0;
    } else {
        int nastepny_kod = fgetc(wejscie);
        
        resztki_bity = nastepny_kod & 0xF; 
        resztki = 1;
        
        kod = (kod << 4) + (nastepny_kod >> 4);
    }
    return kod;
}

