//
// Created by Administrator on 2023/9/25.
//

#include "MyTableWidget.h"
#include "MyButton.h"
#include <QAbstractItemView>
#include <QDebug>
#include <QHeaderView>
#include <QPainter>

const QStringList weeks={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

#define TABLE_CELL_WIDTH 60
#define TABLE_CELL_HEIGHT 60

MyTableWidget::MyTableWidget(int row, int col, QWidget* _p)
    : QTableWidget(row,col,_p)
{
    setHorizontalHeader(new MyHHeaderView(Qt::Horizontal));
    setHorizontalHeaderLabels(weeks);
    verticalHeader()->hide();
    setAlternatingRowColors(false);
    setShowGrid(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);

    QPalette p = this->palette();
    p.setColor(QPalette::Button,QColor(Qt::white));
    setPalette(p);

    for(int r=0;r<5;r++){
        setRowHeight(r,TABLE_CELL_HEIGHT);
        for(int c=0;c<7;c++){
            setColumnWidth(c,TABLE_CELL_WIDTH);
            auto *btn = new MyButton(this);
            btn->setFixedSize(TABLE_CELL_WIDTH,TABLE_CELL_HEIGHT);
            btn->setPaintSize(QSize(50,50));
            btn->setMarginMode(Center);

            MyButtonContent content;
            content.day=QString::number(r*7+c);
            btn->setContent(content);
            setCellWidget(r,c,btn);

            connect(btn,&MyButton::mouseClick,this,[](QString content){
                qDebug()<<"content: "<<content;
            });
        }
    }
}

MyTableWidget::~MyTableWidget(){

}

/////////////////////////////////////////////////

MyHHeaderView::MyHHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation,parent){
    setCascadingSectionResizes(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);
    setSectionResizeMode(Fixed);

    QPalette p = this->palette();
    p.setColor(QPalette::Button,QColor(Qt::white));
    setPalette(p);
}

void MyHHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
    painter->save();

    painter->drawText(rect,Qt::AlignCenter,weeks[logicalIndex]);

    painter->restore();
}
