//
// Created by 常笑男 on 2023/9/15.
//
#include "CustomWindow.h"
#include "MyListWidget.h"
#include "ListItemRole.h"
#include <QListWidgetItem>

CustomWindow::CustomWindow(QWidget* _p)
    : QWidget(_p){
    auto *w=new MyListWidget(this);

    auto item1 = new QListWidgetItem;
    auto item2 = new QListWidgetItem;
    auto item3 = new QListWidgetItem;
    StudentItem s1(tr("cxn"),24,tr("mole"),1);
    StudentItem s2(tr("cxn"),24,tr("mole"),2);
    StudentItem s3(tr("cxn"),24,tr("mole"),3);
    item1->setData(Role::StudentRole,QVariant::fromValue(s1));
    item2->setData(Role::StudentRole,QVariant::fromValue(s2));
    item3->setData(Role::StudentRole,QVariant::fromValue(s3));

    w->addItem(item1);
    w->addItem(item2);
    w->addItem(item3);
    w->show();
}

CustomWindow::~CustomWindow(){

}