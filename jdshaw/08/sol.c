#include "../lib/inc/Utils.h"

int isVisible(uint **f, int line, int col, int lines, int width)
{
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
    uint val = f[line][col];
    for (int i = line - 1; i >= 0; i--)
    {
        if (f[i][col] >= val)
        {
            up = false;
        }
    }
    for (int i = line + 1; i < lines; i++)
    {
        if (f[i][col] >= val)
        {
            down = false;
        }
    }
    for (int i = col - 1; i >= 0; i--)
    {
        if (f[line][i] >= val)
        {
            left = false;
        }
    }
    for (int i = col + 1; i < width; i++)
    {
        if (f[line][i] >= val)
        {
            right = false;
        }
    }

    if (up || down || left || right)
    {
        return 1;
    }
    return 0;
}

uint scenic(uint **f, int line, int col, int lines, int width)
{
    uint up = 0;
    uint down = 0;
    uint left = 0;
    uint right = 0;

    uint val = f[line][col];
    for (int i = line - 1; i >= 0; i--)
    {
        up++;
        if (f[i][col] >= val)
        {
            break;
        }
    }
    for (int i = line + 1; i < lines; i++)
    {
        down++;
        if (f[i][col] >= val)
        {
            break;
        }
    }
    for (int i = col - 1; i >= 0; i--)
    {
        left++;
        if (f[line][i] >= val)
        {
            break;
        }
    }
    for (int i = col + 1; i < width; i++)
    {
        right++;
        if (f[line][i] >= val)
        {
            break;
        }
    }

    return up * down * left * right;
}

int main()
{
    node *list = readInFile("input");
    node *item = list;
    int numLines = 0;
    uint **forest = NULL;
    int width = strlen(item->data) - 1;

    do
    {
        char *str;
        LIST_NEXT(item, str);
        numLines++;

        uint *line = malloc(width * sizeof(uint));

        for (int i = 0; i < width; i++)
        {
            line[i] = str[i] - '0';
        }

        forest = realloc(forest, numLines * sizeof(uint *));
        forest[numLines - 1] = line;
    } while (item != list);

    uint visible = 0;
    for (int i = 0; i < numLines; i++)
    {
        for (int j = 0; j < width; j++)
        {
            visible += isVisible(forest, i, j, numLines, width);
        }
    }
    printf("Part 1: %d\n", visible);

    uint score = 0;
    for (int i = 0; i < numLines; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint s = scenic(forest, i, j, numLines, width);
            if (s > score)
            {
                score = s;
            }
        }
    }
    printf("Part 2: %d\n", score);

    return 0;
}