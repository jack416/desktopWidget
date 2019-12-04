/****************************************************************************
** Copyright (c) 2019 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#ifndef GEO_H
#define GEO_H

#include <QtCore>

namespace geo { //==============================================================

const qreal earth_a            = 6378137.0;           // Большая полуось эллипсоида (Экваториальный радиус)
const qreal earth_b            = 6356752.3142;        // Малая полуось эллипсоида
const qreal earth_e            = 0.0818191908426;     // Эксцентриситет
const qreal earth_equator      = 40075016.685578488;  // Длина экватора в метрах
const qreal earth_half_equator = earth_equator / 2.0; // половина экватора

//==============================================================================
QPointF coordGeoToMap(qreal latitude, qreal longitude, qreal map_width, qreal cx=0, qreal cy=0);
QPointF coordMapToGeo(qreal x, qreal y, qreal map_width, qreal cx=0, qreal cy=0);

} // namespace geo //===========================================================
#endif // GEO_H
