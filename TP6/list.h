#ifndef _LIST_H_
#define _LIST_H_

struct list
{
  struct list *next;
  int data;
};

// Prints a list on the terminal.
// Use the same format used in the examples.
void list_print(const struct list* l);

// Inserts a new element at the beginning of the list.
// This new element must contain "data".
// The pointer to the list is updated.
// (It must point to the new element.)
void list_push_front(struct list** list, int data);

// Removes and frees the first element in the list.
// The "data" field of the element is returned.
// The pointer to the list is updated
// (it must point to the next element).
// We assume that the list is not empty
// (it contains at least one element).
int list_pop_front(struct list** list);

// Returns true (1) if the element pointed to by "elm" is in the list.
// Otherwise, returns false (0).
int list_contains(const struct list* l, const struct list* elm);

// Inserts a new element that contains "data" after
// the element pointed to by "elm".
// If the list is empty and "elm" is NULL, inserts
// the new element as a first element
// (the pointer to the list is updated).
// If "elm" is not in the list, returns false (0).
// If the new element is inserted, returns true (1).
int list_insert_after(struct list** l, struct list* elm, int data);

// Inserts a new element that contains "data" before
// the element pointed to by "elm".
// If the list is empty and "elm" is NULL, inserts
// the new element as a first element.
// If the new element is inserted at the beginning of the list,
// the pointer to the list is updated.
// If "elm" is not in the list, returns false (0).
// If the new element is inserted, returns true (1).
int list_insert_before(struct list** l, const struct list* elm, int data);

// Removes and frees all the elements that contain "data".
// If the first element is deleted, the pointer to the list is updated.
void list_delete(struct list** l, int data);

// Removes and frees all the elements.
// The pointer to the list must be set to NULL.
void list_destroy(struct list** l);

#endif
