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
#include <QTableWidget>

const QStringList weeks={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

CustomWindow::CustomWindow(QWidget* _p)
    : QMainWindow(_p){
    resize(800,400);
    QTableWidget *table = new QTableWidget(5,7,this);
    table->resize(800,400);
    table->setHorizontalHeaderLabels(weeks);
    for(int r=0;r<5;r++){
        table->setRowHeight(r,60);
        for(int c=0;c<7;c++){
            table->setColumnWidth(c,60);
            MyButton *btn = new MyButton(this);
//            btn->resize(30,70);

            MyButtonContent content;
            content.day=QString::number(r*7+c);
            btn->setContent(content);
            table->setCellWidget(r,c,btn);
        }
    }
}

CustomWindow::~CustomWindow(){

}