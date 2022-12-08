#include "../lib/inc/Utils.h"

bool duplicate(char *s, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (s[i] == s[j])
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    node *list = readInFile("input");
    char *str = list->data;

    char *s = str;
    while (duplicate(s, 4))
    {
        s++;
    }

    printf("Part 1: %ld\n", (s - str) + 4);

    s = str;
    while (duplicate(s, 14))
    {
        s++;
    }

    printf("Part 2: %ld\n", (s - str) + 14);

    return 0;
}