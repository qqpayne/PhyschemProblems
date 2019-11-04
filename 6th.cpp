#include <stdio.h>

/*
This program determine which of array elems occur most frequently
Works for integer arrays
Written November 4, 2019
*/

void sort(int* a, int n);
int most(int *a, int n);

int main() {
    FILE *f = fopen("input.txt", "rt");
    if (f == NULL) {
        perror("Cannot open input file");
        return (-1);
    }
    int *a;
    int n;
    if (fscanf(f, "%d", &n) < 1 || n < 0) {
        printf("Incorrect input file.\n");
        return (-1);
    }
    a = new int[n];
    for (int i = 0; i < n; ++i) {
        if (fscanf(f, "%d", a + i) < 1) {
            printf("Incorrect input file.\n");
            fclose(f);
            delete[] a;
            return (-1);
        }
    }
    fclose(f);
    
    sort(a, n);
    int s = most(a, n);
    
    FILE* g = fopen("output.txt", "wt");
    if (g == NULL) {
        perror("Cannot open output file");
        delete[] a;
        return (-1);
    }
    fprintf(g, "%d", s);
    fprintf(g, "\n");
    fclose(g);
    delete[] a;
    return 0;
}

void sort(int* a, int n){ // bubblesort, but you can use any
    bool sorted = false;
    int k = 0;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < n-1-k; ++i) {
            if (a[i] > a[i+1]) {
                sorted = false;
                int tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
            }
        }
        ++k;
    }
}

int most(int *a, int n){ // works only on sorted array (increasing or decreasing)
    int i, p = a[0], count = 1, max = 1, most = a[0]; // in case of 1 elem array
    for (i = 1; i<n; ++i){
        if (a[i] == p)
            ++count;
        else{
            if (count > max){ // if two different numbers appear equally frequently,
                most = p;     // it all depends on which one will first appear in sorted array
                max = count;
            }
            count = 1;
        }
        p = a[i];
    }
    return most;
}