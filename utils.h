#ifndef UTILS_H
#define UTILS_H

#include "vector.h"

#include <QPointF>

using Vec3 = mats::Vector3<double>;
inline Vec3 q2v(const QPointF &p) {return Vec3(p.x(), p.y(), 0.0);}
inline QPointF v2q(const Vec3 &v) {return QPointF(v.x(), v.y());}

#endif // UTILS_H
