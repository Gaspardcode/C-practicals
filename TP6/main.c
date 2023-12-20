#include <stdio.h>
#include "list.h"

#define PRINT_LIST() { printf("list = "); list_print(list); printf("\n"); }
#define PRINT1(f) { printf(#f "\n"); f; }
#define PRINT2(f) { int d = f; printf(#f " -> %i\n", d); }

int main()
{
    struct list* list = NULL;
    PRINT_LIST();

    PRINT1(list_push_front(&list, 42)); struct list* l42 = list;
    PRINT1(list_push_front(&list, 72));
    PRINT1(list_push_front(&list, 13)); struct list* l13 = list;
    PRINT_LIST();

    PRINT1(list_push_front(&list, 2));
    PRINT1(list_push_front(&list, 4)); struct list* l4 = list;
    PRINT1(list_push_front(&list, 8));
    PRINT_LIST();

    PRINT2(list_pop_front(&list));
    PRINT2(list_pop_front(&list));
    PRINT_LIST();

    PRINT2(list_contains(list, l13));
    PRINT2(list_contains(list, l4));
    PRINT2(list_contains(list, NULL));
    printf("\n");

    PRINT2(list_insert_after(&list, l42, 99));
    PRINT2(list_insert_after(&list, l13, 98));
    PRINT2(list_insert_after(&list, list, 97));
    PRINT2(list_insert_after(&list, l4, 1000));
    PRINT2(list_insert_after(&list, NULL, 1000));
    PRINT_LIST();

    PRINT2(list_insert_before(&list, l42, 99));
    PRINT2(list_insert_before(&list, l13, 98));
    PRINT2(list_insert_before(&list, list, 97));
    PRINT2(list_insert_before(&list, l4, 1000));
    PRINT2(list_insert_before(&list, NULL, 1000));
    PRINT_LIST();

    PRINT1(list_delete(&list, 97));
    PRINT1(list_delete(&list, 98));
    PRINT1(list_delete(&list, 99));
    PRINT_LIST();

    PRINT1(list_destroy(&list));
    PRINT_LIST();

    PRINT1(list_delete(&list, 42));
    PRINT_LIST();

    PRINT2(list_contains(list, l13));
    PRINT2(list_contains(list, l42));
    PRINT2(list_contains(list, NULL));
    printf("\n");

    PRINT2(list_insert_after(&list, list, 100));
    PRINT_LIST();

    PRINT1(list_destroy(&list));
    PRINT_LIST();

    PRINT2(list_insert_before(&list, list, 100));
    PRINT2(list_insert_before(&list, list, 100));
    PRINT2(list_insert_before(&list, list, 100));
    PRINT2(list_insert_before(&list, list, 100));
    PRINT2(list_insert_before(&list, list, 100));
    PRINT_LIST();

    PRINT1(list_delete(&list, 99));
    PRINT_LIST();

    PRINT1(list_delete(&list, 100));
    PRINT_LIST();

    PRINT1(list_destroy(&list));

    return 0;
}

