#include "../lib/inc/Utils.h"

void printStacks(node **stacks)
{
    for (int i = 0; i < 9; i++)
    {
        if (stacks[i] == NULL)
        {
            break;
        }
        printf("%c", *(char *)(stacks[i]->prev->data));
    }

    printf("\n");
}

int main()
{
    node *list = readInFile("input");

    node *item = list;
    node *part1[9] = {};
    node *part2[9] = {};
    int i;

    do
    {
        char *str;
        LIST_NEXT(item, str);

        char *pos = strchr(str, '[');

        /* check to see if we got past the boxes */
        if (pos == NULL)
        {
            /* get the empty line */
            LIST_NEXT(item, str);
            break;
        }

        /* find all the boxes */
        while (pos != NULL)
        {
            int i = (pos - str) / 4;
            LIST_ADDITEM_START(&part1[i], pos + 1);
            LIST_ADDITEM_START(&part2[i], pos + 1);
            pos = strchr(pos + 1, '[');
        }

    } while (item != list);

    do
    {
        char *str;
        LIST_NEXT(item, str);

        uint num, from, to;

        sscanf(str, "move %d from %d to %d", &num, &from, &to);

        node *tmp = NULL;
        for (i = 0; i < num; i++)
        {
            node *n = LIST_REMOVE_END(&part1[from - 1]);
            LIST_ADDNODE_END(&part1[to - 1], n);

            n = LIST_REMOVE_END(&part2[from - 1]);
            LIST_ADDNODE_END(&tmp, n);
        }

        for (i = 0; i < num; i++)
        {
            node *n = LIST_REMOVE_END(&tmp);
            LIST_ADDNODE_END(&part2[to - 1], n);
        }

    } while (item != list);

    printf("Part 1: ");
    printStacks(part1);

    printf("Part 2: ");
    printStacks(part2);

    return 0;
}