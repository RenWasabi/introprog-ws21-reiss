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

    for (int i = 0; i < len; i++) { /* gehe jeden Index der Arrays, das entspricht jedem
    		      		 * .csv-Eintrag, durch */
      if (strncmp(argv[2], laender[i], 100) == 0) { /* Prüft, ob dass Bundesland des Eintrags,
    							 * der dran ist, mit dem eingegebenen
    							 * Bundesland übereinstimmt, 100 nur
    							 * zur Sicherheit als Vergleichsgrenze*/
    	printf("eingegeben %s; enthält Stadt: %s\n", argv[2], staedte[i]); // funktioniert

	

      }

    }

    /* // Mithilfe von write_file(...) soll das Ergebnis in die "resultat.txt" */
    // geschrieben werden. 

    // Dynamisch allozierter Speicher muss hier freigegeben werden.
}
