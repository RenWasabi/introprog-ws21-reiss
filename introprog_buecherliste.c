#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_structs_lists_input.h"

#define MAX_STR 255

/* Bewirkt, dass statt 'struct _element' auch 'element' verwendet
 * werden kann.
 */
typedef struct _element element; 

/* Bewirkt, dass statt 'struct _list' auch 'list' verwendet werden
 * kann.  Hier in einem geschrieben, so dass man auch 'list'
 * innerhalb der struct-Definition selbst verwenden kann.
 */
typedef struct _list { /* Separater Wurzelknoten */
    element *first;    /* Anfang/Kopf der Liste */
    int count;         /* Anzahl der Elemente */
} list;

/* HIER struct _element implementieren. */
struct _element {
  // die char Arrays sollen statisch auf 255 begrenzt sein (muss ich initialisieren?)
  char title[MAX_STR];
  char author[MAX_STR];
  int year;
  long long int isbn;
  element *next;   // Pointer auf das nächste Listenelement hat Typ Listenelement-Pointer
};
  
/* Fuege ein Element am Anfang der Liste an, sodass das neue
 * Element immer das erste Element der Liste ist.  Wenn die Liste
 * leer ist, soll das Element direkt an den Anfang platziert
 * werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der
 * Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen Anfang der Liste zurueck.
 */
element *insert_at_begin(element *first, element *new_elem) {
    /* HIER implementieren. */
  new_elem->next = first; // neues Element zeigt auf erstes Listenelement
  /* in read_list: alist->first = insert_at_begin(alist->first, new_elem);
   * die Funktion muss also einen Pointer auf das neue Element zurückggeben */
  // der counter des Wurzelelementes wird in der aufrufenden Fkt read_list erhöht
  return new_elem;  
}

/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char *title, char* author, int year, long long int isbn) {
    /* HIER implementieren. */
  element *book = (element*) malloc(sizeof(element)); // Pointer auf jedes Buchelement
  // Zuweisung der Werte zum richtigen Teil der Element
  /* Zuweisung mit strncpy, sonst beim Compilen:
   * error: array type 'char [255]' is not assignable */
  // Nullterminator: kopiere so weit wie möglich ins Array, setze 0 Terminator
  // für lange Titel/Namen gibt es sonst keinen Terminator
  strncpy(book->title, title, MAX_STR-1);
  book->title[254] = '\0';
  strncpy(book->author,author, MAX_STR-1);
  book->author[254] = '\0';
  book-> year = year;
  book-> isbn = isbn;
  book-> next = NULL; // initialisiere Pointer auf Folgeelement mit NULL
  return book; //gib Pointer auf das konstruierte Listenelement an aufrufende Fkt. zurück
};

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list *alist) {
    /* HIER implementieren. */
  /* über alist iterieren, jedes Element freigeben, vorher next in Variable merken */
  // speichere Adresse des ersten Elementes in Zwischenvariable tmp
  element *tmp = alist->first;
  // go through list until arriving at NULL-Pointer (= last element's pointer)
  while (tmp != NULL) {
    // merke Nachfolger des ersten Elements in tmp
    tmp = alist->first->next;
    // freee erstes Element
    free(alist->first);
    // Nachfolger wird neues erstes Element
    alist->first = tmp;
  }
  // nachdem in oberer Schleife alle Elemente gefreed wurden, nun die Wurzel:
  free(alist);
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 */
void read_list(char* filename, list *alist) {
    element* new_elem;

    char* title;
    char* author;
    int year;
    long long int isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_elem = construct_element(title, author, year, isbn);
	// alist->first (Wurzelknoten zeigt auf erstes richtiges Element)
        alist->first = insert_at_begin(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
// list ist der Typ des Wurzelknoteny
list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}

/* Gib die Liste aus:
 * _Soll nicht angepasst werden_
 */
void print_list(list *alist) {
    printf("Meine Bibliothek\n================\n\n");
    int counter = 1;
    element *elem = alist->first;
    while (elem != NULL) {
        printf("Buch %d\n", counter);
        printf("\tTitel: %s\n", elem->title);
        printf("\tAutor: %s\n", elem->author);
        printf("\tJahr:  %d\n", elem->year);
        printf("\tISBN:  %lld\n", elem->isbn);
        elem = elem->next;
        counter++;
    }
}

/* Main Funktion
 * _Soll nicht angepasst werden_
 */
int main(int argc, char** argv) {
    list *alist = construct_list();
    read_list(argc>1?argv[1]:"buecherliste.txt", alist);
    print_list(alist);
    free_list(alist);
    return 0;
}
