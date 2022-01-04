#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
 */
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
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last)
{
  // A = array (Pointer!), p = first, r = last
  if (first < last){
    /* Division von Integern gibt immer entweder genaues oder abgeschnittenes
     * (= abgerundetes) Ergebnis zurück */    
    int middle = (first+last)/2;
    merge_sort(array, first, middle);
    merge_sort(array, middle+1, last);
    printf("Merge Array[%d]-[%d] mit Array[%d]-[%d]\n", first, middle, middle+1, last);
    merge(array, first, middle, last);
    print_array(array, last+1);   
 
    return;
  }
}
  
/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    // Hier array initialisieren
    // initialize integer array of length specified by user
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
