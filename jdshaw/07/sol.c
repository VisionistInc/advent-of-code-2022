#include "../lib/inc/Utils.h"

typedef struct Entry
{
    char *name;
    uint size;
    struct Entry *parent;
    struct Entry **children;
    uint numChildren;
} Entry;

Entry *find(char *name, Entry *parent)
{
    if (parent == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < parent->numChildren; i++)
    {
        if (strcmp(name, parent->children[i]->name) == 0)
        {
            return parent->children[i];
        }
    }
    return NULL;
}

Entry *newEntry(char *name, uint size, Entry *parent)
{
    Entry *e = find(name, parent);
    if (e != NULL)
    {
        return e;
    }

    e = malloc(sizeof(Entry));
    e->name = name;
    e->size = size;
    e->parent = parent;
    e->children = NULL;
    e->numChildren = 0;

    if (parent != NULL)
    {
        Entry **new;
        new = malloc(sizeof(Entry *) * (parent->numChildren + 1));
        for (int i = 0; i < parent->numChildren; i++)
        {
            new[i] = parent->children[i];
        }
        parent->numChildren += 1;
        new[parent->numChildren - 1] = e;
        free(parent->children);
        parent->children = new;
    }

    return e;
}

Entry *getChild(Entry *e, char *name)
{
    for (int i = 0; i < e->numChildren; i++)
    {
        if (strcmp(name, e->children[i]->name) == 0)
        {
            return e->children[i];
        }
    }
    ERROR("directory not found");
}

uint updateDirSize(Entry *e)
{
    uint size = 0;

    for (int i = 0; i < e->numChildren; i++)
    {
        size += updateDirSize(e->children[i]);
    }

    e->size += size;

    return e->size;
}

uint sumDirSize(Entry *e, uint max)
{
    uint sum = 0;

    if (e->numChildren == 0)
    {
        return 0;
    }

    for (int i = 0; i < e->numChildren; i++)
    {
        sum += sumDirSize(e->children[i], max);
    }

    if (e->size <= max)
    {
        sum += e->size;
    }

    return sum;
}

uint findSmallest(Entry *e, uint smallest, uint needed)
{
    for (int i = 0; i < e->numChildren; i++)
    {
        smallest = findSmallest(e->children[i], smallest, needed);
    }

    if (e->size >= needed)
    {
        if (e->size < smallest)
        {
            return e->size;
        }
    }
    return smallest;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;

    Entry *root = newEntry("/", 0, NULL);
    Entry *current = root;

    do
    {
        char *str;
        LIST_NEXT(item, str);
        int n = strlen(str);
        str[n - 1] = 0;

        if (strncmp(str, "$ cd ", 5) == 0)
        {
            if (strcmp(str + 5, "/") == 0)
            {
                current = root;
            }
            else if (strcmp(str + 5, "..") == 0)
            {
                if (current->parent != NULL)
                {
                    current = current->parent;
                }
            }
            else
            {
                current = getChild(current, str + 5);
            }
        }
        else if (strcmp(str, "$ ls") == 0)
        {
            continue;
        }
        else if (strncmp(str, "dir ", 4) == 0)
        {
            newEntry(str + 4, 0, current);
        }
        else
        {
            int sz = strtoul(str, &str, 10);
            newEntry(str + 1, sz, current);
        }
    } while (item != list);

    updateDirSize(root);

    uint sum = sumDirSize(root, 100000);

    printf("Part 1: %d\n", sum);

    uint needed = 30000000 - (70000000 - root->size);

    uint smallest = findSmallest(root, root->size, needed);

    printf("Part 2: %d\n", smallest);

    return 0;
}