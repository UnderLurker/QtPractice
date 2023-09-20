//
// Created by 常笑男 on 2023/9/15.
//

#ifndef CLIONWIDGET_CUSTOMWINDOW_H
#define CLIONWIDGET_CUSTOMWINDOW_H

#include <QWidget>
#include <QObject>
#include <QBoxLayout>
#include <QMenuBar>

class CustomWindow : public QWidget{
    Q_OBJECT
public:
    explicit CustomWindow(QWidget* _p = nullptr);
    ~CustomWindow();
private:
    QBoxLayout *hlayout;
    QWidget *menuWight;
    QMenuBar *menubar;

public slots:
    void changeSpacing(int val);
};


#endif //!CLIONWIDGET_CUSTOMWINDOW_H
