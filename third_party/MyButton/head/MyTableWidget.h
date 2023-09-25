//
// Created by Administrator on 2023/9/25.
//

#ifndef CLIONWIDGET_MYTABLEWIDGET_H
#define CLIONWIDGET_MYTABLEWIDGET_H

#include <QWidget>
#include <QObject>
#include <QHeaderView>
#include <QTableWidget>

class MyTableWidget : public QTableWidget {
    Q_OBJECT
public:
    MyTableWidget(int row, int col, QWidget* _p = nullptr);
    ~MyTableWidget() override;
private:

};

class MyHHeaderView : public QHeaderView{
    Q_OBJECT
public:
    explicit MyHHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~MyHHeaderView() = default;
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
};

#endif //CLIONWIDGET_MYTABLEWIDGET_H
