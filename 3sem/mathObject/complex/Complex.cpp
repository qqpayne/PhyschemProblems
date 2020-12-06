#include <cmath>
#include "Complex.h"

/*
Функция вычислений корней n-ой степен из комплексного числа
Написано В. В. Борисенко
*/

void Complex::roots(int n, Complex* root) const {
    double r = abs();
    r = pow(r, 1./double(n));
    double phi = arg();
    phi /= double(n);
    Complex z(r*cos(phi), r*sin(phi));
    
    double alpha = 0.;
    double dAlpha = 2.*M_PI/double(n);
    for (int i = 0; i < n; ++i) {
        root[i] = z*Complex(cos(alpha), sin(alpha));
        alpha += dAlpha;
    }
}
