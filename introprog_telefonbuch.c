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
  printf("!!! &name: %p\n", &name);
  printf("name: %s\n", name);
  printf("bst->root: %p\n", bst->root);
  // create and initialize new node
  bst_node *new_node = malloc(sizeof(bst_node));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  new_node->phone = phone;
  new_node->name = malloc (MAX_STR * sizeof(char));
  strncpy(new_node->name, name, MAX_STR);
  
  printf("new_node: %p, left: %p, right: %p, parent: %p, phone: %lu, name: %s\n\n",new_node, new_node->left, new_node->right, new_node->parent, new_node->phone, new_node->name);

  // insert
  // 1.case: tree doesn't exist
  if (bst == NULL){
    printf("bst->count: %d; bst->root->name: %s; new_node->name: %s\n", bst->count, bst->root->name, new_node->name);
    return;
  }
  // 2.case: tree is empty
  // (?) pseudocode line 7: if y = nil then root(T) <- z
  if (bst->root == NULL){
    printf("hier");
    bst->root = new_node;
    bst->count = bst->count + 1;

    printf("bst->count: %d; bst->root->name: %s; &bst->root->name: %p, bst->root->phone: %lu\n", bst->count, bst->root->name, &(bst->root->name),  bst->root->phone);

  printf("new_node: %p, left: %p, right: %p, parent: %p, phone: %lu, name: %s\n\n",new_node, new_node->left, new_node->right, new_node->parent, new_node->phone, new_node->name);
  printf(" new_node->name: %s; &new_node->root->name: %p, new_node->phone: %lu\n\n\n\n",new_node->name, &(new_node->name),  new_node->phone);
    return;
  }
  // 3.case: tree is not empty => insert node at correct place
  // initalize variables for search algorithm
  bst_node *new_node_parent = NULL; // y in pseudocode
  bst_node *current_node = malloc(sizeof(bst_node));
  current_node = bst->root; // x in pseudocode

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

  printf("bst->count: %d; bst->root->name: %s; &bst->root->name: %p, bst->root->phone: %lu\n", bst->count, bst->root->name, &(bst->root->name),  bst->root->phone);

  printf("new_node: %p, left: %p, right: %p, parent: %p, phone: %lu, name: %s\n\n",new_node, new_node->left, new_node->right, new_node->parent, new_node->phone, new_node->name);
  printf("new_node->parent: %p, new_node->parent->name: %s\n", new_node->parent, new_node->parent->name);
  printf(" new_node->name: %s; &new_node->name: %p, new_node->phone: %lu\n\n\n\n",new_node->name, &(new_node->name),  new_node->phone);
  
  return;   
}


/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
  if (node != NULL){
    bst_in_order_walk_node(node->left);
    print_node(node);
    printf("Name zu oben: %s\n", node->name);
    printf("Adresse Name zu oben: %p\n", &(node->name));
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
