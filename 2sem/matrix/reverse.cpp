#include <stdio.h>
#include <math.h>

const double EPS = 1e-8;

void inverse(double *a, int m, double *E);
bool readMatrix(const char *path, double **a, int *m, int *n);
bool writeMatrix(const char *path, const double *a, int m, int n);
void swapRows(double *a, int m, int n, int i1, int i2);
void addRows(double *a, int m, int n, int i1, int i2, double lambda);
void multRows(double *a, int m, int n, int i, double lambda);
void idM(double *E, int m);

int main(){
    int m, n;
    double *a;
    if(!readMatrix("input.txt", &a, &m, &n)) {
        perror("Cannot read.\n");
        return(-1);
    }
    
    if (m != n) {
        printf("Matrix isn't square.\n");
        return (-1);
    }
    
    //int rank = gauss(a, m, n);
    //
    //if (rank < n) {
    //    printf("Singular matrix.");
    //    return (-1);
    //}
    
    double *E = new double [m * m];
    inverse(a, m, E);
    
    if (!writeMatrix("output.txt", E, m, m)) {
        perror("Cannot write.\n");
        return(-1);
    }
}

void inverse(double *a, int m, double *E) {
    idM(E, m);

    int i = 0;
    int j = 0;
    
    // Гаусс с расширенной матрицей
    while (i < m && j < m) {
        // ищем максимумальный ненулевой элемент в j-м столбце с i-ой строки
        double amax = (-1.);
        int kmax = j;
        for (int k = i; k < m; ++k) {
            if (fabs(a[k*m+j])>amax) {
                amax = fabs(a[k*m+j]);
                kmax = k;
            }
        }
        if (amax <= EPS) {
            // seeking null columns
            for (int k = i; k < m; ++k) {
                a[k*m+j]=0.;
            }
            ++j;
            continue;
        }
        if (kmax != i) {
            // swap i and kmax in both matrixes
            swapRows(a, m, m, i, kmax);
            swapRows(E, m, m, i, kmax);
        }
                 
        for (int k = i+1; k < m; ++k) {
            // nulling j column, starting from i+1  
            double lambda = a[k*m+j]/a[i*m+j];
            addRows(a, m, m, k, i, -lambda);
            a[k*m+j] = 0.;
            addRows(E, m, m, k, i, -lambda);
            E[k*m+j] = 0.;
        }
        ++i; ++j;
    }
    
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

void swapRows(double *a, int m, int n, int i1, int i2) {
    // swap i1 and i2, det = const
    for (int j = 0; j<n; ++j) {
        double tmp = a[i1*n+j];
        a[i1*n+j] = a[i2*n+j];
        a[i2*n+j] = (-tmp);
    }
    
}

void addRows(double *a, int m, int n, int i, int k, double lambda) {
    // i1 plus lambda*i2
    for (int j = 0; j<n; ++j) {
        a[i*n+j] += a[k*n+j]*lambda;
    }    
}

void multRows(double *a, int m, int n, int i, double lambda) {
    // multiply i1 by lambda
    for (int j = 0; j<n; ++j) {
        a[i*n+j] *= lambda;   
    }
}

void idM(double *E, int m){
    // make identity matrix m*m
    for (int i = 0; i<m; ++i){
        for (int j = 0; j<m; ++j){
            E[i*m+j]=0;
            if (i == j){
                E[i*m+j]=1;
            }
        }
    }
}
