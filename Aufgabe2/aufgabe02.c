/**
 * Pruefungsleistung TINF22CS1
 * Aufgabe 2
 *
 * Andreas Wolf
 * 2022-11-29
 *
 */
// Standard-Header
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/**
 * Hauptprogramm
 */
int main(int argc, char *argv[])
{
    // Gegeben:
    unsigned short s1, s2;
    // Ausgabewert aus s1 und s2 zusammengesetzt
    int ziel = 0;
    // Bestandteile von s1
    unsigned short s1a, s1b, s1c, s1d;
    // Bestandteile von s2
    unsigned short s2a, s2b, s2c, s2d;
    // Zwischenspeicher
    unsigned short z;

    // Prüfen, ob User Eingaben getätigt hat
    if (argc == 3)
    {
        char testChar1;
        char testChar2;
        sscanf(argv[2], "%s", &testChar2);
        sscanf(argv[1], "%s", &testChar1);

        // Prüfen, ob Eingabe Hexcode ist. Wenn ja, Werte speichern
        if (isxdigit(testChar1) && isxdigit(testChar2))
        {
            sscanf(argv[2], "%X", &s2);
            sscanf(argv[1], "%X", &s1);
        }
        //...Wenn nein, Error ausgeben
        else
        {
            fprintf(stderr, "\n[ERROR1]\nTimestamp: %s - %s\n\nAn error occured in ==> %s <== in line %d.\n\nValues are NOT in Hex-Code.\n\n",
                    __DATE__, __TIME__, __FILE__, __LINE__);
            return EXIT_FAILURE;
        }
    }
    // Sind keine weiteren Parameter angegeben, werden Defaultwerte übernommen
    else if (argc == 1)
    {
        s1 = 0xBDA1;
        s2 = 0xACBE;
    }
    // Sollten 1 oder mehr als 2 Parameter angegeben sein, wird ein Fehler ausgegeben
    else
    {
        fprintf(stderr, "\n[ERROR2]\nTimestamp:\n%s - %s\n\nAn error occured in ==> %s <== in line %d.\n\nPlease specify 2 4-digit Hex-numbers.\n\n",
                __DATE__, __TIME__, __FILE__, __LINE__);
        return EXIT_FAILURE;
    }

    // s1 und s2 ausgeben
    printf("\n");
    printf("s1 = %X\ns2 = %X\n", s1, s2);
    printf("\n");

    // s1 zerlegen und Bestandteile ausgeben
    z = s1 << 4 * 0;
    s1a = z >> 4 * 3;
    printf("s1a = %X\n", s1a);

    z = s1 << 4 * 1;
    s1b = z >> 4 * 3;
    printf("s1b = %X\n", s1b);

    z = s1 << 4 * 2;
    s1c = z >> 4 * 3;
    printf("s1c = %X\n", s1c);

    z = s1 << 4 * 3;
    s1d = z >> 4 * 3;
    printf("s1d = %X\n", s1d);

    // s2 zerlegen und Bestandteile ausgeben
    z = s2 << 4 * 0;
    s2a = z >> 4 * 3;
    printf("s2a = %X\n", s2a);

    z = s2 << 4 * 1;
    s2b = z >> 4 * 3;
    printf("s2b = %X\n", s2b);

    z = s2 << 4 * 2;
    s2c = z >> 4 * 3;
    printf("s2d = %X\n", s2c);

    z = s2 << 4 * 3;
    s2d = z >> 4 * 3;
    printf("s2c = %X\n", s2d);

    // Ausgabe aus Teilen von s1 und s2 zusammensetzen
    ziel += s1a << 4 * 7;
    ziel += s2a << 4 * 6;
    ziel += s1b << 4 * 5;
    ziel += s2b << 4 * 4;
    ziel += s1c << 4 * 3;
    ziel += s2c << 4 * 2;
    ziel += s1d << 4 * 1;
    ziel += s2d << 4 * 0;
    printf("\n");
    printf("ziel = %X\n", ziel);
    printf("\n");

    return EXIT_SUCCESS;
} // main