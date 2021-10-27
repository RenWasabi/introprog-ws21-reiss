#include <stdio.h>
#include <stdlib.h>

/* Gibt die Zahlen des Arrays jeweils durch ein 
 * Komma getrennt mit printf auf der Kommandozeile
 * aus. Man soll eine Schleife verwenden. Nur
 * auf Elemente zugreifen, die tatsächlich im array 
 * vorhanden sind. Man darf die Variable int len 
 * wohl benutzen, nur ihren Namen nicht. */
void print_array(int array[], int len) {
  printf("Array: ");
  for (int i=0; i < len; i++) {  // von 0 bis letzter Index = len-1
    if (i == len - 1) {  // Zeilenumbruch statt Komma hinter letzem Element
      printf(" %d\n", array[i]);
    }
    else {
    printf(" %d,", array[i]); // im Bsp sind Leerzeichen zwischen den Zahlen
    }
  }
}

/* Finde kleinstes Element des Arrays. 
 * Rückgabetyp ist ein int.
 * Parameter wie bei print_array */
int min(int array[], int len) {
  int mini = array[0];  /* Nehme zuerst das erste Element des Arrays
			 * als kleinstes an. Weise mini nur einen anderen
			 * Wert zu, sollte auf einem folgenden Index ein
			 * kleinerer Wert sein. */
  for (int i=0; i<len; i++) {
    if (array[i] < mini) {
      mini = array[i];
    }
  }
  return mini; 
}

// wie Minimum, nur umgedreht
int max(int array[], int len) {
  int maxi = array[0]; 
  for (int i=0; i<len; i++) {
    if (array[i] > maxi) {
      maxi = array[i];
    }
  }
  return maxi; 
}

/* sum hat keinen Rückgabewert, sie ist also void und speichert ihre
 * Operation direkt an einer Adresse (drittes Parameter: pointer), 
 * nutzt also call by reference. */
void sum(int array[], int len, int *summe) {
  *summe = 0;  // belegen des Wertes des pointers
  for (int i=0; i<len; i++) {
    *summe = *summe + array[i];
  }
}
       

int main() {
     int array[] = {9, 4, 7, 8, 10, 5, 1, 6, 3, 2};
     int len = 10;
     print_array(array, len);
     // Gebe hier nacheinander das Minimum, Maximum und die Summe */
     // aus. Trenne die Werte durch einen einzelnen Zeilenumbruch. */
     printf("Minimum: %d\n", min(array, len)); // printf nicht in Funktion (Vorgabe)
     printf("Maximum: %d\n", max(array, len));

     int summe_main = 0; 
     /*     printf("Summe: %d\n", sum(array, len, &summe_main)); funktioniert nicht,
      * da die Funktion selbst ja void ist und somit nichts zurück gibt. */
     sum(array, len, &summe_main);  // sum erwartet als drittes Parameter einen pointer
     printf("Summe: %d\n", summe_main);
}
