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
  } else {
    mylist->last->next = le;
    // Listeninformationen aktualisieren
    mylist->last = le;
  }
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
  /*
  printf("Eingangsliste:\n");
  print_list(input);
  printf("\n");
  */
  // Initialisierung left und right Listen
  left->first = NULL;
  left->last = NULL;
  right->first = NULL;
  right->last = NULL;
  
  // last element is pivot
  list_element *pivot = input->last;
  
  list_element *tmp = input->first;
  // printf("input->first: %s %d\n", input->first->password, input->first->count);
  // printf("input->last: %s %d\n", input->last->password, input->last->count);
    // durchlaufe Liste, füge jedes Element < pivot links, >= pivot rechts ein
  while (tmp != pivot){
    // printf("tmp: %s %d\n", tmp->password, tmp->count);
 
    if (tmp->count < pivot->count){
      // füge in linke Liste ein
      if (left->first == NULL){
	left->first = tmp;
	left->last = tmp;
      }
      else {
      left->last->next = tmp;
      left->last = tmp;
      }
    }
    
    else {
      /*
      if (right->first == NULL){
	right->first = tmp;
	right->last = tmp;
      }
      else {
      right->last->next = tmp;
      right->last = tmp;
      }*/
      insert_list(tmp, right);
    }
      tmp = tmp->next;
      //  printf("next tmp: %s %d\n", tmp->password, tmp->count);
    }
  

  /*
  printf("Pivot: %s %d\n", pivot->password, pivot->count);
  printf("linke Liste:\n");
  print_list(left);
  printf("\n");
  printf("rechte Liste:\n");
  print_list(right);
  printf("\n\n\n");
  */
  
  return pivot;
  }

// Hauptfunktion des quicksort Algorithmus
void qsort_list(list* mylist)
{
  if(mylist->first == mylist->last){
    return;
  }
  else {
    list *left = malloc(sizeof(list));
    list *right = malloc(sizeof(list));
    list_element *pivot = partition(mylist, left, right);
  
    qsort_list(left);
    qsort_list(right);

    //einfügen linker Listenteil
    if(left->first == NULL){
      mylist->first = pivot;
    }
    else {
      mylist->first = left->first;
      left->last->next = pivot;
    }
    //einfügen rechter Listenteil
    if (right->first == NULL){
      pivot->next = NULL;
      mylist->last = pivot;
    }
    else{
      pivot->next = right->first;
      mylist->last = right->last;
    }
    


    free(left);
    free(right);
  }




  
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

