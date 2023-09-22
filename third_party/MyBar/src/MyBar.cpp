//
// Created by 常笑男 on 2023/9/22.
//

#include "MyBar.h"

MyStatusBar::MyStatusBar(QWidget *_p) : QStatusBar(_p) {

}

MyStatusBar::~MyStatusBar() = default;

////////////////////////////////////

MyMenuBar::MyMenuBar(QWidget *_p) : QMenuBar(_p) {

}

MyMenuBar::~MyMenuBar() = default;

/////////////////////////////////////

MyPlainTextEdit::MyPlainTextEdit(QWidget *parent) : QPlainTextEdit(parent) {

}
