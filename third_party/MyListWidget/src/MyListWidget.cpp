//
// Created by 常笑男 on 2023/9/13.
//
#include "MyListWidget.h"
#include "ListItemRole.h"
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QDebug>
#include <QMouseEvent>

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
//    Q_UNUSED(option)
    QStyleOptionViewItem viewItem(option);
    initStyleOption(&viewItem,index);

    QVariant var = index.data(Role::StudentRole);
    StudentItem item = var.value<StudentItem>();

    double itemWidth = 50, itemHeight = 30;
    double curRowHeight = index.row() * itemHeight;

    painter->save();
//    qDebug()<<"row:"<<index.row()<<"\tcheckState:"<<viewItem.checkState;
    if(index.row()>=0){
        QRectF rect1(itemWidth*0,curRowHeight,itemWidth,itemHeight);
        QRectF rect2(itemWidth*1,curRowHeight,itemWidth,itemHeight);
        QRectF rect3(itemWidth*2,curRowHeight,itemWidth,itemHeight);
        QRect rowRect(0,curRowHeight,itemWidth*3,itemHeight);
        if(rowRect.contains(_mouse_pos)){
            painter->fillRect(rowRect,Qt::green);
        }
        else{
            painter->fillRect(rowRect,Qt::white);
        }

        painter->drawText(rect1,Qt::AlignRight,item.name);
        painter->drawText(rect2,Qt::AlignRight,QString::number(item.age));
        painter->drawText(rect3,Qt::AlignRight,item.sex);


    }
    painter->restore();
}

bool MyListWidgetItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                           const QModelIndex &index) {
    auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
    _mouse_pos = mouseEvent->pos();
    switch (mouseEvent->type()) {
        case QEvent::MouseButtonPress:{
            emit selected(index.row());
            break;
        }
    }
    return true;
}

QSize MyListWidgetItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::sizeHint(option, index);
    QSize res;
    res.setHeight(30);
    return res;
}
