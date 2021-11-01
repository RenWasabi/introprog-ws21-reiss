#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input3.h"

/* Die Konstanten:
 *  int MAX_LAENGE_STR - die maximale String Länge
 *  int MAX_LAENGE_ARR - die maximale Array Länge
 *  sind input3.c auf jeweils 255 und 100 definiert
 */

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Aufruf: %s <anzahl> <bundesland>\n", argv[0]);
        printf("Beispiel: %s 100 Bayern\n", argv[0]);
        printf("Klein-/Großschreibung beachten!\n");
        exit(1);
    }
    int anzahl = atoi(argv[1]);
    char *bundesland = argv[2];  /* char pointer zeigt auf erstes Element (Zeichen) des Bundes-
				  * land strings */
     printf("Test: %p\n", bundesland); 
    printf("Test: %c\n", *bundesland); /* wenn ich hier %s verwende, kriege ich ein warning, 
                                   	* dass das argument den typen char hat, beim Ausführen
                                        * gibt es einen Segmentation fault, hier ist der erste
					* Buchstabe des Bundeslands.  */
    printf("%s\n", argv[2]);  // argv[2] enthält den Bundesland-String selbst
    
    // Statisch allokierter Speicher
    char staedte[MAX_LAENGE_ARR][MAX_LAENGE_STR];
    char laender[MAX_LAENGE_ARR][MAX_LAENGE_STR];
    int bewohner[MAX_LAENGE_ARR];


       /* ich glaube, read_file schreibt zum einen die Daten aus der .csv in ein Array
     * und zählt zum anderen während dieses Prozesses die Anzahl der Einträge (also
     * Städte) und gibt diese als int zurück. In diesem Fall würde die Variable len 
     * die Anzahl der Einträge in der .csv Datei und somit die Länge der drei Arrays
     * beschreiben. (scheint zu stimmen)*/
    int len = read_file("staedte.csv", staedte, laender, bewohner);
    

   
    // Hier implementieren

    /* Folgende Schleife filtert, ob welche Städte mit den dazugehörigen Informationen
     * in die .txt-Datei geschrieben werden sollen. Sie macht zwei Dinge:
     *
     * 1. sie zählt die Anzahl an Städten, die durchkommen, sodass diese Größe genutzt
     * werden kann, um den Speicherplatz für das Array mit den verweisen auf die ganzen
     * Sätze zu reservieren (durchgekommene Städte = benötigte Zeilen/Sätze = Adressen im
     * Array, dass an write_file gegeben wird
     *
     * 2. sie "merkt" sich den Index der Städte, die durchkommen, indem sie die Einwohnerzahl
     * der Städte, die (da falsches Bundesland oder zu wenig Einwohner) nicht durchkommen, auf
     * -1 setzt. Dadurch vermeiden wir, ein zusätzliches Array zum "merken" zu brauchen und 
     * sparen damit Speicher. */

    int staedte_in_liste = len; // zählt die Städte, auf die die Bedingungen zutreffen
    
    for (int i = 0; i < len; i++) { /* gehe jeden Index der Arrays, das entspricht jedem
    		      		 * .csv-Eintrag, durch */
      if (strncmp(argv[2], laender[i], 100) != 0) { /* Prüft, ob dass Bundesland des Eintrags,
    							 * der dran ist, NICHT mit dem eingegebenen
    							 * Bundesland übereinstimmt, 100 nur
    							 * zur Sicherheit als Vergleichsgrenze*/
	bewohner[i] = -1;  // falls falsches Bundesland
      }

      if (bewohner[i] < anzahl) { /* prüft, ob Einwohner NICHT ausreichen
				   * tritt entweder ein, wenn falsches Bundesland, oder wenn wirklich
				   * zu wenig Einwohner */
	bewohner[i] = -1; // falls zu wenig Bewohner
	staedte_in_liste = staedte_in_liste -1; // ziehe die rausgefilterten vom Zähler ab
	}
    }

    printf("Insgesamt haben %d Städte in %s mindestens %d Einwohner.\n\n", staedte_in_liste, argv[2], anzahl);
    
    for (int i = 0; i < len; i++) {
      if (bewohner[i] >= anzahl) {
	printf("%s in %s hat %d Einwohner.\n", staedte[i], laender[i], bewohner[i]);
      }
    }
    

    /* // Mithilfe von write_file(...) soll das Ergebnis in die "resultat.txt" */
    // geschrieben werden. 

    // Dynamisch allozierter Speicher muss hier freigegeben werden.
}
