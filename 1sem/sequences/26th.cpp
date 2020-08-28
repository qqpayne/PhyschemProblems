#include <stdio.h>

/*
Подсчёт числа локальных максимумов последовательности целых чисел
Написано 02.12.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

int growing(FILE *file);

int main()
{
    FILE *inFile = fopen("input.txt", "rt");
    int numb = growing(inFile);
    fclose(inFile);

    FILE *outFile = fopen("output.txt", "wt");
    fprintf(outFile, "%d\n", numb);
    fclose(outFile);
    return 0;
}

int growing(FILE *file)
{
    int x, prev, numb = 0;
    bool suspected = false;
    fscanf(file, "%d", &prev);
    while (fscanf(file, "%d", &x) == 1)
    {
        // если точка была подозрительной на максимум, и следующий элемент уже не является большИм
        // то мы прибавляем 1 к счетчику локальных максимумов
        if ((x <= prev) && suspected)
            ++numb;

        // если элемент больше предыдущего, то точка подозрительна на максимум
        if (x >= prev)
            suspected = true;
        else
            suspected = false;

        prev = x;
    }
    return numb;
}