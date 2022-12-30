#include "../lib/inc/Utils.h"

typedef struct range
{
    long s;
    long e;
} range;

typedef struct ranges
{
    long n;
    range *r;
} ranges;

/* add a new range to the end */
void addRange(ranges *r, long s, long e)
{
    r->n++;
    r->r = realloc(r->r, r->n * sizeof(range));
    r->r[r->n - 1].s = s;
    r->r[r->n - 1].e = e;
}

/* remove a range at index i */
void removeRange(ranges *r, long i)
{
    memmove(&r->r[i], &r->r[i + 1], ((r->n - 1) - i) * sizeof(range));
    r->n--;
}

/* iterate over ranges, and see if any overlap.  if so, combine first overlap and return true, otherwise false */
bool combineRange(ranges *r)
{
    for (long i = 0; i < r->n - 1; i++)
    {
        range *r1 = &(r->r[i]);
        range *r2 = &(r->r[i + 1]);

        /* r2 start before r1 and end after where r1 starts? */
        if (r2->s < r1->s && r2->e >= r1->s)
        {
            /* reset r1 start to earlier r2 start */
            r1->s = r2->s;

            /* if r2 extends past r1, set r1 end to further r2 end */
            if (r2->e > r1->e)
            {
                r1->e = r2->e;
            }

            /* now that r1 is adjusted to include r2, remove r2 */
            removeRange(r, i + 1);
            return true;
        }

        /* r2 start in the middle if r1? */
        if (r2->s >= r1->s && r2->s <= r1->e)
        {
            /* if r2 ends after r1, adjust r1 end to further r2 end */
            if (r2->e > r1->e)
            {
                r1->e = r2->e;
            }
            /* now that r1 is adjusted to include r2, remove r2 */
            removeRange(r, i + 1);
            return true;
        }
    }

    return false;
}

void combineRanges(ranges *r)
{
    /* as long as we can successfully combine ranges, keep doing it */
    while (combineRange(r))
    {
        ;
    }
}

/* assume all ranges have been combined, so beacon should only show once, if at all */
void removeBeacon(ranges *r, long b)
{
    for (long i = 0; i < r->n; i++)
    {
        /* if the range is length 1 and is the beacon, just remove it */
        if (r->r[i].s == b && r->r[i].e == b)
        {
            removeRange(r, i);
        }
        /* if beacon is start of range, just adjust start */
        else if (r->r[i].s == b)
        {
            r->r[i].s++;
        }
        /* if beacon is end of range, just adjust end */
        else if (r->r[i].e == b)
        {
            r->r[i].e--;
        }
        /* if beacon is middle of range, create new range and adjust existing range */
        else if (r->r[i].s < b && r->r[i].e > b)
        {
            addRange(r, b + 1, r->r[i].e);
            r->r[i].e = b - 1;
        }
    }
    return;
}

/* see if we can find a valid beacon in the range */
long findBeacon(ranges *r)
{
    long i = 0;
    while (i <= 4000000)
    {
        bool hit = false;
        for (long n = 0; n < r->n; n++)
        {
            /* if i is in range, increase i to the end of the range */
            if (i >= r->r[n].s && i <= r->r[n].e)
            {
                i = r->r[n].e + 1;
                hit = true;
                break;
            }
        }

        /* never found i in the range, we have our beacon */
        if (!hit)
        {
            return i;
        }
    }
    return -1;
}

#define PART1 2000000

int main()
{
    node *list = readInFile("input");
    node *item = list;

    ranges r;
    r.n = 0;
    r.r = NULL;

    long numBeacons = 0;
    long *beacons = NULL;

    long part1 = 0;
    long part2 = 0;

    long *input = NULL;
    long *ptr;
    long nLines = 0;

    /* read in all the input from text once */
    do
    {
        char *line;
        LIST_NEXT(item, line);
        nLines++;

        input = realloc(input, (4 * nLines * sizeof(long)));
        ptr = &input[(nLines - 1) * 4];

        line += 12;
        *ptr = strtoll(line, &line, 10);
        line += 4;
        ptr++;
        *ptr = strtoll(line, &line, 10);
        line += 25;
        ptr++;
        *ptr = strtoll(line, &line, 10);
        line += 4;
        ptr++;
        *ptr = strtoll(line, &line, 10);

    } while (item != list);

    /* for all possible rows */
    for (long y = 0; y <= 4000000; y++)
    {
        /* clear out, init from previous iteration */
        numBeacons = 0;
        free(beacons);
        beacons = NULL;
        free(r.r);
        r.n = 0;
        r.r = NULL;

        for (int l = 0; l < nLines; l++)
        {
            /* pull out the values for the specific line */
            long sx = input[l * 4];
            long sy = input[l * 4 + 1];
            long bx = input[l * 4 + 2];
            long by = input[l * 4 + 3];

            /* we only care about dqing beacons for part 1 */
            if (by == y && y == PART1)
            {
                numBeacons++;
                beacons = realloc(beacons, numBeacons * sizeof(long));
                beacons[numBeacons - 1] = bx;
            }

            /* determine distance to beacon */
            long distance = abs(bx - sx) + abs(by - sy);

            /* determine distance from sensor to current row */
            long base = abs(sy - y);

            /* if current row is in range of sensor, figure out how much of row is in range */
            if (base <= distance)
            {
                long start = sx - (distance - base);
                long end = sx + (distance - base);
                addRange(&r, start, end);
            }
        }

        /* we've got all the ranges each sensor can hit for the current row, now let's reduce them */
        combineRanges(&r);

        /* see if there are any free spots our hidden beacon could be */
        long x = findBeacon(&r);
        if (x != -1)
        {
            /* if we found it, yay, save off part 2, and set y to get to part 1 quicker */
            part2 = x * 4000000 + y;
            y = PART1 - 1;
        }

        if (y == PART1)
        {
            /* remove any beacons from the range */
            for (int i = 0; i < numBeacons; i++)
            {
                removeBeacon(&r, beacons[i]);
            }

            /* add up all the ranges */
            for (int i = 0; i < r.n; i++)
            {
                part1 += (r.r[i].e - r.r[i].s + 1);
            }

            /* if we've already solved part 2, we can be done */
            if (part2 != 0)
            {
                break;
            }
        }
    }

    printf("Part 1: %ld\n", part1);
    printf("Part 2: %ld\n", part2);

    return 0;
}