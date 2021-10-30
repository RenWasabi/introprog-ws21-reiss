#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char wochentag[] = "Freitag";
    int tag = 13;
    char monat[] = "Mai";
    int jahr = 1927;
    char *string; // Hier soll das Datum hineingeschrieben werden!
    const size_t kapazitaet = 100 * sizeof(char); // Maximale Laenge des Datumstrings!
    /* Man soll weniger als 101 byte Speicher reservieren */

    // Hier implementieren und dynamisch Speicher reservieren

    // es darf angenommen werden: maximale Datumslänge sind 100 Zeichen
    // snprintf schließt string mit Nullbyte ab, also Länge +1
    /*    kapazitaet = 101 * sizeof(char); das hier gibt einen Fehler beim Compilen,
     * vielleicht kann die Konstante nur bei ihrer Deklaration festlegen? */

    // Speicher dieser Größe da, wo pointer string hinzeigt, anfordern
    string = (char*) malloc(kapazitaet);

    // das Datum in den String drucken
    snprintf(string, kapazitaet, "%s, der %d. %s %d", wochentag, tag, monat, jahr);

    printf("%s\n", string);
    // Speicher freigeben
    free(string);

    return 0;
}
