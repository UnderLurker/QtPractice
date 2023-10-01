//
// Created by 常笑男 on 2023/9/23.
//

#include "ButtonUtility.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

QPainterPath ButtonUtility::getRadiusRectPath(const QRect &rect, int radius, int radiusPos) {
    return ButtonUtility::getRadiusRectPath(rect,radius,radius,radius,radius,radiusPos);
}

QPainterPath
ButtonUtility::getRadiusRectPath(const QRect &rect, int topLeftRadius, int topRightRadius, int bottomLeftRadius,
                                 int bottomRightRadius, int radiusPos) {
    QPainterPath path;

    path.moveTo(rect.topLeft().x(),rect.topLeft().y()+topLeftRadius);

    if(radiusPos&topLeft){
        //topLeft
        path.arcTo(QRectF(rect.topLeft(),QSizeF(topLeftRadius*2,topLeftRadius*2)),180,-90);
    }
    else{
        path.lineTo(rect.topLeft());
        path.lineTo(rect.topLeft().x()+topLeftRadius,rect.topLeft().y());
    }
    path.lineTo(rect.topRight().x()-topRightRadius,rect.topRight().y());

    if(radiusPos&topRight){
        //topRight
        path.arcTo(QRectF(rect.topRight().x()-topRightRadius*2,rect.topRight().y(),topRightRadius*2,topRightRadius*2),
                   90,-90);
    }
    else{
        path.lineTo(rect.topRight());
        path.lineTo(rect.topRight().x(),rect.topRight().y()+topRightRadius);
    }
    path.lineTo(rect.bottomRight().x(),rect.bottomRight().y()-bottomLeftRadius);

    if(radiusPos&bottomRight){
        //BottomRight
        path.arcTo(QRectF(rect.bottomRight().x()-bottomLeftRadius*2,rect.bottomRight().y()-bottomLeftRadius*2,bottomLeftRadius*2,bottomLeftRadius*2),
                   0,-90);
    }
    else{
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.bottomRight().x()-bottomLeftRadius,rect.bottomRight().y());
    }
    path.lineTo(rect.bottomLeft().x()+bottomRightRadius,rect.bottomLeft().y());

    if(radiusPos&bottomLeft){
        //BottomLeft
        path.arcTo(QRectF(rect.bottomLeft().x(),rect.bottomLeft().y()-bottomRightRadius*2,bottomRightRadius*2,bottomRightRadius*2),
                   270,-90);
    }
    else{
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.bottomLeft().x(),rect.bottomLeft().y()-bottomRightRadius);
    }
    path.lineTo(rect.topLeft().x(),rect.topLeft().y()+topLeftRadius);

    if(!(radiusPos&topLeft)){
        path.lineTo(rect.topLeft());
    }
    path.closeSubpath();
    return path;
}

void RectUtility::paintShadow(QPainter* const painter,const QRect& outRect) {
    painter->save();

    QPoint center(outRect.left()+int(outRect.width()/2),outRect.top()+int(outRect.height()/2));
    QPen pen(QBrush(Qt::transparent),0);
    painter->setPen(pen);

    //top
    QLinearGradient top(0,outRect.top(),0,(int)(outRect.height()/2));
    top.setColorAt(0,QColor(Qt::white));
    top.setColorAt(1,QColor(Qt::gray));

    QPainterPath topPath;
    topPath.moveTo(outRect.topLeft());
    topPath.lineTo(outRect.topRight());
    topPath.lineTo(center);
    topPath.lineTo(outRect.topLeft());

    painter->setBrush(top);
    painter->drawPath(topPath);

    //left
    QLinearGradient left(outRect.left(),0,(int)(outRect.width()/2),0);
    left.setColorAt(0,QColor(Qt::white));
    left.setColorAt(1,QColor(Qt::gray));

    QPainterPath leftPath;
    leftPath.moveTo(outRect.topLeft());
    leftPath.lineTo(center);
    leftPath.lineTo(outRect.bottomLeft());
    leftPath.lineTo(outRect.topLeft());

    painter->setBrush(left);
    painter->drawPath(leftPath);

    //bottom
    QLinearGradient bottom(0,outRect.bottom(),0,(int)(outRect.height()/2));
    bottom.setColorAt(0,QColor(Qt::white));
    bottom.setColorAt(1,QColor(Qt::gray));

    QPainterPath bottomPath;
    bottomPath.moveTo(outRect.bottomLeft());
    bottomPath.lineTo(center);
    bottomPath.lineTo(outRect.bottomRight());
    bottomPath.lineTo(outRect.bottomLeft());

    painter->setBrush(bottom);
    painter->drawPath(bottomPath);

    //bottom
    QLinearGradient right(outRect.right(),0,(int)(outRect.width()/2),0);
    right.setColorAt(0,QColor(Qt::white));
    right.setColorAt(1,QColor(Qt::gray));

    QPainterPath rightPath;
    rightPath.moveTo(outRect.bottomRight());
    rightPath.lineTo(center);
    rightPath.lineTo(outRect.topRight());
    rightPath.lineTo(outRect.bottomRight());

    painter->setBrush(right);
    painter->drawPath(rightPath);

    painter->restore();
}