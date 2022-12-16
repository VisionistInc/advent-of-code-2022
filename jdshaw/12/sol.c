#include "../lib/inc/Utils.h"

uint solve(uint width, uint height, node *list, bool part2)
{
    uint end;
    uint i = 0;
    node *item = list;

    uint spaces = width * height;

    int *map = malloc(spaces * sizeof(uint));
    uint *moves = malloc(spaces * sizeof(uint));

    do
    {
        char *str;
        LIST_NEXT(item, str);

        /* for each space in row */
        for (int x = 0; x < width; x++)
        {
            char c = str[x];
            moves[i] = 0;

            /* if start, set accordingly */
            /* or if part 2 and an 'a' position */
            if (c == 'S' || (part2 && (c == 'a')))
            {
                moves[i] = 1;
                c = 'a';
            }

            /* check for end position */
            if (c == 'E')
            {
                end = i;
                c = 'z';
            }

            /* convert char to int*/
            map[i] = c - 'a' + 1;
            i += 1;
        }

    } while (item != list);

    uint round = 1;

    while (moves[end] == 0)
    {
        for (int x = 0; x < spaces; x++)
        {
            /* no need to do a move if it isn't our current round */
            /* either we got to that spot earlier or it's 0 and we haven't got there yet */
            if (moves[x] != round)
            {
                continue;
            }

            int dir[4];
            /* one row up as long as we aren't top row */
            dir[0] = x >= width ? x - width : -1;
            /* one row down as long as we aren't bottom row */
            dir[1] = x < (spaces - width) ? x + width : -1;
            /* one space left as long as we aren't first in row */
            dir[2] = (x % width) == 0 ? -1 : x - 1;
            /* one space right as long as we aren't last in row */
            dir[3] = ((x + 1) % width) == 0 ? -1 : x + 1;

            for (i = 0; i < 4; i++)
            {
                /* make sure it's valid, hasn't been visited already, and elevation is reachable */
                if ((dir[i] != -1) && (moves[dir[i]] == 0) && (map[dir[i]] <= (map[x] + 1)))
                {
                    moves[dir[i]] = round + 1;
                }
            }
        }
        round += 1;
    }

    return round - 1;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;

    uint height = 0;
    uint width = 0;

    do
    {
        char *str;
        LIST_NEXT(item, str);
        height++;
        width = strlen(str) - 1;

    } while (item != list);

    printf("Part 1: %d\n", solve(width, height, list, false));
    printf("Part 2: %d\n", solve(width, height, list, true));

    return 0;
}