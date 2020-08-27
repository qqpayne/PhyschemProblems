#include <stdio.h>
#include <math.h>

const double EPS = 1e-8;

int inverse(double *a, int m, double *E);
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
    
    double *b = new double [m * m]; // указатель на обратную матрицу 
    int rank = inverse(a, m, b);

    if (rank != m){  // проверка на нулевой дискриминант
        printf("Singular matrix.\n");
        return (-1);
    }

    if (!writeMatrix("output.txt", b, m, m)) {
        perror("Cannot write.\n");
        return(-1);
    }

    printf("Matrix rank is %d\n", rank);
    return(0);
}

int inverse(double *a, int m, double *E) {
    // получаем обратную матрицу методом Гаусса с расширенной матрицей 

    idM(E, m); // создаем единичную матрицу 

    int i = 0;
    int j = 0;

    // приводим исходную матрицу к ступенчатой
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
            // 'обнуляем' нули
            for (int k = i; k < m; ++k) {
                a[k*m+j]=0.;
            }
            ++j;
            continue;
        }
        if (kmax != i) {
            // меняем местами i-ую и максимальную строки в обоих матрицах
            swapRows(a, m, m, i, kmax);
            swapRows(E, m, m, i, kmax);
        }
        for (int k = i+1; k < m; ++k) {
            // зануляем оставшиеся строки 
            double lambda = a[k*m+j]/a[i*m+j];
            addRows(a, m, m, k, i, -lambda);
            addRows(E, m, m, k, i, -lambda);
        }
        ++i; ++j;
    }

    // приводим исходную матрицу к единичной
    j = 0;
    while (j < m) {
    	// диагонализируем
    	for (int k = 0; k<j; ++k){
    		double lambda = a[k*m+j]/a[j*m+j];
    		addRows(a, m, m, k, j, -lambda);
            addRows(E, m, m, k, j, -lambda);
    	}
    	// нормализуем
    	double lambda = (1.0/a[j*m+j]);
    	multRows(a, m, m, j, lambda);
    	multRows(E, m, m, j, lambda);
    	++j;
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

void swapRows(double *a, int m, int n, int i1, int i2) {
    // поменять местами строки i1 и i2, сохраняя значение определителя
    for (int j = 0; j<n; ++j) {
        double tmp = a[i1*n+j];
        a[i1*n+j] = a[i2*n+j];
        a[i2*n+j] = (-tmp);
    }
    
}

void addRows(double *a, int m, int n, int i, int k, double lambda) {
    // сложить строку i с строкой lambda*k
    for (int j = 0; j<n; ++j) {
        a[i*n+j] += a[k*n+j]*lambda;
    }    
}

void multRows(double *a, int m, int n, int i, double lambda) {
    // умножить строку i на лямбду
    for (int j = 0; j<n; ++j) {
        a[i*n+j] *= lambda;   
    }
}

void idM(double *E, int m){
    // создать единичную матрицу размером m*m
    for (int i = 0; i<m; ++i){
        for (int j = 0; j<m; ++j){
            E[i*m+j]=0;
            if (i == j){
                E[i*m+j]=1;
            }
        }
    }
}