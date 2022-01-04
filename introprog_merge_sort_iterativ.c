#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elemements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des Letzten Elements (Ende) des (Teil-)Array
 */
// aus der rekursiven Umsetzung der vorherigen Aufgabe übernommen
void merge(int* array, int first, int middle, int last)
{
  /* A = array, p = first, q = middle, r = last */

  int len = last-first+1;
  // Hilfsarray der Laenge r-p+1 zum Mergen
  int *helper_array =malloc((len)* sizeof(int));

  int left_index = first;
  int right_index = middle+1;
  int merge_index = 0;

  while ((left_index <= middle) && (right_index <= last)){
    if (array[left_index] <= array[right_index]){
      helper_array[merge_index] = array[left_index];
      left_index = left_index+1;
      merge_index = merge_index+1;
    }
    else {
      helper_array[merge_index] = array[right_index];
      right_index = right_index+1;
      merge_index = merge_index+1;
    }  
  }

  while (left_index <= middle){
    helper_array[merge_index] = array[left_index];
    left_index = left_index+1;
    merge_index = merge_index+1;
  }

  while (right_index <= last){
    helper_array[merge_index] = array[right_index];
    right_index = right_index+1;
    merge_index = merge_index+1;
  }

  int i = 0;
 for (int j=first; j<=last; j++){
    array[j] = helper_array[i];
    i++;
  }  
  
  free(helper_array);
  return;
}

/*
 * Diese Funktion implementiert den iterativen Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array:  Pointer auf das Array
 * first:  Index des ersten Elements
 * last :  Index des letzten Elements
 */
void merge_sort(int* array, int first, int last)
{
  /* Initialisierung mit 1 statt 0, da es um Schrittweite (sich
   * vergrößernden Abstand zwischen Indizes) und nicht Indizes selbst
   * handelt. */
  int step = 1;
  // int len = last-first+1;
  // last oder len?
  while (step <= last){
    int left = 0;
    while (left <= (last-step)){
	int middle = left+step-1;
	// middle = min(middle,n)
	if (last < middle){
	  middle = last;
	}
	int right = left+2*step-1;
	if (last < right){
	  right = last;
	}
	merge(array, left, middle, right);
	left = left+2*step;
      }
    step = step*2;
  }
  return;
}


  

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_iterativ <maximale anzahl> \
 * 	   <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    // Hier array initialisieren
    int *array = calloc(atoi(argv[1]), sizeof(int));
    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    // HIER Aufruf von "merge_sort()"
    int first = 0;
    merge_sort(array, first, len-1);


    printf("Sortiert:\n");
    print_array(array, len);

    free(array);

    return 0;
}
