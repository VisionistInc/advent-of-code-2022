#include "../lib/inc/Utils.h"

void updateCrt(char *crt, int val, int cycle)
{
    cycle -= 1;
    if (abs(val - ((cycle) % 40)) <= 1)
    {
        crt[cycle] = '#';
    }
}

void updateStrength(int *strength, int reading, int cycle)
{
    if ((cycle - 20) % 40 == 0)
    {
        *strength = *strength + (reading * cycle);
    }
}

int main()
{
    node *list = readInFile("input");
    node *item = list;

    int reg = 1;
    int strength = 0;
    int cycle = 0;
    char crt[240];
    memset(crt, ' ', 240);

    do
    {
        char *str;
        LIST_NEXT(item, str);

        cycle++;
        updateStrength(&strength, reg, cycle);
        updateCrt(crt, reg, cycle);

        if (str[0] == 'a')
        {
            int val = strtol(str + 5, NULL, 10);
            cycle++;
            updateStrength(&strength, reg, cycle);
            updateCrt(crt, reg, cycle);
            reg += val;
        }

        if (cycle == 240)
        {
            break;
        }

    } while (item != list);

    printf("Part 1: %d\n", strength);
    printf("Part 2:");
    for (int i = 0; i < 240; i++)
    {
        if ((i % 40) == 0)
        {
            printf("\n");
        }
        printf("%c", crt[i]);
    }
    printf("\n");

    return 0;
}