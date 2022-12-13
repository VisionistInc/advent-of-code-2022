#include "../lib/inc/Utils.h"

typedef struct Monkey
{
    node *items;
    char *oper;
    ullong test;
    ullong pass;
    ullong fail;
    ullong inspect;
} Monkey;

void initMonkey(Monkey *m)
{
    m->items = NULL;
    m->oper = NULL;
    m->test = 0;
    m->pass = 0;
    m->fail = 0;
    m->inspect = 0;
}

ullong getVal(char **str, ullong val)
{
    if (strncmp("old", *str, 3) == 0)
    {
        *str = (*str) + 3;
        return val;
    }

    val = strtoul(*str, str, 10);
    return val;
}

ullong updateWorry(char *oper, ullong val)
{
    ullong a, b;
    char op;

    a = getVal(&oper, val);
    op = oper[1];
    oper += 3;
    b = getVal(&oper, val);

    if (op == '+')
    {
        return a + b;
    }
    if (op == '-')
    {
        return a - b;
    }
    if (op == '*')
    {
        return a * b;
    }
    if (op == '/')
    {
        return a / b;
    }
    if (op == '%')
    {
        return a % b;
    }

    printf("%c :", op);
    ERROR("Unknown op\n");
    return 0;
}

ullong solve(ullong relief, ullong numRounds)
{
    node *list = readInFile("input");
    node *item = list;
    Monkey *monkies = NULL;
    ullong numMonkies = 0;

    ullong supermod = 1;

    do
    {
        char *str;
        LIST_NEXT(item, str);

        while (strstr(str, "Monkey ") == NULL)
        {
            LIST_NEXT(item, str);
        }

        numMonkies++;
        monkies = realloc(monkies, ((numMonkies + 1) * sizeof(Monkey)));

        initMonkey(&monkies[numMonkies - 1]);

        LIST_NEXT(item, str);
        str = str + 18;
        char *next = str;
        ullong num = strtol(str, &next, 10);
        while (next != str)
        {
            ullong *val = malloc(sizeof(ullong));
            *val = num;
            LIST_ADDITEM_END(&(monkies[numMonkies - 1].items), val);
            str = next + 1;
            num = strtol(str, &next, 10);
        }

        LIST_NEXT(item, str);
        monkies[numMonkies - 1].oper = str + 19;

        LIST_NEXT(item, str);
        monkies[numMonkies - 1].test = strtol(str + 21, NULL, 10);

        /* secret sauce that i had to look up to solve part 2 */
        supermod *= monkies[numMonkies - 1].test;

        LIST_NEXT(item, str);
        monkies[numMonkies - 1].pass = strtol(str + 29, NULL, 10);

        LIST_NEXT(item, str);
        monkies[numMonkies - 1].fail = strtol(str + 30, NULL, 10);

    } while (item != list);

    for (int round = 0; round < numRounds; round++)
    {
        for (int i = 0; i < numMonkies; i++)
        {
            Monkey *m = &(monkies[i]);
            while (m->items != NULL)
            {
                m->inspect++;
                node *item = LIST_REMOVE_START(&(m->items));
                ullong *v = item->data;
                *v = updateWorry(m->oper, *v);
                /* use least-common denominator to reduce large numbers */
                *v = (*v) % supermod;
                *v = (*v) / relief;
                if (((*v) % m->test) == 0)
                {
                    LIST_ADDNODE_END(&(monkies[m->pass].items), item);
                }
                else
                {
                    LIST_ADDNODE_END(&(monkies[m->fail].items), item);
                }
            }
        }
    }

    ullong inspects[2] = {0};

    for (int i = 0; i < numMonkies; i++)
    {
        ullong x = monkies[i].inspect;
        if (x > inspects[0])
        {
            inspects[1] = inspects[0];
            inspects[0] = x;
        }
        else if (x > inspects[1])
        {
            inspects[1] = x;
        }
    }

    return inspects[0] * inspects[1];
}

int main()
{
    printf("Part 1: %llu\n", solve(3, 20));
    printf("Part 2: %llu\n", solve(1, 10000));

    return 0;
}