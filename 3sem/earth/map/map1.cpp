#include <iostream>
#include <cmath>
#include "../libs/R3Graph.h"
#include "../libs/R3Graph.cpp"
#include "../libs/earth.cpp"

/*
Рассчитывает координаты (в метрах) точки на карте Земли из координат 
этой точки на земной поверхности (широта и долгота в градусах).

Карта (касательная плоскость к земной сфере) отображает точки с поверхности земли
Для отображения используется центральная проекция с центром в центре Земли
На карте используется декартова система координат с осью Y, 
направленной на север, и осью X, направленной на восток.

Решение использует точку пересечения плоскости карты и радиус-вектора 
к данной точке поверхности как проекцию точки на карту, её координаты 
в декартовой системе затем находятся с помощью вектора к ней от центра карты.

Написано 07.09.20 Акостеловым И.И.
*/

using namespace std;
using namespace R3Graph;

int main()
{
    while (true)
    {
        double mlat, mlon; // точка касания (центр) карты
        double lat, lon;   // координаты точки

        cout << "Введите координаты центра карты (широта, долгота):" << endl;
        cin >> mlat >> mlon;
        if (!cin.good() || !validCoords(mlat, mlon))
            break;

        cout << "Введите координаты точки на поверхности Земли (широта, долгота):" << endl;
        cin >> lat >> lon;
        if (!cin.good() || !validCoords(mlat, mlon))
            break;

        // если между точкой, проекцию которой мы хотим найти и центром карты больше 90 градусов, то её невозможно отобразить на карте
        // дальнейшие расчеты не проводим

        if (abs(mlat - lat) >= 90.0 || abs(mlon - lon) >= 90.0)
        {
            cout << "Эта точка находится на другом полушарии, её невозможно отобразить на этой карте"
                 << "\n"
                 << endl;
        }
        else
        {
            R3Point earthCenter = R3Point(0, 0, 0);    // система координат начинается в центре земли
            R3Vector toPoint = radiusVector(lat, lon); // задаем вектор, указывающий на точку на поверхности

            R3Vector toPlane = radiusVector(mlat, mlon).normalized() * EARTH_RADIUS; // вектор, указывающий на центр карты
            R3Point planeCenter = earthCenter + toPlane;                             // центр карты, на поверхности Земли

            R3Point intersection;

            // плоскость задается точкой в ней лежащей и нормалью, прямая - точкой и направляющим вектором
            // пересечение плоскости карты и прямой из центра земли в проецируемую точку есть центральная проекция этой точки на карту
            intersectPlaneAndLine(planeCenter, toPlane.invert(), earthCenter, toPoint, intersection);

            // вектор из центра карты в точку пересечения содержит искомые координаты, которые нам
            // ещё нужно перевести в систему координат карты
            R3Vector toIntersection = intersection - planeCenter;

            R3Vector yAxis, xAxis;
            defineAxes(earthCenter, mlat, mlon, &yAxis, &xAxis);

            double x = toIntersection.projection(xAxis), y = toIntersection.projection(yAxis);

            cout << "x: " << x << ", y: " << y << "\n"
                 << endl;
        }
    }
    return 0;
}
