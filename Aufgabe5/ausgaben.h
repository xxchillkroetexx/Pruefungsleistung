// Bedingtes Kompilieren, damit diese Datei nur 1x bei jedem
//   Uebersetzungsvorgang ausgewertet wird.
#ifndef AUSGABEN_H
#define AUSGABEN_H

// Header-Dateien einfuegen, die hier als Voraussetzung notwendig sind,
//  damit diese aktuelle Header-Datei in jedem Falle uebersetzt werden kann
#include "datentypen.h"

// Prototypen des C-Moduls ausgaben.c
//  ACHTUNG: Diese Protoypen duerfen als wirklich NUR HIER auftauchen!!!
int print_element_by_val(struct flexibler_struct_typ element);
int print_element(const struct flexibler_struct_typ *element_ptr);
int print_element_kurz(const struct flexibler_struct_typ *element_ptr);

#endif // AUSGABEN_H
