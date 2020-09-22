#include "../libs/R3Graph.h"

const double EARTH_RADIUS = 6378*1000.0; // в метрах
const double PI = 3.14159265358979323846;

// Проверяет валидность введённых сферических координат
bool validCoords(const double lat, const double lon)
{
    if (abs(lat) > 90.0 || abs(lon) > 180.0)
    {
        return false;
    }
    return true;
}

// Возвращает радиус-вектор в направлении указанной широты и долготы
R3Graph::R3Vector radiusVector(const double lat, const double lon) {
    double phi = lon*PI/180.;   // перевод в радианы
    double theta = lat*PI/180.;
    
    // Поворачиваем в плоскости экватора на угол, соответствующий долготе, radVec = (cos(phi), sin(phi), 0.)
    // Затем 'поднимаем' вектор на угол широты, radVec = (cos(phi)*cos(theta), sin(phi)*cos(theta), sin(theta))
    return R3Graph::R3Vector(cos(phi)*cos(theta), sin(phi)*cos(theta), sin(theta));
}

// Строит систему координат карты, возвращает единичные векторы осей
void defineAxes(const R3Graph::R3Vector toPlane, R3Graph::R3Vector *yAxis, R3Graph::R3Vector *xAxis)
{
    // в системе координат карты:
    // y смотрит на север и является касательным к меридиану проходящему через центр земли
    // x ему перпендикулярен и смотрит вправо (на восток)
    *xAxis = R3Graph::R3Vector(0, 0, 1).vectorProduct(toPlane).normalize();
    *yAxis = toPlane.vectorProduct(*xAxis).normalize();
}

// Используя вектор к данной точке на поверхности земли, преобразует её координаты в геодезические
void earthCoords(const R3Graph::R3Vector& radiusVec, double *lat, double *lon){
    double phi = atan2(radiusVec.y, radiusVec.x);
    *lon = phi * 180/PI;

    double theta = radiusVec.angle(R3Graph::R3Vector(0, 0, 1)); // находим угол между направлением 'вверх' и нашим радиус-вектором
    *lat = (PI/2 - theta) * (180/PI); // т.к у нас получается на экваторе theta = PI/2, растущий к южному полюсу
}