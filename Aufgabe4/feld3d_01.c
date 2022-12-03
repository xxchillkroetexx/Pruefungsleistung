/**
 * 3D-Felder in C in Kombination mit Zugriffsmatrizen
 * fuer moegliche Indexzugriffe.
 *
 * TINF22CS1, 24.11.2022
 */
// Standard-Header
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Prototypen
void feld_ausgeben(const double *feld_anf_ptr,
				   int ebenen_n,
				   int zeilen_n,
				   int spalten_n);
double ***zugriffsfelder_erstellen(const double *feld_anf_ptr,
								   int ebenen_n,
								   int zeilen_n,
								   int spalten_n);
void feld_ausgeben_mit_indices(const double ***matrix_3d,
							   int ebenen_n,
							   int zeilen_n,
							   int spalten_n);
// neue Funktion aus 4.1
// Initialisieren eines 3d Feldes
void feld3d_init(double *matrix_3d_anf,
				 int ebenen_n,
				 int zeilen_n,
				 int spalten_n);
// Aufgabe 4.3
// Ein Feld wie in Java erstellen
double ***felder_erstellen_wie_java(const double *feld_anf_ptr,
									int ebenen_n,
									int zeilen_n,
									int spalten_n);
// Aufgabe 4.4
void zugriffsfelder_erstellen_by_ref();

/**
 * Hauptprgramm.
 */
int main(int argc, char *argv[])
{
	// Anzahl der Elemente je Dimension
	int ebenen_n = 3;
	int zeilen_n = 5;
	int spalten_n = 4;
	// Anfangsadresse des 3D-Feldes
	double *matrix_3d_anf;
	// Laufvariablen
	int ebene;
	int zeile;
	int spalte;
	// Ein Laufzeiger zum linearen Durchlaufen des Feldes
	double *lauf_ptr;
	// Zeiger links unten auf Folie 421; dient zum Einstieg in die
	//   Zugriffsmatrizen zum Zwecke, die Indexschreibweise zu ermoeglichen
	double ***matrix_3d;

	printf("3D-Felder und Zugriffsmatrizen:\n");

	printf("Speicherplatz fuer das 3D-Feld belegen...\n");
	matrix_3d_anf = (double *)
		malloc(ebenen_n * zeilen_n * spalten_n * sizeof(*matrix_3d_anf));
	assert(matrix_3d_anf != NULL);

	printf("Das Feld initialisieren...\n");
	feld3d_init(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);

	/* Wird durch feld3d_init() anbgebilet
	lauf_ptr = matrix_3d_anf;
	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			for (spalte = 0; spalte < spalten_n; spalte++)
			{
				// Trick: Den 3D-Index als Inhalt des Feldelementes speichern
				*lauf_ptr++ = ebene * 100 + zeile * 10 + spalte;
			} // spalte
		}	  // zeile
	}		  // ebene

	*/

	printf("Das Feld ausgeben (mit linearem Index):\n");
	feld_ausgeben(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);

	printf("Zugriffsfelder laut Folie 421 erstellen, um Feldzugriffe mittels\n"
		   "  der (gut lesbaren!) Indexschreibweise zu ermoeglichen ...\n");
	if (0)
	{
		matrix_3d = zugriffsfelder_erstellen(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);
	}
	else
	{
		matrix_3d = felder_erstellen_wie_java(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);
	}
	printf("Das Feld mittels der Indexschreibweise ausgeben:\n");
	feld_ausgeben_mit_indices(matrix_3d, ebenen_n, zeilen_n, spalten_n);

	printf("Das 3D-Feld freigeben\n");
	if (0)
	{
		free(matrix_3d_anf);
		// Achtung: Der Zeiger wird von free() NICHT auf NULL gesetzt,
		//   weshalb man noch immer zugreifen kann, aber wie diese Daten u.U.
		//   schon verfaelscht sind, das ist rein spekulativ!!!
		//   (Testen Sie das mit verschiedenen Einstellungen, z.B. debug und release
		//    und anderen Compiler!)
		printf("matrix_3d_anf = %p\n", matrix_3d_anf);
	}
	else
	{
		matrix_3d_anf = realloc(matrix_3d_anf, 0);
		/*
		// // // Aufgabe 4.3 // // //

		Mit die Funktion realloc() kann der Zeigerwert neu bestimmt werden.
		Wird er auf 0 gesetzt und der Pointer exisiert, so wird der Speicher auf NULL
		gesetzt und freigegeben, damit dieser anders genutzt werden kann.
		Durch das Zurücksetzen auf NULL wird sichergestellt, dass keine Artefakte mehr
		im Speicher liegen, die weitere Berechnungen beinflussen können.
		*/
		printf("matrix_3d_anf = %p\n", matrix_3d_anf);
	}
	if (0)
		feld_ausgeben(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);
	// Zur Sicherheit also immer NULL einspeichern, damit es - falls man
	//  versehentlich doch noch einmal zugreifen sollte - garantiert einen
	//  sauberen und damit schnell auffindbaren Absturz gibt:
	matrix_3d_anf = NULL;
	printf("matrix_3d_anf = %p\n", matrix_3d_anf);
	if (0)
		feld_ausgeben(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);

	printf("Ende des Programms!\n");

	return EXIT_SUCCESS;
} // main

/**
 * Diese Funktion gibt ein 3D-Feld aus.
 */
void feld_ausgeben(const double *feld_anf_ptr,
				   int ebenen_n,
				   int zeilen_n,
				   int spalten_n)
{
	// Laufvariablen
	int ebene;
	int zeile;
	int spalte;
	int linearer_index;

	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			for (spalte = 0; spalte < spalten_n; spalte++)
			{
				// Trick: Den 3D-Index als Inhalt des Feldelementes speichern
				linearer_index = ebene * zeilen_n * spalten_n +
								 zeile * spalten_n + spalte;
				if (1)
					printf("%05.1lf   ", *(feld_anf_ptr + linearer_index));
				else
					printf("%05.1lf   ", feld_anf_ptr[linearer_index]);
			} // spalte
			printf("\n");
		} // zeile
		printf("\n");
	} // ebene
} // feld_ausgeben

/**
 * Diese Funktion erstellt die erforderlichen Zugriffsfelder,
 * um 3D-Zugriffe mit der Indexschreibweise ausfuehren zu koennen.
 *
 */
double ***zugriffsfelder_erstellen(const double *feld_anf_ptr,
								   int ebenen_n,
								   int zeilen_n,
								   int spalten_n)
{

	// Rueckgabewert
	double ***matrix_3d;
	int ebene, zeile;
	double *zeilen_anfangs_ptr = (double *)feld_anf_ptr;

	// Das Feld mit den doppelt indirekten Zeigern einrichten
	if (0)
		matrix_3d = (double ***)calloc(ebenen_n, sizeof(double **));
	else
		matrix_3d = (double ***)calloc(ebenen_n, sizeof(*matrix_3d));
	assert(matrix_3d != NULL);

	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		matrix_3d[ebene] = (double **)calloc(zeilen_n, sizeof(double *));
		assert(matrix_3d[ebene] != NULL);
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			matrix_3d[ebene][zeile] = zeilen_anfangs_ptr;
			if (1)
				printf("zeilen_anfangs_ptr = %p\n", zeilen_anfangs_ptr);
			zeilen_anfangs_ptr += spalten_n;
		}
	}

	return matrix_3d;
} // zugriffsfelder_erstellen

/**
 * Diese Funktion gibt ein 3D-Feld aus, wobei
 * der Einstieg mittels des Zeigers auf die Zugriffsfelder
 * geschieht und daher die Schreibweise mit eckigen Klammern
 * stattfindet.
 */
void feld_ausgeben_mit_indices(const double ***matrix_3d,
							   int ebenen_n,
							   int zeilen_n,
							   int spalten_n)
{
	// Laufvariablen
	int ebene;
	int zeile;
	int spalte;
	// Hier KEIN linearer Index noetig!! :-)

	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			for (spalte = 0; spalte < spalten_n; spalte++)
			{
				printf("%05.1lf   ", matrix_3d[ebene][zeile][spalte]);
			} // spalte
			printf("\n");
		} // zeile
		printf("\n");
	} // ebene

} // feld_ausgeben_mit_indices

void feld3d_init(double *matrix_3d_anf,
				 int ebenen_n,
				 int zeilen_n,
				 int spalten_n)
{
	// Laufvariablen
	int ebene;
	int zeile;
	int spalte;
	// Ein Laufzeiger zum linearen Durchlaufen des Feldes
	double *lauf_ptr;

	lauf_ptr = matrix_3d_anf;
	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			for (spalte = 0; spalte < spalten_n; spalte++)
			{
				// Trick: Den 3D-Index als Inhalt des Feldelementes speichern
				*lauf_ptr++ = ebene * 100 + zeile * 10 + spalte;
			} // spalte
		}	  // zeile
	}		  // ebene
} // feld3d_init()

// * AUFGABE 4.3
double ***felder_erstellen_wie_java(const double *feld_anf_ptr,
									int ebenen_n,
									int zeilen_n,
									int spalten_n)
{
	// Rueckgabewert
	double ***matrix_3d;
	int ebene, zeile, spalte;
	double *zeilen_anfangs_ptr = (double *)feld_anf_ptr;
	double *lauf_ptr;

	lauf_ptr = zeilen_anfangs_ptr;

	// Das Feld mit den doppelt indirekten Zeigern einrichten
	if (0)
		matrix_3d = (double ***)calloc(ebenen_n * spalten_n, sizeof(double **));
	else
		matrix_3d = (double ***)calloc(ebenen_n * spalten_n, sizeof(*matrix_3d));
	assert(matrix_3d != NULL);

	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		matrix_3d[ebene] = (double **)calloc(zeilen_n, sizeof(double *));
		assert(matrix_3d[ebene] != NULL);

		if (1)
		{
			printf("+ebenen_anfangs_ptr = %p\n", zeilen_anfangs_ptr);
		}
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			matrix_3d[ebene][zeile] = zeilen_anfangs_ptr;
			assert(matrix_3d[ebene][zeile] != NULL);

			if (1)
			{
				printf("+-+zeilen_anfangs_ptr = %p\n", zeilen_anfangs_ptr);
			}
			for (spalte = 0; spalte < spalten_n; spalte++)
			{

				matrix_3d[ebene][zeile][spalte];
				// ? Warum kommt hier ein Fehler auf?
				// assert(matrix_3d[ebene][zeile][spalte] != NULL);
				*lauf_ptr++ = ebene * 100 + zeile * 10 + spalte;

				if (1)
				{
					printf("| +-spalten_anfangs_ptr = %p\n", zeilen_anfangs_ptr);
				}
			}

			zeilen_anfangs_ptr += spalte;
		}
	}

	// Das Feld initialisieren

	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			for (spalte = 0; spalte < spalten_n; spalte++)
			{
				// Trick: Den 3D-Index als Inhalt des Feldelementes speichern
				*lauf_ptr++ = ebene * 100 + zeile * 10 + spalte;
			} // spalte
		}	  // zeile
	}		  // ebene

	return matrix_3d;
} //  felder_erstellen_wie_java

void zugriffsfelder_erstellen_by_ref(const double *feld_anf_ptr,
									 int ebenen_n,
									 int zeilen_n,
									 int spalten_n)
{

} // zugriffsfelder_erstellen_by_ref