#include <stdio.h>

/*
Определяет, удовлетворяет ли последовательность целых чисел рекуррентному соотношению a*x[i] + b*x[i+1] + c*x[i+2] = d
Написано 02.12.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

bool isrecur(FILE *file);

int main()
{
    FILE *inFile = fopen("input.txt", "rt");
    bool res = isrecur(inFile);
    fclose(inFile);

    FILE *outFile = fopen("output.txt", "wt");
    if (res)
        fprintf(outFile, "yes\n");
    else
        fprintf(outFile, "no\n");
    fclose(outFile);
    return 0;
}

bool isrecur(FILE *file)
{
    int a, b, c, d; // коэффициенты 
    int x, x1, x2, sum;
    bool result = false;
    fscanf(file, "%d", &a);
    fscanf(file, "%d", &b);
    fscanf(file, "%d", &c);
    fscanf(file, "%d", &d);
    
    fscanf(file, "%d", &x);
    fscanf(file, "%d", &x1);
    while (fscanf(file, "%d", &x2) == 1)
    {
        sum = (a * x + b * x1 + c * x2);
        if (sum == d) 
        {
            result = true;
            break;
        }
        x = x1;
        x1 = x2;
    }
    return result;
}