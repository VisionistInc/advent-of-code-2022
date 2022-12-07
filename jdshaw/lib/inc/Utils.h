#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ERROR(a) \
    printf(a);   \
    exit(-1)

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short ushort;

#define LONG(a) strtol(a, NULL, 10)

typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} node;

typedef void (*itrFunc)(void *);

void list_addNodeToList(node **list, node *n, bool end);

void list_addItemToList(node **list, void *item, bool end);

node *list_removeNodeFromList(node **list, bool end);

void list_iterate(node *list, itrFunc f);

node *readInFile(char *name);

#define LIST_NEXT(a, b) \
    b = a->data;        \
    a = a->next

#define LIST_PREV(a, b) \
    b = a->data;        \
    a = a->prev

#define LIST_ADDITEM_START(a, b) list_addItemToList(a, b, 0)
#define LIST_ADDITEM_END(a, b) list_addItemToList(a, b, 1)
#define LIST_ADDNODE_START(a, b) list_addNodeToList(a, b, 0)
#define LIST_ADDNODE_END(a, b) list_addNodeToList(a, b, 1)
#define LIST_REMOVE_START(a) list_removeNodeFromList(a, 0)
#define LIST_REMOVE_END(a) list_removeNodeFromList(a, 1)

#endif