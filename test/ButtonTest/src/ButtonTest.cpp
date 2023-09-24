
//
// Created by 常笑男 on 2023/9/13.
//
#include <QApplication>
#include <QString>
#include <QStyleFactory>
#include "CustomWindow.h"
#include "MyListWidget.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *widget=new CustomWindow(nullptr);
    widget->show();
    QApplication::setStyle(QStyleFactory::create(QString("Motif")));
    QApplication::setPalette(QApplication::style()->standardPalette());
    return QApplication::exec();
}
