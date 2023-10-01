//
// Created by 常笑男 on 2023/9/15.
//
#include "CustomWindow.h"
#include "MyTableWidget.h"
#include <QBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QShortcut>

CustomWindow::CustomWindow(QWidget* _p)
    : QMainWindow(_p){
    resize(800,600);

    table = new MyTableWidget(5,7,this);
    table->resize(800,600);

    startTime = new QLabel(this);
    startTime->resize(80,20);
    startTime->move(0,350);
    startTime->setAlignment(Qt::AlignCenter);
    endTime = new QLabel(this);
    endTime->resize(80,20);
    endTime->move(80,350);
    endTime->setAlignment(Qt::AlignCenter);

    connect(table,&MyTableWidget::startTimeClick,this,&CustomWindow::startTimeClick);
    connect(table,&MyTableWidget::endTimeClick,this,&CustomWindow::endTimeClick);

    widget = new MyHangWidget;
    widget->show();
}

CustomWindow::~CustomWindow(){

}

void CustomWindow::startTimeClick(MyButtonContent content) {
    startTime->setText(content.toString());
}

void CustomWindow::endTimeClick(MyButtonContent content) {
    endTime->setText(content.toString());
}
