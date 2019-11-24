#include <stdio.h>
#include <math.h>

// arctg(y)=2arctg((sqrt(1+y^2)-1)/y)
// ((sqrt(1+y^2)-1)/y)=(y/(sqrt(1+y^2)+1))
// it's easy to prove that (y/(sqrt(1+y^2)+1)) is less than x/2
// so it will give us infinitesimal x, arctg(infinitesimal x) ~ x
// for example, if x = 1024, we need 41 iter

const double EPS = 1e-12;

int main(){
	double x;
	while (true){
		int n = 0;
		printf("x: ");
		if (scanf("%lg", &x) < 1)
			break;
		double xiz = x;
		while (x > EPS){
			x = (x/(1+sqrt(1+x*x)));
			++n;
		}
		printf("arctg(x) = %d\n", x*pow(2,n));
		printf("lib arctg(x) = %.14f\n", atan(xiz));
	}
	return 0;
}