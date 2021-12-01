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
/* Fuege ein Element in die Liste ein, sodass die Liste aufsteigend
 * nach ISBN sortiert ist.  Dafür muss das erste Element ermittelt
 * werden, das in der bisher sortierten Liste eine ISBN besitzt,
 * die größer ist als die des neuen Elements.  Wenn die Liste leer
 * ist, soll das Element direkt an den Anfang platziert werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen oder alten Anfang der Liste
 * zurueck.
 */
//element* insert_sorted(element *first, element *new_elem) {
    /* HIER implementieren. */
//} 


element *insert_sorted(element *first, element *new_elem) {
  // Sonderfall 1: leere Liste
  if (first == NULL){
    first = new_elem;
    // new_elem->next = NULL bereits durch Initialisierung in construct_element
  }
  // Sonderfall 2: erstes Element
  else if (new_elem->isbn < first-> isbn){
    new_elem->next = first;
    // gib das neue Element als Anfang der Liste an aufrufende Funktion, beende
    return new_elem;
  }
  // Regelfall bzw. Weg zum 3. Sonderfall
  else {
    // "Initialisierung" der Variablen vor Schleifenbeginn
    new_elem->next = first->next;
    /* prev_pointer zeigt immer auf das Vorgängerelement, dass jeweils auf 
     * new_elem zeigen sollte */
    element *prev_pointer = first;

    // beginnt Schleife nur, wenn zweites Listenelement nicht NULL ist
    if (new_elem->next != NULL){
      /* verschiebe das neue Element und den Zeiger auf seinen Vorgänger nach hinten,
       * bis hinter ihm ein Element mit höherer isbn oder der NULL-Pointer liegt */
      while (new_elem->isbn > new_elem->next->isbn){
	prev_pointer = new_elem->next;
	new_elem->next = new_elem->next->next;
	/* falls das neue Element an das Ende der Liste kommt, brich hier ab, damit kein
	 * unzulässiger while-Vergleich mit dem NULL-Pointer (der kein ->isbn hat)
	 * durchgeführt wird */
	if (new_elem->next == NULL){
	  break;
	}
      }
    }
    // lass das Vorgängerelement nun auf das neue Element zeigen
    /* während prev_pointer oben nur immer wieder neue Adressen zugeweisen werden,
     * wird hier auf das an der Adresse liegende Element selbst zugegriffen (?) */
    prev_pointer->next = new_elem;
  }

  // Pointer auf neuen (Sonderfall 1) oder alten Anfang der Liste
  return first;  
}




element *construct_element(char *title, char* author, int year, long long int isbn) {
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
}

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
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
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
