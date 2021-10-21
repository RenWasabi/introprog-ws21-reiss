#include <stdio.h>
#include <stdlib.h>

int main() {
    int nummer =103; // Probiere verschiedene Werte aus: 101, 103, ...
    printf("Ist %d eine Primzahl?\n", nummer);

    int teiler = 2; // deklariere Teiler jede Zahl ist durch 1 teilbar, Start daher bei 2
    int rest = 1; //deklariere Rest, initialisiere mit Zahl !=0 als Startwert, damit die while-Schleife überhaupt beginnt

    while ( rest != 0 ) {   // Schleife läuft, bis man auf einen Teiler ohne Rest (spätestens die Zahl selbst) stößt
      
      if ( nummer % teiler != 0) {   // solange beim Teilen Rest bleibt, läuft die Schleife weiter
	rest = nummer % teiler;
	teiler = teiler + 1;
	
      } else {                          // lässt sich ohne Test teilen, wird getestet, ob der Teiler die Zahl selbst oder eine andere Zahl (2<= Teiler < nummer) war
	rest = nummer % teiler;         // Der Rest sollte hier 0 werden und damit verhindern, dass die Schleife weiterläuft
	
	if (teiler == nummer) {        // ist der Teiler die Zahl selbst, handelt es sich um eine Primzahl
	  printf("Ja\n");              // Antwort mit Zeilenumbruch ausgeben
	} else {                       // ist der Teiler eine andere Zahl, handelt es sich nicht um eine Primzahl
	  printf("Nein\n");            // Antwot mit Zeilenumbruch ausgeben 
	}
	
      }

    }

    return 0;
}
