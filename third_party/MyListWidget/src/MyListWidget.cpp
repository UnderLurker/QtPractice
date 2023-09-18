//
// Created by 常笑男 on 2023/9/13.
//
#include "MyListWidget.h"
#include "ListItemRole.h"
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QDebug>
#include <QStyle>
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
    Q_ASSERT(index.isValid());
    QStyleOptionViewItem viewItem(option);
    initStyleOption(&viewItem,index);

    QVariant var = index.data(Role::StudentRole);
    StudentItem item = var.value<StudentItem>();

    double itemWidth = 50, itemHeight = 30;
    double curRowHeight = index.row() * itemHeight;

    painter->save();

    QRectF rect1(itemWidth*0,curRowHeight,itemWidth,itemHeight);
    QRectF rect2(itemWidth*1,curRowHeight,itemWidth,itemHeight);
    QRectF rect3(itemWidth*2,curRowHeight,itemWidth,itemHeight);
    if(item.selected.testFlag(QStyle::State_Selected) && curRow == index.row()){
        painter->fillRect(viewItem.rect,Qt::green);
    }
    else{
        painter->fillRect(viewItem.rect,Qt::white);
    }
    if(item.selected.testFlag(QStyle::State_MouseOver)){
        painter->fillRect(viewItem.rect,Qt::red);
    }

    painter->drawText(rect1,Qt::AlignRight | Qt::AlignVCenter,item.name);
    painter->drawText(rect2,Qt::AlignRight | Qt::AlignVCenter,QString::number(item.age));
    painter->drawText(rect3,Qt::AlignRight | Qt::AlignVCenter,item.sex);

    painter->restore();
}

bool MyListWidgetItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                           const QModelIndex &index) {
    auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
    QStyleOptionViewItem viewItem(option);
    initStyleOption(&viewItem,index);

    QVariant var = index.data(Role::StudentRole);
    StudentItem item = var.value<StudentItem>();

    switch (mouseEvent->type()) {
        case QEvent::MouseButtonPress:{
            curRow = index.row();
            item.selected |= QStyle::State_Selected;
            model->setData(index,QVariant::fromValue(item),Role::StudentRole);
            return true;
        }
        case QEvent::Enter:{
            item.selected |= QStyle::State_MouseOver;
            model->setData(index,QVariant::fromValue(item),Role::StudentRole);
            break;
        }
        case QEvent::Leave:{
            item.selected = (QStyle::State)((int)item.selected & ~(int)QStyle::State_MouseOver);
            model->setData(index,QVariant::fromValue(item),Role::StudentRole);
            break;
        }
        default:
            break;
    }
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}

QSize MyListWidgetItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::sizeHint(option, index);
    QSize res;
    res.setHeight(30);
    return res;
}
