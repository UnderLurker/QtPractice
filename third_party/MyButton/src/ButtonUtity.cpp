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

void RectUtility::paintShadow(QPainter* const painter, const QRect &rect, int radius) {
    double a = rect.width()/2.0,b=rect.height()/2.0;
    QRadialGradient shadowBrush(a + rect.left(),b + rect.top(), qSqrt(a*a+b*b));
    shadowBrush.setColorAt(0,Qt::black);
    shadowBrush.setColorAt(1,Qt::white);
    QPen shadowPen(shadowBrush,radius);

    for(int i=1;i<=radius;i++){
        painter->setPen(shadowPen);
        painter->setBrush(QBrush(Qt::transparent));
        QRect oneShadow(rect.topLeft().x()-i, rect.topLeft().y()-i,
                        rect.width()+2*i, rect.height()+2*i);
//        qDebug()<<"oneShadow"<<oneShadow;
        painter->drawPath(ButtonUtility::getRadiusRectPath(oneShadow,10,All));
    }

}