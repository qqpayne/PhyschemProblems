#include <stdio.h>

struct pair lucky(double* a, int n);

// it also possible to return only k and count s = (summ from a[0] till a[k-1]) 
struct pair
{
    int k;
    double s;
};

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
    
    struct pair res = lucky(a, n);
    
    FILE* g = fopen("output.txt", "wt");
    if (g == NULL) {
        perror("Cannot open output file");
        delete[] a;
        return (-1);
    }
    if (res.k == 0)
        fprintf(g, "-1");
    else
        fprintf(g, "%d %g", res.k, res.s);
    fprintf(g, "\n");
    fclose(g);
    delete[] a;
    return 0;
}

// smart version
struct pair lucky(double* a, int n){
    int k, i;
    double s1 = 0, s2 = 0;
    for (i = 0; i<n; ++i){
            s1+=a[i];
        }

    for (k = (n-1); k>0; --k){
        s1-=a[k];
        s2+=a[k];
        if (s1 == s2)
            break;
    }
    struct pair res = {k, s1};
    return res;
}

// dumb version
/*
struct pair lucky(double* a, int n){
    int k, i, j;
    double s1 = 0, s2 = 0;
    for (k = (n-1); k>0; --k){
        for (i = 0; i<k; ++i){
            s1+=a[i]
        }
        for (j = k; j<n; ++j){
            s2+=a[j]
        }
        if (s1 == s2)
            break;
        s1 = 0;
        s2 = 0;
    }
    struct pair res = {k, s1};
    return res;
}
*/
