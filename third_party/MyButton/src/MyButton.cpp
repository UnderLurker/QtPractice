//
// Created by 常笑男 on 2023/9/23.
//

#include "MyButton.h"
#include "ButtonUtility.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QString MyButtonContent::toString() const {
    return day;
}

MyButton::MyButton(QWidget *_p)
        : QPushButton(_p) {
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(70);
    effect->setColor(Qt::gray);
//    this->setGraphicsEffect(effect);
}

MyButton::~MyButton() = default;

void MyButton::paintEvent(QPaintEvent *event) {
    setContentsRect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//反锯齿
    painter.save();

    QLinearGradient otherBgLinear(0,0,0,QWidget::height());
    QLinearGradient otherFontLiner(0,0,0,QWidget::height());
    QLinearGradient rangeBgLinear(0,0,0,QWidget::height());
    QLinearGradient timeLinear(0,0,0,QWidget::height());
    otherBgLinear.setColorAt(0.25,QColor("#90CBFB"));
    otherBgLinear.setColorAt(0.9,QColor(Qt::white));
    otherFontLiner.setColorAt(0.25,QColor(Qt::white));
    otherFontLiner.setColorAt(0.9,QColor(Qt::black));
    rangeBgLinear.setColorAt(0.25,QColor("#A5AAA3"));
    rangeBgLinear.setColorAt(0.9,QColor(Qt::white));
    timeLinear.setColorAt(0.25,QColor("#3E4E69"));
    timeLinear.setColorAt(0.9,QColor(Qt::white));
    if (state() == QEvent::MouseButtonPress) {
        otherBgLinear.setColorAt(0.25,QColor("#FEA443"));
        otherFontLiner.setColorAt(0.9,QColor("#FEA443"));
    }
    QPen fontPen(otherFontLiner,fontWeight);
    QPen radiusRectPen(Qt::NoBrush,0);
    QFont textFont(tr("Consolas"),fontSize,QFont::Bold);

    switch (_timeRange) {
        case OtherTime:{
            painter.setBrush(otherBgLinear);
            painter.setPen(radiusRectPen);
            break;
        }
        case RangeTime:{
            painter.setBrush(rangeBgLinear);
            painter.setPen(radiusRectPen);
            break;
        }
        case StartTime:
        case EndTime:{
            painter.setBrush(timeLinear);
            painter.setPen(radiusRectPen);
            break;
        }
        default:
            break;
    }


    //画背景
    painter.drawPath(ButtonUtility::getRadiusRectPath(_paintRect,10,All));
    //画阴影
    RectUtility::paintShadow(&painter,_paintRect,4);

    //画字体
    painter.setPen(fontPen);
    painter.setFont(textFont);
    painter.drawText(_paintRect,Qt::AlignCenter,_content.day);

    painter.restore();
}

bool MyButton::event(QEvent *e) {
    bool res=false;
    switch (e->type()) {
        case QEvent::MouseButtonPress:{
            auto *mouseEvent=(QMouseEvent*)e;
            if(!_paintRect.contains(mouseEvent->pos()) &&
               e->type() == QEvent::MouseButtonPress){
                setState(QEvent::None);
            }
            else{
                setState(e->type());
                emit mouseClick(mouseEvent->globalPos());
            }
            res=true;
            break;
        }
        case QEvent::MouseButtonRelease:{
            setState(e->type());
            res=true;
            break;
        }
        default:
            res = QPushButton::event(e);
            break;
    }
    return res;
}

void MyButton::setPaintMargin(const QMargins& margin){
    Q_ASSERT(_margin.top()+_margin.bottom()<rect().height()&&
             _margin.left()+_margin.right()<rect().width());
    _margin=margin;
}

void MyButton::setPaintSize(QSize size){
    Q_ASSERT(size.width()<=QWidget::size().width()&&
            size.height()<=QWidget::size().height());
    _paintSize=size;
}

void MyButton::setShadowRadius(int shadowRadius) {
    Q_ASSERT(shadowRadius>=0);
    _shadowRadius = shadowRadius;
}

void MyButton::setContentsRect() {
    switch (_marginMode) {
        case Manual:{
            _paintRect.setLeft(_margin.left());
            _paintRect.setTop(_margin.top());
            _paintRect.setWidth(QWidget::width()-_margin.left()-_margin.right());
            _paintRect.setHeight(QWidget::height()-_margin.top()-_margin.bottom());
            break;
        }
        case TopLeft:{
            _paintRect.setLeft(0);
            _paintRect.setTop(0);
            _paintRect.setSize(_paintSize);
            break;
        }
        case TopRight:{
            _paintRect.setLeft(QWidget::width()-_paintSize.width());
            _paintRect.setTop(0);
            _paintRect.setSize(_paintSize);
            break;
        }
        case BottomLeft:{
            _paintRect.setLeft(0);
            _paintRect.setTop(QWidget::height()-_paintSize.height());
            _paintRect.setSize(_paintSize);
            break;
        }
        case BottomRight:{
            _paintRect.setLeft(QWidget::width()-_paintSize.width());
            _paintRect.setTop(QWidget::height()-_paintSize.height());
            _paintRect.setSize(_paintSize);
            break;
        }
        case HCenter:{
            _paintRect.setLeft((QWidget::width()-_paintSize.width())/2);
            _paintRect.setTop(0);
            _paintRect.setSize(_paintSize);
            break;
        }
        case VCenter:{
            _paintRect.setLeft(0);
            _paintRect.setTop((QWidget::height()-_paintSize.height())/2);
            _paintRect.setSize(_paintSize);
            break;
        }
        case Center:{
            _paintRect.setLeft((QWidget::width()-_paintSize.width())/2);
            _paintRect.setTop((QWidget::height()-_paintSize.height())/2);
            _paintRect.setSize(_paintSize);
            break;
        }
    }
//    qDebug()<<"_paintRect:"<<_paintRect;
}
