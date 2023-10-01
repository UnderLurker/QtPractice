//
// Created by 常笑男 on 2023/9/23.
//

#ifndef CLIONWIDGET_BUTTONUTILITY_H
#define CLIONWIDGET_BUTTONUTILITY_H

#include <QPainterPath>

enum RadiusPos{
    topLeft = 0x0001,
    topRight = 0x0010,
    top = topLeft | topRight,
    bottomRight = 0x0100,
    bottomLeft = 0x1000,
    bottom = bottomLeft | bottomRight,
    All = 0x1111
};

class ButtonUtility {
public:
    static QPainterPath getRadiusRectPath(const QRect& rect, int radius, int radiusPos);
    static QPainterPath getRadiusRectPath(const QRect& rect,
                                          int topLeftRadius,
                                          int topRightRadius,
                                          int bottomLeftRadius,
                                          int bottomRightRadius,
                                          int radiusPos);
};

class RectUtility{
public:
    static void paintShadow(QPainter* const painter,const QRect& outRect);
};

#endif //!CLIONWIDGET_BUTTONUTILITY_H
