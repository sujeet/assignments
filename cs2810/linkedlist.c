/*******************************************************************************************************************/
/* roll number                    : cs09b010                                                                       */
/* name                           : sujeet gholap <sujeetgholap@gmail.com>                                         */
/* aim                            : to implement a singly linked list of integers                                  */
/* reason for long function names : as the consequent assignments may require me to use this code,                 */
/*                                 and may be other ipmlementations as well, (eg. doubly linked lists, heaps etc.) */
/*                                 to avoid the conflict of function names, I have used function names which       */
/*                                 clearly indicate what data structure they manipulate.                           */
/*******************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>

typedef int bool;

#define TRUE 1
#define FALSE 0
#define DEFAULT_INT_VALUE 0

typedef struct lnode
{
     int data;
     struct lnode * next;
}lnode;

typedef struct linked_list
{
     lnode * head;
}linked_list;

lnode * lnode_new()
{
     lnode * node = (lnode*)malloc(sizeof(lnode));
     if ( node == NULL ) {
          fprintf (stderr, "ERROR : could not allocate memory for node.\n");
          exit (-1);
     }
     node->next = NULL;
     node->data = DEFAULT_INT_VALUE;
     return node;
}

linked_list * linked_list_new()
{
     linked_list * list = (linked_list*)malloc(sizeof(linked_list));
     if ( list == NULL ) {
          fprintf(stderr, "ERROR : could not allocate memory for list.\n");
          exit(-1);
     }
     list->head = NULL;
     return list;
}

void linked_list_insert(linked_list * list, int value) 
{
     /* prepends a node having data = value to head and makes it into head */
     lnode * new_head = lnode_new();
     new_head->data = value;
     new_head->next = list->head;
     list->head = new_head;
}

void linked_list_insert_after(linked_list * list, int number_to_insert, int number_in_list) 
{
     /* inserts the number_to_insert after number_in_list, else inserts it after the tail */
     lnode * current_node = list->head;
     lnode * new_node;
     if ( current_node == NULL ) {
          /* this means the list is empty */
          linked_list_insert (list, number_to_insert);
          return;
     }
     while (( current_node->next != NULL )&&( current_node->data != number_in_list )) {
          /* loop is exited when current_node is a tail or it has the desired number */
          current_node = current_node->next;
     }
     new_node = lnode_new();
     new_node->data = number_to_insert;
     new_node->next = current_node->next;
     current_node->next = new_node;
}
  
void linked_list_delete(linked_list * list, int value) 
{
     /* deletes the first node encountered while going from head to tail having data = value 
      * does nothing if no such node is found
      */
     lnode * current_node = list->head;
     lnode * next_node;
     if ( current_node == NULL ) {
          /* this means that the list is empty */
          return;
     }
     next_node = current_node->next;
     if ( current_node->data == value ) {
          /* the head is to be deleted */
          free (list->head);
          list->head = next_node;
     }
     while (( next_node != NULL )&&( next_node->data != value)) {
          /* loop is exited when current node is tail or
           * next node is to be deleted
           */
          current_node = current_node->next;
          next_node = next_node->next;
     }
     if ( next_node == NULL ) {
          /* element not found do nothing */
          return;
     }
     if ( next_node->data == value ) {
          current_node->next = next_node->next;
          free (next_node);
     }
}

bool linked_list_search (linked_list * list, int value) 
{
     lnode * current_node = list->head;
     for ( current_node; current_node != NULL; current_node = current_node->next ) {
          if ( current_node->data == value ) {
               return TRUE;
          }
     }
     return FALSE;
}

bool linked_list_is_empty (linked_list * list) 
{
     if ( list->head == NULL ) {
          return TRUE;
     }
     return FALSE;
}

lnode * lnode_get_next (lnode * somenode) 
{
     return somenode->next;
}

void lnode_print (lnode * node)
{
     if ( node != NULL ) {
          printf ("%d\n", node->data);
     }
}

void linked_list_print (linked_list * list)
{
     lnode * current_node = list->head;
     for ( current_node; current_node != NULL; current_node = current_node->next ) {
          printf ("%d ", current_node->data);
     }
     printf ("\n");
}

int main ()
{
     /* uncomment the following lines to test the code */

     /*
     linked_list * list = linked_list_new();
     int i;
     linked_list_print (list);
     if (linked_list_is_empty(list)){
          printf ("The list is empty.\n");
     }
     else {
          printf ("The list is not empty.\n");
     }
     for ( i = 0; i < 10 ; i++) {
          linked_list_insert (list, i);
     }
     linked_list_print (list);
     linked_list_delete (list, 5);
     linked_list_print (list);
     linked_list_delete (list, 33);
     linked_list_print (list);
     linked_list_insert (list, 44);
     linked_list_print (list);
     linked_list_insert_after (list, 99, 3);
     if (linked_list_is_empty(list)){
          printf ("The list is empty.\n");
     }
     else {
          printf ("The list is not empty.\n");
     }
     if (linked_list_search(list, 88)){
          printf ("88 found.\n");
     }
     else {
          printf ("88 not found.\n");
     }
     linked_list_print (list);
     linked_list_insert_after (list, 88, 20);
     linked_list_print (list);
     if (linked_list_search(list, 88)){
          printf ("88 found.\n");
     }
     else {
          printf ("88 not found.\n");
     }
     */

     return 0;
}
