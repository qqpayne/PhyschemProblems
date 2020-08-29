void swapRows(double *matrix, int rowLength, int i, int k)
{
    // поменять местами строки i и k, сохраняя значение определителя
    for (int j = 0; j < rowLength; ++j)
    {
        double tmp = matrix[i * rowLength + j];
        matrix[i * rowLength + j] = matrix[k * rowLength + j];
        matrix[k * rowLength + j] = (-tmp);
    }
}

void addRows(double *matrix, int rowLength, int i, int k, double lambda)
{
    // сложить строку i с строкой k, умноженной на lambda
    for (int j = 0; j < rowLength; ++j)
    {
        matrix[i * rowLength + j] += matrix[k * rowLength + j] * lambda;
    }
}

void multRows(double *matrix, int rowLength, int i, double lambda)
{
    // умножить строку i на lambda
    for (int j = 0; j < rowLength; ++j)
    {
        matrix[i * rowLength + j] *= lambda;
    }
}