#include <stdio.h>

/*
Отсортировать элементы массива вещественных чисел на нечетных позициях
Написано 4.11.19 Акостеловым И. И.
Рефакторинг 28.08.20
*/

void oddSort(double* arr, int arrLength);
void swap(double *a, double *b);

int main() 
{
    FILE *inFile = fopen("input.txt", "rt");
    if (inFile == NULL) 
    {
        perror("Cannot open input file");
        return (-1);
    }

    double *arr;
    int arrLength;
    if (fscanf(inFile, "%d", &arrLength) < 1 || arrLength < 0) 
    {
        printf("Incorrect input file.\n");
        return (-1);
    }

    arr = new double[arrLength];
    for (int i = 0; i < arrLength; ++i) 
    {
        if (fscanf(inFile, "%lg", arr + i) < 1) 
        {
            printf("Incorrect input file.\n");
            fclose(inFile);
            delete[] arr;
            return (-1);
        }
    }
    fclose(inFile);
    
    oddSort(arr, arrLength);
    
    FILE* outFile = fopen("output.txt", "wt");
    if (outFile == NULL) 
    {
        perror("Cannot open output file");
        delete[] arr;
        return (-1);
    }

    for (int i = 0; i < arrLength; ++i) 
    {
        fprintf(outFile, "%g ", arr[i]);
        // через каждые 10 цифр переходим на новую строку
        if ((i+1)%10 == 0) fprintf(outFile, "\n");
    }
    fprintf(outFile, "\n");
    fclose(outFile);
    delete[] arr;
    return 0;
}

void oddSort(double* arr, int arrLength) 
{
    bool sorted = false;
    int currIter = 0;
    // за каждую итерацию мы отсортировываем один элемент
    while (!sorted) 
    {
        // по умолчанию оптимистично считаем что всё уже отсортировалось
        // затем проверяем, так ли это
        sorted = true;
        for (int i = 0; i < arrLength-2-currIter; i = i+2) 
        {
            if (arr[i] > arr[i+2]) 
            {
                sorted = false;
                swap(&arr[i], &arr[i+2]);
            }
        }
        currIter = currIter+2;
    }
}

void swap(double *a, double *b)
{
    // поменять местами переменные a и b
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
