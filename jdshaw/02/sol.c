#include "../lib/inc/Utils.h"

uint part2(char i, char j)
{
    uint base = 3 * (j - 'X');

    char x;

    if (j == 'X')
    {
        x = i == 'A' ? 'C' : i - 1;
    }
    else if (j == 'Y')
    {
        x = i;
    }
    else
    {
        x = i == 'C' ? 'A' : i + 1;
    }

    return base + (x - 'A' + 1);
}

uint part1(char i, char j)
{
    j = j - ('X' - 'A');

    uint base = j - 'A' + 1;

    /* tie */
    if (j == i)
    {
        return base + 3;
    }

    if ((i == 'A' && j == 'B') ||
        (i == 'B' && j == 'C') ||
        (i == 'C' && j == 'A'))
    {
        return 6 + base;
    }

    return base;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;
    uint score1 = 0;
    uint score2 = 0;
    char *str;

    do
    {
        GET_NEXT(item, str);

        score1 += part1(str[0], str[2]);
        score2 += part2(str[0], str[2]);
    } while (item != list);

    printf("Part 1: %d\n", score1);
    printf("Part 2: %d\n", score2);

    return 0;
}