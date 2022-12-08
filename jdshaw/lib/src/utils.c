#include "../inc/Utils.h"

void printList(node *list)
{
    node *item = list;

    do
    {
        printf("%p %p %p\n", item->data, item->prev, item->next);
        item = item->next;
    } while (item != list);
}

void list_addNodeToList(node **list, node *n, bool end)
{
    if (list == NULL || n == NULL)
    {
        ERROR("addNode: NULL list\n");
    }

    if (n == NULL)
    {
        ERROR("NULL node\n");
    }

    if (*list == NULL)
    {

        *list = n;
        n->next = n;
        n->prev = n;
        return;
    }

    n->prev = (*list)->prev;
    n->next = *list;
    (*list)->prev->next = n;
    (*list)->prev = n;

    if (!end)
    {
        *list = n;
    }
}

void list_addItemToList(node **list, void *item, bool end)
{
    if (list == NULL)
    {
        ERROR("addItem: NULL list\n");
    }

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        ERROR("list malloc\n");
    }

    n->data = item;

    list_addNodeToList(list, n, end);
}

node *
list_removeNodeFromList(node **list, bool end)
{
    if (list == NULL)
    {
        ERROR("remove: NULL list\n");
    }

    if (*list == NULL)
    {
        return NULL;
    }

    node *n = *list;

    if (n == n->next)
    {
        *list = NULL;
        return n;
    }

    if (end)
    {
        n = n->prev;
    }
    else
    {
        *list = n->next;
    }

    n->prev->next = n->next;
    n->next->prev = n->prev;

    return n;
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
    char buf[8192];
    node *list = NULL;
    FILE *f;

    f = fopen(name, "r");
    if (f == NULL)
    {
        ERROR("can't open file");
    }

    while (fgets(buf, 8192, f) != NULL)
    {
        int n = strlen(buf);
        char *val = malloc(n + 1);
        memcpy(val, buf, n + 1);
        LIST_ADDITEM_END(&list, val);
        buf[0] = 0;
    }

    if (list == NULL)
    {
        ERROR("empty file");
    }

    return list;
}
