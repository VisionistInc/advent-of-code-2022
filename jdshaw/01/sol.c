#include "../lib/inc/Utils.h"

void insert(uint val, uint *list)
{
    if (val < list[0])
    {
        return;
    }

    if (val < list[1])
    {
        list[0] = val;
        return;
    }

    list[0] = list[1];

    if (val < list[2])
    {
        list[1] = val;
        return;
    }

    list[1] = list[2];
    list[2] = val;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;
    uint max[3] = {0};
    uint count = 0;

    do
    {
        char *str;
        LIST_NEXT(item, str);
        uint i = LONG(str);

        count += i;
        if (i == 0)
        {
            insert(count, max);
            count = 0;
        }
    } while (item != list);

    printf("Part 1: %d\n", max[2]);
    printf("Part 2: %d\n", max[0] + max[1] + max[2]);

    return 0;
}