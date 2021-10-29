#include <stdio.h>
#include <stdlib.h> // u.a. für malloc
#include "input2.h"

int main() {
  int n = lese_int(); // Nutzer gibt eine Zahl ein
  int laenge = n-1;  // 2 bis einschließlich n, also ist die Länge n-1

    // Hier implementieren

    // Mit print_prim Primzahlen ausgeben
    //print_prim(array, laenge);

  /* 1.:  Speicher für das Array soll mit malloc reserviert werden,
   * hat den Typ int und n-1 Felder */
  int* prim_array = malloc(laenge * sizeof(int));
  
  /* 2.: Initialisierung jedes Elements des Arrays mit 1 (Primzahlwert) */
  for (int i=0; i < laenge; i++) {   // < laenge, da der letzte index immer Arraylänge -1 ist
    prim_array[i] = 1;
  }

  /* 3.: für jedes Element zwischen 2 und n: */
  for (int i=0; i < laenge; i++) {
    /* Wenn das Element am Index i einen Wert von 0 besitzt (Primzahl ist): */
    if (prim_array[i] == 1) {
      /* Setze alle Vielfachen dieser Zahl auf 0, setze also alle Vielfache x
       * der Indizes i+x*zahl=i+x*(i+2) auf 0 */
      
      /* für alle Vielfachen x! x soll aber nicht bis unendlich laufen. 
       * Zahlen, deren Vielfaches größer als n ist, bewirken keine Veränderung
       * am Array. Das Gleiche gilt für alle Vielfachen, die größer als n sind.
       * Hier muss man aufpassen, die Array-Grenzen nicht zu überschreiten, um
       * nicht auf unerlaubte Bereiche zuzugreifen. 
       *
       * Generell muss gelten: i+x*(i+2) <= n-2 = laenge-1
       * also: Index, auf den zugegriffen wird < letzter Index des Arrays */
      int x = 1;
      while ( i+x*(i+2) <= laenge-1) { /* erhöhe Vielfache, bis der Index eines Vielfachen
					* der letzte Index des Arrays ist oder bevor er das
					* Array überschreitet */
	prim_array[i+x*(i+2)] = 0;
	x = x + 1;
      }
    }
  }

  /* 4.: Man muss die Funktion print_prim benutzen. 
   * Diese Funktion gibt die zuvor berechneten Primzahlen im Array array
   *  der Länge laenge aus.  void print_prim(int *array, int laenge) */
  print_prim(prim_array, laenge);

  
  

  free(prim_array); // gibt den für das Array mit malloc angeforderten Speicher wieder frei  

    return 0;
}
