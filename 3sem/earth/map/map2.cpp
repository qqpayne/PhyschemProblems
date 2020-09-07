#include <iostream>
#include <cmath>
#include "../libs/R3Graph.h"
#include "../libs/earth.cpp"

/*
Рассчитывает координаты точки на земной поверхности (широта и долгота в градусах)
из координат этой точки (в метрах) на карте Земли

Карта (касательная плоскость к земной сфере) отображает точки с поверхности земли
Для отображения используется центральная проекция с центром в центре Земли
На карте используется декартова система координат с осью Y, 
направленной на север, и осью X, направленной на восток

Решение использует сложение векторов для получения вектора, лежащего на прямой,
соединяющий центр земли и точку проекции (при этом он проходит через образ точки
на сфере). Затем зная координаты этого вектора (а значит и декартовы координаты точки 
на поверхности Земли), можно с помощью формул получить широту и долготу.

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
        if (!cin.good())
            break;

        cout << "Введите координаты точки на карте (в метрах):" << endl;
        cin >> mapX >> mapY;
        if (!cin.good())
            break;

        R3Point earthCenter = R3Point(0, 0, 0); // система координат начинается в центре земли

        R3Vector toPlane = radiusVector(mlat, mlon);                             // вектор, указывающий на точку центра карты
        R3Point planeCenter = earthCenter + toPlane.normalized() * EARTH_RADIUS; // точка, находящаяся в точке касания (центре карты)

        R3Vector yAxis, xAxis;
        defineAxes(earthCenter, mlat, mlon, &yAxis, &xAxis);

        R3Vector toIntersectionInPlane = yAxis.normalize() * mapY + xAxis.normalize() * mapX; // координаты проекци на карте в системе отсчета сферы
        R3Vector toIntersection = toPlane.normalized()*EARTH_RADIUS + toIntersectionInPlane;    // вектор, направленный из центра земли в точку пересечения

        // теперь у нас есть вектор который выходит из центра земли и проходит через искомую точку на поверхности
        // phi (долготу) находим как arctg(y/x)
        // theta (широту) находим как arccos(z/sqrt(x^2+y^2+z^2) = arctg(sqrt(x^2+y^2)/z)

        double x = toIntersection.x;
        double y = toIntersection.y;
        double z = toIntersection.z;

        double phi = atan2(y, x);
        double theta = atan2(sqrt(x*x + y*y), z);
        theta = (PI/2) - theta; // честно сказать, не совсем понимаю почему нужна эта поправка

        cout << "Широта: " << theta * (180 / PI) << ", долгота: " << phi * (180 / PI) << "\n" << endl;
    }
    return 0;
}
