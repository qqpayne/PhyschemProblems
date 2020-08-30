#include <stdio.h>
#include <math.h>
#include "libs/matrixIO.cpp"
#include "libs/matrixOperations.cpp"
// можно просто скопировать исходный код в этот файл, если напрягает использование библиотек

/*
Преобразует матрицу в обратную и рассчитывает ранг матрицы
Написано 22.05.20 Акостеловым И.И.
Рефакторинг 29.08.20
*/

const double EPS = 1e-8;

int inverse(double *matr, int m);
void idM(double *E, int m);

int main()
{
    int m, n;
    double *matr;

    if (!readMatrix("input.txt", &matr, &m, &n))
    {
        perror("Cannot read.\n");
        return (-1);
    }

    if (m != n)
    {
        printf("Matrix isn't square.\n");
        return (-1);
    }

    int rank = inverse(matr, m);

    // проверка на нулевой дискриминант 
    // (если ранг не равен m, то какие-то строки обнулились и дискриминант нулевой)
    if (rank != m)
    { 
        printf("Singular matrix.\n");
        return (-1);
    }

    if (!writeMatrix("output.txt", matr, m, m))
    {
        perror("Cannot write.\n");
        return (-1);
    }

    printf("Matrix rank is %d\n", rank);
    return 0;
}

// in-place получаем обратную матрицу методом Гаусса с расширенной матрицей
// т.е приводя исходную матрицу (размера m) к диагональной единичной, 
// при этом все операции применяя к двум матрицам сразу
int inverse(double *matr, int m)
{
    // расширяем матрицу, добавляя единичную матрицу
    double *inversed = new double[m*m];
    idM(inversed, m); 

    int i = 0; // строки
    int j = 0; // столбцы

    // приводим исходную матрицу к ступенчатой
    while (i < m && j < m)
    {
        // ищем максимумальный ненулевой элемент в j-м столбце с i-ой строки
        double maxElem = (-1.);
        int maxElemRow = m;

        // находим наибольший элемент в столбце и его позицию
        for (int k = i; k < m; ++k)
        {
            if (abs(matr[k * m + j]) > maxElem)
            {
                maxElem = abs(matr[k * m + j]);
                maxElemRow = k;
            }
        }

        // если столбец оказался нулевым и максимальный элемент меньше погрешности
        if (maxElem <= EPS)
        {
            // окончательно обнуляем его
            for (int k = i; k < m; ++k)
                matr[k * m + j] = 0.;

            // переходим к следующему столбцу
            ++j;
            continue;
        }

        // меняем местами i-ую и максимальную строки в обоих матрицах
        if (maxElemRow != i)
        {
            swapRows(matr, m, i, maxElemRow);
            swapRows(inversed, m, i, maxElemRow);
        }

        // обнуляем j-ый столбец начиная с i+1 строки
        for (int k = i + 1; k < m; ++k)
        {
            // во сколько раз текущий элемент меньше наибольшего
            double lambda = matr[k * m + j] / matr[i * m + j];

            addRows(matr, m, k, i, -lambda);
            addRows(inversed, m, k, i, -lambda);
        }

        ++i; ++j;
    }

    // приводим исходную матрицу к единичной
    j = 0;
    while (j < m)
    {
        // диагонализируем, вычитая из k-ой строки в j-ом столбце j-ую с коэффициентом для обнуления
        for (int k = 0; k < j; ++k)
        {
            double lambda = matr[k * m + j] / matr[j * m + j];
            addRows(matr, m, k, j, -lambda);
            addRows(inversed, m, k, j, -lambda);
        }

        // нормализуем строку
        double lambda = (1.0 / matr[j * m + j]);
        multRows(matr, m, j, lambda);
        multRows(inversed, m, j, lambda);

        ++j;
    }

    // чтобы возвращать обратную матрицу в той же переменной, нам нужно переместить байты
    // из новой (обратной) в старую. просто поменять поинтер не пойдет - при выходе из
    // функции её область стэка очищается, и поинтер будет указывать вникуда (т.к inversed сотрётся)
    for (int i = 0; i < m*m; i++)
        matr[i] = inversed[i];

    return i;
}


void idM(double *inversed, int m)
{
    // создать единичную матрицу размером m*m по указателю
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            inversed[i * m + j] = 0;
            if (i == j)
            {
                inversed[i * m + j] = 1;
            }
        }
    }
}