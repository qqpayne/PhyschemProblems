#include <stdio.h>
#include <math.h>

const double EPS = 1e-8;

int gauss(double *a, int m, int n);
bool readMatrix(const char *path, double **a, int *m, int *n);
bool writeMatrix(const char *path, const double *a, int m, int n);

int main(){
    int m, n;
    double *a;
    if(!readMatrix("input.txt", &a, &m, &n)) {
        perror("Cannot read");
        return(-1);
    }
    
    int rank = gauss(a, m, n);
    
    if (!writeMatrix("output.txt", a, m, n)) {
        perror("Cannot write");
        return(-1);
    }
    
    printf("%d\n", rank);
}

int gauss(double *a, int m, int n) {
    int i = 0;
    int j = 0;
    
    while (i < m && j < n) {
        // ищем максимумальный ненулевой элемент в j-м столбце с i-ой строки
        double amax = (-1.);
        int kmax = j;
        for (int k = i; k < m; ++k) {
            if (fabs(a[k*n+j])>amax) {
                amax = fabs(a[k*n+j]);
                kmax = k;
            }
        }
        if (amax <= EPS) {
            // null column
            for (int k = i; k < m; ++k) {
                a[k*n+j]=0.;
            }
            ++j;
            continue;
        }
        if (kmax != i) {
            // swap i and kmax
            for (int l = j; l<n; ++l) {
                double tmp = a[i*n+l];
                a[i*n+l] = a[kmax*n+l];
                a[kmax*n+l] = (-1)*tmp;
            }
        }
        
        // nulling j column, starting from i+1
        for (int k = i+1; k < m; ++k) {
            double lambda = a[k*n+j]/a[i*n+j];
            a[k*n+j] = 0.;
            for (int l = j+1; l<n; ++l) {
                a[k*n+l] -= lambda*a[i*n+l];
            }
        }
        ++i; ++j;
    }
    return i;
}

bool writeMatrix(const char *path, const double *a, int m, int n) {
    FILE *f = fopen(path, "wt");
    if (f == NULL) {
        return false;
    }
    fprintf(f, "%d %d\n", m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fprintf(f, "%16.6f", a[i*n+j]);
        }
      fprintf(f, "\n");
    }
    fclose(f);
    return true;
}

bool readMatrix(const char *path, double **a, int *m, int *n) {
    FILE *f = fopen(path, "rt");
    if (f == NULL) {
        return false;
    }
    if (fscanf(f, "%d%d", m, n) < 2) {
        fclose(f);
        return false;
    }
    
    *a = new double [(*m) * (*n)];
    
    for (int i = 0; i < *m; ++i) {
        for (int j = 0; j < *n; ++j) {
            if (fscanf(f, "%lf", &((*a)[i*(*n)+j])) < 1) {
                fclose(f);
                return false;
            }
        }
    }
    fclose(f);
    return true;
}





