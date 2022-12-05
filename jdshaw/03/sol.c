#include "../lib/inc/Utils.h"

uint priority(char c)
{
    if (c >= 'a')
    {
        return 1 + (c - 'a');
    }

    return 27 + (c - 'A');
}

int main()
{
    node *list = readInFile("input");

    node *item = list;
    uint total = 0;
    char *str;

    do
    {
        GET_NEXT(item, str);

        int n = strlen(str) - 1;
        int i;

        for (i = 0; i < (n / 2); i++)
        {
            if (strchr(&str[n / 2], str[i]))
            {
                total += priority(str[i]);
                break;
            }
        }
    } while (item != list);

    printf("Part 1: %d\n", total);

    total = 0;

    char *elf1 = NULL;
    char *elf2 = NULL;

    do
    {
        GET_NEXT(item, str);

        if (elf1 == NULL)
        {
            elf1 = str;
            continue;
        }

        if (elf2 == NULL)
        {
            elf2 = str;
            continue;
        }

        while (*str != '\n')
        {
            if (strchr(elf1, *str) && strchr(elf2, *str))
            {
                total += priority(*str);
                break;
            }
            str++;
        }
        elf1 = NULL;
        elf2 = NULL;
    } while (item != list);

    printf("Part 2: %d\n", total);

    return 0;
}