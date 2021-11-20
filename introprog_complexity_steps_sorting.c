#include <stdio.h>
#include <stdlib.h>
#include "introprog_complexity_steps_input.h"

const int MAX_VALUE = 5000000;

void count_sort_calculate_counts(int input_array[], int len, int count_array[], unsigned int* befehle) {
    // Muss implementiert werden
  (*befehle)++; // Initialisierung Laufvariable i
  for (int i = 0; i < len; i++){
    (*befehle)++; // Vergleich true
    count_array[ input_array[i] ] = count_array[ input_array[i] ] +1;
    (*befehle)++; // Zuweisung count_array
    (*befehle)++; // Inkrementierung Laufvariable i
  }
  (*befehle)++; // Vergleich false
}

void count_sort_write_output_array(int output_array[], int len, int count_array[], unsigned int* befehle) {
    // Muss implementiert werden
  int output_array_index = 0;
  (*befehle)++; // Initialiserung output_array_index
  (*befehle)++; // Initialisierung äußere Laufvariable j
  for (int i = 0; j <= MAX_VALUE; i++){
    (*befehle)++;  // äußerer Vergleich true

    (*befehle)++; // Initialisierung innere Laufvariable j
    for (int j = 0; j < count_array[i]; j++){
      (*befehle)++; // innerer Vergleich true

      output_array[output_array_index] = i;
      (*befehle)++; // Zuweisung output_array
      output_array_index = output_array_index +1;
      (*befehle)++; // Zuweisung output_array_index
      (*befehle)++; // Inkrementierung innere Laufvariable i
    }
    (*befehle)++; // innerer Vergleich false
    
    (*befehle)++; // Inkrementierung äußere LAufvariable i
  }
  (*befehle)++; // äußerer Vergleich false
}

void count_sort(int array[], int len, unsigned int* befehle) {
    // Muss implementiert werden
}


void insertion_sort(int array[], int len, unsigned int* befehle) {
    // Muss implementiert werden
  (*befehle)++; // Initialisierung Laufvariable j der for-Schleife
  for (int j=1; j<len; j++{
      (*befehle)++; // Vergleich for-Schleife true
      int key = array[j];
      (*befehle)++; // Zuweisung key
      
      int i = j-1; // Zuweisung Anfangswert der Laufvariablen i der while-Schleife
      while (i>=0 && array[i] > key){
	(*befehle)++; // Vergleich while-Schleife true
	array[i+1] = array[i];
	(*befehle)++;  // Zuweisung Array[i+1] (Verschiebung Elemente nach rechts)
	i= i-1;
	(*befehle)++;  // Verringerung Laufvariable i der while-Schleife
      }
      (*befehle)++;  // Vergleich while-Schleife false
      array[i+1] = key; 
      (*befehle)++; // Zuweisung array[i+1] (füge Element an soriertem Platz ein)
      (*befehle)++; // Inkrementierung Laufvariable j der for-Schleife
  }
  (*befehle)++; // Vergleich for-Schleife false
}


int main(int argc, char *argv[]) {
    const int WERTE[] = {10000,20000,30000,40000,50000};
    const int LEN_WERTE = 5;
    const int LEN_ALGORITHMEN = 2;

    int rc = 0;
    unsigned int befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];

        // Reserviere Speicher für  Arrays der Länge n
        int* array_countsort = malloc(sizeof(int) * n);
        int* array_insertionsort = malloc(sizeof(int) * n);

        // Fülle array_countsort mit Zufallswerten ..
        fill_array_randomly(array_countsort, n, MAX_VALUE);
        // ... und kopiere die erzeugten Werte in das Array
        // array_insertionsort
        copy_array_elements(array_insertionsort, array_countsort, n);

        // Teste ob beide Arrays auch wirklich die gleichen Werte
        // enthalten
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Eingaben für beide Algorithmen müssen für die Vergleichbarkeit gleich sein!\n");
            return -1;
        }

        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            unsigned int anzahl_befehle = 0;

            start_timer();

            // Aufruf der entsprechenden Sortieralgorithmen
            if(i==0) {
                    count_sort(array_countsort, n, &anzahl_befehle);
            } else if(i==1) {
                    insertion_sort(array_insertionsort, n, &anzahl_befehle);
            }

            // Speichere die Laufzeit sowie die Anzahl benötigter
            // Befehle
            laufzeit_array[i][j] = end_timer();
            befehle_array[i][j] = anzahl_befehle;
        }

        // Teste, ob die Ausgabe beider Algorithmen gleich sind
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Arrays sind nicht gleich. Eines muss (falsch) sortiert worden sein!\n");
            rc = -1;
        }

        // Gib den Speicherplatz wieder frei
        free(array_countsort);
        free(array_insertionsort);
    }

    // Ausgabe der Anzahl ausgeführter Befehle sowie der gemessenen
    // Laufzeiten (in Millisekunden)
    printf("Parameter MAX_VALUE hat den Wert %d\n", MAX_VALUE);
    printf("\t %32s           %32s \n", "Countsort","Insertionsort");
    printf("%8s \t %16s %16s \t %16s %16s \n", "n","Befehle", "Laufzeit","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%8d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%16u %16.4f \t ",  befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return rc;
}
