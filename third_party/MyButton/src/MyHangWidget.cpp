//
// Created by 常笑男 on 2023/10/1.
//

#include "MyHangWidget.h"
#include <QPainter>
#include <QDebug>
#include <QBitmap>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QTimer>
#include <QHostAddress>
#include <QProcess>
#include <windows.h>

MyHangWidget::MyHangWidget(QWidget *_p) : QWidget(_p){
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground); //不加这个会导致图片边缘有白边
    //强制初始化qrc资源，原因：本代码用于编译静态库，qt中资源文件若要编译就要生成一个cpp文件，需要这个宏
    Q_INIT_RESOURCE(resource);
    pixmap = new QPixmap(":/hang/Resources/hang/lighting.png");
    Q_CLEANUP_RESOURCE(resource);

    QScreen *screen = QGuiApplication::primaryScreen();
    move(screen->availableGeometry().width()-pixmap->size().width()-100,100);
    resize(pixmap->size());
//    setMask(pixmap->mask());

    table = new MyTableWidget(5,7);
    table->resize(600,500);
    table->hide();
    table->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

    pos = QPoint();

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MyHangWidget::timeOut);
    timer->start(1000);

//    //socket
//    tcpSocket = new QTcpSocket(this);
//    tcpSocket->connectToHost("www.baidu.com",8888);
//    connect(tcpSocket,&QTcpSocket::connected,this,&MyHangWidget::tcpConnected);
//    connect(tcpSocket,&QTcpSocket::readyRead,this,&MyHangWidget::tcpReadyRead);
}

void MyHangWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.save();

    //主背景
    painter.drawPixmap(0,0,*pixmap);

    painter.restore();
}

MyHangWidget::~MyHangWidget() {
    delete pixmap;
    delete table;
    delete tcpSocket;
}

void MyHangWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    pos = event->globalPos()-geometry().topLeft();
}

void MyHangWidget::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    if(pos == QPoint())
        return;
    move(event->globalPos()-pos);
}

void MyHangWidget::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    pos = QPoint();
}

bool MyHangWidget::event(QEvent *event) {
    QMouseEvent *mouseEvent = (QMouseEvent*)event;
    switch (event->type()) {
        case QEvent::Enter:{
            state = event->type();
            qDebug()<<window()->pos();
            table->move(window()->pos().x()+20,window()->pos().y()+10);
            table->show();
            return true;
        }
        case QEvent::Leave:{
            state = event->type();
            table->hide();
            return true;
        }
        default:
            break;
    }
    return QWidget::event(event);
}

void MyHangWidget::tcpConnected() {
    qDebug()<<"baidu connected";

    const char* str="GET / HTTP/1.1\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\nAccept-Encoding: gzip, deflate, br\nAccept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6,es;q=0.5\nCache-Control: max-age=0\nConnection: keep-alive\nSec-Fetch-Dest: document\nSec-Fetch-Mode: navigate\nSec-Fetch-Site: none\nSec-Fetch-User: ?1\nUpgrade-Insecure-Requests: 1\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.47\nsec-ch-ua: \"Microsoft Edge\";v=\"117\", \"Not;A=Brand\";v=\"8\", \"Chromium\";v=\"117\"\nsec-ch-ua-mobile: ?0\nsec-ch-ua-platform: Windows";
    QByteArray arry(str);
    arry.replace("\n","\r\n");
    arry.append("\r\n");
    tcpSocket->write(arry, arry.length());
}

void MyHangWidget::tcpReadyRead() {
    QByteArray array = tcpSocket->readAll();
//    QString str=QString::fromLocal8Bit(array);
    qDebug()<<"array:"<<array;
    tcpSocket->disconnect();
}

void MyHangWidget::timeOut() {
    MEMORYSTATUSEX memorystatus;
    memorystatus.dwLength = sizeof(memorystatus);
    if(GlobalMemoryStatusEx(&memorystatus)){
        qDebug()<<memorystatus.dwMemoryLoad<<"%";
    }
    else{
        qDebug()<<"通过windows获取信息失败";
    }

    QProcess cpuProcess;
    cpuProcess.start("wmic cpu get Name");
    cpuProcess.waitForFinished();
    qDebug()<<cpuProcess.readAllStandardOutput().replace("\r","").replace("\n","");

    QProcess gpuProcess;
    cpuProcess.start("wmic path win32_VideoController get Name");
    cpuProcess.waitForFinished();
    qDebug()<<cpuProcess.readAllStandardOutput().replace("\r","").replace("\n","");
}
