#include "../lib/inc/Utils.h"

/* return list length, not including opening/closing brackets */
uint getListLen(char *l)
{
    uint d = 1;
    uint n = 1;
    l++;
    while (d > 0)
    {
        if (*l == '[')
        {
            d++;
        }
        if (*l == ']')
        {
            d--;
        }
        n++;
        l++;
    }

    return n - 2;
}

/* 0 means list are equal, -1 means right list is less, 1 means left list is less */
int compareList(char *left, char *right, uint nl, uint nr)
{
    char *lend = left + nl;
    char *rend = right + nr;
    while (left < lend && right < rend)
    {
        if (*left == ',')
        {
            left++;
        }
        if (*right == ',')
        {
            right++;
        }
        /* compare sub lists*/
        if (*left == '[' && *right == '[')
        {
            nl = getListLen(left);
            nr = getListLen(right);
            int result = compareList(left + 1, right + 1, nl, nr);
            if (result != 0)
            {
                return result;
            }
            left += (nl + 2);
            right += (nr + 2);
        }
        /* convert right to a list and compare sub lists */
        else if (*left == '[')
        {
            char *end;
            strtoul(right, &end, 10);
            nr = end - right;
            nl = getListLen(left);
            int result = compareList(left + 1, right, nl, nr);
            if (result != 0)
            {
                return result;
            }
            left += (nl + 2);
            right += (nr);
        }
        /* convert left to a list and compare sub lists */
        else if (*right == '[')
        {
            char *end;
            strtoul(left, &end, 10);
            nl = end - left;
            nr = getListLen(right);
            int result = compareList(left, right + 1, nl, nr);
            if (result != 0)
            {
                return result;
            }
            left += (nl);
            right += (nr + 2);
        }
        /* compare values */
        else
        {
            uint l = strtoul(left, &left, 10);
            uint r = strtoul(right, &right, 10);
            if (l < r)
            {
                return 1;
            }
            if (r < l)
            {
                return -1;
            }
            /* don't do anything for equal */
        }
    }

    /* if we got to the end of both lists, we are equal */
    if (left == lend && right == rend)
    {
        return 0;
    }

    /* got to left list end first, it is less */
    if (left == lend)
    {
        return 1;
    }

    /* got to right list end first, it is less */
    return -1;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;

    uint pair = 0;
    uint part1 = 0;
    uint div2Cnt = 0;
    uint div6Cnt = 0;

    do
    {
        char *left;
        char *right;
        char *div2 = "[2]";
        char *div6 = "[6]";
        LIST_NEXT(item, left);
        LIST_NEXT(item, right);
        pair += 1;

        uint nl = getListLen(left);
        uint nr = getListLen(right);

        int result = compareList(left + 1, right + 1, nl, nr);
        if (result != -1)
        {
            part1 += pair;
        }
        result = compareList(div2, left + 1, 3, nl);
        if (result != 1)
        {
            div2Cnt++;
        }
        result = compareList(div2, right + 1, 3, nr);
        if (result != 1)
        {
            div2Cnt++;
        }

        result = compareList(div6, left + 1, 3, nl);
        if (result != 1)
        {
            div6Cnt++;
        }

        result = compareList(div6, right + 1, 3, nr);
        if (result != 1)
        {
            div6Cnt++;
        }

        if (item != list)
        {
            LIST_NEXT(item, left);
        }

    } while (item != list);

    printf("Part 1: %d\n", part1);
    /* div2 position is one above all the ones it was greater than */
    /* div6 position is one above all the ones it was greater than + one for div2 */
    printf("Part 2: %d\n", (div2Cnt + 1) * (div6Cnt + 2));

    return 0;
}