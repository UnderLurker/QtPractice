//
// Created by 常笑男 on 2023/9/15.
//

#ifndef CLIONWIDGET_CUSTOMWINDOW_H
#define CLIONWIDGET_CUSTOMWINDOW_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include "MyTableWidget.h"
#include "MyHangWidget.h"

class CustomWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit CustomWindow(QWidget* _p = nullptr);
    ~CustomWindow() override;
public slots:
    void startTimeClick(MyButtonContent content);
    void endTimeClick(MyButtonContent content);
private:
    MyTableWidget *table;
    QLabel *startTime;
    QLabel *endTime;
    MyHangWidget *widget;
};


#endif //!CLIONWIDGET_CUSTOMWINDOW_H
