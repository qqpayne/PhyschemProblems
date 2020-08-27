#include <stdio.h>
#include <math.h>

/* arctg(y)=2*arctg((sqrt(1+y^2)-1)/y) from trigonometry
 ((sqrt(1+y^2)-1)/y)=(y/(sqrt(1+y^2)+1)) obvious
 arctg(x) = pi/2 - arctg(1/x) give us O(1) for n > 50
 arctg(x) = -arctg(-x) so we can count arctg(x) only for positive x
 we iter over x to get it less than 0.02
 it's easy to prove that (x/(sqrt(1+x^2)+x)) is less than x/2, so it will be O(logn) for 0<n<50 
 if we have x<=0.02, we'll have to count arctg(x) series only till 4th term for 1e-12 accuracy  */


const double EPS = 1e-12;
const double PI = 3.141592653589793;
double arctg(double x);

int main(){
	double x, res;
	while (true){
		int n = 0;
		bool invert = false;
		printf("x: ");
		if (scanf("%lg", &x) < 1)
			break;
		double xiz = x;
		if (x<0) {
		    x = (-1)*x;
		    invert = true;
		}
		if (x>50)
		    res = (PI/2)-arctg(1/x);
		else { 
		    while (x > 0.02) {             
			    x = (x/(1+sqrt(1+x*x)));  
			    ++n;					  
		    }
		    res = arctg(x)*(1<<n);
		}
		if (invert)
		    res = (-1)*res;
		printf("arctg(x) = %.14f\n", res);
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
