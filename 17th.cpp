#include <stdio.h>
#include <stdlib.h> // abs

// нужно найти максимальные и минимальный элементы, собрать все элементы и их число - для вычисления среднего арифм. затем найти кто сильнее отклоняется от ср. арифм - макс\мин

double maxdev(FILE *f){
    double x, s, n, mean = 0.;
    double min = 1e30;
    double max = 1e-30;
    while (fscanf(f, "%lf", &x){
        s+=x;
        ++n;
        if x > max
            max = x;
        if x < min
            min = x;
    }
    mean = s/n;
    if (abs(mean-max) > abs(mean-min))
        return max;
    return min;
}
    
    
