#include <stdio.h>
#include <stdlib.h>
#include "input2.h"

int main() {
    int n = lese_int();
    int laenge = n-1;

    // Hier implementieren

    // Mit print_prim Primzahlen ausgeben
    //print_prim(array,

    // Erstelle Array für int mit n Elementen
    int* prim_array = malloc(n* sizeof(int));

    // initialisiere Array mit 1 überall
    for (int i=0; i<n; i++) {
      prim_array[i] = 1;
    }
    
    // filtern
    for (int i=0; i<n; i++) {
      if (i == 1) {  // nur rausfiltern, wenn durch nichts Voriges teilbar
	for (int j=i+1; j<n; j++) { // gehe mit diesem Index über alle nachfolgenden Zahlen
	  if ((j+2) % (i+2) == 0) {  //falls Nachfolgende teilbar, setze ihren Wert gleich 0
	    prim_array[j] = 0;
	  }
	}
      }
    }
   
    
    
    // jetzt sollten wir unser Primzahlenarray habe (Wert 1 = Primzahl)

    print_prim(prim_array, laenge);

      free(prim_array);

    return 0;
}
