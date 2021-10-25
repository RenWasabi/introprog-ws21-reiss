#include <stdio.h>
#include <stdlib.h>
#include "input.h" // Hier binden wir die Bibliothek ein

// Schreibe hier die Funktion "int fibonacci"
int fibonacci(zahl) {  // zahl erhält fib durch lese_int
  if (zahl==1) {       // Anker 1: f(1)=1 (tritt nur für n=1 ein)
    //    printf("fib(%d)= 1\n",zahl);
    return 1;
  }
  else if (zahl==2) {  // Anker 2: f(2)=1
    // printf("fib(%d)= 1\n",zahl);    
    return 1; 
  }
  int result = fibonacci(zahl-1)+fibonacci(zahl-2); // falls kein Anker, rufe Rekursion
  //  printf("fib(%d)= %d\n", zahl, result);
  return result;
}

int main(){
    int n = lese_int(); // Hier rufen wir die Funktion lese_int auf.
    int f = fibonacci(n);
    printf("Fib(%d) = %d\n" , n, f); 

    return 0; //Beende das Programm ohne Fehlermeldung
}
