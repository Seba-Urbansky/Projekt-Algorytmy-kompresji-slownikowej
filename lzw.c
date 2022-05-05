#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw.h"

int resztki = 0;
int resztki_bity;

void wczytaj_kompresje_LZW(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego)
{
    FILE *plik_wejsciowy = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik_wejsciowy == NULL)
    {
        exit(0);
    }
    FILE *plik_wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");
    if (plik_wyjsciowy == NULL)
    {
        exit(0);
    }
    kompresuj_LZW(plik_wejsciowy, plik_wyjsciowy);
    fclose(plik_wejsciowy);
    fclose(plik_wyjsciowy);
}

void kompresuj_LZW(FILE *wejscie_plik, FILE *wyjscie_plik) {    
    int prefiks = getc(wejscie_plik);
    if (prefiks == EOF) {
        return;
    }
    int znak;

    int nastepny_kod;
    int indeks;
 
    nastepny_kod = 256; 
    slownik_inicjalizacja();
    
    while ((znak = getc(wejscie_plik)) != (unsigned)EOF) { 
        
        if ((indeks = slownik_szukaj(prefiks, znak)) != -1) prefiks = indeks; 
        else {
            pisz_binarnie(wyjscie_plik, prefiks);
            if (nastepny_kod < slownik_wielkosc) slownik_dodaj(prefiks, znak, nastepny_kod++);
            prefiks = znak; 
        }
    }
    pisz_binarnie(wyjscie_plik, prefiks); 
    
    if (resztki > 0) fputc(resztki_bity << 4, wyjscie_plik);
    
    slownik_zniszcz();
}

void wczytaj_dekompresje_LZW(char *nazwa_pliku_wejsciowego, char *nazwa_pliku_wyjsciowego)
{
    FILE *plik_wejsciowy = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik_wejsciowy == NULL)
    {
        exit(0);
    }
    FILE *plik_wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");
    if (plik_wyjsciowy == NULL)
    {
        exit(0);
    }
    dekompresuj_LZW(plik_wejsciowy, plik_wyjsciowy);
    fclose(plik_wejsciowy);
    fclose(plik_wyjsciowy);
}


void dekompresuj_LZW(FILE* wejscie_plik, FILE* wyjscie_plik) {
   
    int wczesniejszy_kod; int aktualny_kod;
    int nastepny_kod = 256; 

    int pierwszy_char;

    wczesniejszy_kod = czytaj_binarnie(wejscie_plik);
    if (wczesniejszy_kod == 0) {
        return;
    }
    fputc(wczesniejszy_kod, wyjscie_plik);
    
    while ((aktualny_kod = czytaj_binarnie(wejscie_plik)) > 0) { 
        if (aktualny_kod >= nastepny_kod) {
            fputc(pierwszy_char = dekoduj_LZW(wczesniejszy_kod, wyjscie_plik), wyjscie_plik); 
        } else {
            pierwszy_char = dekoduj_LZW(aktualny_kod, wyjscie_plik); 
        }
        if (nastepny_kod < slownik_wielkosc) {
            tablica_dodaj(wczesniejszy_kod, pierwszy_char, nastepny_kod++);
        }
        wczesniejszy_kod = aktualny_kod;
    }
   
}

int dekoduj_LZW(int kod, FILE* wyjscie_plik) {
    int znak; int tymczasowa;

    if (kod > 255) { 
        znak = tablica_znak(kod);
        tymczasowa = dekoduj_LZW(tablica_prefiks(kod), wyjscie_plik); 
    } else {
        znak = kod; 
        tymczasowa = kod;
    }
    fputc(znak, wyjscie_plik);
    return tymczasowa;
}

void pisz_binarnie(FILE * wyjscie, int kod) {
    if (resztki > 0) {
        int wczesniejszy_kod = (resztki_bity << 4) + (kod >> 8);
        
        fputc(wczesniejszy_kod, wyjscie);
        fputc(kod, wyjscie);
        
        resztki = 0; 
    } else {
        resztki_bity = kod & 0xF; 
        resztki = 1;
        
        fputc(kod >> 4, wyjscie);
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
