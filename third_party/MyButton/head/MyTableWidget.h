//
// Created by Administrator on 2023/9/25.
//

#ifndef CLIONWIDGET_MYTABLEWIDGET_H
#define CLIONWIDGET_MYTABLEWIDGET_H

#include <QWidget>
#include <QObject>
#include <QHeaderView>
#include <QTableWidget>
#include <functional>

struct TablePos{
    int row;
    int col;
    bool operator<(const TablePos& p) const {
        if(row==p.row)
            return col<p.col;
        return row<p.row;
    }
    void swap(TablePos& p){
        int rTemp=row,cTemp = col;
        row=p.row;
        col=p.col;
        p.row=rTemp;
        p.col=cTemp;
    }
};

class MyTableWidget : public QTableWidget {
    Q_OBJECT
public:
    MyTableWidget(int row, int col, QWidget* _p = nullptr);
    ~MyTableWidget() override;
public slots:
    void contentClick(QPoint pos);
private:
    int clickCount{0};
    TablePos startPos;
    TablePos endPos;
};

class MyHHeaderView : public QHeaderView{
    Q_OBJECT
public:
    explicit MyHHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~MyHHeaderView() override = default;
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
};

#endif //CLIONWIDGET_MYTABLEWIDGET_H
