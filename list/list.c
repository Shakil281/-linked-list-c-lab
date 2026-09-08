// list/list.c
//
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() {
  list_t* mylist = (list_t *) malloc(sizeof(list_t));
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  if (l == NULL) return;
  node_t *curr = l->head;
  while (curr != NULL) {
    node_t *next = curr->next;   // save next BEFORE freeing curr
    free(curr);
    curr = next;
  }
  l->head = NULL;
  free(l);
}

void list_print(list_t *l) {
  char *s = listToString(l);
  printf("%s\n", s);
  free(s);                       // listToString mallocs, so we free it
}

char * listToString(list_t *l) {
  /* Longest an int can print is 11 chars ("-2147483648") plus "->" = 13.
     Add room for the trailing "NULL" and the '\0'. */
  int n = list_length(l);
  char* buf = (char *) malloc(sizeof(char) * (n * 13 + 8));
  char* p = buf;                 // write cursor: keeps this O(n), not O(n^2)

  node_t* curr = l->head;
  while (curr != NULL) {
    p += sprintf(p, "%d->", curr->value);
    curr = curr->next;
  }
  strcpy(p, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
  node_t *n = getNode(value);

  if (l->head == NULL) {         // empty list: new node becomes head
    l->head = n;
    return;
  }

  node_t *curr = l->head;
  while (curr->next != NULL) {   // walk to the last node
    curr = curr->next;
  }
  curr->next = n;
}

void list_add_to_front(list_t *l, elem value) {
    node_t *cur_node = (node_t *) getNode(value);

    /* Insert to front */
    node_t *head = l->head;  // get head of list

    cur_node->next = head;
    l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

/* Indices are 1-BASED: index 1 == front. Index past the end appends. */
void list_add_at_index(list_t *l, elem value, int index) {
  if (index <= 1 || l->head == NULL) {
    list_add_to_front(l, value);
    return;
  }

  // stop at the node BEFORE the insertion point (position index-1)
  node_t *curr = l->head;
  int i = 1;
  while (i < index - 1 && curr->next != NULL) {
    curr = curr->next;
    i++;
  }

  node_t *n = getNode(value);
  n->next = curr->next;
  curr->next = n;
}

elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) return -1;      // -1 signals "nothing to remove"

  node_t *victim = l->head;
  elem value = victim->value;
  l->head = victim->next;
  free(victim);
  return value;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) return -1;

  // only one node: the head itself is the victim
  if (l->head->next == NULL) {
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value;
  }

  // stop at the SECOND-TO-LAST node so we can unlink the last one
  node_t *curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }

  elem value = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return value;
}

elem list_remove_at_index(list_t *l, int index) {
  if (l->head == NULL) return -1;
  if (index <= 1) return list_remove_from_front(l);

  // stop at the node BEFORE the one being removed
  node_t *curr = l->head;
  int i = 1;
  while (i < index - 1 && curr->next != NULL) {
    curr = curr->next;
    i++;
  }

  if (curr->next == NULL) return -1;   // index past the end

  node_t *victim = curr->next;
  elem value = victim->value;
  curr->next = victim->next;           // unlink before freeing
  free(victim);
  return value;
}

bool list_is_in(list_t *l, elem value) {
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  return false;
}

elem list_get_elem_at(list_t *l, int index) {
  if (index < 1) return -1;

  node_t *curr = l->head;
  int i = 1;
  while (curr != NULL) {
    if (i == index) return curr->value;
    curr = curr->next;
    i++;
  }
  return -1;                           // index past the end
}

int list_get_index_of(list_t *l, elem value) {
  node_t *curr = l->head;
  int i = 1;
  while (curr != NULL) {
    if (curr->value == value) return i;
    curr = curr->next;
    i++;
  }
  return -1;                           // not found
}
