//
// Created by 常笑男 on 2023/9/15.
//
#include "CustomWindow.h"
#include <QListWidgetItem>
#include <QBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QShortcut>

CustomWindow::CustomWindow(QWidget* _p)
    : QMainWindow(_p){
    resize(800,400);
    btn = new MyButton(this);
    btn->resize(100,100);
    btn->move(100,100);

    MyButtonContent content;
    content.day=QString::number(20);
    btn->setContent(content);
}

CustomWindow::~CustomWindow(){

}