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
    effect->setColor(Qt::black);
    this->setGraphicsEffect(effect);
}

MyButton::~MyButton() = default;

void MyButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.save();

    QLinearGradient bgLinear(0,0,0,QWidget::height());
    QLinearGradient fontLiner(0,0,0,QWidget::height());
    bgLinear.setColorAt(0.25,QColor("#90CBFB"));
    bgLinear.setColorAt(0.9,QColor(Qt::white));
    fontLiner.setColorAt(0.25,QColor(Qt::white));
    fontLiner.setColorAt(0.9,QColor(Qt::black));
    if (state() == QEvent::MouseButtonPress) {
        bgLinear.setColorAt(0.25,QColor("#FEA443"));
        fontLiner.setColorAt(0.9,QColor("#FEA443"));
    }
    QPen fontPen(fontLiner,40);
    QPen radiusRectPen(Qt::NoBrush,0);
    QFont textFont(tr("Consolas"),30,QFont::Bold);

    //画背景
    painter.setBrush(bgLinear);
    painter.setPen(radiusRectPen);
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
