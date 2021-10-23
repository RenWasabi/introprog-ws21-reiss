#include <stdio.h>

int main() {
    int breite = 6;
    int hoehe = 3;

    for (int j=0; j < hoehe; j++) {  // geht zuerst jede Zeile, dann jede Spalte durch
      
      if (j==0) {  // wenn oberste Zeile:
	for (int i=0; i < breite; i++) { // gibt A in jeder Spalte aus
	  printf("A ");
	}
	printf("\n"); // setze Umbruch hinter oberste Zeile       
      } // Ende if-Schleife Rand oben
      
    } // Ende for-Schleife Zeilen
}  // Eine main-Fkt
