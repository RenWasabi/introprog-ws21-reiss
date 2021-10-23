/* Erstelle ein Rechteck, mit einem Inneren Rechteck mit den Maßen
   hoehe und breite, dass als Bs ausgegeben wird, und As als Rand. */
#include <stdio.h>

int main() {
    int breite = 6;
    int hoehe = 3;
    breite = breite+2;  // damit die Maße sich auf B beziehen und A zusätzlicher Rand ist
    hoehe = hoehe+2;

    if (breite < 0) {    // macht nichts, falls hoehe oder breite keine positiven Zahlen
      printf("\n");
    } else if (hoehe < 0) {
      printf("\n");
    } else {

    for (int j=0; j <= hoehe-1; j++) {  // geht zuerst jede Zeile, dann jede Spalte durch
      
      if (j==0) {  // wenn oberste Zeile:
	for (int i=0; i <= breite-1; i++) { // gibt A in jeder Spalte aus
	  printf("A ");
	}
	printf("\n"); // setze Umbruch hinter oberste Zeile       
      } // Ende if-Schleife Rand oben

      else if (j==hoehe-1) {  // wenn unterste Zeile:
	for (int i=0; i <= breite-1; i++) { // gibt A in jeder Spalte aus
	  printf("A ");
	}
	printf("\n"); // keine Leerzeile nach unterster Zeile ist eigentlich Aufgabenvorgabe
      } // Ende else-if-Schleife Rand unten

      else { // falls weder oberste noch unterste, somit mittlere Zeile
	for (int i=0; i<= breite-1; i++) { // für jede mittlere Zeile
	  if (i==0) { // am linken Rand: gibt A aus
	    printf("A "); 
	  }
	  else if (i==breite-1) { // am rechten Rand: gibt A aus
	    printf("A ");
	  }
	  else { // in den mittleren Spalten: gibt B aus
	    printf("B ");
	  }
	} // Ende for-Schleife Spalten
        printf("\n");  // setze Umbruch hinter jede mittlere Zeile	
      } // Ende else-Schleife Mitte
    } // Ende for-Schleife Zeilen

} // Ende else-Schleife, falls hoehe/breite nicht zulässig
}  // Eine main-Fkt
