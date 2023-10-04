//
// Created by 常笑男 on 2023/10/1.
//

#ifndef CLIONWIDGET_MYHANGWIDGET_H
#define CLIONWIDGET_MYHANGWIDGET_H

#include <QWidget>
#include <QObject>
#include <QPoint>
#include <QEvent>
#include <QTcpSocket>
#include <QImage>
#include <windows.h>


class MyHangWidget : public QWidget {
    Q_OBJECT
public:
    explicit MyHangWidget(QWidget *_p = nullptr);
    ~MyHangWidget() override;
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *event) override;
public slots:
    void timeOut();
private:
    QPoint pos;
    QEvent::Type state;
    QTcpSocket *tcpSocket;
    QTimer *timer;
    QImage *cpuImage;
    QImage *memoryImage;
    MEMORYSTATUSEX memoryStatus;
    double cpuLoad{0};
    FILETIME preIdleTime;
    FILETIME preKernelTime;
    FILETIME preUserTime;
};


#endif //CLIONWIDGET_MYHANGWIDGET_H
