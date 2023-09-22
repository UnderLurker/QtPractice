//
// Created by 常笑男 on 2023/9/15.
//
#include "CustomWindow.h"
#include "MyListWidget.h"
#include "ListItemRole.h"
#include <QListWidgetItem>
#include <QBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QShortcut>

CustomWindow::CustomWindow(QWidget* _p)
    : QMainWindow(_p){
    resize(800,400);
    menubar = new MyMenuBar;
    QMenu *file = new QMenu("file");
    QMenu *add = new QMenu("add");
    add->addAction(tr("project"));
    add->addAction(tr("file"));

    QAction *open = new QAction(tr("open"));
    open->setShortcut(QKeySequence(tr("Ctrl+k,Ctrl+c")));
    connect(open,&QAction::triggered,this,&CustomWindow::openFile);

    file->addAction(open);
    file->addSeparator();
    file->addMenu(add);
    file->addSection(tr("section"));
    menubar->addMenu(file);

    statusbar = new MyStatusBar;
    statusbar->addPermanentWidget(new QLabel(tr("Permanent")));
    statusbar->addWidget(new QLabel(tr("label")));

    textEdit = new MyPlainTextEdit;

    this->setMenuBar(menubar);
    this->setStatusBar(statusbar);
    this->setCentralWidget(textEdit);
}

CustomWindow::~CustomWindow(){

}

void CustomWindow::openFile(bool checked) {
    textEdit->clear();
    QString filePath = QFileDialog::getOpenFileName();
    QFile file(filePath);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    QByteArray content = file.readAll();
    textEdit->setPlainText(content);
    file.close();
}
