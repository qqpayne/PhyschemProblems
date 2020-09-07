#include <iostream>
#include <cmath>
#include "../libs/R3Graph.h"
#include "../libs/earth.cpp"

/*
Вычисляет дистанцию (в метрах) между 2 точками на поверхности Земли, считая её идеальным шаром
В качестве аргументов использует широту и долготу в градусах

Написана Борисенко В.В.
*/

using namespace std;
using namespace R3Graph;

int main()
{
    while (true)
    {
        double lat0, lon0;
        double lat1, lon1;

        cout << "Введите координаты двух точек на Земле (в широте и долготе):" << endl;
        cin >> lat0 >> lon0 >> lat1 >> lon1;
        if (!cin.good())
            break;

        R3Vector v0 = radiusVector(lat0, lon0);
        R3Vector v1 = radiusVector(lat1, lon1);
        double alpha = v0.angle(v1); // угол в радианах

        double dist = alpha * EARTH_RADIUS; // Из формулы для длины окружности (l = 2pi*R)
        cout << "Расстояние между ними - " << dist << "\n"
             << endl;
    }
    return 0;
}
