#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw_algorytmy.c"
#include "lzw_plik.c" 
#include "lz78.h"
#include "lzw_tablica.c" 


void kompresuj_LZW(FILE *inputFile, FILE *outputFile) {    
    int prefix = getc(inputFile);
    if (prefix == EOF) {
        return;
    }
    int character;

    int nextCode;
    int index;
    
    // LZW starts out with a dictionary of 256 characters (in the case of 8 codeLength) and uses those as the "standard"
    //  character set.
    nextCode = 256; // next code is the next available string code
    dictionaryInit();
    
    // while (there is still data to be read)
    while ((character = getc(inputFile)) != (unsigned)EOF) { // ch = read a character;
        
        // if (dictionary contains prefix+character)
        if ((index = dictionaryLookup(prefix, character)) != -1) prefix = index; // prefix = prefix+character
        else { // ...no, try to add it
            // encode s to output file
            pisz_binarnie(outputFile, prefix);
            
            // add prefix+character to dictionary
            if (nextCode < dictionarySize) dictionaryAdd(prefix, character, nextCode++);
            
            // prefix = character
            prefix = character; //... output the last string after adding the new one
        }
    }
    // encode s to output file
    pisz_binarnie(outputFile, prefix); // output the last code
    
    if (resztki > 0) fputc(resztki_bity << 4, outputFile);
    
    // free the dictionary here
    dictionaryDestroy();
}

// decompression
// to reconstruct a string from an index we need to traverse the dictionary strings backwards, following each
//   successive prefix index until this prefix index is the empty index
void dekompresuj_LZW(FILE * inputFile, FILE * outputFile) {
    // int prevcode, currcode
    int previousCode; int currentCode;
    int nextCode = 256; // start with the same dictionary of 256 characters

    int firstChar;
    
    // prevcode = read in a code
    previousCode = czytaj_binarnie(inputFile);
    if (previousCode == 0) {
        return;
    }
    fputc(previousCode, outputFile);
    
    // while (there is still data to read)
    while ((currentCode = czytaj_binarnie(inputFile)) > 0) { // currcode = read in a code
    
        if (currentCode >= nextCode) {
            fputc(firstChar = decode(previousCode, outputFile), outputFile); // S+C+S+C+S exception [2.]
            //printf("%c", firstChar);
            //appendCharacter(firstChar = decode(previousCode, outputFile));
        } else firstChar = decode(currentCode, outputFile); // first character returned! [1.]
        
        // add a new code to the string table
        if (nextCode < dictionarySize) dictionaryArrayAdd(previousCode, firstChar, nextCode++);
        
        // prevcode = currcode
        previousCode = currentCode;
    }
    //printf("\n");
}

int decode(int code, FILE * outputFile) {
    int character; int temp;

    if (code > 255) { // decode
        character = dictionaryArrayCharacter(code);
        temp = decode(dictionaryArrayPrefix(code), outputFile); // recursion
    } else {
        character = code; // ASCII
        temp = code;
    }
    fputc(character, outputFile);
    //printf("%c", character);
    //appendCharacter(character);
    return temp;
}
