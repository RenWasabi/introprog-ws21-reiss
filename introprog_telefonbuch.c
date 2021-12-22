#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
  // create and initialize new node
  bst_node *new_node = malloc(sizeof(bst_node));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  new_node->phone = phone;
  // +1 because strlen doesn't count '/0' 
  new_node->name = malloc (MAX_STR * sizeof(strlen(name+1)));
  strncpy(new_node->name, name, strlen(name+1));

  // insert
  // 1.case: tree doesn't exist
  if (bst == NULL){
      return;
  }
  // 2.case: tree is empty
  // (?) pseudocode line 7: if y = nil then root(T) <- z
  if (bst->root == NULL){
      bst->root = new_node;
    bst->count = bst->count + 1;
    return;
  }
  // 3.case: tree is not empty => insert node at correct place
  // initalize variables for search algorithm
  bst_node *new_node_parent = NULL; // y in pseudocode
  bst_node *current_node = bst->root; // x in pseudocode

  /* new node will be inserted as leaf => algorithm ends when current
   * node (new node's position) is                          NULL-Pointer */
  while (current_node != NULL){
    /* new_node_parent goes down one level (becomes current position),
     * (?) pseudocode line 6 can be ommited because of this direct assignment */
    new_node_parent = current_node;
    /* current node goes down one level 
     * (becomes left or right child after comparison of phone number value) */
    // 1. case: number already exists in tree
    if (new_node->phone == current_node->phone){
      // error message to stout or sterror?
      printf("Für diese Telefonnummer existiert bereits ein Eintrag. Abbruch...\n");
      return;
    } // new number smaller than current position's number => go down left
    else if (new_node->phone < current_node->phone){
      current_node = current_node->left;  // x <- lc(x)
    }
    // new number greater than current position's number => go down right
    else {
      current_node = current_node->right;  // x <- rc(x)
    }
  }

  // assign the parent of current position to new_node
  new_node->parent = new_node_parent;

  // assign new node as child of its new parents
  if (new_node->phone < new_node->parent->phone){
    new_node->parent->left = new_node;
  }
  else {
    new_node->parent->right = new_node;
  }  

  // if code makes it to this line, a new element was inserted
  bst->count = bst->count +1;  
  return;   
}


/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
  // we start searching at the root
  bst_node *current_node = bst->root;

  while (current_node != NULL && current_node->phone != phone){
    if (phone < current_node->phone){
      current_node = current_node->left;
    }
    else {
      current_node = current_node->right;
    }
  }
  return current_node;
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
  if (node != NULL){
    bst_in_order_walk_node(node->left);
    print_node(node);
     bst_in_order_walk_node(node->right);
    return;
  }
}

/* 
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {
  if (node != NULL){
    bst_free_subtree(node->left);
    bst_free_subtree(node->right);
    // space for name was manually allocated in bst_insert_node
    free(node->name);
    free(node);
  }
  return;
}

/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
