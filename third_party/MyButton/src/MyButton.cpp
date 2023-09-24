//
// Created by 常笑男 on 2023/9/23.
//

#include "MyButton.h"
#include "ButtonUtility.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>
#include <QGraphicsDropShadowEffect>
#include <QDebug>


MyButton::MyButton(QWidget *_p)
        : QPushButton(_p) {
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(70);
    effect->setColor(Qt::gray);
    this->setGraphicsEffect(effect);
}

MyButton::~MyButton() = default;

void MyButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.save();

    QLinearGradient otherBgLinear(0,0,0,QWidget::height());
    QLinearGradient otherFontLiner(0,0,0,QWidget::height());
    QLinearGradient rangeBgLinear(0,0,0,QWidget::height());
    QLinearGradient timeLinear(0,0,0,QWidget::height());
    otherBgLinear.setColorAt(0.25,QColor("#90CBFB"));
    otherBgLinear.setColorAt(0.9,QColor(Qt::white));
    otherFontLiner.setColorAt(0.25,QColor(Qt::white));
    otherFontLiner.setColorAt(0.9,QColor(Qt::black));
    rangeBgLinear.setColorAt(0.25,QColor("#A5AAA3"));
    rangeBgLinear.setColorAt(0.9,QColor(Qt::white));
    timeLinear.setColorAt(0.25,QColor("#3E4E69"));
    timeLinear.setColorAt(0.9,QColor(Qt::white));
    if (state() == QEvent::MouseButtonPress) {
        otherBgLinear.setColorAt(0.25,QColor("#FEA443"));
        otherFontLiner.setColorAt(0.9,QColor("#FEA443"));
    }
    QPen fontPen(otherFontLiner,fontWeight);
    QPen radiusRectPen(Qt::NoBrush,0);
    QFont textFont(tr("Consolas"),fontSize,QFont::Bold);

    switch (_timeRange) {
        case OtherTime:{
            painter.setBrush(otherBgLinear);
            painter.setPen(radiusRectPen);
            break;
        }
        case RangeTime:{
            painter.setBrush(rangeBgLinear);
            painter.setPen(radiusRectPen);
            break;
        }
        case StartTime:
        case EndTime:{
            painter.setBrush(timeLinear);
            painter.setPen(radiusRectPen);
            break;
        }
        default:
            break;
    }


    //画背景
    painter.drawPath(ButtonUtility::getRadiusRectPath(rect(),10,All));
    //画字体
    painter.setPen(fontPen);
    painter.setFont(textFont);
    painter.drawText(rect(),Qt::AlignCenter,_content.day);

    painter.restore();
}

bool MyButton::event(QEvent *e) {
    if(e->type() == QEvent::MouseButtonPress ||
        e->type() == QEvent::MouseButtonRelease ||
        e->type() == QEvent::MouseButtonDblClick){
        setState(e->type());
        update();
        return true;
    }
    return QPushButton::event(e);
}
