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
#include "MyButton.h"

struct TablePos{
    int row;
    int col;
    bool operator<(const TablePos& p) const;
    void swap(TablePos& p);
};

class MyTableWidget : public QTableWidget {
    Q_OBJECT
public:
    MyTableWidget(int row, int col, QWidget* _p = nullptr);
    ~MyTableWidget() override;
signals:
    void startTimeClick(MyButtonContent content);
    void endTimeClick(MyButtonContent content);
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
