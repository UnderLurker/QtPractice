//
// Created by 常笑男 on 2023/9/13.
//
#include "MyListWidget.h"
#include "ListItemRole.h"
#include <QPainter>
#include <QRectF>

MyListWidget::MyListWidget(QWidget *_p)
    : QListWidget(_p){
    this->resize(200,100);
    this->setItemDelegate(new MyListWidgetItemDelegate());
}

MyListWidget::~MyListWidget(){

}

MyListWidgetItemDelegate::MyListWidgetItemDelegate(QWidget* _p)
    : QStyledItemDelegate(_p)
{

}

MyListWidgetItemDelegate::~MyListWidgetItemDelegate(){

}

void MyListWidgetItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    Q_UNUSED(option)

    QVariant var = index.data(Role::StudentRole);
    StudentItem item = var.value<StudentItem>();

    double itemWidth = 50, itemHeight = 20;
    double curRowHeight = (item.no - 1) * itemHeight;

    painter->save();

    QRectF rect1(itemWidth*0,curRowHeight,itemWidth,itemHeight);
    QRectF rect2(itemWidth*1,curRowHeight,itemWidth,itemHeight);
    QRectF rect3(itemWidth*2,curRowHeight,itemWidth,itemHeight);

    painter->drawText(rect1,Qt::AlignRight,item.name);
    painter->drawText(rect2,Qt::AlignRight,QString::number(item.age));
    painter->drawText(rect3,Qt::AlignRight,item.sex);

    painter->restore();

}