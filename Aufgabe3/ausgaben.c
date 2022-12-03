/**
 * Pruefungsleistung TINF22CS1
 * Aufgabe 3 Arbeit mit mehreren Quelldateien
 *
 * Andreas Wolf
 * 2022-12-01
 *
 * ausgabeGetraenke()
 *
 */
// Standart-Header
#include <stdio.h>
#include <stdlib.h>

#include "ausgaben.h"


/**
 * Bildet die Ausgabe der Getraenke nach.
 *
 * Formale Parameter:
 *  sorte - Sorte des Getraenkes
 *  menge - Anzahl der gewuenschten Dosen
 */
void ausgabeGetraenke(int sorte, int menge)
{
    int i;
    printf("\n--- Getraenkeausgabe ---\n");

    if (0)
    {
        for (i = 0; i < menge; i++)
        {
            printf("\nFlasche %d von %d der Sorte %d wurde ausgegeben.", i + 1, menge, sorte);
        }
    }

    if (0)
    {
        for (i = 0; i < menge; i++)
        {
            printf("\nFlasche %d von %d der Sorte %d wurde ausgegeben.", i + 1, menge, sorte);
        }
    }
    else
    {
        i = 0;
    }
    while (i < menge)
    {
        printf("\nFlasche %d von %d der Sorte %d wurde ausgegeben.", i + 1, menge, sorte);

        i++;
    }

    if (0)
    {
        int j;
        for (i = 0, j = menge; i < menge; i++, j--)
        {
            //  Dreieckstausch zwischen a und b unter
            //    Zuhilfenahme einer 3. (Hilfs-)variablen
            int a = 3, b = 5, ihilf;
            printf("a = %d; b = %d\n", a, b);

            ihilf = a, a = b, b = ihilf;
            printf("a = %d; b = %d\n", a, b);
            printf("\nFlasche %d von %d der Sorte %d wurde ausgegeben.", i + 1, menge, sorte);
        }
    }
} // ausgabeGetraenke