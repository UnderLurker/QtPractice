//
// Created by 常笑男 on 2023/10/1.
//

#include "MyHangWidget.h"
#include <QPainter>
#include <QDebug>
#include <QBitmap>
#include <QMouseEvent>

MyHangWidget::MyHangWidget(QWidget *_p) : QWidget(_p){
    move(100,100);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground); //不加这个会导致图片边缘有白边
    //强制初始化qrc资源，原因：本代码用于编译静态库，qt中资源文件若要编译就要生成一个cpp文件，需要这个宏
    Q_INIT_RESOURCE(resource);
    pixmap = new QPixmap(":/hang/Resources/hang/lighting.png");
    Q_CLEANUP_RESOURCE(resource);

    resize(pixmap->size());
    setMask(pixmap->mask());

    pos = QPoint();
}

void MyHangWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.save();

    painter.drawPixmap(0,0,*pixmap);

    painter.restore();
}

MyHangWidget::~MyHangWidget() {
    delete pixmap;
}

void MyHangWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    pos = event->globalPos()-geometry().topLeft();
}

void MyHangWidget::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    if(pos == QPoint())
        return;
    move(event->globalPos()-pos);
}

void MyHangWidget::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    pos = QPoint();
}
