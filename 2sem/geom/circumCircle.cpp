#include <iostream>
#include <cmath>
#include "libs/R2Graph.cpp"

/*
Найти центр описанной окружности
Написано 06.05.20 Акостеловым И.И.
Рефакторинг 29.08.20
*/

using namespace std;

void circumCircle(const R2Point *points, R2Point &center, double &radius);

int main()
{
    R2Point points[3];
    R2Point center;
    double radius;

    cout << "Вычислить центр и радиус описанной окружности." << endl;
    cout << "Введите 3 вершины треугольника:" << endl;
    cin >> points[0] >> points[1] >> points[2];

    // Вычисляем описанную окружность
    circumCircle(points, center, radius);

    cout << "Центр окружности = " << center << ", радиус = " << radius << endl;
    return 0;
}

void circumCircle(const R2Point *points, R2Point &center, double &radius)
{
    R2Vector ab = points[1] - points[0];    // сторона AB
    R2Point abMid = points[0] + (ab * 0.5); // середина стороны AB
    R2Vector abOrt = ab.normal();           // перпендикуляр к AB

    R2Vector ac = points[2] - points[0];    // сторона AC
    R2Point acMid = points[0] + (ac * 0.5); // середина стороны AC
    R2Vector acOrt = ac.normal();           // перпендикуляр к AC

    // Вычисляем центр окружности как пересечение серединных перпендикуляров
    intersectStraightLines(
        abMid, abOrt, acMid, acOrt, center);

    // Вычисляем расстояние от центра окружности до вершины A (равное радиусу опис. окружности)
    radius = (points[0] - center).length();
}
