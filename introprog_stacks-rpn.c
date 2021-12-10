#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

/* 
 * Füge Element am Anfang des Stacks ein
 *
 * astack - Ein Pointer auf den Stack.
 * value  - Zahl, die als neues Element auf den Stack gelegt
 *          werden soll.
 */
void stack_push(stack* astack, float value)
{
  // allocate memory for new element on stack
  stack_element *new_value = (stack_element *) calloc(1, sizeof(stack_element));
  
  new_value->value = value;
  // new element points to previous top element on stack
  new_value->next = astack->top;

  // new element is pointed to as top element of stack
  astack->top = new_value;

  return;
}

/* 
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * astack - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* astack)
{
  // return NAN if stack is empty
  if (astack->top == NULL){
    return NAN;
  }
  // otherwise remove top element and return its value
  else {
    // store pointer to top element in variable
    stack_element *popped_elem = astack->top;
    float popped_value = popped_elem-> value;

    // remove top element from stack
    astack->top = popped_elem->next;

    // free memory of popped element
    free(popped_elem);

    return popped_value;
  }
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * astack - Ein Pointer auf den Stack
 * token  - Eine Zeichenkette
 */
void process(stack* astack, char* token)
{
  // 1st case: token is a number
  if (is_number(token)){
    
    // convert token string to double
    int value = atof(token);
    // push number onto stack
    stack_push(astack, value);
  }

  // 2nd case: number is operator +,-,*
  // +
  else if (is_add(token)){
    //pop second operand
    int b = stack_pop(astack);
    // pop first operand
    int a = stack_pop(astack);

    // push result of operation onto stack
    stack_push(astack, a+b);
  }
  // -
  else if (is_sub(token)){
    //pop second operand
    int b = stack_pop(astack);
    // pop first operand
    int a = stack_pop(astack);

    // push result of operation onto stack
    stack_push(astack, a-b);
  }
  // *
  else if (is_mult(token)){
    //pop second operand
    int b = stack_pop(astack);
    // pop first operand
    int a = stack_pop(astack);

    // push result of operation onto stack
    stack_push(astack, a*b);
  }
  
  // 3rd case: token is neither number nor operator
  // ignore = no action?
  else {}
  
    return;
    /* Du kannst zur Erkennung der Token folgende Hilfsfunktionen
     * benutzen:
     *
     * Funktion          Rückgabewert von 1 bedeutet
     * ---------------------------------------------
     * is_add(token)     Token ist ein Pluszeichen
     * is_sub(token)     Token ist ein Minuszeichen
     * is_mult(token)    Token ist ein Multiplikationszeichen
     * is_number(token)  Token ist eine Zahl
     */
}

/* 
 * Debugausgabe des Stack
 * Diese Funktion kannst du zum debugging des Stack verwenden.
 *
 * astack - Ein Pointer auf den Stack
 */
void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}

/* 
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
  // allocate memory for stack
  stack* astack = (stack *) calloc(1, sizeof(stack));
  // initialize stack as pointing to NULL (empty stack)
  astack->top = NULL;
  return astack;
}

int main(int argc, char** args)
{
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;

    intro();
    while (taschenrechner_input(zeile) == 0) {
        // Erstes Token einlesen
        token = strtok(zeile, " ");

        while (token != NULL) {
            printf("Token: %s\n", token);
            // Stackoperationen durchführen
            process(astack, token);
            // Nächstes Token einlesen
            token = strtok(NULL, " ");
            print_stack(astack);
        }

        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);

        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);   //Räume Stack auf
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}
