/**
 * Ein Programm zum Sortieren und Suchen.
 *
 * TINF22CS1, 25.11.2022
 */
// Standard-Header
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Prototypen
int vgl_fkt_double_aufsteigend(const void *, const void *);
int vgl_fkt_double_absteigend(const void *, const void *);
int vgl_fkt_int_aufsteigend(const void *, const void *);
int vgl_fkt_int_absteigend(const void *, const void *);

/**
 * Hauptprogramm.
 */
int main(int argc, char*argv[])
{
	double dfeld[] = {
		1.3, 3.5, 3.0, 2.5, 1.7, 2.3
	};
	int dfeld_n = sizeof(dfeld) / sizeof(dfeld[0]);
	int ifeld[] = {
		3, 5, 2, 6, 7, 1
	};
	int ifeld_n = sizeof(ifeld) / sizeof(ifeld[0]);
	int i;

	printf("Sortieren und Suchen (Gleitkommazahlen):\n");

	printf("Unsortiertes Feld:\n");
	for(i = 0; i < dfeld_n; i++)
		printf("%.1lf; ", dfeld[i]);
	printf("\n");

	printf("Aufsteigend sortieren mittels qsort() ...\n");
	qsort(&dfeld[0], dfeld_n, sizeof(dfeld[0]), 
		vgl_fkt_double_aufsteigend);
	
	printf("Aufsteigend sortiertes Feld:\n");
	for(i = 0; i < dfeld_n; i++)
		printf("%.1lf; ", dfeld[i]);
	printf("\n");

	printf("Einen Wert im Feld suchen...\n");
	{
		double zu_suchende_werte[] = { 2.5, 4.0 };
		int zu_suchende_werte_n = sizeof(zu_suchende_werte) / sizeof(zu_suchende_werte[0]);
		double *treffer_ptr;

		for(i = 0; i < zu_suchende_werte_n; i++)
		{
			treffer_ptr = (double*)
				bsearch(&zu_suchende_werte[i], &dfeld[0], dfeld_n, sizeof(dfeld[0]), 
					vgl_fkt_double_aufsteigend);
			if(treffer_ptr == NULL)
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
	for(i = 0; i < dfeld_n; i++)
		printf("%.1lf; ", dfeld[i]);
	printf("\n");

	printf("\n"); // --------------------------------------------


	printf("Sortieren und Suchen (Ganzzahlen):\n");

	printf("Unsortiertes Feld:\n");
	for(i = 0; i < ifeld_n; i++)
		printf("%d; ", ifeld[i]);
	printf("\n");

	printf("Aufsteigend sortieren mittels qsort() ...\n");
	qsort(&ifeld[0], ifeld_n, sizeof(ifeld[0]), 
		vgl_fkt_int_aufsteigend);
	
	printf("Aufsteigend sortiertes Feld:\n");
	for(i = 0; i < ifeld_n; i++)
		printf("%d; ", ifeld[i]);
	printf("\n");

	printf("Einen Wert im Feld suchen...\n");
	{
		int zu_suchende_werte[] = { 2, 8 };
		int zu_suchende_werte_n = sizeof(zu_suchende_werte) / sizeof(zu_suchende_werte[0]);
		int *treffer_ptr;

		for(i = 0; i < zu_suchende_werte_n; i++)
		{
			treffer_ptr = (int*)
				bsearch(&zu_suchende_werte[i], &ifeld[0], ifeld_n, sizeof(ifeld[0]), 
					vgl_fkt_int_aufsteigend);
			if(treffer_ptr == NULL)
				printf("Diese Note %d gibt es nicht!\n", zu_suchende_werte[i]);
			else
				printf("Diese Note %d gibt es! :-) Adresse = %p\n", zu_suchende_werte[i],
					treffer_ptr);
		}
	}

	printf("Absteigend sortieren mittels qsort() ...\n");
	qsort(&ifeld[0], ifeld_n, sizeof(ifeld[0]), 
		vgl_fkt_int_absteigend);

	printf("Absteigend sortiertes Feld:\n");
	for(i = 0; i < ifeld_n; i++)
		printf("%d; ", ifeld[i]);
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
	const double *dbl1_ptr = (const double*)v1_ptr;
	const double *dbl2_ptr = (const double*)v2_ptr;
	// *(double*)v1_ptr; Das waere auch moeglich, wir verwenden aber typgebundene
	//   Zeiger, um den Code auch bei erweiterten Datentypen wie Personendatensaetzen
	//   etc. uebersichtlicher zu gestalten, als wenn wir jedesmal einen Type-Cast
	//   vor v1_ptr bzw. v2_ptr setzen wuerden.
	// Das geht bei Gleitkommazahlen nicht, weil die Differenz
	//  zwischen 2 zu vergleichenden Zahlen gerne kleiner als 1.0
	//  sein kann und durch das Casten dieser Wert zu 0 werden wuerde,
	//  was bedeuten wuerde, dass die beiden Zahlen gleich zu sein scheinen,
	//  obwohl sie es nicht sind.
	if (0) return (int)(*dbl1_ptr - *dbl2_ptr); // NEIN!!!
	if(*dbl1_ptr < *dbl2_ptr)
		return -1;
	if(*dbl1_ptr == *dbl2_ptr)
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
	const double *dbl1_ptr = (const double*)v2_ptr;
	const double *dbl2_ptr = (const double*)v1_ptr;
	// *(double*)v1_ptr; Das waere auch moeglich, wir verwenden aber typgebundene
	//   Zeiger, um den Code auch bei erweiterten Datentypen wie Personendatensaetzen
	//   etc. uebersichtlicher zu gestalten, als wenn wir jedesmal einen Type-Cast
	//   vor v1_ptr bzw. v2_ptr setzen wuerden.
	if(*dbl1_ptr < *dbl2_ptr)
		return -1;
	if(*dbl1_ptr == *dbl2_ptr)
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
	const int *i1_ptr = (const int*)v1_ptr;
	const int *i2_ptr = (const int*)v2_ptr;

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
	const int *i1_ptr = (const int*)v2_ptr;
	const int *i2_ptr = (const int*)v1_ptr;

	return *i1_ptr - *i2_ptr;
} // vgl_fkt_int_absteigend

