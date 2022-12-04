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
// ! Aufgabe 4.1
// Initialisieren eines 3d Feldes
void feld3d_init(double *matrix_3d_anf,
				 int ebenen_n,
				 int zeilen_n,
				 int spalten_n);
// ! Aufgabe 4.3
// Ein Feld wie in Java erstellen
double ***felder_erstellen_wie_java(const double *feld_anf_ptr,
									int ebenen_n,
									int zeilen_n,
									int spalten_n);
// ! Aufgabe 4.4
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

	/*
	! Aufgabe 4.1
	* Wird durch feld3d_init() anbgebilet
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

	if (1)
	{
		// Standard
		matrix_3d = zugriffsfelder_erstellen(matrix_3d_anf, ebenen_n, zeilen_n, spalten_n);
	}
	else
	{
		// ! Aufgabe 4.3
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
		! Aufgabe 4.2

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

/**
 * 3D-Matrix initialisieren
 * ! Aufgabe 4.2
 */
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

/**
 * ! Aufgabe 4.3
 */
double ***felder_erstellen_wie_java(const double *feld_anf_ptr,
									int ebenen_n,
									int zeilen_n,
									int spalten_n)
{
	// Rueckgabewert

	double ***matrix_3d;
	int ebene, zeile, spalte;

	// Feldindex im Feld Speichern
	for (ebene = 0; ebene < ebenen_n; ebene++)
	{
		for (zeile = 0; zeile < zeilen_n; zeile++)
		{
			for (spalte = 0; spalte < spalten_n; spalte++)
			{
				matrix_3d[ebene][zeile][spalte] = ebene * 100 + zeile * 10 + spalte;
			}
		}
	}

	return matrix_3d;
} //  felder_erstellen_wie_java

/**
 * ! Aufgabe 4.4
 * TODO
 */
void zugriffsfelder_erstellen_by_ref(const double *feld_anf_ptr,
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
} // zugriffsfelder_erstellen_by_ref

/**
 * ! Aufgabe 4.5
 * Wenn der Speicher am Ende des Programms nicht wieder freigegeben wird, kann der Speicher immer weiter wachsen.
 * Auch kann es sein, dass der Heap-Speicher irgendwann voll ist, oder so stark fragmentiert ist, dass rein rechnerisch
 *  noch ein neues Element auf dem Speicher angelegt werden könnte, aber die freien Stellen nicht zusammenhängen,
 */

/**
 * ! Aufgabe 4.6
 * Als Speicherleiche bezeichnet man Daten, die zwar noch auf dem Speicher liegen, aber nicht mehr benötigt werden.
 */

/**
 * ! Aufgabe 4.7
 * Speicherfragmentierung entsteht, wenn man Daten im Speicher löscht, die zwischen anderen Datenblöcken liegen. Dadurch entsteht
 *  zwischen zwei Datenblöcken eine Lücke an freiem Speicher. Je nachdem, wie viele solcher Lücken im Speicher vorhanden
 *  sind, spricht man von mehr oder weniger starker Fragmentierung. Der Speicher muss dann defragmentiert werden. Das
 *  bedeutet, dass der belegte Speicher zusammengerückt wird und der freie Speicher am Ende als ein großer Bereich zur
 *  Verfügung steht.
 */

/**
 * ! Aufgabe 4.8
 * Ist der Heap-Speicher stark fragmentiert, kann die Situation auftreten, dass die Summe des freien Speichers ausreicht,
 *  einen neuen Datenblock zu speichern, aber die Lücken zwischen dem belegten Speicher als einzelnes nicht groß genug sind.
 *  Weil Speicher nur am Stück reserviert werden kann, ist die Speicherreservierung nicht möglich.
 */

/**
 * ! Aufgabe 4.9
 * Bei der Festplatte schlägt sich eine starke Fragmentierung hauptsächlich in einer verschlechterten Geschwindigkeit nieder,
 *  weil die Daten von verschiedenen Stellen der Platte gelesen werden müssen. Schreibt die Festplatte hinter eine Datei andere
 *  Datenblöcke, so werden beim Vergrößern der Datei die neuen Daten einfach hinter die jetzt neuen Datenblöcke geschrieben.
 * Beim Heap-Speicher hingegen kann bei einer zu starken Fragmentierung kein weiterer Datenblock gespeichert werden und die
 *  Speicherbelegung schlägt fehl. Das Programm stürzt ab.
 */

/**
 * ! Aufgabe 4.10
 * TODO
*/

/**
 * ! Aufgabe 4.11
 * TODO
*/