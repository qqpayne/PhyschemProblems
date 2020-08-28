#include <stdio.h>

/*
Подсчёт количества строго возрастающих участков последовательности целых чисел
Написано 02.12.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

int locMax(FILE *file);

int main()
{
    FILE *inFile = fopen("input.txt", "rt");
    int numb = locMax(inFile);
    fclose(inFile);

    FILE *outFile = fopen("output.txt", "wt");
    fprintf(outFile, "%d\n", numb);
    fclose(outFile);
    return 0;
}

int locMax(FILE *file)
{
    int x, prev, numb = 0, counter = 1;
    fscanf(file, "%d", &prev);
    while (fscanf(file, "%d", &x) == 1)
    {
        if (x > prev)
            ++counter;
        else
        {
            // строго возрастающими участками считаем только участки содержащие два элемента и более
            if (counter >= 2)
                ++numb;
            counter = 1;
        }
        prev = x;
    }
    return numb;
}