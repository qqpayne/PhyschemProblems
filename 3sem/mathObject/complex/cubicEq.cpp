#include <iostream>
#include <cmath>
#include "Complex.h"

/*
Решение кубических уравнений с вещественными коэффициентами.
Написано 06.12.20 Акостеловым И.И.
*/

using namespace std;

struct solutions {
    Complex first, second, third;
}; 

struct coeffs {
    double a, b, c, d;
}; 

solutions solveEq(coeffs coeffs);

int main()
{
    coeffs input;
    solutions solution;
    while (true)
    {
        cout << "Введите коэффициенты уравнения ax^3 + bx^2 + cx + d = 0:" << endl;
        cin >> input.a >> input.b >> input.c >> input.d;
        if (!cin.good())
            break;

        solution = solveEq(input);

        cout << "x1: " << solution.first << endl << "x2: " << solution.second << endl << "x3: " << solution.third << endl << endl;
    }
    return 0;
}

solutions solveEq(coeffs coeffs){
    Complex first, second, third;
    double p, q, Q, alpha, beta, arccos;
    double a = coeffs.a, b = coeffs.b, c = coeffs.c, d = coeffs.d;

    // приводим первый коэффициент к единице
    b /= a;
    c /= a;
    d /= a;

    // коэффициенты канонической формы; сразу делим их на 3 и на 2.
    p = (3.*c - b*b)/3.; p /= 3.;
    q = (2.*b*b*b - 9.*b*c + 27.*d)/27.; q /= 2.;

    Q = p*p*p + q*q; // дискриминант 

    if (Q > 0 || Q == 0){ // сначала рассмотрим случаи, в которых не приходится брать квадратный корень из отрицательного числа
        alpha = -q + sqrt(Q);
        alpha = ((alpha < 0) ? -pow(-alpha, 1./3.) : pow(alpha, 1./3.)); // т.к pow выдаёт nan, если нужно вычислить корень из отрицательного числа

        beta = -q - sqrt(Q);
        beta = ((beta < 0) ? -pow(-beta, 1./3.) : pow(beta, 1./3.));

        first = Complex(alpha+beta); 
        second = Complex(-(alpha+beta)/2, sqrt(3.)*(alpha-beta)/2);;
        third = Complex(-(alpha+beta)/2, -1*sqrt(3.)*(alpha-beta)/2);
    }
    else { // не усложняя жизнь, используем тригонометрическую формулу для корней неприводимого случая
        arccos = acos(-q/sqrt(-p*p*p))/3.;
        double precos = 2.*sqrt(-p);
        double arbitrary = 2.*M_PI/3;

        first = Complex(precos*cos(arccos - 0.*arbitrary)); 
        second = Complex(precos*cos(arccos - 1.*arbitrary));
        third = Complex(precos*cos(arccos - 2.*arbitrary));
    }

    Complex diff = Complex(-b/3., 0); // разница между переменной в оригинальном уравнении и в канонической форме (преобразование Чирнгауза)
    first += diff;
    second += diff;
    third += diff;

    solutions solution;
    solution.first = first, solution.second = second, solution.third = third;
    return solution;
}