#include "../lib/inc/Utils.h"

uint part2(char i, char j)
{
    uint base = 3 * (j - 'X');

    i = i - 'A';

    char add = 0;

    if (j == 'X')
    {
        add = 2;
    }
    else if (j == 'Z')
    {
        add = 1;
    }

    return base + 1 + ((i + add) % 3);
}

uint part1(char i, char j)
{
    j = j - 'X';
    i = i - 'A';

    /* tie */
    if (j == i)
    {
        return j + 4;
    }

    if (j == ((i + 1) % 3))
    {
        return 7 + j;
    }

    return j + 1;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;
    uint score1 = 0;
    uint score2 = 0;

    do
    {
        char *str;
        LIST_NEXT(item, str);

        score1 += part1(str[0], str[2]);
        score2 += part2(str[0], str[2]);
    } while (item != list);

    printf("Part 1: %d\n", score1);
    printf("Part 2: %d\n", score2);

    return 0;
}