#include "../inc/Utils.h"

node *
list_addToList(node *list, void *item)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Error allocating list\n");
        return NULL;
    }

    n->data = item;

    if (list == NULL)
    {
        n->next = n;
        n->prev = n;
        return n;
    }

    n->prev = list->prev;
    list->prev = n;
    n->prev->next = n;
    n->next = list;

    return list;
}

void list_iterate(node *list, itrFunc f)
{
    node *item = list;

    if (item == NULL)
    {
        return;
    }

    do
    {
        f(item->data);
        item = item->next;
    } while (list != item);
}

node *
readInFile(char *name)
{
    char buf[2048];
    node *list = NULL;
    FILE *f;

    f = fopen(name, "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        exit(-1);
    }

    while (fgets(buf, 2048, f) != NULL)
    {
        int n = strlen(buf);
        char *val = malloc(n + 1);
        memcpy(val, buf, n + 1);
        list = list_addToList(list, val);
        buf[0] = 0;
    }

    if (list == NULL)
    {
        printf("Empty file\n");
        exit(-1);
    }

    return list;
}
