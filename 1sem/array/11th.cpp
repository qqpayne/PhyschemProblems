#include <stdio.h>

/*
Возможно ли разбить целочисленный массив на два так, что сумма в первой половине равна сумме во второй
Если возможно, возвращает "точку" разбиения и сумму. Если нет, возвращает -1
Написано 4.11.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

struct pair lucky(int* arr, int arrLength);

struct pair
{
    int breakpoint, sum;
};

int main() 
{
    FILE *inFile = fopen("input.txt", "rt");
    if (inFile == NULL) 
    {
        perror("Cannot open input file");
        return (-1);
    }

    int *arr;
    int arrLength;
    if (fscanf(inFile, "%d", &arrLength) < 1 || arrLength < 0) 
    {
        printf("Incorrect input file.\n");
        return (-1);
    }

    arr = new int[arrLength];
    for (int i = 0; i < arrLength; ++i) 
    {
        if (fscanf(inFile, "%d", arr + i) < 1) 
        {
            printf("Incorrect input file.\n");
            fclose(inFile);
            delete[] arr;
            return (-1);
        }
    }
    fclose(inFile);
    
    struct pair res = lucky(arr, arrLength);
    
    FILE* outFile = fopen("output.txt", "wt");
    if (outFile == NULL) 
    {
        perror("Cannot open output file");
        delete[] arr;
        return (-1);
    }

    if (res.breakpoint == 0) fprintf(outFile, "-1");
    else fprintf(outFile, "%d %d\n", res.breakpoint, res.sum);
    fclose(outFile);
    delete[] arr;
    return 0;
}

struct pair lucky(int* arr, int arrLength)
{
    
    int breakpoint, firstSum = 0, secondSum = 0;

    // сначала считаем сумму всего массива
    for (int i = 0; i < arrLength; ++i)
    {
        firstSum += arr[i];
    }

    // затем начиная с конца вычитаем по одному элементу и проверяем не равна ли первая половина второй
    for (breakpoint = (arrLength-1); breakpoint > 0; --breakpoint)
    {
        firstSum -= arr[breakpoint];
        secondSum += arr[breakpoint];
        if (firstSum == secondSum)
        break;
    }

    struct pair res = {breakpoint, firstSum};
    return res;
}
