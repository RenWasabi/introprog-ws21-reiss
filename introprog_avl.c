#include <stdlib.h>		
#include <stdio.h>	// Ein- / Ausgabe
#include <math.h>	// Für die Berechnungen der Ausgabe
#include "avl.h"

/* Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus. */
void AVL_in_order_walk(AVLTree* avlt)
{
    //Hier Code implementieren!
}

/* Diese Funktion führt eine Linksrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_left(AVLTree* avlt, AVLNode* x)
{
    // Hier Code implementieren!
}

/* Diese Funktion führt eine Rechtsrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_right(AVLTree* avlt, AVLNode* y)
{
    // Hier Code implementieren!
}

/* Balanciere den Teilbaum unterhalb von node.
 * 
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen _nicht_
 * angepasst werden, da dieses schon in den Rotationen geschieht.
 * Falls dies nicht eingehalten wird funktionieren die Unit-Tests
 * ggf. nicht.
 */
void AVL_balance(AVLTree* avlt, AVLNode* node)
{
    // Hier Code implementieren!
}


/* Fügt der Wert value in den Baum ein.
 *
 * Die Implementierung muss sicherstellen, dass der Baum nach dem
 * Einfügen immer noch balanciert ist!
 */
void AVL_insert_value(AVLTree* avlt, int value)
{
    // Hier Code implementieren!
}

/* Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten
 * frei.
 */
void AVL_remove_all_elements(AVLTree* avlt)
{
    // Hier Code implementieren!
}
