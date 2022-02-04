#include <stdlib.h>		
#include <stdio.h>	// Ein- / Ausgabe
#include <math.h>	// Für die Berechnungen der Ausgabe
#include "avl.h"

// custom: create a new node
AVLNode* AVL_create_node(AVLNode* parent, int value){
     AVLNode* new_node = malloc(sizeof(AVLNode));
     new_node->left = NULL;
     new_node->right = NULL;
     new_node->parent = parent;
     new_node->value = value;
     new_node->height = 0; // new node is leaf

     return new_node;
}

/* custom: update the height of nodes */
// no loops: complexit should be O(c) with c constant
void AVL_update_height(AVLNode* node)
{
  // max height of a child of 
  if(node->left == NULL){
    //no children
    if(node->right == NULL){
      node->height = 0;
    }
    // only right child
    else{
      node->height = 1+(node->right->height);
    }
  }
  else{
    // only left child
    if(node->right == NULL){
      node->height = 1+(node->left->height);
    }
    // left and right child
    else{
      if(node->left->height >= node->right->height){
	node->height = 1+(node->left->height);
      }
      else{
	node->height = 1+(node->right->height);
      }
    }
  }
  return;
}

/* Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus. */
void AVL_in_order_walk(AVLTree* avlt)
{
  if(avlt != NULL){
    AVL_in_order_walk_node(avlt->root);
  }
  return;
}

// custom: für tree walk
void AVL_in_order_walk_node(AVLNode* root){
  if (root != NULL){
    AVL_in_order_walk_node(root->left);
    printf("%d ", root->value);
    AVL_in_order_walk_node(root->right);
  }
  printf("\n");
}




/* Diese Funktion führt eine Linksrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
// no loops: complexit should be O(c) with c constant
void AVL_rotate_left(AVLTree* avlt, AVLNode* x)
{
  // left rotation is only possible when x has a right child
  if(x->right == NULL){
    printf("Kein rechtes Kind! Linke Rotation nicht möglich.");
    return;
  }
  else{
    AVLNode* rising_node = x->right;
    // correct pointers concerning rising node's left child
    x->right = rising_node->left;
    if(rising_node->left != NULL){
      rising_node->left->parent = x;
    }
    // correct pointers concerning new parent of rising node
    // (p.r.n. root)
    rising_node->parent = x->parent;
    if(x->parent == NULL){
      avlt->root = rising_node;
    }
    else if(x == x->parent->left){
      x->parent->left = rising_node;
    }
    else{
      x->parent->right = rising_node;
    }
    // correct pointers for relation of rotation node and rising node
    rising_node->left = x;
    x->parent = rising_node;
    // update node heights
    AVL_update_height(x);
    AVL_update_height(rising_node);
  }
  return;
}

/* Diese Funktion führt eine Rechtsrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
// no loops: complexit should be O(c) with c constant
void AVL_rotate_right(AVLTree* avlt, AVLNode* y)
{
  // copy pasted from left, exchanged left <-> right, need to check
  // for errors
  // right rotation is only possible when x has a left child
  if(y->left == NULL){
    printf("Kein linkes Kind! Reche Rotation nicht möglich.");
    return;
  }
  else{
    AVLNode* rising_node = y->left;
    // correct pointers concerning rising node's right child
    y->left = rising_node->right;
    if(rising_node->right != NULL){
      rising_node->right->parent = y;
    }
    // correct pointers concerning new parent of rising node
    // (p.r.n. root)
    rising_node->parent = y->parent;
    if(y->parent == NULL){
      avlt->root = rising_node;
    }
    else if(y == y->parent->left){
      y->parent->left = rising_node;
    }
    else{
      y->parent->right = rising_node;
    }
    // correct pointers for relation of rotation node and rising node
    rising_node->right = y;
    y->parent = rising_node;
    // update node heights
    AVL_update_height(y);
    AVL_update_height(rising_node);
  }
  return;
}

/* Balanciere den Teilbaum unterhalb von node.
 * 
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen _nicht_
 * angepasst werden, da dieses schon in den Rotationen geschieht.
 * Falls dies nicht eingehalten wird funktionieren die Unit-Tests
 * ggf. nicht.
 */
// no loops: complexit should be O(c) with c constant
void AVL_balance(AVLTree* avlt, AVLNode* node)
{
  // left subtree more than one higher than right subtree
  if(node->left->height > node->right->height+1){
    // inner subtree higher than outer => additional left rotation
    if(node->left->right->height > node->left->left->height){
      AVL_rotate_left(avlt, node->left);
    }
    AVL_rotate_right(avlt, node);
  }
  // right subtree more than one higher than left subtree
  else if(node->right->height > node->left->height+1){
    // inner subtree higher than outer => additional right rotation
    if(node->right->left->height > node->right->right->height){
      AVL_rotate_right(avlt, node->right);
    }
    AVL_rotate_left(avlt, node);
  }
  // difference of subtree height <= 1 => do nothing
  return;
}


/* Fügt der Wert value in den Baum ein.
 *
 * Die Implementierung muss sicherstellen, dass der Baum nach dem
 * Einfügen immer noch balanciert ist!
 */

void AVL_insert_value(AVLTree* avlt, int value)
{
   AVLNode* current_node = avlt->root;

   /* end of recursion is one recursion level above end in 
    * Pseudocode as access to the parent of the new node is required */
   // new node will be left child
   if(value < current_node->value && current_node->left == NULL){
     // create node
     AVLNode* new_node = AVL_create_node(current_node, value);
     current_node->left = new_node;
     // height of current_node will be updated in balance()
   }
   // new node will be right child
   else if(value > current_node->value && current_node->right == NULL){
     // create node
     AVLNode* new_node = AVL_create_node(current_node, value);
     current_node->right = new_node;
     // height of current_node will be updated in balance()
   }
   // continue search for right place
   else if(value < current_node->value){
     // construct subtree
     AVLTree* subtree = malloc(sizeof(AVLTree));
     subtree->root = current_node->left;
     subtree->numberOfNodes = 0; // wrong, but not needed here
     AVL_insert_value(subtree, value);
   }
   else if(value > current_node->value){
     // construct subtree
     AVLTree* subtree = malloc(sizeof(AVLTree));
     subtree->root = current_node->right;
     subtree->numberOfNodes = 0; // wrong, but not needed here
     AVL_insert_value(subtree, value);   
   }
   // current node is key
   else{
     printf("Wert bereits im Baum vorhanden!\n");
     return;
   }
   
   AVL_update_height(current_node);

   AVL_balance(avlt, current_node);
   
   // update avlt->numberOfNodes
   avlt->numberOfNodes++;
   

   return;
}

 



/* Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten
 * frei.
 */
void AVL_remove_all_elements(AVLTree* avlt)
{
    // Hier Code implementieren!
}
