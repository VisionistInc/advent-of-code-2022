#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

#define GET_NEXT(a, b) \
    b = a->data;       \
    a = a->next

typedef void (*itrFunc)(void *);

void list_iterate(node *list, itrFunc f);

node *readInFile(char *name);

#endif