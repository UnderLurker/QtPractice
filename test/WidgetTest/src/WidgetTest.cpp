//
// Created by 常笑男 on 2023/9/13.
//
#include <QApplication>
#include <QString>
#include "CustomWindow.h"
#include "MyListWidget.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *widget=new CustomWindow(nullptr);
    widget->resize(400,250);
    widget->show();
    return QApplication::exec();
}
