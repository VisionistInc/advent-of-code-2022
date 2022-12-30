#include "../lib/inc/Utils.h"

/* assume big enough */
char gCave[1000][1000];

/* track max depth */
uint gDepth;

/* fill in the map */
void addSegment(uint x1, uint y1, uint x2, uint y2)
{
    /* rearrange if necessary */
    if (x1 > x2)
    {
        uint x = x2;
        x2 = x1;
        x1 = x;
    }
    if (y1 > y2)
    {
        uint y = y2;
        y2 = y1;
        y1 = y;
    }

    /* set new extremes */
    gDepth = gDepth > y1 ? gDepth : y1;

    /* fill in */
    for (uint x = x1; x <= x2; x++)
    {
        for (uint y = y1; y <= y2; y++)
        {
            gCave[x][y] = '#';
        }
    }
}

/* parse the input line */
void addLine(char *line)
{
    uint x1, x2, y1, y2;

    /* grab first coordinates */
    x1 = strtoul(line, &line, 10);

    /* move past comma */
    line++;
    y1 = strtoul(line, &line, 10);

    /* move past arrow */
    line += 4;
    while (true)
    {
        /* grab second coordinates */
        x2 = strtoul(line, &line, 10);

        /* move past comma */
        line++;
        y2 = strtoul(line, &line, 10);

        /* fill in map */
        addSegment(x1, y1, x2, y2);

        /* end of line, we are done */
        if (*line == '\n')
        {
            return;
        }

        /* second coordinates become first coordinates */
        x1 = x2;
        y1 = y2;

        /* move past arrow */
        line += 4;
    }
}

/* move sand down the map till it stops */
bool dropSand()
{
    /* start at 500,0 */
    uint x = 500;
    uint y = 0;
    while (true)
    {
        /* go down ? */
        if (gCave[x][y + 1] == ' ')
        {
            y++;
        }
        /* go down to left? */
        else if (gCave[x - 1][y + 1] == ' ')
        {
            x--;
            y++;
        }
        /* go down to right? */
        else if (gCave[x + 1][y + 1] == ' ')
        {
            x++;
            y++;
        }
        /* no where else to move, place sand on map*/
        else
        {
            gCave[x][y] = 'o';
            break;
        }
    }

    /* if we've gone past the depth for part 1, return true */
    if (y >= gDepth)
    {
        return true;
    }
    return false;
}

void printCave()
{
    uint min = 1000;
    uint max = 0;

    /* grab min and max x */
    for (uint y = 0; y < gDepth + 2; y++)
    {
        for (uint x = 0; x < 1000; x++)
        {
            if (gCave[x][y] != ' ')
            {
                min = x < min ? x : min;
                max = x > max ? x : max;
            }
        }
    }

    /* print out cave */
    for (uint y = 0; y <= gDepth + 2; y++)
    {
        for (uint x = min - 3; x <= max + 3; x++)
        {
            printf("%c", gCave[x][y]);
        }
        printf("\n");
    }
}

int main()
{
    node *list = readInFile("input");
    node *item = list;

    /* set global vars */
    memset(gCave, ' ', sizeof(gCave));
    gDepth = 0;

    uint part1 = 0;

    /* rad all in and build out map */
    do
    {
        char *line;
        LIST_NEXT(item, line);

        addLine(line);

    } while (item != list);

    /* add floor of cave for part 2 */
    for (int x = 0; x < 1000; x++)
    {
        gCave[x][gDepth + 2] = '#';
    }

    uint count = 0;

    while (true)
    {
        count++;
        if (dropSand())
        {
            /* see if we have already captured part 1 */
            if (part1 == 0)
            {
                part1 = count - 1;
            }
        }

        /* filled to top? */
        if (gCave[500][0] == 'o')
        {
            break;
        }
    }

    // printCave();

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", count);

    return 0;
}