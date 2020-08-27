#include <stdio.h>

void heapSort(double *a, int n);
void makeP(double *a, int n);
void bubbleD(double *a, int n, int m);
void swap(double *a, double *b);

void heapSort(double *a, int n){
	makeP(a, n);
	int k = n;
	while (k > 1) {
		--k;
		swap(&(a[0]), &(a[k]));
		bubbleD(a, k, 0);
	}
}

void makeP(double *a, int n){
//	Создаёт пирамиду из входного массива. 
	int m = n/2;
	while (m>0){
		--m;
		bubbleD(a, n, m);
	}
}

void bubbleD(double *a, int n, int i){
//	Просеиваем i-ый элемент в пирамиде. 
	while (true) {
		int d1 = 2*i+1;
		// проверяем, не является ли элемент терминальным  
		if (d1 >= n)
			break;
		// находим наибольший из сыновей
		int d2 = d1+1;
		int m = d1;
		if (d2 < n && a[d2] > a[d1])
			m = d2;
		// проверяем условие пирамиды
		if (a[i] >= a[m])
			break;
		swap(&(a[i]), &(a[m]));
		i = m;
	}
}

void swap(double *a, double *b){
//	Меняем a-ое и b-ое значение в массиве.
	double tmp = *a; 
	*a = *b;
	*b = tmp;
}