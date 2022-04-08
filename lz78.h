#ifndef LZ78_H
#define LZ78_H

#include <stdio.h>
#include <stdlib.h>


typedef unsigned char indeks;


typedef struct node
{
    indeks idx;
    char znak;
    struct list* dziecko;
} drzewo;


typedef struct list
{
    struct node wezel;
    struct list* nastepny;
} lista;


void dodaj_potomka(lista** Dziecko, indeks idx, char znak);


lista* wyszukaj_potomka(lista* Dziecko, char znak);


drzewo* wyszukaj(drzewo* Rodzic, char* znak, long long int* pozycja, long long int RozmiarNapisu);


void kompresuj(char* znak, long long int RozmiarNapisu, char* nazwa_pliku_wyjsciowego);


long long int dlugosc_slowa(indeks* idx, long long int pozycja);


char* czytaj_slowo(indeks* idx, char* znak, long long int pozycja, long long int RozmiarSlowa, char* slowo);


void dekompresuj(indeks* idx, char* znak, long long int RozmiarTablic, char* nazwa_pliku_wyjsciowego);


void wczytaj_kompresje(char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);


void wczytaj_dekompresje(char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);


void usun_slownik(drzewo* Drzewo);

#endif