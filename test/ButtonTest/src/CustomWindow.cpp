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
    resize(800,400);

    table = new MyTableWidget(5,7,this);

    table->resize(800,400);
}

CustomWindow::~CustomWindow(){

}