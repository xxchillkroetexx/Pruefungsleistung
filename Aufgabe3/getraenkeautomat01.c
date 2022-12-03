/**
 * Getraenkeautomat simulieren.
 *
 * TINF22CS1, 25.10.2022
 */

// Standard-Header
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// eigener Header
#include "ausgaben.h"

// Funktionsprototypen (= Funktionsdeklarationen)
int auswahlGetraenkeSorte(void);
int eingabeMenge(void);
float ermittlePreis(int);
void bezahlen(float);

/**
 * Hauptprogramm.
 */
int main(int argc, char *argv[])
{
	// Lokale auto-Variablen
	// sort = Getraenkesorte
	// menge = Anzahl der Dosen
	int sorte, menge;
	// preis = Preis fuer 1 Dose eines best. Getraenkes
	// zuZahlen = Zu bezahlender Gesamtpreis
	float preis, zuZahlen;

	sorte = auswahlGetraenkeSorte();
	preis = ermittlePreis(sorte);
	menge = eingabeMenge();
	zuZahlen = preis * menge;
	bezahlen(zuZahlen);
	ausgabeGetraenke(sorte, menge);
	printf("\n\nVielen Dank, bitte entnehmen Sie Ihre Getraenke.\n");

	return EXIT_SUCCESS;
} // main

/**
 * Funktion, in der der Benutzer die gewuenschte Getraenke-
 * sorte auswaehlen kann.
 *  Formale Parameter:
 *    Keine! (Leere Klammern bedeuten im C eigentlich nur, dass
 *     ueber die Parameter nichts gesagt wird, waehrend im Java
 *     leere Klammern tatsaechlich bedeuten, dass es keine Parameter
 *     gibt. Wenn man das im C ausdruekcken moechte, muss man
 *     void in die Klammern schreiben.)
 *  Rueckgabewert:
 *     Die gewuenschte Getraenkesorte (1..3).
 */
int auswahlGetraenkeSorte(void)
{
	int sorte;
	printf("Waehlen Sie Ihr Getraenk aus:\n");
	printf("1) Wasser (0,50 Euro)\n");
	printf("2) Limonade (1,00 Euro)\n");
	printf("3) Bier (2,00 Euro)\n\n");
	printf("Geben Sie 1, 2 oder 3 ein: ");
	scanf("%d", &sorte);
	return sorte;
}

/**
 * Interaktive Auswahl der Anzahl von Getraenkedosen.
 * Formale Parameter:
 *   KEINE!
 * Rueckgabewert:
 *   Anzahl der Dosen.
 */
int eingabeMenge(void)
{
	int menge = 1;
	printf("\nGeben Sie die gewuenschte Menge ein: ");
	scanf("%d", &menge);
	return menge;
} // eingabeMenge

/**
 * Hier wird der Einzelpreis einer Dose eines bestimmten
 * Getraenkes ermittelt.
 * Formale Parameter:
 *   affe - Etwas merkwuerdiger Name fuer die Sorte
 *     des gewaehlten Getraenkes (1..3).

 */
float ermittlePreis(int affe)
{
	float preis = 0;
	FILE *file_ptr = stdout;
	file_ptr = fopen("testausgaben.txt", "w");
	if (affe < 1 || 3 < affe)
	{
		fprintf(file_ptr, "ermittlePreis(): affe = %d ist ein fehlerhafter Wert!\n",
				affe);
		exit(EXIT_FAILURE);
	}
	fclose(file_ptr);

	// affe muss ganzzahliger Ausdruck sein
	//  break kann auch fehlen; dann aber wird einfach der naechste Zweig
	//   ausgefuehrt.
	switch (affe)
	{
	case 1:
		preis = 0.5f;
		break;
	case 4: // Irgendein weiteres Getraenke der neuen Sorte 4, das ebenfalls 1 EUR kostet.
		printf("Hier koennten Sepzialitaeten von Getraenk 4 programmiert werden...\n");
	case 2:
		preis = 1.0f;
		break;
	case 3:
	{
		preis = 2.0f;
	}
	break;
		// Goldene Regel: IMMER (auch wenn Sie ihn aktuell nicht benoetigen
		//   sollten!) einen default-Zweig mit einem Programmabbruch und
		//   einer Fehlermeldung vorsehen, um bei spaeteren PRogrammaenderungen
		//   lieber einen sauberen Absturz zu bewirken als ein schrottiges Programm
		//   weiter vor sich hintaumeln zu lassen.
	default:
		fprintf(stderr, "ermittlePreis(): affe = %d ist ein fehlerhafter Wert!\n",
				affe);
		exit(EXIT_FAILURE);
	} // switch

	// Alternativ mit if-else
	if (affe == 1)
		preis = 0.5;
	else if (affe == 2)
		preis = 1.0;
	else
		preis = 2.0;

	// Anders formatiert, dann fuer nahezu beliebig viele
	//   Abfragen geeignet.
	if (affe == 1)
		preis = 0.5;
	else if (affe == 2)
		preis = 1.0;
	else if (affe == 3)
		preis = 2.0;

	// Viel einfach geht's mit einem Feld mit vorbelegtn
	//  Werten:
	{
		float preise_feld[] = {0.5f, 1.0f, 2.0f};
		float ein_feld2[10]; // Groesse: 4*10=40
		preise_feld[0];		 // Zugriff auf das 1. Feldelement (= 0.5f)
		preise_feld[1];		 // Zugriff auf das 2. Feldelement (= 1.0f)
		preise_feld[2];		 // Zugriff auf das 3. Feldelement (= 1.0f)
							 // Bei Index 2 wird also 2*sizeof(float)=2*4=8 als Offset
							 //  zu der Anfangsadr3esse des Feldes addiert; die Anfangsadresse
							 //  ergibt sich aus dem Namen des Feldes.
							 // Im Feld liegen ab der 1. Adresse alle Feldelemente aufsteigend
							 //  nahtlos hintereinander.
							 // C prueft weder beim Uebersetzen noch beim Ausfuehren des
							 //  Programmes, ob sich die Indices im zulaessigen Rahmen bewegen,
							 //  also zwischen inkl. 0 und inkl. 2 bei preise_feld bzw.
							 //  zwischen 0 und 9 (je inkl.) bei ein_feld2.
							 // Als C-Programmierer muss man immer die Groesse des Feldes
							 //  getrennt vorhalten, entweder als feste Zahl (schlecht zu
							 //  warten!), als Praeprozessor-Konstante (gut zu warten, aber
							 //  bei Aenderungen muss trotzdem das Programm neu uebersetzt
							 //  werden) oder als Variable (entfaltet seine Maechtigkeit
							 //  allerdings erst beim Verwenden des Heaps).
							 // const int anzahl3 = 10;
							 // float feld3[anzahl];// Das geht NICHT!!!
							 // In C kann man auch mit negativen Indices arbeiten, was
							 //  bedeutet, dass der berechnete Offset negativ ist und somit
							 //  auf Adressen unterhalb des Feldanfangs zugegriffen wird.
							 // Interessant kann dies im Zusammenhang mit Adressvariablen sein,
							 //  die nicht auf den Feldanfang zeigen, sondern z.B. in die
							 //  Mitte des Feldes; dann kann man mit positiven und negativen
							 //  Indices relativ zu dieser Adressvariablen auf das Feld
							 //  zugreifen.
							 // Wenn man nicht alle Elemente eines Feldes nutzen will, muss
							 //  man sich in einer weiteren Variablen die Zahl der tatsaechlich
							 //  genutzten Feldelemente vorhalten.
							 // Bei einem Feld spielt es von der Zugriffsgeschwindigkeit her
							 //  keine Rolle, an weilcher Stelle man zugreift; bei einer sog.
							 //  verketteten Liste muss man dagegen wie bei einer Schnitzeljagd
							 //  zuerst u.U. sehr viele Elemetne durchlaufen (zeitaufwendig!),
							 //  bevor man zu dem gewuenschten Element gelangt. Ausserdem ist
							 //  der Verwaltungaufwand bei einer verketteten Liste deutlich
							 //  hoeher.
							 // Felder koennen als globale Variablen (sei es nur in 1 Modul oder
							 //  moduluebergreifend), als lokale (auto) Variablen oder als
							 //  Bereiche auf dem Heap angelegt werden.
							 // Bei globalen und lokalen Feldern wird die Groesse beim
							 //  Uebersetzen fest vorgegeben und kann waehrend der Laufzeit
							 //  nicht geaendert werden.
	}

	return preis;
} // ermittlePreis

/**
 * Diese Funktion bildet den Bezahlvorgang ab.
 *
 * Formale Parameter:
 *  zuZahlen - der zu zahlende Gesamtpreis.
 */
void bezahlen(float zuZahlen)
{
	float einwurf;
	printf("\n--- Bezahlvorgang ---\n");
	// Die do-while-Schleife ist die einzige fussgesteuerte und
	//  damit annehmende Schleife in C.
	do
	{
		printf("\nEs fehlen noch %.2f Euro.", zuZahlen);
		printf("\nBitte werfen Sie ein Geldstueck ein: ");
		scanf("%f", &einwurf);

		// zuZahlen = zuZahlen - einwurf;
		zuZahlen -= einwurf;
	} while (zuZahlen > 0.0);
	return; // Optional
} // bezahlen
