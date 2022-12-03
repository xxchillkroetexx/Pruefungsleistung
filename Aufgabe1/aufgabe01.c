/**
 * Pruefungsleistung TINF22CS1
 * Aufgabe 1
 *
 * Andreas Wolf
 * 2022-11-28
 *
 */

// Standard-Header
#include <stdio.h>
#include <stdlib.h>

/**
 * Hauptprogramm
 */
int main(int argc, char *argv[])
{
    // Eingangsvariablen
    int a, b, c, d;
    // Zwischenvariablen []-Strich
    int as, bs, cs, ds;
    // Eingangswertekombination
    int ewk;
    // Ausgabevariable
    int z;
    // Schleifenoperator
    int i;
    // Maske um nur 4 Bit darzustellen
    int totschlagmaske;

    printf("\nWertetabelle mit verschachtelter Schleife\n");
    printf("=========================================\n");
    printf("\n");

    printf("hex  dec  oct | a  b  c  d | z\n");
    printf("--------------+------------+----\n");

    for (a = 0; a < 2; a++)
    {
        for (b = 0; b < 2; b++)
        {
            for (c = 0; c < 2; c++)
            {
                for (d = 0; d < 2; d++)
                {
                    // Boolischer Ausdruck
                    z = (a && c && !d) ||
                        (b && !c && d) ||
                        (a && b && !d) ||
                        (a && !c && d);

                    // Engangsvariablen als eine Binärzahl darstellen
                    as = a << 3;
                    bs = b << 2;
                    cs = c << 1;
                    ds = d << 0;
                    // Eingangswertekombination aus dem Eingangsvariablen zusammenführen
                    ewk = as | bs | cs | ds;

                    printf(" %X    %d    %o  | %d  %d  %d  %d | %d\n",
                           ewk, ewk, ewk, a, b, c, d, z);
                }
            }
        }
    }

    printf("\nWertetabelle mit einer Schleife mit Ganzzahldivision\n");
    printf("====================================================\n");
    printf("\n");

    printf("hex  dec  oct | a  b  c  d | z\n");
    printf("--------------+------------+----\n");

    for (i = 0; i < 16; i++)
    {
        // Zahlen auf Bitebene isolieren (letzte 4 Bit)
        as = i << 0;
        a = as >> 3;

        bs = i << 1;
        b = bs >> 3;

        cs = i << 2;
        c = cs >> 3;

        ds = i << 3;
        d = ds >> 3;

        // Mit der Maske alle anderen Bits auf 0 setzen
        totschlagmaske = 0x1;

        a &= totschlagmaske;
        b &= totschlagmaske;
        c &= totschlagmaske;
        d &= totschlagmaske;

        // Boolischer Ausdruck
        z = (a && c && !d) ||
            (b && !c && d) ||
            (a && b && !d) ||
            (a && !c && d);

        printf(" %X    %d    %o  | %d  %d  %d  %d | %d\n",
               i, i, i, a, b, c, d, z);
    }
    printf("\n");
    return EXIT_SUCCESS;
} // main