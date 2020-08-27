// Простой пример на использование классов
// R2Point и R2Vector, представляющих точку и вектор
// на плоскости: вычислить центр и радиус окружности,
// вписанной в треугольник
#include <iostream>
#include <cmath>
#include "libs/R2Graph.cpp"

using namespace std;

void inCircle(
    const R2Point* points, R2Point& center, double& radius
); 

int main() {
    R2Point points[3];
    R2Point center;
    double radius;
    
    cout << "Вычислить центр и радиус вписанной окружности." << endl;
    cout << "Введите 3 вершины треугольника:" << endl;
    cin >> points[0] >> points[1] >> points[2];

    // Вычисляем вписанную окружность
    inCircle(points, center, radius);

    cout << "Центр окружности = " << center << 
        ", радиус = " << radius << endl;
    return 0;
}

void inCircle(
    const R2Point* points, R2Point& center, double& radius
) {
    R2Vector ab = points[1] - points[0]; // сторона AB
    ab.normalize();
    R2Vector ac = points[2] - points[0]; // сторона AC
    ac.normalize();
    R2Vector bisa = ab + ac; // Биссектриса угла A
    
    R2Vector bc = points[2] - points[1]; // сторона BC
    bc.normalize();
    R2Vector ba = points[0] - points[1]; // сторона BA
    ba.normalize();
    R2Vector bisb = bc + ba; // Биссектриса угла B
    
    // Вычисляем центр окружности как пересечение биссектрис
    intersectStraightLines(
        points[0], bisa, points[1], bisb, center
    );
    
    // Вычисляем расстояние от центра до прямой AB
    //... R2Vector n = ab.normal();
    //... radius = fabs( (center - points[0])*n );
    radius = center.distanceToLine(points[0], ab);
}
