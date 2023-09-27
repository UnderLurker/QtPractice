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

enum PaintMarginMode{
    Manual = 0,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    HCenter,
    VCenter,
    Center
};

using ButtonState = QEvent::Type;

struct MyButtonContent {
    QString day{};
    QString description{};
    QString toString() const;
};

class MyButton : public QPushButton {
Q_OBJECT
public:
    explicit MyButton(QWidget *_p = nullptr);

    ~MyButton() override;

    void paintEvent(QPaintEvent *event) override;

    bool event(QEvent *e) override;

signals:
    void mouseClick(QPoint pos);

public:
    ButtonState state() const { return _state; }
    MyButtonContent content() const {return _content;}
    QMargins paintMargin() const {return _margin;}
    QSize paintSize() const {return _paintSize;}
    PaintMarginMode marginMode() const {return _marginMode;}
    int shadowRadius() const {return _shadowRadius;}
    DataTimeRange timeRange() const {return _timeRange;}

    void setState(const ButtonState& state) { _state = state; update();}
    void setContent(const MyButtonContent& content) { _content = content; update();}
    //用来设置内部有效内容区域margin
    void setPaintMargin(const QMargins& margin);
    void setPaintSize(QSize size);
    void setMarginMode(PaintMarginMode mode) {_marginMode = mode;}
    void setShadowRadius(int shadowRadius);
    void setTimeRange(DataTimeRange timeRange){_timeRange=timeRange;}

private:
    ButtonState _state;
    MyButtonContent _content;
    DataTimeRange _timeRange{OtherTime};
    QMargins _margin{0,0,0,0};
    QRect _paintRect{rect()};
    PaintMarginMode _marginMode{Manual};
    QSize _paintSize{size()};
    int _shadowRadius{0};
public:
    qreal fontSize{20};
    qreal fontWeight{10};
private:
    void setContentsRect();
};


#endif //CLIONWIDGET_MYBUTTON_H
