//
// Created by 常笑男 on 2023/9/13.
//

#ifndef CLIONWIDGET_MYLISTWIDGET_H
#define CLIONWIDGET_MYLISTWIDGET_H

#include <QListWidget>
#include <QWidget>
#include <QObject>
#include <QStyledItemDelegate>
#include <utility>

class MyListWidget : public QListWidget{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *_p = nullptr);
    ~MyListWidget() override;

public:

};

struct StudentItem{
    QString name;
    int age{};
    QString sex;
    int no{};
    StudentItem() = default;
    StudentItem(QString  _n,const int& _a,QString  _s,int _no)
        :name(std::move(_n)),
        age(_a),
        sex(std::move(_s)),
        no(_no){}
};

Q_DECLARE_METATYPE(StudentItem)

class MyListWidgetItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    explicit MyListWidgetItemDelegate(QWidget* _p = nullptr);
    ~MyListWidgetItemDelegate() override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif //!CLIONWIDGET_MYLISTWIDGET_H
