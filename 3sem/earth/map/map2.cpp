#include <iostream>
#include <cmath>
#include "../libs/R3Graph.h"
#include "../libs/earth.cpp"

/*
Рассчитывает координаты точки на земной поверхности (широта и долгота в градусах)
из координат этой точки (в метрах) на карте Земли.

Карта (касательная плоскость к земной сфере) отображает точки с поверхности земли
Для отображения используется центральная проекция с центром в центре Земли
На карте используется декартова система координат с осью Y, 
направленной на север, и осью X, направленной на восток.

Решение использует сложение двух векторов: к центру карты и от центра карты до
проекции точки, для получения вектора от центра земли к проекции. Этот вектор проходит
и через прообраз точки на сфере, поэтому мы можем из его координат получить долготу и
широту.

Написано 07.09.20 Акостеловым И.И.
*/

using namespace std;
using namespace R3Graph;

int main()
{
    while (true)
    {
        double mlat, mlon; // точка касания (центр) карты
        double mapX, mapY; // координаты точки

        cout << "Введите координаты центра карты (широта, долгота):" << endl;
        cin >> mlat >> mlon;
        if (!cin.good() || !validCoords(mlat, mlon))
            break;

        cout << "Введите координаты точки на карте (в метрах):" << endl;
        cin >> mapX >> mapY;
        if (!cin.good())
            break;

        R3Point earthCenter = R3Point(0, 0, 0); // система координат начинается в центре земли

        R3Vector toPlane = radiusVector(mlat, mlon).normalized() * EARTH_RADIUS; // вектор, указывающий на центр карты
        R3Point planeCenter = earthCenter + toPlane;                             // центр карты, на поверхности Земли

        R3Vector yAxis, xAxis;
        defineAxes(earthCenter, mlat, mlon, &yAxis, &xAxis);

        R3Vector toIntersectionInPlane = yAxis * mapY + xAxis * mapX; // координаты проекции на карте в земной системе отсчёта
        R3Vector toIntersection = toPlane + toIntersectionInPlane;    // вектор из центра земли в точку проекции; также проходит через её прообраз

        // т.к toIntersection проходит через прообраз точки, то мы можем перевести его координаты в сферические:
        // phi (долготу) находим как arctg(y/x)
        // theta (почти широту) находим как arccos(z/sqrt(x^2+y^2+z^2) = arctg(sqrt(x^2+y^2)/z)

        double x = toIntersection.x, y = toIntersection.y, z = toIntersection.z;

        double phi = atan2(y, x);
        double theta = atan2(sqrt(x * x + y * y), z);
        // в сферической системе координат на экваторе theta = PI/2, и он растёт к южному полюсу, преобразуем его:
        theta = (PI / 2) - theta;

        cout << "Широта: " << theta * (180 / PI) << ", долгота: " << phi * (180 / PI) << "\n"
             << endl;
    }
    return 0;
}
