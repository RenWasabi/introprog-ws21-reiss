#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input3.h"

/* Die Konstanten:
 *  int MAX_LAENGE_STR - die maximale String Länge
 *  int MAX_LAENGE_ARR - die maximale Array Länge
 *  sind input3.c auf jeweils 255 und 100 definiert
 */

/* Um den Speicher für die Zeilen dynamisch festzulegen, müssen wir damit
 * umgehen können, dass unterschiedlich große Einwohnerzahlen unterschiedliche
 * viele Zeichen zur Darstellung als String benötigen. Laut VL soll man besser 
 * nicht versuchen, Datentypen */
int einwohner_string(int bewohnerzahl) {
  if (bewohnerzahl < 10) {
    return 1;
  }
   if (bewohnerzahl < 100) {
    return 2;
  }
    if (bewohnerzahl < 1000) {
    return 3;
  }
     if (bewohnerzahl < 10000) {
    return 4;
  }
      if (bewohnerzahl < 100000) {
    return 5;
  }
      if (bewohnerzahl < 1000000) {
    return 6;
  }
      if (bewohnerzahl < 10000000) {
     return 7;
  }
      return 8;
}
 
    

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Aufruf: %s <anzahl> <bundesland>\n", argv[0]);
        printf("Beispiel: %s 100 Bayern\n", argv[0]);
        printf("Klein-/Großschreibung beachten!\n");
        exit(1);
    }
    int anzahl = atoi(argv[1]); // Anzahl als Int (atoi konvertiert von str)
    char *bundesland = argv[2]; // Bundesland als String

    //   Statisch allokierter Speicher
    char staedte[MAX_LAENGE_ARR][MAX_LAENGE_STR];
    char laender[MAX_LAENGE_ARR][MAX_LAENGE_STR];
    int bewohner[MAX_LAENGE_ARR];

    /* ich glaube, read_file schreibt zum einen die Daten aus der .csv in ein Array
     * und zählt zum anderen während dieses Prozesses die Anzahl der Einträge (also
     * Städte) und gibt diese als int zurück. In diesem Fall würde die Variable len 
     * die Anzahl der Einträge in der .csv Datei und somit die Länge der drei Arrays
     * beschreiben. (scheint zu stimmen, siehe test unten)*/
    int len = read_file("staedte.csv", staedte, laender, bewohner);

    //    printf("%s\n", staedte);

    /* Tests, damit ich die Vorgaben verstehe */
    /* printf("Eingegebene Anzahl: %d\n", anzahl); */
    /* printf("Eingegebenes Bundesland: %s\n", bundesland); */

    /* printf("Erstes Land: %s\n", laender[0]); // Das gibt "Berlin aus" */
    /* printf("Erste Stadt: %s\n", staedte[0]); // auch Berlin */
    /* printf("Erste Einwohnerzahl: %d\n", bewohner[0]); // Das passt alles als erster Eintrag */

    /* printf("Die Länge der Liste (und somit Arrays) ist: %d\n", len); */
    /* /\* gibt 80 aus, dies stimmt mit der tatsächlichen Anzahl der Einträge der .csv überein. *\/ */

    /* // so kann man durch die Werte der Arrays iterieren */
    /* // druckt alle Städte */
    /* for (int i=0; i < len; i++) { */
    /*   printf("%s\n", staedte[i]); */
    /* } */

    /* // finde heraus, ob die Städte mehr als anzahl Einwohner haben */
    /* for (int i=0; i < len; i++) { */
    /*   if (bewohner[i] >= anzahl) { */
    /* 	printf("%s hat %d Bewohner.\n", staedte[i], bewohner[i]); */
    /*   } */

    /* } */

    /* Der Speicherbedarf des Arrays resultat_array ist fest, seine Elemente sind alle pointer
     * und haben somit eine einheitliche Größe. 
     * Wie kann ich nun,,,, kann ich größen reservieren, während ich schon imr resultat array bin?
     *  */
  
    // zunächst statische Initialiserung des resultat-Arrays (enthält pointer)
    char* resultat_array[len]; // zunächst begrenzt durch Anzahl der Einträge der .csv Datei

    //Initialisierung des Arrays mit 0:
    for (int i=0; i < len; i++) {
      if (bewohner[i] >= anzahl) { // falls Stadt aufgenommen

        // dynamische Reservierung des Speichers für Zeilen
	
 
	int zeilenlaenge = 27 + strlen(staedte[i]) + einwohner_string(bewohner[i]);// 27=26 Zeichen+/0
       // reserviere für den i-ten pointer Speicher
       resultat_array[i] = malloc(zeilenlaenge * sizeof(char));


      }
      }



  						       

    

    /* int zeile = 0; /\* zählt, wie viele Zeilen bereits mit einem Eintrag belegt sind *\/ */
    /* for (i=0; i < len; i++) { // für jeden Eintrag der .csv-Datei */
    /*   if (bewohner[i] >= anzahl){  // wenn die Einwohnerzahl ausreicht */
    /* 	resultat_array[zeile] =  // hier muss der pointer zu der Zeile hin */

    /*   } */

    /* } */

    

    
    // Hier implementieren

    // Mithilfe von write_file(...) soll das Ergebnis in die "resultat.txt"
    // geschrieben werden. 

    // Dynamisch allozierter Speicher muss hier freigegeben werden.
}
