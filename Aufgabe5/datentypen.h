// Bei jeder Header-Datei wird mit den folgenden Zeilen (pragma once ist die neuere Loesung,
//  ifndef ... die aeltere) dafuer gesorgt, dass die Header-Datei nur genau 1x bei jedem
//  Uebersetzungsvorgang ausgewertet wird, da sonst u.U. Konflikte entstehen koennen.
// #ifdef ... bzw. #ifndef bezeichnet man als "bedingtes Kompilieren", was bedeutet, dass
//  der Praeprozessor einen bestimmten Abschnitt des Quelltextes aus- oder einblendet.
// 
// Das bedingte Kompilieren laesst sich auch sehr gut dafuer verwenden, um beim 
//  Uebersetzen eines bestimmten Quelltextes verschiedene Code-Varianten fuer verschiedene
//  Zielsysteme und/oder Compiler vorzusehen. Hierfuer gibt es die Moeglichkeit, 
//  mit bestimmten Praeprozessor-Symbolen den Compiler, dessen Version, ggf. das 
//  Betriebssystem und dgl. abzufragen.
//  
// Entweder so ....
#pragma once
// ... oder so:
#ifndef DATENTYPEN_H
#define DATENTYPEN_H


/* Feldgroessen der statischen Felder.
*/
/* Laenge der statischen Textfelder. */
#define STR_LEN		100

/* Definitionen von eigenen Variablentypen */
enum typeninfo_typ{double_typ, int_typ, text_typ};
union mein_union_typ{double d; int i; char text[STR_LEN];};
struct flexibler_struct_typ
  { enum typeninfo_typ			aktuellerTyp;
    union mein_union_typ		daten;
    struct flexibler_struct_typ	*next_ptr;
    struct flexibler_struct_typ	*back_ptr;
  };
enum richtungs_typ {
	vorwaerts, rueckwaerts
};

#endif // DATENTYPEN_H



