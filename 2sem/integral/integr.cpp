#include <math.h>
#include <stdio.h>

const double EPS = 1e-5;

double f(double x);
double integrate(double (*f)(double), double a, double b);

int main(){
	double a, b;
	printf("Введите пределы интегрирования: \n");
	scanf("%lf %lf", &a, &b);
	
	double integr = integrate(f, a, b);
	
	printf("Интеграл равен %.4f \n", integr);
	return(0);
}

double f(double x){ // placeholder-функция x^2
	return(x*x);
}

double integrate(double (*f)(double), double a, double b){
	double h, x, sum, integr, integrnew, diff;
	bool sign;
	if (a > b){ // поворачиваем пределы интегрирования нужным образом
		double tmp = a;
		a = b; b = tmp;
		sign = 1;
	}

	h = (b-a); // первое приближение
	integr = 0;

	while(true){
		h *= 0.5;
		sum = 0;

		for (x = a+h; x < b; x=x+h){ // суммируем все промежуточные значения
			sum += f(x); 
		}
		integrnew = h*((0.5)*(f(a)+f(b))+sum); // вычисляем по формуле трапеций интеграл

		diff = fabs(integrnew - integr);
		if (diff<EPS){
			break;
		}
		integr = integrnew;
	}

	if(sign){ // если мы поворачивали пределы интегрирования, нужно поменять знак
		integrnew = (-1)*integrnew;
	}
	return integrnew;
}
