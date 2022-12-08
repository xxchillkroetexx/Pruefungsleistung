/**
 * Ein Programm zum Sortieren und Suchen.
 *
 * TINF22CS1, 25.11.2022
 */
// Standard-Header
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypen
int vgl_fkt_double_aufsteigend(const void *, const void *);
int vgl_fkt_double_absteigend(const void *, const void *);
int vgl_fkt_int_aufsteigend(const void *, const void *);
int vgl_fkt_int_absteigend(const void *, const void *);
// ! Aufgabe 6.1
int vgl_fkt_char_aufsteigend(const void *, const void *);
int vgl_fkt_char_absteigend(const void *, const void *);
// ! Aufgabe 6.2
int struct_vergleich(const void *, const void *);

// ! Aufgabe 6.2
struct feld_typ
{
	double gehalt;
	int personal_nr;
	char *name_ptr;
};

/**
 * Hauptprogramm.
 */
int main(int argc, char *argv[])
{
	double dfeld[] = {
		1.3, 3.5, 3.0, 2.5, 1.7, 2.3};
	int dfeld_n = sizeof(dfeld) / sizeof(dfeld[0]);
	int ifeld[] = {
		3, 5, 2, 6, 7, 1};
	int ifeld_n = sizeof(ifeld) / sizeof(ifeld[0]);
	int i;

	// ! Aufgabe 6.1
	char *sfeld[] = {"Caesar", "Doris", "Anton", "Peter", "Fritz"};
	int sfeld_n = sizeof(sfeld) / sizeof(sfeld[0]);

	printf("Sortieren und Suchen (Gleitkommazahlen):\n");

	printf("Unsortiertes Feld:\n");
	for (i = 0; i < dfeld_n; i++)
		printf("%.1lf; ", dfeld[i]);
	printf("\n");

	printf("Aufsteigend sortieren mittels qsort() ...\n");
	qsort(&dfeld[0], dfeld_n, sizeof(dfeld[0]),
		  vgl_fkt_double_aufsteigend);

	printf("Absteigend sortiertes Feld:\n");
	for (i = 0; i < dfeld_n; i++)
		printf("%.1lf; ", dfeld[i]);
	printf("\n");

	printf("Einen Wert im Feld suchen...\n");
	{
		double zu_suchende_werte[] = {2.5, 4.0};
		int zu_suchende_werte_n = sizeof(zu_suchende_werte) / sizeof(zu_suchende_werte[0]);
		double *treffer_ptr;

		for (i = 0; i < zu_suchende_werte_n; i++)
		{
			treffer_ptr = (double *)
				bsearch(&zu_suchende_werte[i], &dfeld[0], dfeld_n, sizeof(dfeld[0]),
						vgl_fkt_double_aufsteigend);
			if (treffer_ptr == NULL)
				printf("Diese Note %.1lf gibt es nicht!\n", zu_suchende_werte[i]);
			else
				printf("Diese Note %.1lf gibt es! :-) Adresse = %p\n", zu_suchende_werte[i],
					   treffer_ptr);
		}
	}

	printf("Absteigend sortieren mittels qsort() ...\n");
	qsort(&dfeld[0], dfeld_n, sizeof(dfeld[0]),
		  vgl_fkt_double_absteigend);

	printf("Absteigend sortiertes Feld:\n");
	for (i = 0; i < dfeld_n; i++)
		printf("%.1lf; ", dfeld[i]);
	printf("\n");

	printf("\n"); // --------------------------------------------

	printf("Sortieren und Suchen (Ganzzahlen):\n");

	printf("Unsortiertes Feld:\n");
	for (i = 0; i < ifeld_n; i++)
		printf("%d; ", ifeld[i]);
	printf("\n");

	printf("Aufsteigend sortieren mittels qsort() ...\n");
	qsort(&ifeld[0], ifeld_n, sizeof(ifeld[0]),
		  vgl_fkt_int_aufsteigend);

	printf("Aufsteigend sortiertes Feld:\n");
	for (i = 0; i < ifeld_n; i++)
		printf("%d; ", ifeld[i]);
	printf("\n");

	printf("Einen Wert im Feld suchen...\n");
	{
		int zu_suchende_werte[] = {2, 8};
		int zu_suchende_werte_n = sizeof(zu_suchende_werte) / sizeof(zu_suchende_werte[0]);
		int *treffer_ptr;

		for (i = 0; i < zu_suchende_werte_n; i++)
		{
			treffer_ptr = (int *)
				bsearch(&zu_suchende_werte[i], &ifeld[0], ifeld_n, sizeof(ifeld[0]),
						vgl_fkt_int_aufsteigend);
			if (treffer_ptr == NULL)
				printf("Diese Note %d gibt es nicht!\n", zu_suchende_werte[i]);
			else
				printf("Diese Note %d gibt es! :-) Adresse = %p\n", zu_suchende_werte[i],
					   treffer_ptr);
		}
	}

	printf("Absteigend sortieren mittels qsort() ...\n");
	qsort(&ifeld[0], ifeld_n, sizeof(ifeld[0]), vgl_fkt_int_absteigend);

	printf("Absteigend sortiertes Feld:\n");
	for (i = 0; i < ifeld_n; i++)
		printf("%d; ", ifeld[i]);
	printf("\n");

	// ! Aufgabe 6.1
	printf("\n\nSortieren und Suchen (Textfelder):\n");

	printf("Unsortiertes Feld:\n");
	for (i = 0; i < sfeld_n; i++)
		printf("%s\n", sfeld[i]);
	printf("\n");

	printf("Aufsteigend sortieren mittels qsort() ...\n");
	if (0)
	{
		qsort(sfeld, sfeld_n, sizeof(char *), vgl_fkt_char_aufsteigend);
	}
	else
	{
		qsort(sfeld, sfeld_n, sizeof(char *), vgl_fkt_char_absteigend);
	}

	printf("Aufsteigend sortiertes Feld:\n");
	for (i = 0; i < sfeld_n; i++)
		printf("%s\n", sfeld[i]);
	printf("\n");

	printf("Einen Wert im Feld suchen...\n");
	{
		char *suche = "Caesar"; // String, der im Feld gesucht werden soll
		for (int j = 0; j < sfeld_n; j++)
		{
			const char *ergebnis = strstr(sfeld[j], suche);
			if (ergebnis != NULL)
			{
				printf("Der Name %s wurde gefunden: %s\n", suche);
			}
		}
	}
	printf("\n");

	// ! Aufgabe 6.2
	printf("Vergleich feld_typ\n");
	struct feld_typ person1 = {1500.0, 4711, "Anton"};
	struct feld_typ person2 = {2500.0, 1234, "Peter"};
	struct feld_typ person3 = {1000.0, 1337, "Anton"};
	struct feld_typ person4 = {3000.0, 9999, "Fritz"};
	struct feld_typ person5 = {1500.0, 2022, "Anton"};
	struct feld_typ personal[] = {person1, person2, person3, person4, person5};
	int personal_n = sizeof(personal) / sizeof(personal[0]);

	printf("\n\nSortieren feld_typ):\n");

	printf("Unsortiertes Feld:\n");
	for (i = 0; i < personal_n; i++)
		printf("Name: %s | Gehalt: %lf | Pers.-Nr.: %d\n",
			   personal[i].name_ptr, personal[i].gehalt, personal[i].personal_nr);
	printf("\n");

	printf("Aufsteigend sortieren mittels qsort() ...\n");
	qsort(personal, personal_n, sizeof(struct feld_typ), struct_vergleich);

	printf("Aufsteigend sortiertes Feld:\n");
	for (i = 0; i < personal_n; i++)
		printf("Name: %s | Gehalt: %lf | Pers.-Nr.: %d\n",
			   personal[i].name_ptr, personal[i].gehalt, personal[i].personal_nr);
	printf("\n");

	printf("\n");
	return EXIT_SUCCESS;
} // main

/**
 * Diese Callback-Funktion ist eine Vergleichsfunktion
 * fuer z.B. qsort und bsearch, die 2 double-Werte
 * miteinander vergleicht und fuer eine austeigende
 * Sortierung sorgt.
 *
 * Formale Parameter:
 *  v1_ptr - Adresse des ersten zu vergleichenden Feldelementes
 *  v2_ptr - Adresse des zweiten zu vergleichenden Feldelementes
 *
 * Rueckgabewert:
 *  neg. Ganzzahl --> 1. Wert ist vor dem 2. einzusortieren
 *              0 --> beide Werte sind gleich
 *  pos. Ganzzahl --> 1. Wert ist nach dem 2. einzusortieren
 */
int vgl_fkt_double_aufsteigend(const void *v1_ptr, const void *v2_ptr)
{
	const double *dbl1_ptr = (const double *)v1_ptr;
	const double *dbl2_ptr = (const double *)v2_ptr;
	// *(double*)v1_ptr; Das waere auch moeglich, wir verwenden aber typgebundene
	//   Zeiger, um den Code auch bei erweiterten Datentypen wie Personendatensaetzen
	//   etc. uebersichtlicher zu gestalten, als wenn wir jedesmal einen Type-Cast
	//   vor v1_ptr bzw. v2_ptr setzen wuerden.
	// Das geht bei Gleitkommazahlen nicht, weil die Differenz
	//  zwischen 2 zu vergleichenden Zahlen gerne kleiner als 1.0
	//  sein kann und durch das Casten dieser Wert zu 0 werden wuerde,
	//  was bedeuten wuerde, dass die beiden Zahlen gleich zu sein scheinen,
	//  obwohl sie es nicht sind.
	if (0)
		return (int)(*dbl1_ptr - *dbl2_ptr); // NEIN!!!
	if (*dbl1_ptr < *dbl2_ptr)
		return -1;
	if (*dbl1_ptr == *dbl2_ptr)
		return 0;
	return +1;
} // vgl_fkt_double_aufsteigend

/**
 * Diese Callback-Funktion ist eine Vergleichsfunktion
 * fuer z.B. qsort und bsearch, die 2 double-Werte
 * miteinander vergleicht und fuer eine absteigende
 * Sortierung sorgt.
 *
 * Formale Parameter:
 *  v1_ptr - Adresse des ersten zu vergleichenden Feldelementes
 *  v2_ptr - Adresse des zweiten zu vergleichenden Feldelementes
 *
 * Rueckgabewert:
 *  neg. Ganzzahl --> 1. Wert ist vor dem 2. einzusortieren
 *              0 --> beide Werte sind gleich
 *  pos. Ganzzahl --> 1. Wert ist nach dem 2. einzusortieren
 */
int vgl_fkt_double_absteigend(const void *v1_ptr, const void *v2_ptr)
{
	const double *dbl1_ptr = (const double *)v2_ptr;
	const double *dbl2_ptr = (const double *)v1_ptr;
	// *(double*)v1_ptr; Das waere auch moeglich, wir verwenden aber typgebundene
	//   Zeiger, um den Code auch bei erweiterten Datentypen wie Personendatensaetzen
	//   etc. uebersichtlicher zu gestalten, als wenn wir jedesmal einen Type-Cast
	//   vor v1_ptr bzw. v2_ptr setzen wuerden.
	if (*dbl1_ptr < *dbl2_ptr)
		return -1;
	if (*dbl1_ptr == *dbl2_ptr)
		return 0;
	return +1;
} // vgl_fkt_double_absteigend

/**
 * Diese Callback-Funktion ist eine Vergleichsfunktion
 * fuer z.B. qsort und bsearch, die 2 inte-Werte
 * miteinander vergleicht und fuer eine austeigende
 * Sortierung sorgt.
 *
 * Formale Parameter:
 *  v1_ptr - Adresse des ersten zu vergleichenden Feldelementes
 *  v2_ptr - Adresse des zweiten zu vergleichenden Feldelementes
 *
 * Rueckgabewert:
 *  neg. Ganzzahl --> 1. Wert ist vor dem 2. einzusortieren
 *              0 --> beide Werte sind gleich
 *  pos. Ganzzahl --> 1. Wert ist nach dem 2. einzusortieren
 */
int vgl_fkt_int_aufsteigend(const void *v1_ptr, const void *v2_ptr)
{
	const int *i1_ptr = (const int *)v1_ptr;
	const int *i2_ptr = (const int *)v2_ptr;

	return *i1_ptr - *i2_ptr;
} // vgl_fkt_int_aufsteigend

/**
 * Diese Callback-Funktion ist eine Vergleichsfunktion
 * fuer z.B. qsort und bsearch, die 2 int-Werte
 * miteinander vergleicht und fuer eine absteigende
 * Sortierung sorgt.
 *
 * Formale Parameter:
 *  v1_ptr - Adresse des ersten zu vergleichenden Feldelementes
 *  v2_ptr - Adresse des zweiten zu vergleichenden Feldelementes
 *
 * Rueckgabewert:
 *  neg. Ganzzahl --> 1. Wert ist vor dem 2. einzusortieren
 *              0 --> beide Werte sind gleich
 *  pos. Ganzzahl --> 1. Wert ist nach dem 2. einzusortieren
 */
int vgl_fkt_int_absteigend(const void *v1_ptr, const void *v2_ptr)
{
	const int *i1_ptr = (const int *)v2_ptr;
	const int *i2_ptr = (const int *)v1_ptr;

	return *i1_ptr - *i2_ptr;
} // vgl_fkt_int_absteigend

// ! Aufgabe 6.1
int vgl_fkt_char_aufsteigend(const void *v1_ptr, const void *v2_ptr)
{
	const char *c1_ptr = *(const char **)v1_ptr;
	const char *c2_ptr = *(const char **)v2_ptr;

	int result = strcmp(c1_ptr, c2_ptr);

	return result;
} // vgl_fkt_char_aufsteigend

// ! Aufgabe 6.1
int vgl_fkt_char_absteigend(const void *v1_ptr, const void *v2_ptr)
{
	const char *c1_ptr = *(const char **)v2_ptr;
	const char *c2_ptr = *(const char **)v1_ptr;

	int result = strcmp(c1_ptr, c2_ptr);

	return result;
} // vgl_fkt_char_aufsteigend

// ! Aufgabe 6.2
int struct_vergleich(const void *v1_ptr, const void *v2_ptr)
{
	const struct feld_typ *f1_ptr = (const struct feld_typ *)v1_ptr;
	const struct feld_typ *f2_ptr = (const struct feld_typ *)v2_ptr;

	int ergebnis = strcmp(f1_ptr->name_ptr, f2_ptr->name_ptr);
	if (ergebnis != 0)
		return ergebnis;

	if (f1_ptr->gehalt < f2_ptr->gehalt)
		return 1;
	if (f1_ptr->gehalt > f2_ptr->gehalt)
		return -1;

	if (f1_ptr->personal_nr < f2_ptr->personal_nr)
		return 1;
	if (f1_ptr->personal_nr > f2_ptr->personal_nr)
		return -1;

	return 0;
}