#include <stdio.h>

/*
Определить самый частый элемент в массиве целых чисел
Написано 4.11.19 Акостеловым И. И.
Рефакторинг 28.08.20
*/

void sort(int* arr, int arrLength);
void swap(int* a, int* b);
int freq(int *arr, int arrLength);

int main()
{
    FILE *file = fopen("input.txt", "rt");
    if (file == NULL) 
    {
        perror("Cannot open input file");
        return (-1);
    }

    int *arr;
    int arrLength;
    if (fscanf(file, "%d", &arrLength) < 1 || arrLength < 0) 
    {
        printf("Incorrect input file.\n");
        return (-1);
    }

    arr = new int[arrLength];
    for (int i = 0; i < arrLength; ++i) 
    {
        if (fscanf(file, "%d", arr + i) < 1) 
        {
            printf("Incorrect input file.\n");
            fclose(file);
            delete[] arr;
            return (-1);
        }
    }
    fclose(file);
    
    sort(arr, arrLength);
    int mostFreq = freq(arr, arrLength);
    
    FILE* outFile = fopen("output.txt", "wt");
    if (outFile == NULL) 
    {
        perror("Cannot open output file");
        delete[] arr;
        return (-1);
    }

    fprintf(outFile, "%d\n", mostFreq);
    fclose(outFile); // забавный факт: если не закрыть файл и выйти, то в него ничего не запишется
    delete[] arr;
    return 0;
}

// баблсорт, но можно использовать любой алгоритм
void sort(int* arr, int arrLength)
{
    bool sorted = false;
    int currIter = 0; 
    // за каждую итерацию мы отсортировываем один элемент
    while (!sorted) 
    {
        // по умолчанию оптимистично считаем что всё уже отсортировалось
        // затем проверяем, так ли это
        sorted = true; 
        for (int i = 0; i < arrLength-1-currIter; ++i) 
        {
            if (arr[i] > arr[i+1]) 
            {
                sorted = false;
                swap(&arr[i], &arr[i+1]);
            }
        }
        ++currIter;
    }
}

void swap(int *a, int *b)
{
    // поменять местами переменные a и b
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// работает только на отсортированных массивах (не важно, по убыванию или по возрастанию)
int freq(int *arr, int arrLength)
{
    // первоначальная инициализация для сохранения работы программы в случае 1-элементного массива
    int curNum = arr[0], counter = 1, maxCounter = 1, mostFreq = arr[0];
    for (int i = 1; i < arrLength; ++i)
    {
        // если следующий элемент в массиве совпадает с текущим, увеличиваем счетчик
        // иначе, сбиваем счетчик и сравниваем его с наибольшим накопленным
        if (arr[i] == curNum) ++counter;
        else
        {
            if (counter > maxCounter)
            { 
                // т.к сравнение строгое, то в случае двух одинаково часто встречающихся элементов в массиве
                // самым частым будет признан первый встреченный 
                mostFreq = curNum;
                maxCounter = counter;
            }
            counter = 1;
        }
        curNum = arr[i];
    }
    return mostFreq;
}