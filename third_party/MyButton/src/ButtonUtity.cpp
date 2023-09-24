//
// Created by 常笑男 on 2023/9/23.
//

#include "ButtonUtility.h"

QPainterPath ButtonUtility::getRadiusRectPath(const QRect &rect, int radius, int radiusPos) {
    QPainterPath path;

    path.moveTo(rect.topLeft().x(),rect.topLeft().y()+radius);

    if(radiusPos&topLeft){
        //topLeft
        path.arcTo(QRectF(rect.topLeft(),QSizeF(radius*2,radius*2)),180,-90);
    }
    else{
        path.lineTo(rect.topLeft());
        path.lineTo(rect.topLeft().x()+radius,rect.topLeft().y());
    }
    path.lineTo(rect.topRight().x()-radius,rect.topRight().y());

    if(radiusPos&topRight){
        //topRight
        path.arcTo(QRectF(rect.topRight().x()-radius*2,rect.topRight().y(),radius*2,radius*2),
                   90,-90);
    }
    else{
        path.lineTo(rect.topRight());
        path.lineTo(rect.topRight().x(),rect.topRight().y()+radius);
    }
    path.lineTo(rect.bottomRight().x(),rect.bottomRight().y()-radius);

    if(radiusPos&bottomRight){
        //BottomRight
        path.arcTo(QRectF(rect.bottomRight().x()-radius*2,rect.bottomRight().y()-radius*2,radius*2,radius*2),
                   0,-90);
    }
    else{
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.bottomRight().x()-radius,rect.bottomRight().y());
    }
    path.lineTo(rect.bottomLeft().x()+radius,rect.bottomLeft().y());

    if(radiusPos&bottomLeft){
        //BottomLeft
        path.arcTo(QRectF(rect.bottomLeft().x(),rect.bottomLeft().y()-radius*2,radius*2,radius*2),
                   270,-90);
    }
    else{
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.bottomLeft().x(),rect.bottomLeft().y()-radius);
    }
    path.lineTo(rect.topLeft().x(),rect.topLeft().y()+radius);

    if(!(radiusPos&topLeft)){
        path.lineTo(rect.topLeft());
    }
    path.closeSubpath();
    return path;
}