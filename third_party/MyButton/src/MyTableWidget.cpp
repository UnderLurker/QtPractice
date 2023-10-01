//
// Created by Administrator on 2023/9/25.
//

#include "MyTableWidget.h"
#include "MyButton.h"
#include <QAbstractItemView>
#include <QDebug>
#include <QHeaderView>
#include <QPainter>
#include <QApplication>

const QStringList weeks={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

#define TABLE_CELL_WIDTH 80
#define TABLE_CELL_HEIGHT 80

bool TablePos::operator<(const TablePos& p) const {
    if(row==p.row)
        return col<p.col;
    return row<p.row;
}

void TablePos::swap(TablePos& p){
    int rTemp=row,cTemp = col;
    row=p.row;
    col=p.col;
    p.row=rTemp;
    p.col=cTemp;
}

MyTableWidget::MyTableWidget(int row, int col, QWidget* _p)
    : QTableWidget(row,col,_p)
{
    startPos.row=0;
    startPos.col=0;
    endPos.row=0;
    endPos.col=0;
    setHorizontalHeader(new MyHHeaderView(Qt::Horizontal));
    setHorizontalHeaderLabels(weeks);
    verticalHeader()->hide();
    setAlternatingRowColors(false);
    setShowGrid(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::NoSelection);
    setMouseTracking(true);

    QPalette p = this->palette();
    p.setColor(QPalette::Button,QColor(Qt::white));
    setPalette(p);

    for(int r=0;r<5;r++){
        setRowHeight(r,TABLE_CELL_HEIGHT);
        for(int c=0;c<7;c++){
            setColumnWidth(c,TABLE_CELL_WIDTH);
            auto *btn = new MyButton(this);
            btn->setFixedSize(TABLE_CELL_WIDTH,TABLE_CELL_HEIGHT);
            btn->setPaintSize(QSize(60,60));
            btn->setMarginMode(Center);

            MyButtonContent content;
            content.day=QString::number(r*7+c);
            btn->setContent(content);
            setCellWidget(r,c,btn);

            connect(btn,&MyButton::mouseClick,this,&MyTableWidget::contentClick);
        }
    }
}

MyTableWidget::~MyTableWidget(){

}

void MyTableWidget::contentClick(QPoint pos) {
    clickCount=(clickCount+1)%2;
    QPoint relativePos = pos - window()->pos() - this->pos();
    relativePos.setY(relativePos.y()-horizontalHeader()->height()-style()->pixelMetric(QStyle::PM_TitleBarHeight));
    auto model = this->indexAt(relativePos);
    auto btn = (MyButton*)indexWidget(model);
    if(btn == nullptr)
        return;

    if(clickCount == 1){
        //修改按钮样式
        for(int i=startPos.row;i<=endPos.row;i++){
            for(int j=(i==startPos.row?startPos.col:0);j<=(i==endPos.row?endPos.col:(columnCount()-1));j++){
                auto otherBtn = (MyButton*) cellWidget(i,j);
                otherBtn->setTimeRange(OtherTime);
                otherBtn->update();
            }
        }
        startPos.row = model.row();
        startPos.col = model.column();
        endPos.row = 0;
        endPos.col = 0;
        btn->setTimeRange(StartTime);
        emit startTimeClick(btn->content());
        emit endTimeClick(MyButtonContent());
    }
    else if(clickCount == 0){
        endPos.row = model.row();
        endPos.col = model.column();
        if(endPos<startPos){
            endPos.swap(startPos);
        }
        btn->setTimeRange(EndTime);
        //修改按钮样式
        for(int i=startPos.row;i<=endPos.row;i++){
            for(int j=(i==startPos.row?startPos.col+1:0);j<=(i==endPos.row?endPos.col-1:(columnCount()-1));j++){
                auto otherBtn = (MyButton*) cellWidget(i,j);
                otherBtn->setTimeRange(RangeTime);
                otherBtn->update();
            }
        }
        emit endTimeClick(btn->content());
    }
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
