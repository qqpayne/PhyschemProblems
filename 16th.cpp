#include <stdio.h>

void oddSort(double* a, int n);

int main() {
    FILE *f = fopen("input.txt", "rt");
    if (f == NULL) {
        perror("Cannot open input file");
        return (-1);
    }
    double *a;
    int n;
    if (fscanf(f, "%d", &n) < 1 || n < 0) {
        printf("Incorrect input file.\n");
        return (-1);
    }
    a = new double[n];
    for (int i = 0; i < n; ++i) {
        if (fscanf(f, "%lg", a + i) < 1) {
            printf("Incorrect input file.\n");
            fclose(f);
            delete[] a;
            return (-1);
        }
    }
    fclose(f);
    
    oddSort(a, n);
    
    FILE* g = fopen("output.txt", "wt");
    if (g == NULL) {
        perror("Cannot open output file");
        delete[] a;
        return (-1);
    }
    for (int i = 0; i < n; ++i) {
        fprintf(g, "%g ", a[i]);
        if ((i+1)%10 == 0)
            fprintf(g, "\n");
    }
    fprintf(g, "\n");
    fclose(g);
    delete[] a;
    return 0;
}

void oddSort(double* a, int n) {
    bool sorted = false;
    int k = 0;
    while (!sorted) {
        sorted = true;
        for (int i = 1; i < n-2-k; i=i+2) {
            if (a[i] > a[i+2]) {
                sorted = false;
                double tmp = a[i];
                a[i] = a[i+2];
                a[i+2] = tmp;
            }
        }
        k=k+2;
    }
}