#include <iostream>
#include <cmath>
#include "libs/R2Graph.h"

using namespace std;

void circumCircle(
    const R2Point* points, R2Point& center, double& radius
); 

int main() {
    R2Point points[3];
    R2Point center;
    double radius;
    
    cout << "Вычислить центр и радиус вписанной окружности." << endl;
    cout << "Введите 3 вершины треугольника:" << endl;
    cin >> points[0] >> points[1] >> points[2];

    // Вычисляем описанную окружность
    circumCircle(points, center, radius);

    cout << "Центр окружности = " << center << 
        ", радиус = " << radius << endl;
    return 0;
}

void circumCircle(
    const R2Point* points, R2Point& center, double& radius
) {
    R2Vector ab = points[1] - points[0]; // сторона AB
    R2Point abmid = points[0]+(ab*0.5); // середина стороны AB
    ab = ab.normal(); // перпендикуляр к AB

    R2Vector ac = points[2] - points[0]; // сторона AC
    R2Point acmid = points[0]+(ac*0.5); // середина стороны AC
    ac = ac.normal(); // перпендикуляр к AC
    
    // Вычисляем центр окружности как пересечение серединных перпендикуляров
    intersectStraightLines(
        abmid, ab, acmid, ac, center
    );
    
    // Вычисляем расстояние от центра до вершины A
    radius = (points[0]-center).length();
}
