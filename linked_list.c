#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *n = calloc(1, sizeof(struct list_node));
  n->value = value;

  return n;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *n = new_node(value);
  n->next = list->head;
  list->head = n;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *n = new_node(value);
  if (list->head == NULL) { // First node
    list->head = n;
    return;
  }

  struct list_node *q = list->head;
  while ((q->next) != NULL) {
    q = q->next;
  }
  q->next = n;
}

// Returns the value of the removed node
size_t remove_from_head(struct linked_list *list) {
  struct list_node *n = list->head;
  size_t value = n->value;
  list->head = n->next;
  free(n);
  return value;
}

size_t remove_from_tail(struct linked_list *list) {

  if (list->head->next == NULL) {
    size_t value = list->head->value;
    free(list->head);
    list->head = NULL;
    return value;
  }

  struct list_node *prev = list->head;
  struct list_node *curr = prev->next;
  
  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }
  
  size_t value = curr->value;
  prev->next = NULL;
  free(curr);
  return value;
}

void free_list(struct linked_list list) {
  struct list_node *current = list.head;
  struct list_node *next;
  
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
