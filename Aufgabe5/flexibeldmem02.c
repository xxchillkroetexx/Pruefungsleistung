/**********************************************
 *
 * Dieses Programm zeigt die Verwendung des
 * struct-Datentyps in Verbindung mit
 *  enum   fuer die Metainformation ueber den
 *         aktuellen Datentyp
 *  union  fuer unterschiedliche Nutzung
 *
 * Ausserdem zeigt das Programm, wie man die
 * beiden Elemente miteinander verketten kann.
 * In dieser Programmversion besteht eine
 * doppelte Verkettung.
 *
 * 18.11.2022 TINF22CS1
 *
 **********************************************/

/* Compiler-Direktiven
   fuer den Praeprozessor
*/

/* System-Header-Dateien */
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Eigene Header-Dateien */
#include "datentypen.h"
#include "ausgaben.h"

/* Globale Variablen */
/* ... */

/* Funktionsprototypen */
void atexit_funktion1(void);
void atexit_funktion2(void);
int liste_durchlaufen(struct flexibler_struct_typ *einstiegs_ptr,
					  enum richtungs_typ richtung,
					  int ausgabe_fkt_ptr(const struct flexibler_struct_typ *));
// ! Aufgabe 5.1
void liste_einfuegen(struct flexibler_struct_typ **anfang_ptr,
					 struct flexibler_struct_typ **ende_ptr,
					 struct flexibler_struct_typ *neu_ptr,
					 struct flexibler_struct_typ *liste_ptr);

// ! Aufgabe 5.2
struct flexibler_struct_typ *liste_loeschen(struct flexibler_struct_typ **anfang_ptr,
											struct flexibler_struct_typ **ende_ptr,
											struct flexibler_struct_typ *loesch_ptr);

/**************************************
 *                                    *
 * Hauptprogramm ist Funktion main()  *
 *                                    *
 **************************************/

int main(int argc, char *argv[])
{
	/* Lokale Variablen */
	// Adresse des 1. Listenelementes
	struct flexibler_struct_typ *anfang_ptr = NULL;
	struct flexibler_struct_typ *reserve_anf_ptr = NULL; // ! Aufgabe 5.2
	// Adresse des letzten Listenelementes
	struct flexibler_struct_typ *ende_ptr = NULL;
	struct flexibler_struct_typ *reserve_ende_ptr = NULL; // ! Aufgabe 5.2
	// Adresse eines jeden neu eingerichteten Elementes
	struct flexibler_struct_typ *neu_ptr;
	// Zeigervariable zum Durchlaufen einer verketteten Liste
	struct flexibler_struct_typ *lauf_ptr;
	// ! Aufgabe 5.2
	// Pointer für ein gelöschtes Element, das der Reserveliste hinzugefügt werden soll
	struct flexibler_struct_typ *reserve_ptr;
	// Das ist ein Funktionszeiger, der auf eine Funktion zeigen kann,
	//   wie sie von ateixt() erwartet wird.
	void (*atexit_fkt_ptr)(void) = NULL;
	// Ein Funktionszeiger, der auf die Masse an kompatiblen
	//   mathematischen Funktionen zeigen kann
	double (*mathe_fkt_ptr)(double x);
	double x;
	int n;

	// Zeigen, wie die atexit()-Funktion arbeitet (1. Bsp.)
	printf("Jetzt registrieren wir die Funktion atexit_funktion1() !\n");
	atexit(atexit_funktion1);

	// 2. Beispiel: Hier wird die Einsprungadresse zuerst in einer Zeigervariablen
	//   atexit_fkt_ptr zwischengespeichert, bevor sie mittels atexit()
	//   registriert wird.
	printf("Der atexit_fkt_ptr ist eine ganz normale Zeigervariable;\n"
		   "  Groesse = %d\n",
		   sizeof(atexit_fkt_ptr));
	printf("atexit_fkt_ptr = %p\n", atexit_fkt_ptr);
	atexit_fkt_ptr = atexit_funktion2;
	printf("atexit_fkt_ptr = %p\n", atexit_fkt_ptr);
	atexit(atexit_fkt_ptr);
	// Unsinnige Zuweisung!!! sin hat voellig anderen Parameter und Rueckgabewert
	//  als eine der atexit-Funktionen ist daher voellig inkompatibel; es wuerde
	//  also ein voelliges Fehleverhalten geben, wenn man z.B. den sin als atexit-
	//  Funktion mittels atexit() registrieren wuerde!!!
	// atexit_fkt_ptr = sin;

	x = 4.0;
	mathe_fkt_ptr = sin;
	mathe_fkt_ptr = tan;
	mathe_fkt_ptr = tanh;
	mathe_fkt_ptr = sqrt;
	// mathe_fkt_ptr = pow(x, 2); geht NICHT, da hier ein 2. Parameter vorhanden ist
	printf("mathe_fkt_ptr(x) = %lf\n", mathe_fkt_ptr(x));

	printf("Liste durchlaufen (Leere Liste!):\n");
	lauf_ptr = anfang_ptr;
	while (lauf_ptr != NULL)
	{
		print_element_by_val(*lauf_ptr);
		// Fortschalten
		lauf_ptr = lauf_ptr->next_ptr;
	} // while

	// 1. Element einrichten
	// 1.) Speicherplatz belegen
	neu_ptr = (struct flexibler_struct_typ *)
		malloc(sizeof(struct flexibler_struct_typ));
	if (neu_ptr == NULL)
	{
		fprintf(stderr,
				"Kein Heap-Speicher mehr verfuegbar! Datei %s, Zeile %d, Datum %s, Zeit %s\n",
				__FILE__, __LINE__, __DATE__, __TIME__);
		exit(EXIT_FAILURE);
	}
	// 2.) Initialisieren
	(*neu_ptr).aktuellerTyp = double_typ; // Explizite Dereferenzierungsschreibweise mit Klammern
	neu_ptr->aktuellerTyp = double_typ;	  // Neue Schreibweise mit Pfeil-Operator
	neu_ptr->daten.d = 5.7;
	neu_ptr->next_ptr = NULL;
	neu_ptr->back_ptr = NULL;
	printf("Adresse des neuen Heap-Elementes = %p\n", neu_ptr);
	// 3.) Element in die Liste einfuegen (die derzeit noch leer ist)
	// ! Aufgabe 5.1
	if (1)
	{
		liste_einfuegen(&anfang_ptr, &ende_ptr, neu_ptr, neu_ptr);
	}
	else
	{
		anfang_ptr = neu_ptr;
		ende_ptr = neu_ptr;
	}

	printf("Liste durchlaufen:\n");
	lauf_ptr = anfang_ptr;
	while (lauf_ptr != NULL)
	{
		if (0)
			print_element_by_val(*lauf_ptr);
		else
			print_element(lauf_ptr);
		// Fortschalten
		lauf_ptr = lauf_ptr->next_ptr;
	} // while

	/* 2. Element initialisieren. */
	// 1. Speicherplatz auf Heap belegen
	neu_ptr = (struct flexibler_struct_typ *)
		calloc(1, sizeof(*neu_ptr));
	assert(neu_ptr != NULL);
	// 2. Element initialisieren
	neu_ptr->aktuellerTyp = text_typ;
	strcpy(neu_ptr->daten.text, "Jetzt ist hier ein Text.");
	neu_ptr->next_ptr = NULL;
	neu_ptr->back_ptr = NULL;
	// 3. Element an das Listenende anhaengen
	// ! Aufgabe 5.1
	if (1)
	{
		liste_einfuegen(&anfang_ptr, &ende_ptr, neu_ptr, ende_ptr->next_ptr);
	}
	else
	{
		ende_ptr->next_ptr = neu_ptr;
		neu_ptr->back_ptr = ende_ptr;
		ende_ptr = neu_ptr;
	}

	/* 3. Element initialisieren. */
	// 1. Speicherplatz auf Heap belegen
	neu_ptr = (struct flexibler_struct_typ *)
		realloc(NULL, sizeof(*neu_ptr));
	assert(neu_ptr != NULL);
	// 2. Element initialisieren
	neu_ptr->aktuellerTyp = int_typ;
	neu_ptr->daten.i = 3;
	neu_ptr->next_ptr = NULL;
	neu_ptr->back_ptr = NULL;
	// 3. Element an das Listenende anhaengen
	// ! Aufgabe 5.1
	if (1)
	{
		liste_einfuegen(&anfang_ptr, &ende_ptr, neu_ptr, ende_ptr->next_ptr);
	}
	else
	{
		ende_ptr->next_ptr = neu_ptr;
		neu_ptr->back_ptr = ende_ptr;
		ende_ptr = neu_ptr;
	}

	// Durchlaufen der Verkettung
	printf("Liste durchlaufen:\n");
	lauf_ptr = anfang_ptr;
	while (lauf_ptr != NULL)
	{
		if (0)
			print_element_by_val(*lauf_ptr);
		else
			print_element(lauf_ptr);
		// Fortschalten
		lauf_ptr = lauf_ptr->next_ptr;
	} // while
	printf("\n");

	// Durchlaufen mit allgemeiner Funktion
	printf("Durchlaufen mit allgemeiner Funktion (lange Ausgabe):\n");
	n = liste_durchlaufen(anfang_ptr, vorwaerts, print_element);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	printf("Durchlaufen mit allgemeiner Funktion (kurze Ausgabe):\n");
	n = liste_durchlaufen(ende_ptr, rueckwaerts, print_element_kurz);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	printf("Durchlaufen mit allgemeiner Funktion (OHNE Ausgabe):\n");
	n = liste_durchlaufen(anfang_ptr, vorwaerts, NULL);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	// ! Aufgabe 5.2
	// Mittleres Element löschen
	reserve_ptr = liste_loeschen(&anfang_ptr, &ende_ptr, anfang_ptr->next_ptr);
	// gelöschtes Element in Reserveliste einfügen
	liste_einfuegen(&reserve_anf_ptr, &reserve_ende_ptr, reserve_ptr, reserve_ptr);

	// Letztes Element löschen
	reserve_ptr = liste_loeschen(&anfang_ptr, &ende_ptr, ende_ptr);
	// gelöschtes Element in Reserveliste einfügen
	liste_einfuegen(&reserve_anf_ptr, &reserve_ende_ptr, reserve_ptr, reserve_ende_ptr->next_ptr);

	// Verbleibendes erstes Element löschen
	reserve_ptr = liste_loeschen(&anfang_ptr, &ende_ptr, anfang_ptr);
	// gelöschtes Element in Reserveliste einfügen
	liste_einfuegen(&reserve_anf_ptr, &reserve_ende_ptr, reserve_ptr, reserve_ende_ptr->next_ptr);

	// ? Liste leer
	// Durchlaufen mit allgemeiner Funktion
	printf("Durchlaufen mit allgemeiner Funktion (lange Ausgabe):\n");
	n = liste_durchlaufen(anfang_ptr, vorwaerts, print_element);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	printf("Durchlaufen mit allgemeiner Funktion (kurze Ausgabe):\n");
	n = liste_durchlaufen(ende_ptr, rueckwaerts, print_element_kurz);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	printf("Durchlaufen mit allgemeiner Funktion (OHNE Ausgabe):\n");
	n = liste_durchlaufen(anfang_ptr, vorwaerts, NULL);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	// ! Aufgabe 5.2
	// Reserveliste ausgeben
	printf("\nRESERVELISTE:\n");
	printf("Durchlaufen mit allgemeiner Funktion (kurze Ausgabe):\n");
	n = liste_durchlaufen(reserve_ende_ptr, rueckwaerts, print_element_kurz);
	printf("Anzahl der durchlaufenen Listenelemente: %d\n", n);

	// Durchlaufen der Verkettung
	printf("Liste durchlaufen:\n");
	lauf_ptr = reserve_anf_ptr;
	while (lauf_ptr != NULL)
	{
		if (0)
			print_element_by_val(*lauf_ptr);
		else
			print_element(lauf_ptr);
		// Fortschalten
		lauf_ptr = lauf_ptr->next_ptr;
	} // while
	printf("\n");

	printf("ENDE!!! \n\n");

	return 0;
} /* main */

/**
 * Diese Funktion kann mittels atexit()
 * registriert werden und wird dann vom
 * System aufgerufen, wenn das Programm endet.
 */
void atexit_funktion1(void)
{
	printf("Hier meldet sich die atexit_funktion1()!\n");
} // atexit_funktion1

/**
 * Diese Funktion kann mittels atexit()
 * registriert werden und wird dann vom
 * System aufgerufen, wenn das Programm endet.
 */
void atexit_funktion2(void)
{
	printf("Und das ist die atexit_funktion2()!\n");
} // atexit_funktion2

/**
 * Diese Funktion ist eine allgemein gehalten Funktion,
 * mit der eine Liste von Elementen des Typs
 * struct flexibler_struct_typ
 * vorwaerts oder rueckwaerts durchlaufen werden kann.
 *
 * Formale Parameter:
 *  einstiegs_ptr - Adresse desjenigen Elementes, mit dem
 *    beim Durchlaufen begonnen werden soll.
 *  richtung - Richtung, in der die Liste durchlaufen werden
 *    soll.
 *  ausgabe_fkt_ptr - Einsprungadresse derjenigen Funktion,
 *    die zum Ausgeben eines jeden Listenelementes verwendet
 *    werden soll. - Wenn der Zeiger NULL enthaelt, sollen
 *    keine Ausgaben erfolgen; es wird dann nur die Anzahl
 *    der Listenelemente ermittelt.
 *
 * Rueckgabewert:
 *  Anzahl der durchlaufenen Listenelemente.
 */
int liste_durchlaufen(struct flexibler_struct_typ *einstiegs_ptr,
					  enum richtungs_typ richtung,
					  int ausgabe_fkt_ptr(const struct flexibler_struct_typ *))
{
	int n_elemente = 0;
	struct flexibler_struct_typ *lauf_ptr = einstiegs_ptr;
	// while(lauf_ptr != NULL) "Ordentliche Variante"
	while (lauf_ptr) // Geht nur in C, weil hier die einfache Regel gilt, dass jeder Wert
					 //  ausgewertet werden kann (und so auch ein Zeiger bzw. eine Adresse)
	{
		if (ausgabe_fkt_ptr != NULL)
			ausgabe_fkt_ptr(lauf_ptr);
		n_elemente++;
		if (richtung == vorwaerts)
			lauf_ptr = lauf_ptr->next_ptr;
		else
			lauf_ptr = lauf_ptr->back_ptr;
	} // while
	return n_elemente;
} // liste_durchlaufen

/**
 * ! Aufgabe 5.1
 * Fügt ein Element rechts von dem übergebenen Element ein
 */
void liste_einfuegen(struct flexibler_struct_typ **anfang_ptr,
					 struct flexibler_struct_typ **ende_ptr,
					 struct flexibler_struct_typ *neu_ptr,
					 struct flexibler_struct_typ *liste_ptr)
{

	// Element an Position des Pointers liste_ptr einhaengen
	if (*anfang_ptr == NULL)
	{
		if (*ende_ptr != NULL)
		{
			// Fehler bei Übergabe der Pointer
			printf("return EXIT_FAILURE\n");
		}
		// leere Liste
		*anfang_ptr = neu_ptr;
		*ende_ptr = neu_ptr;
	}
	else
	{
		if (liste_ptr == NULL)
		{
			// als erstes Element einfuegen
			neu_ptr->next_ptr = *anfang_ptr;
			(*anfang_ptr)->back_ptr = neu_ptr;
			(*anfang_ptr) = neu_ptr;
		}
		else
		{
			// in die Liste nach Pointer liste_ptr einfuegen
			neu_ptr->next_ptr = liste_ptr->next_ptr;
			neu_ptr->next_ptr = liste_ptr;
			liste_ptr->next_ptr = neu_ptr;

			if (neu_ptr->next_ptr == NULL)
			{
				// am Ende der Liste einfuegen
				*ende_ptr = neu_ptr;
			}
			else
			{
				neu_ptr->next_ptr->back_ptr = neu_ptr;
			}
		}
	}
} // liste_einfuegen

/**
 * ! Aufgabe 5.2
 * Löscht ein entsprechendes Element aus der Liste
 */
struct flexibler_struct_typ *liste_loeschen(struct flexibler_struct_typ **anfang_ptr,
											struct flexibler_struct_typ **ende_ptr,
											struct flexibler_struct_typ *loesch_ptr)
{
	if (loesch_ptr == NULL)
	{
		printf("LOESCH_PTR_ERROR\n");
		return loesch_ptr;
	}
	else
	{
		if (*anfang_ptr == loesch_ptr)
		{
			// erstes Element löschen - NULL, wenn Liste leer
			*anfang_ptr = loesch_ptr->next_ptr;
		}
		if (*ende_ptr == loesch_ptr)
		{
			// letztes Element löschen - NULL, wenn Liste leer
			*ende_ptr = loesch_ptr->back_ptr;
		}
		if (loesch_ptr->next_ptr != NULL)
		{
			// Verkettung bei Nachfolger korrigieren
			loesch_ptr->next_ptr->back_ptr = loesch_ptr->back_ptr;
		}
		if (loesch_ptr->back_ptr != NULL)
		{
			// Verkettung bei Vorgänger korrigieren
			loesch_ptr->back_ptr->next_ptr = loesch_ptr->next_ptr;
		}
		loesch_ptr->next_ptr = NULL;
		loesch_ptr->back_ptr = NULL;
		return loesch_ptr;
	}
} // liste_loeschen