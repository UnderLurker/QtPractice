//
// Created by 常笑男 on 2023/9/15.
//

#ifndef CLIONWIDGET_CUSTOMWINDOW_H
#define CLIONWIDGET_CUSTOMWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QMenuBar>
#include "MyBar.h"

class CustomWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit CustomWindow(QWidget* _p = nullptr);
    ~CustomWindow() override;
    void openFile(bool checked);
private:
    MyMenuBar *menubar;
    MyStatusBar *statusbar;
    MyPlainTextEdit *textEdit;
};


#endif //!CLIONWIDGET_CUSTOMWINDOW_H
