#include <stdio.h>
#include <math.h>

// arctg(y)=2*arctg((sqrt(1+y^2)-1)/y) from trigonometry
// ((sqrt(1+y^2)-1)/y)=(y/(sqrt(1+y^2)+1)) obvious

const double EPS = 1e-12;
double arctg(double x);

int main(){
	double x;
	while (true){
		int n = 0;
		printf("x: ");
		if (scanf("%lg", &x) < 1)
			break;
		double xiz = x;
		while (x > 0.02){             // iter over x to get it less than 0.02
			x = (x/(1+sqrt(1+x*x)));  // it's easy to prove that (x/(sqrt(1+x^2)+x)) is less than x/2
			++n;					  // if we have x<=0.02, we'll have to count arctg(x) series only till 4th term for 1e-12 accuracy
		}
		printf("arctg(x) = %.14f\n", arctg(x)*(2<<(n-1)));
		printf("lib arctg(x) = %.14f\n", atan(xiz));
	}
	return 0;
}

double arctg(double x){
	// taylor series for arctg(x), accuracy given by EPS
	double a = x, s = x, prev = x;
	int n = 1;
	while (fabs(a) > EPS){
		a = (-1)*((prev*x*x*n)/(n+2));
		s += a;
		prev = a;
		n += 2;
	}
	return s;
}
