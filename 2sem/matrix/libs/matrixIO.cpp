#include <stdio.h>

bool writeMatrix(const char *path, const double *matr, int m, int n)
{
    FILE *file = fopen(path, "wt");
    if (file == NULL)
        return false;

    fprintf(file, "%d %d\n", m, n);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fprintf(file, "%16.6f", matr[i * n + j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return true;
}

// Читает матрицу из файла по пути path, записывает матрицу в matr, а её размер в переменные m и n
// **matr - это двойной указатель, в данном случае указывает на массив
bool readMatrix(const char *path, double **matr, int *m, int *n)
{
    FILE *file = fopen(path, "rt");
    if (file == NULL)
        return false;

    if (fscanf(file, "%d %d", m, n) < 2)
    {
        fclose(file);
        return false;
    }

    // обращаться к таким образом заданной матрице нужно по адресу matr[i*n+j]
    *matr = new double[(*m) * (*n)];

    for (int i = 0; i < *m; ++i)
    {
        for (int j = 0; j < *n; ++j)
        {
            if (fscanf(file, "%lf", &((*matr)[i * (*n) + j])) < 1)
            {
                fclose(file);
                return false;
            }
        }
    }
    fclose(file);

    return true;
}