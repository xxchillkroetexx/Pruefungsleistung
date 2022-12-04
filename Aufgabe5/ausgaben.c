/**
 * Diese C-Modul enthaelt die Definitionen der 
 * Ausgabefunktionen.
 *
 * TINF22CS1, 22.11.2022
 */
// System-Header
#include <stdio.h>
#include <stdlib.h>

// Eigene Header-Dateien
#include "ausgaben.h"

/**
 * Diese Funktion gibt ein Listenelement aus.
 * Hier ineffizient, da das gesamte Element kopiert wird!
 */
int print_element_by_val(struct flexibler_struct_typ element)
{
	int n_zeichen_ausgegeben;
	switch (element.aktuellerTyp)
	{
		case double_typ:
			n_zeichen_ausgegeben = printf("Aktuelles Element enthaelt double_typ-Daten:  %f\n",
				element.daten.d);
			break;
		case int_typ:
			n_zeichen_ausgegeben = printf("Aktuelles Element enthaelt int_typ-Daten:  %d\n",
				element.daten.i);
			break;
		case text_typ:
			n_zeichen_ausgegeben = printf("Aktuelles Element enthaelt einen Text: '%s'\n",
				element.daten.text);
			break;
		default:
			fprintf(stderr, "print_element_by_val(): switch - Interner Fehler!\n");
			exit(EXIT_FAILURE);
	}
	return n_zeichen_ausgegeben;
} // print_element_by_val


/**
 * Diese Funktion gibt ein Listenelement aus,
 * effizienter, da Uebergabe nur der Anfangsadresse 
 * des auszugebenden Elementes.
 */
int print_element(const struct flexibler_struct_typ *element_ptr)
{
	int n_zeichen_ausgegeben;
	switch (element_ptr->aktuellerTyp)
	{
		case double_typ:
			n_zeichen_ausgegeben = printf("Aktuelles Element enthaelt double_typ-Daten:  %f\n",
				element_ptr->daten.d);
			break;
		case int_typ:
			n_zeichen_ausgegeben = printf("Aktuelles Element enthaelt int_typ-Daten:  %d\n",
				element_ptr->daten.i);
			break;
		case text_typ:
			n_zeichen_ausgegeben = printf("Aktuelles Element enthaelt einen Text: '%s'\n",
				(*element_ptr).daten.text);
			break;
		default:
			fprintf(stderr, "print_element_by_val(): switch - Interner Fehler!\n");
			exit(EXIT_FAILURE);
	}
	return n_zeichen_ausgegeben;
} // print_element


/**
 * Diese Funktion gibt ein Listenelement aus,
 * effizienter, da Uebergabe nur der Anfangsadresse 
 * des auszugebenden Elementes.
 * Hier: Kurze Version!
 */
int print_element_kurz(const struct flexibler_struct_typ *element_ptr)
{
	int n_zeichen_ausgegeben;
	switch (element_ptr->aktuellerTyp)
	{
		case double_typ:
			n_zeichen_ausgegeben = printf("%.2f\n",
				element_ptr->daten.d);
			break;
		case int_typ:
			n_zeichen_ausgegeben = printf("%d\n",
				element_ptr->daten.i);
			break;
		case text_typ:
			n_zeichen_ausgegeben = printf("%s\n",
				(*element_ptr).daten.text);
			break;
		default:
			fprintf(stderr, "print_element_by_val(): switch - Interner Fehler!\n");
			exit(EXIT_FAILURE);
	}
	return n_zeichen_ausgegeben;
} // print_element_kurz
