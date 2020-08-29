#include <math.h>
#include <stdio.h>

/*
Интегрирование функции методом трапеций с последовательным приближением
Написано 19.04.20 Акостеловым И.И.
Рефакторинг 29.08.20
*/

const double EPS = 1e-5;

double f(double x);
double integrate(double (*f)(double), double a, double b);
void swap(double *a, double *b);

int main()
{
	double a, b;
	printf("Введите пределы интегрирования: \n");
	scanf("%lf %lf", &a, &b);

	double integr = integrate(f, a, b);

	printf("Интеграл равен %.4f \n", integr);
	return (0);
}

// функция для интегрирования
double f(double x)
{
	return (x * x);
}

// double (*f)(double) - указатель на функцию
double integrate(double (*f)(double), double a, double b)
{
	double integr = 0;
	bool invert;

	// если пределы интегрирования заданы некорректно, переворачиваем их
	if (a > b)
	{ 
		swap(&a, &b);
		invert = true;
	}

	double dx = (b-a); // первое приближение
	while (true)
	{
		dx *= 0.5; // на каждом шаге увеличиваем точность интегрирования в 2 раза
		double sum = 0;

		// суммируем все промежуточные значения
		for (double x = a + dx; x < b; x += dx)
		{ 
			sum += f(x);
		}

		// вычисляем по формуле трапеций интеграл
		double newIntegr = dx * ((0.5) * (f(a) + f(b)) + sum); 

		double diff = abs(newIntegr - integr);
		integr = newIntegr;
		
		// если нас удовлетворяет точность, заканчиваем приближение
		if (diff < EPS) break;
	}

	// если мы поворачивали пределы интегрирования, нужно поменять знак
	if (invert)
		integr *= (-1);

	return integr;
}

// поменять местами переменные a и b
void swap(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
