//
// Created by 常笑男 on 2023/9/15.
//
#include "CustomWindow.h"
#include "MyListWidget.h"
#include "ListItemRole.h"
#include <QListWidgetItem>
#include <QBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QSlider>
#include <QShortcut>

CustomWindow::CustomWindow(QWidget* _p)
    : QWidget(_p){
    resize(800,400);
    menuWight = new QWidget;
    menuWight->setFixedHeight(20);
    menubar = new QMenuBar(menuWight);
    QMenu *file = new QMenu("file");
    QMenu *add = new QMenu("add");
    add->addAction(tr("project"));
    add->addAction(tr("file"));

    QAction *open = new QAction(tr("open"));
    open->setShortcut(QKeySequence(tr("Ctrl+k,Ctrl+c")));
    connect(open,&QAction::triggered,this,[](bool){qDebug()<<"open";});

    file->addAction(open);
    file->addSeparator();
    file->addMenu(add);
    file->addSection(tr("section"));
    menubar->addMenu(file);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    QWidget *vwidget=new QWidget;
    vwidget->setMaximumHeight(50);
    vwidget->setMinimumHeight(50);
    vwidget->setStyleSheet(tr("background-color:red"));

    QBoxLayout *vlayout=new QBoxLayout(QBoxLayout::LeftToRight,vwidget);
    hlayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");
    QPushButton *button6 = new QPushButton("LeftToRight");
    QPushButton *button7 = new QPushButton("RightToLeft");
    QPushButton *button8 = new QPushButton("TopToBottom");
    QPushButton *button9 = new QPushButton("BottomToTop");
    QSlider *slider=new QSlider(Qt::Orientation::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setMaximumSize(100,50);
    slider->setTickInterval(20);

    layout->addWidget(menuWight);

    vlayout->addWidget(button6);
    vlayout->addWidget(button7);
    vlayout->addWidget(button8);
    vlayout->addWidget(button9);
    vlayout->addWidget(slider);
    layout->addWidget(vwidget);

    hlayout->addWidget(button1);
    hlayout->addWidget(button2);
    hlayout->addWidget(button3);
    hlayout->addWidget(button4);
    hlayout->addWidget(button5);
    layout->addLayout(hlayout);
    layout->addStretch();

    connect(button6,&QPushButton::clicked,this,[&](bool){
        hlayout->setDirection(QBoxLayout::LeftToRight);
    });
    connect(button7,&QPushButton::clicked,this,[&](bool){
        hlayout->setDirection(QBoxLayout::RightToLeft);
    });
    connect(button8,&QPushButton::clicked,this,[&](bool){
        hlayout->setDirection(QBoxLayout::TopToBottom);
    });
    connect(button9,&QPushButton::clicked,this,[&](bool){
        hlayout->setDirection(QBoxLayout::BottomToTop);
    });
    connect(slider, &QSlider::sliderMoved,this, &CustomWindow::changeSpacing);
//    auto *w=new MyListWidget(this);
//
//    auto item1 = new QListWidgetItem;
//    auto item2 = new QListWidgetItem;
//    auto item3 = new QListWidgetItem;
//    StudentItem s1(tr("cxn"),24,tr("male"));
//    item1->setData(Role::StudentRole,QVariant::fromValue(s1));
//    item2->setData(Role::StudentRole,QVariant::fromValue(s1));
//    item3->setData(Role::StudentRole,QVariant::fromValue(s1));
//
//    w->addItem(item1);
//    w->addItem(item2);
//    w->addItem(item3);
//    w->show();
}

CustomWindow::~CustomWindow(){

}

void CustomWindow::changeSpacing(int val) {
    hlayout->setSpacing(val);
}
