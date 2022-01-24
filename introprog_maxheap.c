#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"

// for array address calculation
#define INDEX_WORD sizeof(int)

// for me while developing
/*
void print_heap(heap* h){
  printf("Heap:\n");
  for (int i = 0; i<h->size; i++){
    printf("%d,", *(h->elements+i*sizeof(int)));
  }
  printf("\nheap size %zu\n\n",h->size);
  return;
  } */


// ceiling function for calculating parent in heap_insert
size_t calc_parent(size_t i){
  size_t parent;
  if (i % 2 == 0){
    parent = i/2-1;
  }
  else {
    // division result will be cut off
    parent = i/2;
  }
  //printf("parent of %lu is %lu\n", i, parent);
  return parent;
}

/* Reserviere Speicher für einen Heap
 *
 * Der Heap soll dabei Platz für capacity Elemente bieten.
 *
 * Um konsistent mit den Parametern für malloc zu sein, ist
 * capacity als size_t (entspricht unsigned long auf x86/64)
 * deklariert.
 * Da es sauberer ist, sind auch alle Indizes in dieser Aufgabe
 * als size_t deklariert. Ob man size_t oder int als Index für
 * ein Array verwendet, macht in der Praxis (auf x86/64) nur
 * bei Arrays mit mehr als 2.147.483.647 Elementen einen
 * Unterschied.
 */
heap* heap_create(size_t capacity) {
  // allocate space for heap head element
  heap* h = malloc(sizeof(heap));
  // allocate space for the elements of the heap
  h->elements = calloc(capacity, INDEX_WORD);
  h->size = 0;
  h->capacity = capacity;
  return h;
}

/* Stellt die Heap Bedingung an Index i wieder her
 *
 * Vorraussetzung: Der linke und rechte Unterbaum von i
 * erfüllen die Heap-Bedingung bereits.
 */
void heapify(heap* h, size_t i) {
  int* beginning_of_heap = h->elements;  
  // indices of the children of index i
  size_t l = 2*i+1;
  size_t r = 2*i+2;
  size_t largest;
  // test if left child larger than i
  if (l<h->size && beginning_of_heap[l] > beginning_of_heap[i]){
    largest = l;
  }
  else {
    largest = i;
  }
  // test if right child larger than max{left child, i}
  if (r<h->size && beginning_of_heap[r] > beginning_of_heap[largest]){
    largest = r;
  }
  if (largest != i){
    // swap heap[i] and heap[largest]
    int temp_value = beginning_of_heap[i];
    beginning_of_heap[i] = beginning_of_heap[largest];
    beginning_of_heap[largest] = temp_value;
    heapify(h, largest);
  }
  return;
 
}

/* Holt einen Wert aus dem Heap
 *
 * Wenn der Heap nicht leer ist, wird die größte Zahl
 * zurückgegeben. Wenn der Heap leer ist, wird -1 zurückgegeben.
 */
int heap_extract_max(heap* h) {
  int* beginning_of_heap = h->elements;
  if (h->size == 0){
    return -1;
  }
  else {
    // first element = root is max bc of heap property
    int max = beginning_of_heap[0];
    // first element = last element
    beginning_of_heap[0] = beginning_of_heap[h->size-1];
    h->size = h->size-1;
    heapify(h,0);
    // print_heap(h);
    return max;    
  }
}

/* Fügt einen Wert in den Heap ein
 *
 * Wenn der Heap bereits voll ist, wird -1 zurückgegeben.
 */
int heap_insert(heap* h, int key) {
  
  int* beginning_of_heap = h->elements;
   if (h->size == h->capacity){
    return -1;
  }
   else {
   }
  h->size = h->size+1;
  size_t i = h->size-1; // -1 because index starts at 0
  size_t parent = calc_parent(i);
 // division of uneven size_t/lu returns cut off result
  while (i>0 && beginning_of_heap[parent] < key){
    beginning_of_heap[i] = beginning_of_heap[parent];
   i = parent;
   parent = calc_parent(i);
 }
 beginning_of_heap[i] = key;
 return 0;
}

/* Gibt den Speicher von einem Heap wieder frei
 */
void heap_free(heap* h) {
  free(h->elements);
  free(h);  
}
