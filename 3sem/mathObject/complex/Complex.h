#ifndef COMPLEX_H
#define COMPLEX_H 1

#include <cmath>
#include <iostream>

/*
Реализация класса комплексных чисел с внутренним представлением в экспоненциальной форме (ввод\вывод всё еще в декартовой форме).
Написано 06.12.20 Акостеловым И.И. на основе класса В. В. Борисенко
*/

const double EPS = 1e-8;

class Complex {
private:
    double r;
    double phi;
    // z = r*e^(i*phi)
public:
    Complex(double a = 0., double b = 0.):
        r(sqrt(pow(a, 2)+pow(b, 2))),
        phi(atan2(b, a))
    {}

    // Деструктор и копи-конструктор не нужны; динамически память не захватываем

    double real() const { return r*cos(phi); }
    double imag() const { return r*sin(phi); }
    void changeReal(double newReal) { double oldImag = imag(); r = sqrt(pow(newReal, 2)+pow(oldImag, 2)); phi = atan2(oldImag, newReal); }
    void changeImag(double newImag) { double oldReal = real(); r = sqrt(pow(oldReal, 2)+pow(newImag, 2)); phi = atan2(newImag, oldReal); }
    
    double abs() const { return r; }
    double& abs() { return r; }
    
    double abs2() const {
        return r*r;
    }
    
    double arg() const { return phi; }
    double& arg() { return phi; }

    Complex& operator+=(const Complex& z) {
        changeReal(real() + z.real());
        changeImag(imag() + z.imag());
        return *this;
    }
    
    Complex& operator-=(const Complex& z) {
        changeReal(real() - z.real());
        changeImag(imag() - z.imag());
        return *this;
    }
    
    Complex& operator*=(const Complex& z) {
        r *= z.r;
        phi += z.phi;
        return *this;
    }
    
    Complex& operator/=(const Complex& z) {
        r /= z.r;
        phi -= z.phi;
        return *this;
    }

    Complex conjugate() const {
        return Complex(r, -phi);
    }
    
    Complex inverse() const {
        return Complex(1/r, -phi);
    }
    
    void roots(int n, Complex* root) const;
};

inline Complex operator+(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res += v;
    return res;
}

inline Complex operator-(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res -= v;
    return res;
}

inline Complex operator*(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res *= v;
    return res;
}

inline Complex operator/(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res /= v;
    return res;
}

/* Логика вывода слегка монструозна, но позволяет получать красивые "0.5 - 0.4*i" вместо "0.5 + -0.4*i" 
 и не выводить бесполезные мнимые\реальные нулевые части */
inline std::ostream& operator<<(std::ostream& s, const Complex& z) {
    double imag = z.imag(), real = z.real();
    if (fabs(imag) <= EPS){
        if (fabs(real) <= EPS){
            s << 0;
        }
        else {
            s << real;
        }
    } 
    else if (fabs(real) <= EPS){
        s << imag << "*i";
    }
    else {
        if (imag < 0){
           s << real << " - " << fabs(imag) << "*i";  
        }
        else{
            s << real << " + " << imag << "*i";
        }
    }
    return s;
}

inline std::istream& operator>>(std::istream& s, Complex& z) {
    double real, imag;
    s >> real >> imag; 
    z.changeReal(real);
    z.changeImag(imag);
    return s;
}

#endif
