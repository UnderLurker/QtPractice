//
// Created by 常笑男 on 2023/10/1.
//

#ifndef CLIONWIDGET_MYHANGWIDGET_H
#define CLIONWIDGET_MYHANGWIDGET_H

#include <QWidget>
#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QEvent>
#include "MyTableWidget.h"
#include <QTcpSocket>


class MyHangWidget : public QWidget {
    Q_OBJECT
public:
    explicit MyHangWidget(QWidget *_p = nullptr);
    ~MyHangWidget() override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool event(QEvent *event) override;
public slots:
    void tcpConnected();
    void tcpReadyRead();
    void timeOut();
private:
    QPixmap *pixmap;
    QPoint pos;
    QEvent::Type state;
    MyTableWidget *table;
    QTcpSocket *tcpSocket;
    QTimer *timer;
};


#endif //CLIONWIDGET_MYHANGWIDGET_H
