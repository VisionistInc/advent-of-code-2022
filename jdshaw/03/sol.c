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

    do
    {
        char *str;
        LIST_NEXT(item, str);

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

    do
    {
        char *elf1, *elf2, *elf3;
        LIST_NEXT(item, elf1);
        LIST_NEXT(item, elf2);
        LIST_NEXT(item, elf3);

        while (*elf3 != '\n')
        {
            if (strchr(elf1, *elf3) && strchr(elf2, *elf3))
            {
                total += priority(*elf3);
                break;
            }
            elf3++;
        }
    } while (item != list);

    printf("Part 2: %d\n", total);

    return 0;
}