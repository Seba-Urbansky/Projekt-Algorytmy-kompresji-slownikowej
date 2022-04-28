#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw_algorytmy.c"
#include "lzw_plik.c" 
#include "lzw.h"
#include "lzw_tablica.c" 


void kompresuj_LZW(FILE *wejscie_plik, FILE *wyjscie_plik) {    
    int prefiks = getc(wejscie_plik);
    if (prefix == EOF) {
        return;
    }
    int postac;

    int nastepny_kod;
    int indeks;
 
    nastepny_kod = 256; 
    slownik_w_tym();
    
    while ((postac = getc(wejscie_plik)) != (unsigned)EOF) { 
        
        if ((indeks = przeglad_slownika(prefiks, postac)) != -1) prefiks = indeks; 
        else {
            
            pisz_binarnie(wyjscie_plik, prefiks);
            

            if (nastepny_kod < slownik_wielkosc) slownik_dodaj(prefiks, postac, nastepny_kod++);
            prefiks = postac; 
        }
    }
    pisz_binarnie(wyjscie_plik, prefiks); 
    
    if (resztki > 0) fputc(resztki_bity << 4, wyjscie_plik);
    
    slownik_zniszcz();
}

void dekompresuj_LZW(FILE * wejscie_plik, FILE * wyjscie_plik) {
   
    int wczesniejszy_kod; int aktualny_kod;
    int nastepny_kod = 256; 

    int pierwszy_char;

    wczesniejszy_kod = czytaj_binarnie(wejscie_plik);
    if (wczesniejszy_kod == 0) {
        return;
    }
    fputc(wczesniejszy_kod, wyjscie_plik);
    
    while ((aktualny_kod = czytaj_binarnie(wejscie_plik)) > 0) { 
    
        if (aktualny_kod >= nastepnykod) {
            fputc(pierwszy_char = dekoduj_lzw(wczesniejszy_kod, wyjscie_plik), wyjscie_plik); 
            
        } else pierwszy_char = dekoduj_lzw(aktualny_kod, wyjscie_plik); 
        
        if (nastepny_kod < slownik_wielkosc) slownik_tablica_dodaj(wczesniejszy_kod, pierwszy_char, nastepny_kod++);
        wczesniejszy_kod = aktualny_kod;
    }
   
}


int dekoduj_lzw(int kod, FILE * wyjscie_plik) {
    int postac; int tymczasowa;

    if (kod > 255) { 
        postac = slownik_tablica_postac(kod);
        tymczasowa = dekoduj_lzw(slownik_tablica_prefiks(kod), wyjscie_plik); 
    } else {
        postac = kod; 
        tymczasowa = kod;
    }
    fputc(postac, wyjscie_plik);
   
    return tymczasowa;
}
