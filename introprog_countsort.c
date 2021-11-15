#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;
int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[MAX_LAENGE]) {

  /* count the number of occurences
   * count_array index := value, count_array value := number of occurences */
    
  for (int i = 0; i < len; i++) {
    // increase count by 1
    count_array[ input_array[i] ] = count_array[ input_array[i]] + 1;
  }
}

void count_sort_write_output_array(int output_array[], int len, int count_array[]) {

  // initialize a counter to track the index to which a value has to be copied to
  int output_array_index = 0;

  /* copy each index of the counter array into the output array, 
   * number of copies = value of the counter array at that index */

  // i := index of counter array (value)
  for (int i = 0; i < MAX_VALUE; i++){

    // copy the index into the output array according to the counter value
    // j := times of copying
    for (int j = 0; j < count_array[i]; j++){
      output_array[output_array_index] = i;
      
      // increase the counter for index to be copied to
      output_array_index = output_array_index +1;
    }
  }
}



int main(int argc, char *argv[]) {

    if (argc < 2){
      // argv[0] ist der Name des Programms selbst
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1); 
    }

    char *filename = argv[1];
    
    // keine dynamische Allozierung mit Malloc nötig, da Array-Länge von Beginn an feststeht
    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

  
    
    // initialize array for counting the number of occurences of a value with 0
    // int *count_array = calloc(MAX_VALUE, sizeof(int));
    // +1 to include MAX_VALUR itself,necesary because 0 is included
    int count_array[MAX_VALUE+1];
    for (int i = 0; i <= MAX_VALUE; i++){

      count_array[i] = 0;
    }

    // take input array, count its values using the count array
    count_sort_calculate_counts( input_array, len, count_array);

    // initialize the output array
    int output_array[MAX_LAENGE];

    // write values into the output array
    count_sort_write_output_array(output_array, len, count_array);

		      

    printf("Sortiertes Array:");
  
    print_array(output_array, len);

    
      
    return 0;
}
