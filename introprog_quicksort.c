#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

/*****************************************************
 * Die benoetigten structs findet Ihr in quicksort.h *
 *****************************************************/
// Liste wird in main deklariert, hier also keine Speicherallozierung mehr
void init_list(list* mylist)
{
  mylist->first = NULL;
  mylist->last = NULL;
}



// Diese Funktion fügt Listenelemente an die Liste an
void insert_list(list_element* le, list* mylist)
{
  // Liste ist leer
  if (mylist->first == NULL){
    mylist->first = le;
    mylist->last = le;
    return;
  }
  mylist->last->next = le;
  // Listeninformationen aktualisieren
  mylist->last = le;
  return;
}

// Speicher für Listenelemente wieder freigeben
void free_list(list* mylist)
{

  list_element *tmp = mylist->first;
  while (tmp != NULL){
    tmp = mylist->first->next;
    if(mylist->first == mylist->last){
      mylist->last = NULL;
    }
    free(mylist->first->password);
    free(mylist->first);
    mylist->first = tmp;
  }
  // free(mylist);
  return;
}


// Namen, Zahlen Paare in Liste einlesen
void read_data(char* filename, list* mylist)
{
		// HIER Code einfügen:
        // * Speicher allozieren
        // * Daten in list_element einlesen
        // * insert_list benutzen, um list_element in Liste einzufügen

  size_t MAX_LINE_LEN = 200;
  FILE* input_file = fopen(filename,"r");

  // allocate buffer in which lines while be stored for parsing
  char* newline = (char*) malloc(MAX_LINE_LEN*sizeof(char));
  int pw_frequency = 0;
  // max passwort length will definitely be lower than max line length
  char* password = (char*) malloc(MAX_LINE_LEN*sizeof(char));


  while(fgets(newline, MAX_LINE_LEN, input_file) != NULL){
    sscanf(newline, "%s %d", password, &pw_frequency);

    list_element* new_element = malloc(sizeof(list_element));
    new_element->password = malloc(MAX_LINE_LEN*sizeof(char));
    strncpy(new_element->password, password, MAX_LINE_LEN);
    // new_element->password[MAX_LINE_LEN-1] = '\0';
    new_element->count = pw_frequency;
    
    // printf("%s\n", new_element->password);
    // printf("%d\n", new_element->count);
    // puts(newline);
    insert_list(new_element, mylist);
  }
  free(password);
  free(newline);
  fclose(input_file);

  return;
}

// Liste teilen. Teillisten werden in left und right zurück gegeben
list_element* partition( list* input, list* left, list* right )
{
    // HIER Code einfügen:
    // parition() Funktion implementieren
}

// Hauptfunktion des quicksort Algorithmus
void qsort_list(list* mylist)
{
    // HIER Code einfügen
}

// Liste ausgeben
void print_list(list* mylist)
{
  list_element* counter = mylist->first;
  while(counter != NULL){
    printf("%s %d\n", counter->password, counter->count);
    counter = counter->next;
  }
  return;
}

