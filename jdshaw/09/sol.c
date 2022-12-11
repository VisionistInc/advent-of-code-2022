#include "../lib/inc/Utils.h"

#define LEN 512

char part1[LEN][LEN] = {0};
char part2[LEN][LEN] = {0};

void update(int *x, int *y, int num)
{
    if (abs(y[0] - y[1]) == 2)
    {
        y[1] += (y[0] - y[1]) / 2;
        if (x[1] < x[0])
            x[1]++;
        else if (x[1] > x[0])
            x[1]--;
    }
    if (abs(x[0] - x[1]) == 2)
    {
        x[1] += (x[0] - x[1]) / 2;
        if (y[1] < y[0])
            y[1]++;
        else if (y[1] > y[0])
            y[1]--;
    }

    if (num == 0)
    {
        part1[x[1]][y[1]] = 1;
    }
    if (num == 8)
    {
        part2[x[1]][y[1]] = 1;
    }
}

int main()
{
    node *list = readInFile("input");
    node *item = list;
    int x[10];
    int y[10];

    for (int i = 0; i < 10; i++)
    {
        x[i] = LEN / 2;
        y[i] = LEN / 2;
    }

    part1[x[1]][y[1]] = 1;
    part2[x[9]][y[9]] = 1;

    do
    {
        char *str;
        LIST_NEXT(item, str);

        uint cnt = strtoul(str + 1, NULL, 10);

        for (int i = 0; i < cnt; i++)
        {
            switch (str[0])
            {
            case 'R':
                x[0]++;
                break;
            case 'L':
                x[0]--;
                break;
            case 'U':
                y[0]++;
                break;
            case 'D':
                y[0]--;
                break;
            default:
                ERROR("Unknown direction");
            }

            for (int j = 0; j < 9; j++)
            {
                update(&x[j], &y[j], j);
            }
        }

    } while (item != list);

    uint total1 = 0;
    uint total2 = 0;
    for (int i = 0; i < LEN; i++)
    {
        for (int j = 0; j < LEN; j++)
        {
            total1 += part1[i][j];
            total2 += part2[i][j];
        }
    }

    printf("Part 1: %d\n", total1);
    printf("Part 2: %d\n", total2);

    return 0;
}