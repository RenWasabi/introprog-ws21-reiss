#include <stdio.h>
#include "introprog_complexity_steps_input.h"

long for_linear(int n, int* befehle)
{ 
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;
    (*befehle)++;   // Initialisierung sum
    (*befehle)++;   // Initialisierung Laufvariable i for-Schleife
    for(int i = 1; i <= n; ++i) {
        (*befehle)++;  // Vergleich true
        // Zähle die folgende Zeile als genau ein Befehl!
        sum += get_value_one();
	(*befehle)++;  // Erhöhung sum um 1
	(*befehle)++;  // Inkrementierung Laufvariable i
    }
    (*befehle)++;  // Vergleich false
    (*befehle)++; // return
    return sum;
}

long for_quadratisch(int n, int* befehle)
{
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;
    (*befehle)++; // Initialisierung sum
    (*befehle)++; // Initialisierung Laufvariable i äußere for-Schleife
    for(int i = 1; i <= n; ++i) {
      (*befehle)++; // Vergleich äußere Schleife true
      (*befehle)++; // Initialisierung Laufvariable j innere for-Schleife
        for(int j = 1; j <= n; ++j) {
	  (*befehle)++; // Vergleich innere Schleife true
            // Zähle die folgende Zeile als genau ein Befehl!
            sum += get_value_one();
	    (*befehle)++;  // Erhöhung sum um 1
	    (*befehle)++;  // Inkrementierung innere Laufvariable j
        }
	(*befehle)++;  // Vergleich innere for-Schleife false
	(*befehle)++; // Inkrementiere äußere Laufvariable i
    }
    (*befehle)++;  // Vergleich äußere Schleife false
    (*befehle)++; // return
    return sum;
}

long for_kubisch(int n, int* befehle)
{
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;
    (*befehle)++; // Initialisierung sum
    (*befehle)++; // Initialiserung äußere Laufvariable i
    for(int i = 1; i <= n; ++i) {
      (*befehle)++; // äußerer Vergleich true
      (*befehle)++; // Initialisierung mittlere Laufvariable j
        for(int j = 1; j <= n; ++j) {
	  (*befehle)++; // mittlerer Vergleich true
	  (*befehle)++; // Initialisierung innere Laufvariable k
            for(int k = 1; k <= n; ++k) {
	      (*befehle)++; // innerer Vergleich true
                // Zähle die folgende Zeile als genau ein
                // Befehl!
                sum += get_value_one();
		(*befehle)++; // Erhöhung sum um 1
		(*befehle)++; // Inkrementierung innere Laufvariable k
            }
	    (*befehle)++; // innerer Vergleich false
	    (*befehle)++; // Inkrementierung mittlere Laufvariable k
        }
	(*befehle)++; // mittlerer Vergleich false
	(*befehle)++; // Inkrementierung äußere Laufvariable i
    }
    (*befehle)++; // äußerer Vergleich false
    (*befehle)++; // return
    return sum;
}


int main(int argc, char *argv[])
{
    const int WERTE[] = {5,6,7,8,9,10};
    const int LEN_WERTE = 6;
    const int LEN_ALGORITHMEN = 3;

    long befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    long werte_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("Starte Algorithmus %d mit Wert %d\n",
                (i+1), n);
            int anzahl_befehle = 0;
            int wert = 0;

            // Starte den Timer
            start_timer();

            // Aufruf der entsprechenden Funktion
            if(i==0) {
                wert = for_linear(n, &anzahl_befehle);
            }
            else if(i==1) {
                wert = for_quadratisch(n, &anzahl_befehle);
            }
            else if(i==2) {
                wert = for_kubisch(n, &anzahl_befehle);
            }

            // Speichere Laufzeit, Rückgabewert und Anzahl
            // ausgeführter Befehle ab
            laufzeit_array[i][j] = end_timer();
            werte_array[i][j] = wert;
            befehle_array[i][j] = anzahl_befehle;
        }
        printf("\n");
    }

    // Ausgabe der Rückgabewerte, Anzahl ausgeführter Befehle
    // sowie der gemessenen Laufzeiten (in Millisekunden)
    printf("%3s \t%-28s \t%-28s \t%-28s\n", "","linear", "quadratisch", "kubisch");
    printf("%3s \t %5s %10s %10s\t %5s %10s %10s\t %5s %10s %10s\n", "n","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%3d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%5ld %10ld %10.4f \t ", werte_array[i][j], befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
