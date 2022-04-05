#include <string.h>
#include "lz78.h"

extern void *malloc(int);

/* Rozmiar słownika */
#define HTSIZE 16384

/* Słownik */
int *larray;
int *carray;
int *codearray;

/* Inicjalizacja słownika */

int inicjalizuj(void)
{
    if (!(larray = malloc(sizeof(int) * HTSIZE)))
        return -1;
    if (!(carray = malloc(sizeof(int) * HTSIZE)))
        return -1;
    if (!(codearray = malloc(sizeof(int) * HTSIZE)))
        return -1;
    return 0;
}

/* Kompresuj blok 'src' lub wielkość 'len' do buforu 'dst'.  Zwroc
 * skompresowany rozmiar bloku. */

int kompresuj(unsigned char *dst, unsigned char *src, int len)
{
    int x;
    int l, c;
    int count = 0;
    int ln = len;
    unsigned char *s = src;
    unsigned char *d = dst;
    unsigned assm = 0; /* Zamontuj bity*/
    int nbits = 0;     /* Nie. Bity w bitach - zamontowane*/
    int code = 256;    /* Dotychczasowy kod */
    int end = 512;     /* Inny bit */
    int bits = 9;      /* Bity potrzebne do kodu*/
    int tmp;

    /* Obecny i wcześniejszy obiekt */

    if (!len) /* Pusty blok */
        return 0;

    /* Sprawdzenie dla dlugosci kompresji */
    c = s[0];
    for (x = 0; x != len; ++x)
        if (s[x] != c)
            break;
    if (x == len)
    { /* Uruchom kodowanie dlugosci dla blokow */
        *d++ = 0;
        *d++ = c;
        *d++ = len;
        *d++ = (len >> 8);
        return d - dst;
    }

    /* Zainicjalizuj slownik*/
    memset(carray, 255, sizeof(int) * HTSIZE);
    memset(larray, 255, sizeof(int) * HTSIZE);
    memset(codearray, 255, sizeof(int) * HTSIZE);

    /* Kompresuj */

    /* Otrzymaj pierwsze slowo */
    l = *s++;
    --ln;

    /* Wyjsciowy typ kompresji */
    *d++ = 2;

    while (ln)
    {
        int hv;
        c = *s++;
        --ln;

        /* Znajdowanie L+C w tablicy mieszajacej*/
        for (hv = ((l << 8) ^ (c) ^ (l >> 6)) & (HTSIZE - 1); larray[hv] != -1; hv = (hv + 1) & (HTSIZE - 1))
            if (larray[hv] == l && carray[hv] == c)
                break;

        if (larray[hv] != -1)
        { /* Znalezione wejscie */
            l = codearray[hv];
        }
        else
        {
            /* dodaj wejscie - l+c nie jest tablica mieszajaca */
            larray[hv] = l;
            carray[hv] = c;
            codearray[hv] = code++;
            if (code == end)
                count = 3;
            if (count > 0)
                if (!--count)
                    (end <<= 1), ++bits;

            /* Wypisanie 'l' */
            tmp = bits;
            while (tmp)
            {
                assm |= (l << nbits);
                if (tmp + nbits <= 16)
                    nbits += tmp, tmp = 0;
                else
                    tmp -= (16 - nbits), l >>= (16 - nbits), nbits = 16;
                while (nbits >= 8)
                {
                    *d++ = assm;
                    assm >>= 8;
                    nbits -= 8;
                    if (d - dst == len)
                        goto none;
                }
            }
            /* Zacznij nowe typ string */
            l = c;
        }
    }

    /* Wyjscie ostatniego kodu */
    tmp = bits;
    while (tmp)
    {
        assm |= (l << nbits);
        if (tmp + nbits <= 16)
            nbits += tmp, tmp = 0;
        else
            tmp -= (16 - nbits), l >>= (16 - nbits), nbits = 16;
        while (nbits >= 8)
        {
            *d++ = assm;
            assm >>= 8;
            nbits -= 8;
            if (d - dst == len)
                goto none;
        }
    }
    while (nbits > 0)
    {
        *d++ = assm;
        assm >>= 8;
        nbits -= 8;
        if (d - dst == len)
            goto none;
    }

    return d - dst;


none:
    dst[0] = 1;                
    memcpy(dst + 1, src, len); /* Skopiuj blok */
    return len + 1;
}

/* Dekompresuj
 */

int dekompresuj(unsigned char *dst, unsigned char *src, int len)
{
    if (!len) /* Bez danych */
        return 0;

    if (*src == 0) /* Zerowany blok*/
    {
        int x;
        int c = src[1];
        len = src[2] + (src[3] << 8);
        for (x = 0; x != len; ++x)
            dst[x] = c;
        return len;
    }

    if (*src == 1) 
    {
        if (len - 1)
            memcpy(dst, src + 1, len - 1);
        return len - 1;
    }

    if (*src == 2) /* lz78 */
    {
        int x, q, cnt;

        /* Zamontowanie slowa */
        unsigned long assm = 0;
        int nbits = 0;

        /* menedzer kodu */
        int bits = 9;
        int end = 512;

        /* aktualny string */
        int l, c;
        int code;
        unsigned char *d = dst;
        code = 256;

        /* dekomprsuj */

        ++src;
        --len;

        /* Dostaj pierwsze slowo */
        while (nbits < bits)
        {
            assm |= ((unsigned long)*src++ << nbits);
            --len;
            nbits += 8;
        }
        l = (assm & (end - 1));
        assm >>= bits;
        nbits -= bits;
        *d++ = l;

        while (len)
        {
            /* Dostan */
            while (nbits < bits)
            {
                assm |= ((unsigned long)*src++ << nbits);
                --len;
                nbits += 8;
            }
            c = (assm & (end - 1));
            assm >>= bits;
            nbits -= bits;

            if (c < 256)
            {
                /* Dostan slowo*/
                /* W tym punkcie trzeba wygenerowac nowy kod */
                larray[code] = l;
                carray[code] = c;
                ++code;

                /* Wypisanie */
                *d++ = c;

                /* Rozpocznij nowy string */
                l = c;
            }
            else
            {
                /* Dostan kod*/

                /* Musisz wygenerowac nowy kod w tym punkcie */
                larray[code] = l;
                for (q = larray[c]; q >= 256; q = larray[q])
                    ;
                carray[code] = q;
                ++code;

                /* Rozpocznij nowy string */
                l = c;

                /* Wypisanie */
                cnt = 0;
                while (larray[c] >= 256)
                {
                    ++cnt;
                    *d++ = carray[c];
                    c = larray[c];
                }
                *d++ = carray[c];
                ++cnt;
                *d++ = larray[c];
                ++cnt;
                for (x = 0; x != cnt / 2; ++x)
                {
                    q = d[-1 - x];
                    d[-1 - x] = d[-cnt + x];
                    d[-cnt + x] = q;
                }
            }
            if (code == end)
                end *= 2, bits += 1;
        }
        return d - dst;
    }

    return -1; /* Nie wiem jak to zdekompresowac */
}