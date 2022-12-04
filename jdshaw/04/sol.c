#include "../lib/inc/Utils.h"

int main()
{
    node *list = readInFile("input");

    node *item = list;
    uint part1 = 0;
    uint part2 = 0;

    do
    {
        char *str;
        GET_NEXT(item, str);

        uint a, b, c, d;

        sscanf(str, "%d-%d,%d-%d\n", &a, &b, &c, &d);
        if (c < a)
        {
            c = a;
            a = d;
            d = b;
            b = a;
        }

        if (d <= b)
        {
            part1++;
        }

        if (c <= b)
        {
            part2++;
        }

    } while (item != list);

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);

    return 0;
}