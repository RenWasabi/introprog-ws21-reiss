#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;

void insertion_sort(int array[], int len) {
    /*
     * Hier Insertionsort implementieren!
     * Diese Funktion soll das Eingabearray nach dem
     * Insertionsort-Verfahren sortieren.
     * Hinweis: Verwende die "in place"-Variante! D.h. der
     * Sortiervorgang soll auf dem originalen Array stattfinden und
     * kein zweites verwendet werden.
     */
  /* Wenn einer Funktion ein Array als Eingangsparameter gegeben wird, 
   * greift man innerhalb der Funktion standardmäßig mit call by reference
   * auf das Originalarray zu. */

  // äußere for-Schleife: gehe von rechts nach links durch alle Elemente
  for (int j=1; j<len; j++){

    // Zwischenspeichern der des aktuellen Elementes in key
    int key = array[j];

    //Laufvariable für innere Schleife
    int i = j-1;

    // gehe von rechts nach links durch sortiere Elemente, verschiebe jene größer key nach rechts
    while (i>=0 && array[i] > key){
      // verschiebe Vergleichselement nach rechts
      array[i+1] = array[i];
      i = i-1; 
    }

    // füge key auf dem freigewordenen Platz ein
    // falls die while-Schleife nie läuft: i+1=j-1+1=j, also array[i+1]=array[j]
    array[i+1] = key;

  }
  
}

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LAENGE];
    int len = read_array_from_file(array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(array, len);

    /* Aufruf Insertionsort */
    insertion_sort(array, len);

    printf("Sortiertes Array:");
    print_array(array, len);

    return 0;
}
