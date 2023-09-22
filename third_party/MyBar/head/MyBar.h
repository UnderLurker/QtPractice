//
// Created by 常笑男 on 2023/9/22.
//

#ifndef CLIONWIDGET_MYBAR_H
#define CLIONWIDGET_MYBAR_H

#include <QObject>
#include <QMenuBar>
#include <QStatusBar>
#include <QPlainTextEdit>

class MyStatusBar : public QStatusBar {
    Q_OBJECT
public:
    explicit MyStatusBar(QWidget *_p = nullptr);
    ~MyStatusBar() override;
};

class MyMenuBar : public QMenuBar{
    Q_OBJECT
public:
    explicit MyMenuBar(QWidget *_p = nullptr);
    ~MyMenuBar() override;
};

class MyPlainTextEdit : public QPlainTextEdit{
    Q_OBJECT
public:
    explicit MyPlainTextEdit(QWidget *parent = nullptr);
    ~MyPlainTextEdit() override = default;
};

#endif //CLIONWIDGET_MYBAR_H
