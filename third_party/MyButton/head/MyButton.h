//
// Created by 常笑男 on 2023/9/23.
//

#ifndef CLIONWIDGET_MYBUTTON_H
#define CLIONWIDGET_MYBUTTON_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QEvent>

enum DataTimeRange {
    StartTime = 0,
    EndTime,
    RangeTime,
    OtherTime
};

using ButtonState = QEvent::Type;

struct MyButtonContent {
    QString day;
    QString description;
};

class MyButton : public QPushButton {
Q_OBJECT
public:
    explicit MyButton(QWidget *_p = nullptr);

    ~MyButton() override;

    void paintEvent(QPaintEvent *event) override;

    bool event(QEvent *e) override;

public:
    ButtonState state() const { return _state; }
    MyButtonContent content() const {return _content;}

    void setState(const ButtonState& state) { _state = state; update();}
    void setContent(const MyButtonContent& content) { _content = content; update();}
    qreal fontSize{20};
    qreal fontWeight{10};
private:
    ButtonState _state;
    MyButtonContent _content;
    DataTimeRange _timeRange{OtherTime};
};


#endif //CLIONWIDGET_MYBUTTON_H
